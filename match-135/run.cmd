@REM build

@rmdir /s /q build
@mkdir build
@pushd build
cl /EHsc /Fe"solution" ../solution/main.cpp
@popd

@REM run
java -jar "./tools/tester.jar" -exec "./build/solution.exe" -seed 1
