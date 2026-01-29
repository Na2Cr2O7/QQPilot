#pragma once
#include "pch.h"
//#include "findTencentFiles.cpp"
std::optional<std::wstring> findTencentFiles();
void findEveryFiles2(const std::filesystem::path& dir, std::vector<std::filesystem::path>& files);
void listFolders(const std::filesystem::path& path, std::vector<std::filesystem::path>& files);
bool folderValid(const std::filesystem::path& path);