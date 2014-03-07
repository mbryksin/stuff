@echo off

if "%builder_starts%"=="" goto :EOF

if exist %attache% echo ,>%attache% 
echo %msbuild_log%>%attache%

set email_extra_subject=MSBUILD FAILED