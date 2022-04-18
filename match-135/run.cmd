@echo off

@REM check env vars
if "%CC%" equ "" (
  echo CC not set. Use run-cl.cmd or run-gcc.cmd or set CC
  exit 1
)

@REM build

echo Building...
echo.

rmdir /s /q build
mkdir build
pushd build
%CC% /EHsc /Fe"solution" ../solution/main.cpp
popd

echo.
echo Build done!

@REM run
echo Running...
echo.
java -jar "./tester.jar" -exec "./build/solution.exe" -seed 1 -novis
