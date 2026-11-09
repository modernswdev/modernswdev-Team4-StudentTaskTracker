@echo off

echo Starting Student Task Tracker...

cd /d "%~dp0StudentTaskTracker"

start "Student Task Tracker Backend" cmd /k "x64\Debug\StudentTaskTracker.exe"

timeout /t 3 >nul

start "" "http://127.0.0.1:8080/"

exit