g++ bridge-builder.cpp -o bridge-builder 
java -jar tester.jar -exec "bridge-builder.exe" -seed 1 %*
