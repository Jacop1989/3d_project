cmake_minimum_required(VERSION 3.10)

project(3d_project C)

enable_testing()

add_subdirectory(tests)

project(3d_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

