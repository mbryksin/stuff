@echo off

if "%builder_starts%"=="" goto :EOF

if exist %git_errors% del %git_errors%
if exist %msbuild_log% del %msbuild_log%
if exist %search_log% del %search_log%
if exist %attache% del %attache%