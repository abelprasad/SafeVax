@echo off
REM Download Crow header-only library

echo Downloading Crow C++ web framework...

REM Create lib directory if it doesn't exist
if not exist "lib" mkdir lib
cd lib

REM Download crow_all.h (single header version)
curl -L -o crow_all.h https://raw.githubusercontent.com/CrowCpp/Crow/master/include/crow_all.h

echo Crow downloaded successfully to backend/lib/crow_all.h
echo.
echo Next steps:
echo 1. Install Boost: Download from https://www.boost.org/
echo 2. Update CMakeLists.txt with Boost path if needed
echo 3. Build: mkdir build ^&^& cd build ^&^& cmake .. ^&^& make

cd ..
