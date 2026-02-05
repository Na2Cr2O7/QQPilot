#include <windows.h>
#include <iostream>
#include <string>
#define BUFFERSIZE 1024
DWORD g_BytesTransferred = 0;

int main() {
    HANDLE fileHandle = CreateFileW(
        L"example.txt", // 文件名
        GENERIC_READ, // 访问模式：只读
        FILE_SHARE_READ, // 共享模式：允许其他进程读取
        NULL, // 安全属性
        OPEN_EXISTING, // 打开模式：仅打开已存在的文件
        FILE_ATTRIBUTE_NORMAL, // 文件属性
        NULL // 模板文件句柄
    );

    if (fileHandle == INVALID_HANDLE_VALUE) {
        std::cout << "无法打开文件，错误代码：" << GetLastError() << std::endl;
        return -1;
    } else {
        std::cout << "文件成功打开！" << std::endl;
        
        // 读取文件内容并保存到std::string中
        std::string fileContent;
        DWORD dwBytesRead = 0;
        char ReadBuffer[BUFFERSIZE] = {0};
        
        BOOL bResult = FALSE;
        while ((bResult = ReadFile(fileHandle, ReadBuffer, BUFFERSIZE-1, &dwBytesRead, NULL)) && (dwBytesRead != 0)) {
            fileContent.append(ReadBuffer, dwBytesRead);
        }
        
        std::cout << "文件内容：" << std::endl << fileContent << std::endl;
        
        // 关闭文件
        CloseHandle(fileHandle);
    }

    return 0;
}