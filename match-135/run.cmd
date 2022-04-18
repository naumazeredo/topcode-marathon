@echo off

@REM check env vars
if "%CC%" == "" (
  echo CC not set. Use run-cl.cmd or run-gcc.cmd or set CC
  exit 1
) else (
  @REM build

  rmdir /s /q build
  mkdir build

  echo Building...
  echo.

  if "%CC%" == "cl" (
    %CC% %OPTS% /std:c++17 /EHsc /Fe"./build/solution" ./src/solution/*.cpp
    %CC% %OPTS% /std:c++17 /EHsc /Fe"./build/stats" ./src/tools/stats.cpp
  ) else if "%CC%" == "g++" (
    %CC% %OPTS% -std=c++17 -o "./build/solution" ./src/solution/*.cpp
    %CC% %OPTS% -std=c++17 -o"./build/stats" ./src/tools/stats.cpp
  ) else (
    echo CC not cl or gcc
    exit 1
  )

  echo.
  echo Build done!
)


@REM run
echo Running...
echo.
java -jar "./tester.jar" -exec "./build/solution.exe" -seed 1 -novis
