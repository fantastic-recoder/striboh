cmake_minimum_required(VERSION 3.10)
project(striboh)

set(CMAKE_CXX_STANDARD 17)
set(MSGPACK_CXX17 ON)
add_definitions("-std=c++17")
enable_testing()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(src/main/cpp/NamedType)
add_subdirectory(src/main/cpp/striboh)
add_subdirectory(src/test/cpp)
