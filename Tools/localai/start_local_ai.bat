@echo off
rem Starts the local model, queues pre-reading of the next targets, and runs the reader, in one go (Tools\localai\watch_ai.py). Double-click it, or run it
rem from any folder. Leave both windows open during a decompilation session; close them when done.
rem The model is only reachable from this PC (127.0.0.1). The first start downloads the model once.

rem --- change these two lines if your setup differs -------------------------------------------------
set LLAMA=llama-server.exe
set MODEL=mradermacher/Qwen3.5-9B-heretic-GGUF:Q4_K_M
rem ---------------------------------------------------------------------------------------------------

cd /d "%~dp0..\.."
where %LLAMA% >nul 2>nul || if not exist "%LLAMA%" (
    echo Cannot find %LLAMA%. Edit the LLAMA= line in Tools\localai\start_local_ai.bat to its full path.
    pause & exit /b 1
)
start "local model (llama-server)" "%LLAMA%" -hf %MODEL% -ngl 99 -c 32768 --jinja --host 127.0.0.1 --port 8080
rem pre-read the next targets (Tools\next.py) so the next session starts from short digests
py Tools\localai\preread.py
py Tools\localai\watch_ai.py --url http://127.0.0.1:8080
pause
