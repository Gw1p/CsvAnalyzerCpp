@RD /S /Q build
mkdir build
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=vcpkg\\scripts\\buildsystems\\vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release