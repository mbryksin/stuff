@echo off

if "%builder_starts%"=="" goto :EOF

echo Missed %file_missed%.>%search_log%
if exist %attache% echo ,>%attache% 
echo %search_log%>>%attache%

set email_extra_subject=BUILD FAILED
