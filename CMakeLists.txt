cmake_minimum_required(VERSION 4.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(ProjectDungeon)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(ProjectDungeon main.cpp)

add_subdirectory(lib/SDL)
target_link_libraries(ProjectDungeon PUBLIC SDL3::SDL3)
target_include_directories(ProjectDungeon PUBLIC lib/SDL/include)