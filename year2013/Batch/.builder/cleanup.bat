@echo off   

if "%builder_starts%"=="" goto :EOF

if not "%repo_name%"=="" if exist %repo_name% rd /q /s %repo_name%