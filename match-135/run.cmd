@echo off

@REM check env vars
if "%CC%" == "" (
  echo CC not set. Use run-cl.cmd or run-gcc.cmd or set CC
  exit 1
) else (
  @REM build

  rmdir /s /q build
  mkdir build
  pushd build

  echo Building...
  echo.

  if "%CC%" == "cl" (
    %CC% %OPTS% /std:c++17 /EHsc /I../src /Fe"./solution" ../src/solution/*.cpp
    %CC% %OPTS% /std:c++17 /EHsc /I../src /Fe"./stats" ../src/tools/stats.cpp
  ) else if "%CC%" == "g++" (
    %CC% %OPTS% -std=c++17 -I../src -o "./solution" ../src/solution/*.cpp
    %CC% %OPTS% -std=c++17 -I../src -o"./stats" ../src/tools/stats.cpp
  ) else (
    echo CC not cl or gcc
    exit 1
  )

  popd

  echo.
  echo Build done!
)


@REM run
echo Running...
echo.
java -jar "./tester.jar" -exec "./build/solution.exe" -seed 1 -novis
