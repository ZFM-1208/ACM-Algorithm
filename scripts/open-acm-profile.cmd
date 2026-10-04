@echo off
for %%i in ("%~dp0..") do set "ROOT=%%~fi\"
powershell -NoProfile -ExecutionPolicy Bypass -File "%ROOT%tools\setup_acm_profile.ps1" -SkipInstall
code --new-window --user-data-dir "%ROOT%.acm-vscode\user-data" --extensions-dir "%ROOT%.acm-vscode\extensions" "%ROOT%"
