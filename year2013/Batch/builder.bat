@echo off
echo Builder starts

set builder_starts=TRUE
set config=.builder

call %config%\settings.bat
call %config%\cleanup.bat
call %config%\gitclone.bat
if /I "%git_failed%"=="TRUE" call %config%\gitfailed.bat & goto :end

call %config%\msbuild.bat
if /I "%msbuild_failed%"=="TRUE" call %config%\msbfailed.bat & goto :end

call %config%\existcheck.bat
if /I "%check_failed%"=="TRUE" call %config%\checkfailed.bat

:end

call %config%\email.bat
call %config%\deltemp.bat

echo Done.