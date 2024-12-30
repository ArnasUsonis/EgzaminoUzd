cmake CMakeLists.txt
cmake --install .
cmake --build .
copy src\tekstas.txt Debug\tekstas.txt
copy src\tekstas_URL.txt Debug\tekstas_URL.txt
cd Debug\
Work_with_Files.exe
pause