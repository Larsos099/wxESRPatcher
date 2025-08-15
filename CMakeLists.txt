cmake_minimum_required(VERSION 3.31)
project(wxESRPatcher VERSION 1.0 LANGUAGES CXX)

# --- Force C++23 ---
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)        
find_package(wxWidgets CONFIG REQUIRED)
add_executable(wxESRPatcher
        wxESRPatcher.cpp
        MainWindowFrame.hpp
        defines.hpp
        Patcher.cpp
        MainWindowFrame.cpp
)
target_link_libraries(wxESRPatcher PRIVATE wx::core wx::base)