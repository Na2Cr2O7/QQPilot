// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "dllmain.h"
//#include "screenscale.cpp"
#include "inicpp.hpp"
#include<iostream>
#include <set>

using namespace inicpp;

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

int getScreenW()
{
	int screenW = ::GetSystemMetrics(SM_CXSCREEN);
	return screenW;

}
bool gethdc()
{
	HWND hwd = ::GetDesktopWindow();
	HDC hdc = ::GetDC(hwd);
	if (!hdc) {
		return false;

	}
	::ReleaseDC(hwd, hdc); // 必须释放 DC
	return true;

}
int getWidth()
{
	HWND hwd = GetDesktopWindow();

	HDC hdc = GetDC(hwd);
	int width = ::GetDeviceCaps(hdc, DESKTOPHORZRES);
	return width;

}

static int CaptureAnImage(HWND hWnd, const float& scale, const wchar_t* name = L"")
{
	HDC hdcScreen;
	HDC hdcWindow;
	HDC hdcMemDC = NULL;
	HBITMAP hbmScreen = NULL;
	BITMAP bmpScreen;
	DWORD dwBytesWritten = 0;
	DWORD dwSizeofDIB = 0;
	HANDLE hFile = NULL;
	char* lpbitmap = NULL;
	HANDLE hDIB = NULL;
	DWORD dwBmpSize = 0;

	// Retrieve the handle to a display device context for the client 
	// area of the window. 
	hdcScreen = GetDC(NULL);
	hdcWindow = GetDC(hWnd);

	// Create a compatible DC, which is used in a BitBlt from the window DC.
	hdcMemDC = CreateCompatibleDC(hdcWindow);

	if (!hdcMemDC)
	{
		MessageBox(hWnd, L"CreateCompatibleDC has failed", L"Failed", MB_OK);
		goto done;
	}

	// Get the client area for size calculation.
	RECT rcClient;
	GetClientRect(hWnd, &rcClient);

	// This is the best stretch mode.
	SetStretchBltMode(hdcWindow, HALFTONE);

	// The source DC is the entire screen, and the destination DC is the current window (HWND).
	if (!StretchBlt(hdcWindow,
		0, 0,
		rcClient.right, rcClient.bottom,
		hdcScreen,
		0, 0,
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN),
		SRCCOPY))
	{
		MessageBox(hWnd, L"StretchBlt has failed", L"Failed", MB_OK);
		goto done;
	}
	//Screen Scale


	rcClient.bottom *= scale;
	rcClient.top *= scale;
	rcClient.left *= scale;
	rcClient.right *= scale;

	// Create a compatible bitmap from the Window DC.
	hbmScreen = CreateCompatibleBitmap(hdcWindow, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);

	if (!hbmScreen)
	{
		MessageBox(hWnd, L"CreateCompatibleBitmap Failed", L"Failed", MB_OK);
		goto done;
	}

	// Select the compatible bitmap into the compatible memory DC.
	SelectObject(hdcMemDC, hbmScreen);

	// Bit block transfer into our compatible memory DC.
	if (!BitBlt(hdcMemDC,
		0, 0,
		rcClient.right - rcClient.left, rcClient.bottom - rcClient.top,
		hdcWindow,
		0, 0,
		SRCCOPY))
	{
		MessageBox(hWnd, L"BitBlt has failed", L"Failed", MB_OK);
		goto done;
	}

	// Get the BITMAP from the HBITMAP.
	GetObject(hbmScreen, sizeof(BITMAP), &bmpScreen);

	BITMAPFILEHEADER   bmfHeader;
	BITMAPINFOHEADER   bi;

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bmpScreen.bmWidth;
	bi.biHeight = bmpScreen.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	dwBmpSize = ((bmpScreen.bmWidth * bi.biBitCount + 31) / 32) * 4 * bmpScreen.bmHeight;

	// Starting with 32-bit Windows, GlobalAlloc and LocalAlloc are implemented as wrapper functions that 
	// call HeapAlloc using a handle to the process's default heap. Therefore, GlobalAlloc and LocalAlloc 
	// have greater overhead than HeapAlloc.
	hDIB = GlobalAlloc(GHND, dwBmpSize);
	lpbitmap = (char*)GlobalLock(hDIB);

	// Gets the "bits" from the bitmap, and copies them into a buffer 
	// that's pointed to by lpbitmap.
	GetDIBits(hdcWindow, hbmScreen, 0,
		(UINT)bmpScreen.bmHeight,
		lpbitmap,
		(BITMAPINFO*)&bi, DIB_RGB_COLORS);

	// A file is created, this is where we will save the screen capture.
	hFile = CreateFile(name,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	// Add the size of the headers to the size of the bitmap to get the total file size.
	dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	// Offset to where the actual bitmap bits start.
	bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);

	// Size of the file.
	bmfHeader.bfSize = dwSizeofDIB;

	// bfType must always be BM for Bitmaps.
	bmfHeader.bfType = 0x4D42; // BM.

	WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPSTR)lpbitmap, dwBmpSize, &dwBytesWritten, NULL);

	// Unlock and Free the DIB from the heap.
	GlobalUnlock(hDIB);
	GlobalFree(hDIB);

	// Close the handle for the file that was created.
	CloseHandle(hFile);

	// Clean up.
done:
	DeleteObject(hbmScreen);
	DeleteObject(hdcMemDC);
	ReleaseDC(NULL, hdcScreen);
	ReleaseDC(hWnd, hdcWindow);

	return 0;
}
static bool fileExists(const wchar_t* path)
{
	DWORD attributes = GetFileAttributes(path);
	return (attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY));
}
extern "C" __declspec(dllexport)
int fullScreenshot()
{
	float scale = 1.0f;
	if (gethdc())
	{
		scale = float(getWidth()) / getScreenW();
	}
	CaptureAnImage(GetDesktopWindow(), scale, L"screenshot.bmp");
	if (not fileExists(L"screenshot.bmp"))
	{
		return 1;
	}
	return 0;
}
extern "C" __declspec(dllexport)
int screenshot(int left, int right, int width, int height)
{
	float scale = 1.0f;
	if (gethdc())
	{
		scale = float(getWidth()) / getScreenW();
	}
	CaptureAnImage(GetDesktopWindow(), scale, L"captureqwsx.bmp");
	if (not fileExists(L"captureqwsx.bmp"))
	{
		return 1;
	}
	CImg screenshot("captureqwsx.bmp");
	CImg cropped = screenshot.get_crop(left, right, width + left, right + height);
	cropped.save("screenshot.bmp");
	return 0;
}

extern "C" __declspec(dllexport)
Point containsRedDot(RECT rect)

{
	CImg<unsigned char> screenshot("screenshot.bmp");
	const Color RED_DOT = { 247,76,48 };
	int width = screenshot.width();
	int height = screenshot.height();
	//std::cout<<"(" << rect.right<<"," << rect.top << "),(" << rect.bottom << "," << rect.left << ")\n";
	for (int x = rect.left; x < rect.right; ++x)
	{
		for (int y = rect.top; y < rect.bottom; ++y)
		{
			//if (screenshot(x, y, 0) == RED_DOT.r and screenshot(x, y, 1) == RED_DOT.g and screenshot(x, y, 2) == RED_DOT.b)
			if (std::tie(screenshot(x, y, 0), screenshot(x, y, 1), screenshot(x, y, 2)) == std::tie(RED_DOT.r, RED_DOT.g, RED_DOT.b))
			{
				return { static_cast<unsigned>(x), static_cast<unsigned>(y) };
			}
		}
	}

	return { 0,0 };
}

extern "C" __declspec(dllexport)
Point containsBlue()
{
	CImg<unsigned char> screenshot("screenshot.bmp");
	const Color RED_DOT = { 0,153,255 };
	for (int x = 0; x < screenshot.width(); x += 10)

	{
		for (int y = 0; y < screenshot.height(); y += 10)
		{
			if (std::tie(screenshot(x, y, 0), screenshot(x, y, 1), screenshot(x, y, 2)) == std::tie(RED_DOT.r, RED_DOT.g, RED_DOT.b))
			{
				return { static_cast<unsigned>(x), static_cast<unsigned>(y) };
			}
		}
	}
	return { 0,0 };
}
extern "C" __declspec(dllexport)
Point point(unsigned x, unsigned y)

{
	return { x,y };
}
extern "C" __declspec(dllexport)
RECT rect(unsigned left, unsigned top, unsigned right, unsigned bottom)
{
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;
	return r;
}
template<typename T>
bool inRange(T number,T upper,T lower)
{
	if (upper < lower)
	{
		return false;
	}
	return ((upper - number) > 0) and ((lower - number) < 0);
}

extern "C" __declspec(dllexport)
int matchTemplate(
	const char* image,
	const char* templateImage,
	int threshold,
	int* outX,
	int* outY
) {
	if (!image || !templateImage || !outX || !outY) {
		return 0; // 无效参数
	}

	try {
		CImg<unsigned char> background(image);

		//CImg<unsigned char> background = background.resize(1920,1080);

		CImg<unsigned char> foreground(templateImage);

		const int bg_w = background.width();
		const int bg_h = background.height();
		const int fg_w = foreground.width();
		const int fg_h = foreground.height();

		// 模板不能比背景大
		if (fg_w > bg_w || fg_h > bg_h) {
			return 0;
		}

		const int channels = min(background.spectrum(), foreground.spectrum());

		for (int bx = 0; bx <= bg_w - fg_w; ++bx) {
			for (int by = 0; by <= bg_h - fg_h; ++by) {
				bool match = true;
				for (int fx = 0; fx < fg_w && match; ++fx) {
					for (int fy = 0; fy < fg_h && match; ++fy) {
						for (int c = 0; c < channels; ++c) {
							int diff = background(bx + fx, by + fy, c) -
								foreground(fx, fy, c);
							if (diff < 0) diff = -diff;
							if (diff > threshold) {
								match = false;
								break;
							}
						}
					}
				}
				if (match) {
					*outX = bx;
					*outY = by;
					return 1; // 找到
				}
			}
		}
	}
	catch (...) {
		// CImg 可能抛异常（如文件不存在）
		return 0;
	}

	return 0; // 未找到
}