cmake_minimum_required(VERSION 3.10)
project(striboh)

set(CMAKE_CXX_STANDARD 17)
set(MSGPACK_CXX17 ON)
add_definitions("-std=c++17")
enable_testing()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

###############################################################################
# SML begin
include(FetchContent)
FetchContent_Declare(sml
        PREFIX ${CMAKE_SOURCE_DIR}/src/main/cpp/sml
        URL https://raw.githubusercontent.com/boost-ext/sml/master/include/boost/sml.hpp
        DOWNLOAD_NO_EXTRACT true
        )
FetchContent_GetProperties(sml)
if(NOT sml_POPULATED)
    FetchContent_Populate(sml)
    # Copy an additional/replacement file into the populated source
    file(COPY ${CMAKE_SOURCE_DIR}/src/main/cpp/sml/src/sml.hpp DESTINATION
            ${CMAKE_SOURCE_DIR}/src/main/cpp/sml)
endif()
# SML end
###############################################################################

set(STRIBOH_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/main/cpp)

add_subdirectory(src/main/cpp/NamedType)
add_subdirectory(src/main/cpp/fmt)
add_subdirectory(src/main/cpp/striboh)
add_subdirectory(src/test/cpp)

