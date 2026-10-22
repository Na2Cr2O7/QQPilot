#define _CRT_SECURE_NO_WARNINGS
// windows.h 的 min/max 宏会跟 std::min/std::max 打架
#define NOMINMAX

// QQPilot 运行状态浮窗：
//   * 无边框、置顶、不进任务栏、不抢焦点、鼠标可穿透；
//   * 贴在主屏工作区右下角，随 DPI 缩放，屏幕分辨率/工作区变化时自动归位；
//   * GDI+ 画一张带圆角、渐变和阴影的卡片，用 UpdateLayeredWindow 做逐像素透明；
//   * 被 qqpilot5 用 Job 拉起，QQPilot 退出时一起结束（另外还盯着父进程做兜底）。

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

#include <algorithm>
#include <memory>
#include <string>
#include <thread>
#include <vector>

//#include "localization.h"
#include <ShellScalingApi.h>

#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "shell32.lib")

using namespace Gdiplus;

namespace
{
	constexpr wchar_t kWindowClass[] = L"QQPilotRunningOverlay";
	constexpr wchar_t kWindowTitle[] = L"QQPilot";
	constexpr wchar_t kMutexName[] = L"Local\\QQPilotRunningOverlay";

	constexpr UINT_PTR kFadeTimer = 1;
	constexpr UINT kFadeIntervalMs = 15;
	constexpr int kFadeStep = 40;

	// 96 DPI 下的设计尺寸，实际渲染时按当前 DPI 等比放大。
	constexpr float kCardWidth = 65.0f;
	constexpr float kCardHeight = 66.0f;
	constexpr float kCardRadius = 0.0f;
	constexpr float kMargin = 22.0f;
	constexpr float kShadowPadding = 0.0f;

	HWND g_window = nullptr;
	HDC g_cache_dc = nullptr;
	HBITMAP g_cache_bitmap = nullptr;
	HGDIOBJ g_cache_previous = nullptr;
	SIZE g_cache_size{};
	POINT g_window_position{};
	int g_dpi = 96;
	int g_alpha = 0;

	int Scale(int value)
	{
		return MulDiv(value, g_dpi, 96);
	}

	float Scaled(float value)
	{
		return value * g_dpi / 96.0f;
	}



	void AddRoundRect(GraphicsPath& path, const RectF& rect, float radius)
	{
		const float diameter = radius * 2.0f;
		path.AddArc(rect.X, rect.Y, diameter, diameter, 180.0f, 90.0f);
		path.AddArc(rect.GetRight() - diameter, rect.Y, diameter, diameter, 270.0f, 90.0f);
		path.AddArc(rect.GetRight() - diameter, rect.GetBottom() - diameter,
			diameter, diameter, 0.0f, 90.0f);
		path.AddArc(rect.X, rect.GetBottom() - diameter, diameter, diameter, 90.0f, 90.0f);
		path.CloseFigure();
	}

	void ReleaseCache()
	{
		if (g_cache_dc != nullptr)
		{
			if (g_cache_previous != nullptr)
			{
				SelectObject(g_cache_dc, g_cache_previous);
				g_cache_previous = nullptr;
			}
			DeleteDC(g_cache_dc);
			g_cache_dc = nullptr;
		}
		if (g_cache_bitmap != nullptr)
		{
			DeleteObject(g_cache_bitmap);
			g_cache_bitmap = nullptr;
		}
		g_cache_size = {};
	}

	/// 算出浮窗应该待的位置：主屏工作区右下角（自动避开任务栏）。
	void UpdatePosition()
	{
		RECT work_area{};
		if (!SystemParametersInfoW(SPI_GETWORKAREA, 0, &work_area, 0))
		{
			work_area = RECT{ 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
		}

		const int padding = Scale(static_cast<int>(kShadowPadding));
		const int card_width = Scale(static_cast<int>(kCardWidth));
		const int card_height = Scale(static_cast<int>(kCardHeight));
		const int margin = Scale(static_cast<int>(kMargin));

		g_window_position.x = work_area.right - margin - card_width + padding-40;
		g_window_position.y = work_area.bottom - margin - card_height + padding;
	}

	/// 把卡片画到一张预乘 ARGB 位图上，再拷进 UpdateLayeredWindow 用的 DIB。
	void RenderCard()
	{
		ReleaseCache();

		const int padding = Scale(static_cast<int>(kShadowPadding));
		const int card_width = Scale(static_cast<int>(kCardWidth));
		const int card_height = Scale(static_cast<int>(kCardHeight));
		const int width = card_width + padding * 2;
		const int height = card_height + padding * 2;

		Bitmap bitmap(width, height, PixelFormat32bppPARGB);
		if (bitmap.GetLastStatus() != Ok)
		{
			return;
		}

		Graphics graphics(&bitmap);
		graphics.SetSmoothingMode(SmoothingModeAntiAlias);
		graphics.SetTextRenderingHint(TextRenderingHintAntiAliasGridFit);
		graphics.SetPixelOffsetMode(PixelOffsetModeHalf);
		graphics.Clear(Color(0, 0, 0, 0));

		const RectF card(static_cast<REAL>(padding), static_cast<REAL>(padding),
			static_cast<REAL>(card_width), static_cast<REAL>(card_height));
		// ============================================
		// 
		// 
		//			  deepseek你的审美好抽象啊
		// 
		// 
		// ============================================
		// 阴影：几层逐渐变淡、逐渐外扩的圆角矩形，近似高斯模糊。
		//for (int layer = 7; layer >= 1; --layer)
		//{
		//	const float spread = Scaled(1.1f * layer);
		//	const BYTE alpha = static_cast<BYTE>(std::max(4, 18 - layer * 2));
		//	GraphicsPath shadow;
		//	AddRoundRect(shadow,
		//		RectF(card.X - spread, card.Y + Scaled(2.0f + layer * 0.7f),
		//			card.Width + spread * 2.0f, card.Height + spread * 2.0f),										C
		//		Scaled(kCardRadius) + spread);
		//	SolidBrush brush(Color(alpha, 0, 0, 0));
		//	graphics.FillPath(&brush, &shadow);
		//}

		// 卡片本体：深色竖向渐变 + 一圈很淡的高光边框。
		GraphicsPath body;
		AddRoundRect(body, card, Scaled(0.01f));

		SolidBrush background(Color(30,30,30));
		graphics.FillPath(&background, &body);

		SolidBrush border_brush(Color(16,16,16));
		Pen border(&border_brush, 5.0f);
		graphics.DrawPath(&border, &body);



		//// 左侧图标：蓝色渐变圆角方块 + 白色鼠标。
		const float tile_size = Scaled(40.0f);
		const RectF tile(card.X + Scaled(13.0f), card.Y + (card.Height - tile_size) / 2.0f,
			tile_size, tile_size);
		GraphicsPath tile_path;
		AddRoundRect(tile_path, tile, Scaled(0.01f));


		LinearGradientBrush tile_brush(
			PointF(tile.X, tile.Y), PointF(tile.GetRight(), tile.GetBottom()),
			Color(255, 210, 83), Color(253,197,46));
		graphics.FillPath(&tile_brush, &tile_path);

		SolidBrush tile_highlight(Color(160,130,51));
		Pen highlight_pen(&tile_highlight, 3.0f);
		graphics.DrawPath(&highlight_pen, &tile_path);

		const float center_x = tile.X + tile.Width / 2.0f;
		const float center_y = tile.Y + tile.Height / 2.0f;
		const float mouse_width = Scaled(15.0f);
		const float mouse_height = Scaled(21.0f);
		const float mouse_radius = mouse_width / 2.0f;

		GraphicsPath mouse;
		AddRoundRect(mouse,
			RectF(center_x - mouse_width / 2.0f, center_y - mouse_height / 2.0f,
				mouse_width, mouse_height),
			mouse_radius);
		SolidBrush mouse_brush(Color(240, 255, 255, 255));
		graphics.FillPath(&mouse_brush, &mouse);

		Pen wheel(Color(210, 76, 111, 233), Scaled(1.8f));
		wheel.SetStartCap(LineCapRound);
		wheel.SetEndCap(LineCapRound);
		graphics.DrawLine(&wheel, center_x, center_y - mouse_height / 2.0f + Scaled(3.0f),
			center_x, center_y - mouse_height / 2.0f + Scaled(7.0f));

		// 文字：上面一行产品名，下面一行运行状态。
		//const std::wstring title_text = UiText("program.name", L"QQPilot", L"QQPilot");
		//const std::wstring status_text = UiText("info.running", L"正在运行", L"Running");
		//const float text_x = tile.GetRight() + Scaled(13.0f);

		////const bool status_chinese = HasNonAscii(status_text);
		////const bool title_chinese = HasNonAscii(title_text);

		//auto title_family = UiFamily(title_chinese);
		//Font title_font(title_family.get(), Scaled(11.5f), FontStyleBold, UnitPixel);
		//SolidBrush title_brush(Color(255, 143, 163, 191));
		//graphics.DrawString(title_text.c_str(), -1, &title_font,
		//	PointF(text_x, card.Y + Scaled(12.0f)), &title_brush);

		//auto status_family = UiFamily(status_chinese);
		//Font status_font(status_family.get(), Scaled(15.0f), FontStyleRegular, UnitPixel);
		//SolidBrush status_brush(Color(255, 245, 248, 253));
		//graphics.DrawString(status_text.c_str(), -1, &status_font,
		//	PointF(text_x, card.Y + Scaled(29.0f)), &status_brush);

		//// 右侧呼吸点：外面一圈淡淡的绿光，里面是实心圆点。
		//const float dot_x = card.GetRight() - Scaled(23.0f);
		//const float dot_y = card.Y + Scaled(41.0f);
		//const float glow_radius = Scaled(9.0f);
		//const float dot_radius = Scaled(4.0f);

		//SolidBrush glow_brush(Color(46, 61, 220, 132));
		//graphics.FillEllipse(&glow_brush,
		//	dot_x - glow_radius, dot_y - glow_radius, glow_radius * 2.0f, glow_radius * 2.0f);
		//SolidBrush dot_brush(Color(255, 61, 220, 132));
		//graphics.FillEllipse(&dot_brush,
		//	dot_x - dot_radius, dot_y - dot_radius, dot_radius * 2.0f, dot_radius * 2.0f);

		// 拷进 DIB。GDI+ 的 PARGB 像素本身是预乘的，正好符合 UpdateLayeredWindow 的要求。
		BitmapData locked{};
		const Rect lock_rect(0, 0, width, height);
		if (bitmap.LockBits(&lock_rect, ImageLockModeRead, PixelFormat32bppPARGB, &locked) != Ok)
		{
			return;
		}

		BITMAPINFO info{};
		info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		info.bmiHeader.biWidth = width;
		info.bmiHeader.biHeight = -height;
		info.bmiHeader.biPlanes = 1;
		info.bmiHeader.biBitCount = 32;
		info.bmiHeader.biCompression = BI_RGB;

		void* pixels = nullptr;
		HDC screen = GetDC(nullptr);
		g_cache_bitmap = CreateDIBSection(screen, &info, DIB_RGB_COLORS, &pixels, nullptr, 0);
		if (g_cache_bitmap != nullptr && pixels != nullptr)
		{
			for (int y = 0; y < height; ++y)
			{
				const auto* source = static_cast<const BYTE*>(locked.Scan0) + y * locked.Stride;
				auto* target = static_cast<BYTE*>(pixels) + static_cast<size_t>(y) * width * 4;
				memcpy(target, source, static_cast<size_t>(width) * 4);
			}
			g_cache_dc = CreateCompatibleDC(screen);
			if (g_cache_dc != nullptr)
			{
				g_cache_previous = SelectObject(g_cache_dc, g_cache_bitmap);
				g_cache_size = { width, height };
			}
		}
		ReleaseDC(nullptr, screen);
		bitmap.UnlockBits(&locked);
	}

	void PushLayer()
	{
		if (g_cache_dc == nullptr || g_cache_size.cx <= 0 || g_cache_size.cy <= 0)
		{
			return;
		}

		HDC screen = GetDC(nullptr);
		BLENDFUNCTION blend{ AC_SRC_OVER, 0, static_cast<BYTE>(g_alpha), AC_SRC_ALPHA };
		POINT source{ 0, 0 };
		UpdateLayeredWindow(g_window, screen, &g_window_position, &g_cache_size,
			g_cache_dc, &source, 0, &blend, ULW_ALPHA);
		ReleaseDC(nullptr, screen);
	}

	int DpiOfWindow(HWND window)
	{
		using GetDpiForWindowFn = UINT(WINAPI*)(HWND);
		static const auto get_dpi_for_window = reinterpret_cast<GetDpiForWindowFn>(
			GetProcAddress(GetModuleHandleW(L"user32.dll"), "GetDpiForWindow"));
		if (get_dpi_for_window != nullptr)
		{
			return static_cast<int>(get_dpi_for_window(window));
		}

		HDC screen = GetDC(nullptr);
		const int dpi = GetDeviceCaps(screen, LOGPIXELSX);
		ReleaseDC(nullptr, screen);
		return dpi > 0 ? dpi : 96;
	}
	bool DPIAwarenessPrologue()
	{
		// 尝试 Windows 8.1+ 方法
		HMODULE shcore = LoadLibraryW(L"shcore.dll");
		if (shcore) {
			typedef HRESULT(WINAPI* SetProcessDpiAwarenessFunc)(PROCESS_DPI_AWARENESS);
			auto func = (SetProcessDpiAwarenessFunc)GetProcAddress(shcore, "SetProcessDpiAwareness");
			if (func) {
				HRESULT hr = func(PROCESS_SYSTEM_DPI_AWARE);
				FreeLibrary(shcore);
				return SUCCEEDED(hr);
			}
			FreeLibrary(shcore);
		}

		// 回退到 Vista~Win8 方法（仅系统 DPI 感知）
		typedef BOOL(WINAPI* SetProcessDPIAwareFunc)();
		HMODULE user32 = GetModuleHandleW(L"user32.dll");
		if (user32) {
			auto func = (SetProcessDPIAwareFunc)GetProcAddress(user32, "SetProcessDPIAware");
			if (func) {
				return func() != FALSE;
			}
		}

		return false; // 不支持
	}
	void EnableDpiAwareness()
	{
		//选用其他关联C++程序使用的方法
		DPIAwarenessPrologue();
		//return;
		//// 动态取（Win10 1703+ 才有），老系统退回系统级 DPI 感知。
		//using SetProcessDpiAwarenessContextFn = BOOL(WINAPI*)(HANDLE);
		//const auto set_context = reinterpret_cast<SetProcessDpiAwarenessContextFn>(
		//	GetProcAddress(GetModuleHandleW(L"user32.dll"), "SetProcessDpiAwarenessContext"));
		//if (set_context != nullptr && set_context(reinterpret_cast<HANDLE>(-4)))
		//{
		//	// DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2
		//	return;
		//}

		//using SetProcessDpiAwareFn = BOOL(WINAPI*)();
		//const auto set_aware = reinterpret_cast<SetProcessDpiAwareFn>(
		//	GetProcAddress(GetModuleHandleW(L"user32.dll"), "SetProcessDPIAware"));
		//if (set_aware != nullptr)
		//{
		//	set_aware();
		//}
	}

	/// QQPilot 会全屏截图做模板匹配，浮窗不能被拍进去，否则会盖住聊天区域。
	void ExcludeFromCapture(HWND window)
	{
		return;
		using SetWindowDisplayAffinityFn = BOOL(WINAPI*)(HWND, DWORD);
		static const auto set_affinity = reinterpret_cast<SetWindowDisplayAffinityFn>(
			GetProcAddress(GetModuleHandleW(L"user32.dll"), "SetWindowDisplayAffinity"));
		if (set_affinity != nullptr)
		{
			// WDA_EXCLUDEFROMCAPTURE：Win10 2004+；老系统返回失败，忽略即可。
			set_affinity(window, 0x00000011);
		}
	}

	void ShowOverlay()
	{
		g_dpi = DpiOfWindow(g_window);
		if (g_dpi <= 0)
		{
			g_dpi = 96;
		}
		UpdatePosition();
		RenderCard();
		if (GetEnvironmentVariableW(L"QQPILOT_OVERLAY_CAPTURE", nullptr, 0) == 0)
		{
			ExcludeFromCapture(g_window);
		}
		g_alpha = 0;
		PushLayer();
		ShowWindow(g_window, SW_SHOWNOACTIVATE);
		SetTimer(g_window, kFadeTimer, kFadeIntervalMs, nullptr);
	}

	DWORD ParentProcessId()
	{
		int argc = 0;
		LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
		if (argv == nullptr)
		{
			return 0;
		}

		DWORD pid = 0;
		for (int index = 1; index + 1 < argc; ++index)
		{
			if (_wcsicmp(argv[index], L"--parent") == 0)
			{
				pid = static_cast<DWORD>(_wtoi(argv[index + 1]));
				break;
			}
		}
		LocalFree(argv);
		return pid;
	}

	/// Job 对象已经能保证随 QQPilot 退出；这里再盯一眼父进程，方便单独调试时也能自己关掉。
	void WatchParent(HWND window, DWORD parent_pid)
	{
		if (parent_pid == 0)
		{
			return;
		}
		HANDLE parent = OpenProcess(SYNCHRONIZE, FALSE, parent_pid);
		if (parent == nullptr)
		{
			return;
		}
		std::thread([window, parent]()
		{
			WaitForSingleObject(parent, INFINITE);
			CloseHandle(parent);
			PostMessageW(window, WM_CLOSE, 0, 0);
		}).detach();
	}

	LRESULT CALLBACK WndProc(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
	{
		switch (message)
		{
		case WM_TIMER:
			if (w_param == kFadeTimer)
			{
				g_alpha = std::min(255, g_alpha + kFadeStep);
				PushLayer();
				if (g_alpha >= 255)
				{
					KillTimer(window, kFadeTimer);
				}
			}
			return 0;

		case WM_DPICHANGED:
			g_dpi = HIWORD(w_param);
			UpdatePosition();
			RenderCard();
			PushLayer();
			return 0;

		case WM_DISPLAYCHANGE:
		case WM_SETTINGCHANGE:
			UpdatePosition();
			PushLayer();
			return 0;

		case WM_ERASEBKGND:
			return 1;

		case WM_DESTROY:
			KillTimer(window, kFadeTimer);
			PostQuitMessage(0);
			return 0;

		default:
			return DefWindowProcW(window, message, w_param, l_param);
		}
	}
}

INT WINAPI WinMain(HINSTANCE instance, HINSTANCE, PSTR, INT)
{
	// 只允许一个浮窗。第二个实例直接退出，避免叠两张卡片。
	HANDLE mutex = CreateMutexW(nullptr, TRUE, kMutexName);
	if (mutex != nullptr && GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(mutex);
		return 0;
	}

	EnableDpiAwareness();

	GdiplusStartupInput gdiplus_input;
	ULONG_PTR gdiplus_token = 0;
	if (GdiplusStartup(&gdiplus_token, &gdiplus_input, nullptr) != Ok)
	{
		if (mutex != nullptr)
		{
			CloseHandle(mutex);
		}
		return 1;
	}

	//localization::load();

	WNDCLASSEXW window_class{};
	window_class.cbSize = sizeof(WNDCLASSEXW);
	window_class.style = 0;
	window_class.lpfnWndProc = WndProc;
	window_class.hInstance = instance;
	window_class.hCursor = LoadCursorW(nullptr, IDC_ARROW);
	window_class.hbrBackground = nullptr;
	window_class.lpszClassName = kWindowClass;
	if (RegisterClassExW(&window_class) == 0)
	{
		GdiplusShutdown(gdiplus_token);
		if (mutex != nullptr)
		{
			CloseHandle(mutex);
		}
		return 1;
	}

	const DWORD extended_style = WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW |
		WS_EX_TRANSPARENT | WS_EX_NOACTIVATE;

	g_window = CreateWindowExW(extended_style, kWindowClass, kWindowTitle, WS_POPUP,
		0, 0, 0, 0, nullptr, nullptr, instance, nullptr);
	if (g_window == nullptr)
	{
		GdiplusShutdown(gdiplus_token);
		if (mutex != nullptr)
		{
			CloseHandle(mutex);
		}
		return 1;
	}

	WatchParent(g_window, ParentProcessId());
	ShowOverlay();

	MSG message{};
	while (GetMessageW(&message, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&message);
		DispatchMessageW(&message);
	}

	ReleaseCache();
	GdiplusShutdown(gdiplus_token);
	if (mutex != nullptr)
	{
		CloseHandle(mutex);
	}
	return 0;
}
