@echo off

setlocal

set "DST=%~1"

rem // Read DISTRIBUTION value from mod-distribution.txt.
for /f "usebackq tokens=2 delims==" %%A in (`findstr /b "DISTRIBUTION=" "mod-distribution.txt"`) do (
    set "DISTRIBUTION=%%A"
)

rem // Default to Yakuza 3.
if not defined DISTRIBUTION (
   set "DISTRIBUTION=Y3"
)

rem // Select thumbnail for mod manager.
if /i "%DISTRIBUTION%" == "Y3" (
    set "SRC=mod-image-y3.png"
) else if /i "%DISTRIBUTION%" == "Y4" (
    set "SRC=mod-image-y4-y5.png"
) else if /i "%DISTRIBUTION%" == "Y5" (
    set "SRC=mod-image-y4-y5.png"
) else (
    echo Invalid distribution.
    exit /b 1
)

copy "%SRC%" "%DST%\mod-image.png" /Y

if errorlevel 1 (
    echo Failed to copy mod manager thumbnail.
    exit /b 1
)

endlocal
