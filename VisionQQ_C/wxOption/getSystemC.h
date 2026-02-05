#pragma once

#pragma comment(lib, "readFileC.lib")
extern "C" __declspec(dllexport)
char* getSystemC();
extern "C" __declspec(dllexport)
char* getFile();