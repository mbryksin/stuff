@echo off

if "%builder_starts%"=="" goto :EOF

for /F "tokens=*" %%f in (%binaries%) do (
        if not exist "%build_folder%\%%f" (
                set file_missed="%%f"
                goto :fail
        )
)                                  

set email_extra_subject=SUCCSES BUILD
goto :EOF

:fail
set check_failed=TRUE