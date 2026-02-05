#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    system("chcp 65001>nul");
    size_t currentSize = 10;
    char* content = (char*)malloc(sizeof(char) * currentSize);
    if (content == NULL) {
        perror("malloc failed");
        return 1;
    }

    FILE* fp = fopen("config.ini", "r");
    if (fp == NULL) {
        perror("Failed to open config.ini");
        free(content);
        return 1;
    }

    size_t position = 0;
    int ch;

    while ((ch = fgetc(fp)) != EOF) {
        if (position >= currentSize - 1) {  // 留一个位置给 '\0'
            currentSize *= 2;
            char* new_content = (char*)realloc(content, currentSize);
            if (new_content == NULL) {
                perror("realloc failed");
                free(content);
                fclose(fp);
                return 1;
            }
            content = new_content;
        }
        content[position++] = (char)ch;
    }

    content[position] = '\0';  // 空终止字符串
    int i;
    int pos=0;
    for(i=0;i<position;++i)
    {
        if (content[i]=='=')
        {
            pos=i;
        }
        // puts(content[i]);
    }

    char* lastValue=content+pos+1;


    // 可选：打印内容c
    printf("%s\n", lastValue);

    fclose(fp);
    free(content);
    return 0;
}