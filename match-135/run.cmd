@echo off

for %%O in (%*) do (
  if "%%O" == "stats" (
    set STATS=1
    set OPTS=%OPTS% /DSTATS
  )
)

@REM check env vars
if "%CC%" == "" (
  echo CC not set. Use run-cl.cmd or run-gcc.cmd or set CC
  exit 1
)

@REM build

rmdir /s /q build
mkdir build
pushd build

echo Building...
echo.

if "%CC%" == "cl" (
  %CC% %OPTS% /std:c++20 /EHsc /I../src /Fe"./solution" ../src/solution/*.cpp
  %CC% %OPTS% /std:c++20 /EHsc /I../src /Fe"./stats" ../src/tools/stats.cpp
) else if "%CC%" == "g++" (
  %CC% %OPTS% -std=c++20 -I../src -o "./solution" ../src/solution/*.cpp
  %CC% %OPTS% -std=c++20 -I../src -o"./stats" ../src/tools/stats.cpp
) else (
  echo CC not cl or gcc
  exit 1
)

popd

echo.
echo Build done!

@REM run

if "%STATS%" == "1" (
  @REM run single test
  echo Running stats tests...
  echo.

  for /L %%S in (1,1,3) do (
    java -jar "./tester.jar" -exec "./build/solution.exe" -seed %%S -novis >> ./build/stats_raw
  )
) else (
  @REM run single test
  echo Running single test...
  echo.

  java -jar "./tester.jar" -exec "./build/solution.exe" -seed 1 -novis
)
