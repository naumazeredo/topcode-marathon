@REM build

@rmdir /s /q build
@mkdir build
@pushd build
%CC% /EHsc /Fe"solution" ../solution/main.cpp
@popd

@REM run
java -jar "./tester.jar" -exec "./build/solution.exe" -seed 1 -novis
