#include <stdlib.h>

int main()
{
    //由Convert.py自动生成,不要修改
	system("   taskkill /F /IM ollama.exe");
	system("   taskkill /F /IM \"ollama app.exe\"");
	system("   set OLLAMA_HOST=0.0.0.0");
	system("   set OLLAMA_ORIGINS=*");
	system("   ollama serve");

    return 0;
}