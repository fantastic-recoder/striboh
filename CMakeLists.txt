cmake_minimum_required(VERSION 3.10)
project(striboh)

set(CMAKE_CXX_STANDARD 17)
set(MSGPACK_CXX17 ON)
add_definitions("-std=c++17")
enable_testing()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include(FetchContent)
FetchContent_Declare(sml
        PREFIX ${CMAKE_SOURCE_DIR}/src/main/cpp/sml
        URL https://github.com/boost-ext/sml/archive/master.zip
        )

FetchContent_GetProperties(sml)
if(NOT sml_POPULATED)
    FetchContent_Populate(sml)
    add_subdirectory(${sml_SOURCE_DIR} ${sml_BINARY_DIR})
endif()

add_subdirectory(src/main/cpp/NamedType)
add_subdirectory(src/main/cpp/fmt)
add_subdirectory(src/main/cpp/striboh)
add_subdirectory(src/test/cpp)

