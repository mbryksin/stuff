@echo off

if "%builder_starts%"=="" goto :EOF

if not exist %attache% echo. >%attache%
Blat -body " " -to %email_to% -server %email_server% -f %email_from% -subject "Building solution [%email_extra_subject%]" -atf %attache%>nul