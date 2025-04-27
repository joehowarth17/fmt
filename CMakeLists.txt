project(effectControl C CXX)
cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

add_definitions(-DCMAKE_POSITION_INDEPENDENT_CODE=TRUE)
set(FMT_OS OFF)
add_definitions(-DFMT_USE_FALLBACK_FILE=1)
add_subdirectory(lib/fmt)
