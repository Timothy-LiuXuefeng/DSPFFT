@ECHO OFF
SETLOCAL

:: Directory of the target platform
SET BINARY_DIR=x64\Release

MKDIR publish
MKDIR publish\include
MKDIR publish\include\prior
MKDIR publish\include\prior\include
MKDIR publish\bin
MKDIR publish\test
COPY /Y "%BINARY_DIR%\dspfft.lib" publish\bin\
COPY /Y "%BINARY_DIR%\homework.exe" publish\test\
XCOPY /Y/E prior\include\ publish\include\prior\include\
XCOPY /Y/E dspfft\include\ publish\include\
PAUSE
