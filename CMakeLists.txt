cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)              # Compile as C++17.
set(CMAKE_CXX_STANDARD_REQUIRED ON)     # Require C++17 support.

project(coccoc VERSION 1.0)

# Compiler flags.
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Werror")

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(src)
