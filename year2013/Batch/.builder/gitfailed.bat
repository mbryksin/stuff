@echo off

if "%builder_starts%"=="" goto :EOF

if exist %attache% echo ,>%attache% 
echo %git_errors%>>%attache%

set email_extra_subject=GIT CLONE FAILED