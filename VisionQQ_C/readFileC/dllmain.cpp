// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule,
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


extern "C" __declspec(dllexport)
char* getSystemC() {
    system("chcp 65001>nul");
    size_t currentSize = 10;
    char* content = (char*)malloc(sizeof(char) * currentSize);
    if (content == NULL) {
        perror("malloc failed");
        return (char*)"";
    }

    FILE* fp = fopen("config.ini", "r");
    if (fp == NULL) {
        perror("Failed to open config.ini");
        free(content);
        return (char*)"";
    }

    size_t position = 0;
    int ch;

    while ((ch = fgetc(fp)) != EOF) {
        if (position >= currentSize - 1) {  // 留一个位置给 '\0'
            currentSize *= 2;
            char* new_content = (char*)realloc(content, currentSize);
            if (new_content == 0) {
                perror("realloc failed");
                free(content);
                fclose(fp);
                return (char*)"";
            }
            content = new_content;
        }
        content[position++] = (char)ch;
    }

    content[position] = '\0';  // 空终止字符串
    int i;
    int pos = 0;
    for (i = 0; i < position; ++i)
    {
        if (content[i] == '=')
        {
            pos = i;
        }
        // puts(content[i]);
    }

    char* lastValue = content + pos + 1;

    //有内存泄露，但是这个函数只会使用一次，

    // 可选：打印内容c
    //printf("%s\n", lastValue);

    fclose(fp);
    return lastValue;

    //free(content);
    //return 0;
}

extern "C" __declspec(dllexport)
char* getFile() {
    size_t currentSize = 10;
    char* content = (char*)malloc(sizeof(char) * currentSize);
    if (content == NULL) {
        perror("malloc failed");
        return (char*)"";
    }

    FILE* fp = fopen("config.ini", "r");
    if (fp == NULL) {
        perror("Failed to open config.ini");
        free(content);
        return (char*)"";
    }

    size_t position = 0;
    int ch;

    while ((ch = fgetc(fp)) != EOF) {
        if (position >= currentSize - 1) {  // 留一个位置给 '\0'
            currentSize *= 2;
            char* new_content = (char*)realloc(content, currentSize);
            if (new_content == 0) {
                perror("realloc failed");
                free(content);
                fclose(fp);
                return (char*)"";
            }
            content = new_content;
        }
        content[position++] = (char)ch;
    }

    content[position] = '\0';  // 空终止字符串
    return content;
}