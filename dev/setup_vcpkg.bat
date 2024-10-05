:: setup_vcpkg.bat
@echo off

:: Check if vcpkg directory exists
if not exist "vcpkg" (
    echo Cloning vcpkg...
    git clone https://github.com/microsoft/vcpkg.git
)

:: Bootstrap vcpkg (build it)
if exist "vcpkg" (
    echo Bootstrapping vcpkg...
    vcpkg\bootstrap-vcpkg.bat
)

:: Install dependencies
vcpkg\vcpkg.exe install --triplet x64-windows

echo vcpkg setup complete!
