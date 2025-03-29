cmake_minimum_required(VERSION 4.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(ProjectDungeon)

add_executable(ProjectDungeon main.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(lib/SDL)

target_include_directories(ProjectDungeon PUBLIC lib/SDL/include lib/SDL3_shadercross-3.0.0-windows-mingw-x64/include)

file(COPY
  lib/SDL3_shadercross-3.0.0-windows-mingw-x64/bin/dxcompiler.dll
  lib/SDL3_shadercross-3.0.0-windows-mingw-x64/bin/dxil.dll
  lib/SDL3_shadercross-3.0.0-windows-mingw-x64/bin/libspirv-cross-c-shared.dll
  lib/SDL3_shadercross-3.0.0-windows-mingw-x64/bin/SDL3_shadercross.dll
  DESTINATION .
)