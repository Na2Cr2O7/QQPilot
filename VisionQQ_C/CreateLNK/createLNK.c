#include <direct.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        printf("usage: %s <source_file> <target_directory> <link_name>\n", argv[0]);
        return -1;
    }

    const char* src = argv[1];
    const char* dstDir = argv[2];
    const char* linkName = argv[3];

    if (chdir(dstDir) != 0)
    {
        perror("Failed to change directory to target directory");
        return 1;
    }

    // 获取目标目录的绝对路径
    char newDir[260] = {0};
    if (getcwd(newDir, sizeof(newDir)) == NULL)
    {
        perror("getcwd failed");
        return 1;
    }

    // 构建完整的目标链接路径
    char linkPath[520] = {0};
    snprintf(linkPath, sizeof(linkPath), "%s\\%s", newDir, linkName);
    
    char cmd[1024] = {0};
    snprintf(cmd, sizeof(cmd), "mklink \"%s\" \"%s\"", linkPath, src);

    printf("Executing: %s\n", cmd);
    int result = system(cmd);
    if (result != 0)
    {
        fprintf(stderr, "mklink command failed.\n");
        return 1;
    }

    return 0;
}