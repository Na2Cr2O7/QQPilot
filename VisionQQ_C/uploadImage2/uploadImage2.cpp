#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <GdiPlus.h>
#include <iostream>
#include <strsafe.h>
#include<cstdlib>
#include <memory>
#include<algorithm>
#include<vector>
#include<ctime>
#include<chrono>
#include<random>
//#include<pathcch.h>
#pragma comment(lib, "GdiPlus")

bool copyimage(const wchar_t* filename);
std::wstring selectedImage;
static int select()
{


	const wchar_t* imageExts[] = { L".gif",L".png",L".jpg",L".jpeg",L".webp",L".avif",L".bmp" };
	//列出所有文件
	WIN32_FIND_DATA findFileData;

	HANDLE hFind = INVALID_HANDLE_VALUE;
	WCHAR pathwithastar[MAX_PATH];
	WCHAR path[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, pathwithastar);
	std::wcscat(pathwithastar, L"\\Images\\*");
	//std::wcscat(pathwithastar, L"\\Images\\");
	std::wcsncpy(path, pathwithastar, std::wcslen(pathwithastar) - 1);

	std::wcout << pathwithastar << std::endl;
	std::wcout << path << std::endl;
	;
	std::vector<std::wstring> images;

	hFind = FindFirstFile(pathwithastar, &findFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		std::wcerr << "错误:" << GetLastError() << std::endl;
		return -2;

	}
	do {
		if (std::wcscmp(findFileData.cFileName, L"..") == 0)
		{
			continue;
		}
		if (std::wcscmp(findFileData.cFileName, L".") == 0)
		{
			continue;
		}
		//图片文件
		for (int i = 0; i < 6; ++i)
		{
			const wchar_t* ext = imageExts[i];
			size_t length = std::wcslen(ext);
			//std::wcout << ext << length;
			//std::cout << std::endl;
			size_t fileNameLength = std::wcslen(findFileData.cFileName);
			if (std::wcscmp(findFileData.cFileName + fileNameLength + 1 - length, ext) == 0)
			{


				goto Picture;
			}

		}
	Picture:
		//std::wcout << findFileData.cFileName << std::endl;
		images.emplace_back(std::wstring(findFileData.cFileName));
	} while (FindNextFile(hFind, &findFileData));


	for (auto& image : images)
	{
		std::wcout << image << std::endl;
	}
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(images.begin(), images.end(), std::default_random_engine(seed));
	if (images.size() == 0)
	{
		std::wcerr << TEXT("没有找到图片") << std::endl;
		return -1;
	}
	selectedImage = std::wstring(path, std::wcslen(pathwithastar) - 1) + images.at(0);
}
int main()
{

	////HRESULT result0 = PathCchCombine(copyDirectory, MAX_PATH, currentDirectory, argv[1]);
	//std::cout << result0 << "\n";
	//std::wcout << copyDirectory << "\n";

	//initialize Gdiplus once:
	select();

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	std::wcout << selectedImage << std::endl;
	bool result = copyimage(selectedImage.c_str());

	std::cout << result;
	Gdiplus::GdiplusShutdown(gdiplusToken);
}
bool copyimage(const wchar_t* filename)
{
	bool result = false;
	Gdiplus::Bitmap* gdibmp = Gdiplus::Bitmap::FromFile(filename);
	if (gdibmp)
	{
		HBITMAP hbitmap;
		gdibmp->GetHBITMAP(0, &hbitmap);
		if (OpenClipboard(NULL))
		{
			EmptyClipboard();
			DIBSECTION ds;
			if (GetObject(hbitmap, sizeof(DIBSECTION), &ds))
			{
				HDC hdc = GetDC(HWND_DESKTOP);
				//create compatible bitmap (get DDB from DIB)
				HBITMAP hbitmap_ddb = CreateDIBitmap(hdc, &ds.dsBmih, CBM_INIT,
					ds.dsBm.bmBits, (BITMAPINFO*)&ds.dsBmih, DIB_RGB_COLORS);
				ReleaseDC(HWND_DESKTOP, hdc);
				SetClipboardData(CF_BITMAP, hbitmap_ddb);
				DeleteObject(hbitmap_ddb);
				result = true;
			}
			CloseClipboard();
		}

		//cleanup:
		DeleteObject(hbitmap);
		delete gdibmp;
	}
	return result;
}