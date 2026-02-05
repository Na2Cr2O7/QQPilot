   taskkill /F /IM ollama.exe
   taskkill /F /IM "ollama app.exe"
   set OLLAMA_HOST=0.0.0.0
   set OLLAMA_ORIGINS=*
   ollama serve