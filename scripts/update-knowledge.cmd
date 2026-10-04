@echo off
for %%i in ("%~dp0..") do set "ROOT=%%~fi\"
powershell -NoProfile -ExecutionPolicy Bypass -File "%ROOT%tools\update_acm_index.ps1"
