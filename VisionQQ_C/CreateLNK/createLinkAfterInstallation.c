#include <direct.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int main(int argc,char** argv)
{
    int i;
    char oldPath[260];
    getcwd(oldPath, 260);
    _chdir("..\\");
    char newPath[260];
    char tmp[260];
    char tmp2[260];
    getcwd(newPath, 260);
    printf("%s\n",oldPath);
    printf("%s\n",newPath);
    char cmd[1024] = {0};
    for(i=1;i<argc;++i)
    {

        strcpy(tmp,oldPath);
        strcpy(tmp2,newPath);
        strcat(tmp,"\\");
        strcat(tmp2,"\\");
        strcat(tmp,argv[i]);
        strcat(tmp2,argv[i]);
        snprintf(cmd, sizeof(cmd), "mklink \"%s.lnk\" \"%s\"", tmp2, tmp);
        printf("Executing: %s\n", cmd);
        system(cmd);
    }
}