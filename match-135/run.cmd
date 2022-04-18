@echo off

set TESTER_OPTS=-novis

for %%O in (%*) do (
  if "%%O" == "stats" (
    set STATS=1
    set OPTS=%OPTS% /DSTATS
  )

  if "%%O" == "vis" (
    set TESTER_OPTS=
  )
)

REM check env vars
if "%CC%" == "" (
  echo CC not set. Use run-cl.cmd or run-gcc.cmd or set CC
  exit 1
)

REM build

set INCLUDE_DIR=src
set SOLUTION_DIR=src/solution
set COMMON_DIR=src/common
set TOOLS_DIR=src/tools

set SOLUTION_EXE=solution
set STATS_EXE=stats

rmdir /s /q build
mkdir build
pushd build

echo Building...
echo.

if "%CC%" == "cl" (
  %CC% %OPTS% /std:c++20 /EHsc /I../%INCLUDE_DIR% /Fe"./%SOLUTION_EXE%" ../%SOLUTION_DIR%/*.cpp ../%COMMON_DIR%/*.cpp
  %CC% %OPTS% /std:c++20 /EHsc /I../%INCLUDE_DIR% /Fe"./%STATS_EXE%" ../%TOOLS_DIR%/stats.cpp ../%COMMON_DIR%/*.cpp
) else if "%CC%" == "g++" (
  %CC% %OPTS% -std=c++20 -I../%INCLUDE_DIR% -o "./%SOLUTION_EXE%" ../%SOLUTION_DIR%/*.cpp ../%COMMON_DIR%/*.cpp
  %CC% %OPTS% -std=c++20 -I../%INCLUDE_DIR% -o"./%STATS_EXE%" ../%TOOLS_DIR%/stats.cpp ../%COMMON_DIR%/*.cpp
) else (
  echo CC not cl or gcc
  exit 1
)

popd

echo.
echo Build done!

REM run

if "%STATS%" == "1" (
  @REM run multiple tests
  echo Running stats tests...
  echo.

  for /L %%S in (1,1,3) do (
    java -jar "./tester.jar" -exec "./build/solution.exe" -seed %%S -novis >> ./build/raw_stats
  )
) else (
  REM run single test
  echo Running single test...
  echo.

  java -jar "./tester.jar" -exec "./build/solution.exe" -seed 1 %TESTER_OPTS%
)
