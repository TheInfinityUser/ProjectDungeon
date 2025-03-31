cmake_minimum_required(VERSION 4.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(ProjectDungeon)

add_executable(ProjectDungeon main.cpp)

add_subdirectory(lib/glad)
add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)

target_link_libraries(ProjectDungeon PRIVATE glad glfw glm)
target_include_directories(ProjectDungeon PRIVATE 
  lib/glad/include
  lib/glfw/include
  lib/glm
)