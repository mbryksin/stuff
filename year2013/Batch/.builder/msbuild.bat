@echo off

if "%builder_starts%"=="" goto :EOF

%msbuildpath%\msbuild.exe %solution_file%>%msbuild_log%

if errorlevel 1 goto :fail
goto :EOF

:fail
set msbuild_failed=TRUE