#define _CRT_SECURE_NO_WARNINGS
#include "inicpp.hpp"
#include <windows.h>
using namespace inicpp;
//IniManager ini("config.ini");

bool fileExists(const wchar_t* fileName)
{
    wchar_t workingDirectory[MAX_PATH]{};
    GetCurrentDirectory(MAX_PATH, workingDirectory);
    //std::wcout << workingDirectory;
    if (std::wcslen(workingDirectory) > MAX_PATH - 1)
    {
        return false;
    }
    std::wcscat(workingDirectory, L"\\");
    std::wcscat(workingDirectory, fileName);
    DWORD attributes = GetFileAttributes(workingDirectory);
    if (attributes != INVALID_FILE_ATTRIBUTES)
    {
        return !(attributes & FILE_ATTRIBUTE_DIRECTORY);
    }
    return false;
}

