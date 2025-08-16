# wxESRPatcher












wxESRPatcher is a **cross-platform graphical user interface (GUI) application** written in **C++23** using wxWidgets, serving as a modern rewrite of the original Windows-only ESR Patchers





## Features





- Fully rewritten in **C++23** with modern C++ practices


- **Cross-platform**: Runs on Windows, Linux, FreeBSD, and macOS (unlike the original Windows-only version)


- Super Simple GUI Interface, just 2 buttons and a textbox


- Supports all core ESR patching functionality





## Why wxESRPatcher?





The original ESR Patchers were tightly coupled to Windows and WinAPI, limiting portability and modern C++ development practices. ESRPatcherGUI modernizes the codebase and uses wxWidgets, making it:





- Platform-independent thanks to wxWidgets


- Future-proof with modern C++23 features





## Requirements





- **C++23 compiler** (tested with GCC 15 & Clang 17)


- **CMake ≥ 4**


- **wxWidgets ≥ 3.0**


- Standard C++ libraries only (without wxWidgets)





## Building





```bash


git clone https://github.com/Larsos099/wxESRPatcher.git


cd wxESRPatcher


mkdir build && cd build


cmake --preset <your desired preset> ..


cmake --build .


```


### When using vcpkg, make sure VCPKG_ROOT is set!


## Available CMake Presets


ARM MacOS Static & Dynamic (with and without vcpkg)





Intel MacOS Static & Dynamic (with and without vcpkg)





ARM Generic Target Static & Dynamic (with and without vcpkg)





Windows MinGW Static & Dynamic (with and without vcpkg)





Windows MSVC Static & Dynamic (with and without vcpkg)





Linux Generic Static & Dynamic (with and without vcpkg)





BSD Static & Dynamic (with and without vcpkg)