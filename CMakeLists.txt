cmake_minimum_required(VERSION 3.10)
project(striboh)

set(CMAKE_CXX_STANDARD 17)
set(MSGPACK_CXX17 ON)
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/bigobj)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-std=c++2a -fPIC -Wall -Wextra -pedantic)
endif()

enable_testing()

find_package(Python3 3.8 REQUIRED COMPONENTS Interpreter Development)

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(TARGETS)
else()
    message(ERROR "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

include(FetchContent)

###############################################################################
# DI begin
FetchContent_Declare(di
        PREFIX ${CMAKE_SOURCE_DIR}/src/main/cpp/di
        URL https://raw.githubusercontent.com/boost-ext/di/cpp14/include/boost/di.hpp
        DOWNLOAD_NO_EXTRACT true
        )
FetchContent_GetProperties(di)
if(NOT di_POPULATED)
    FetchContent_Populate(di)
    # Copy an additional/replacement file into the populated source
    file(COPY ${CMAKE_SOURCE_DIR}/src/main/cpp/di/src/di.hpp DESTINATION
            ${CMAKE_SOURCE_DIR}/src/main/cpp/di)
endif()
# SML end
###############################################################################


set(STRIBOH_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/main/cpp)
set(STRIBOH_LIBS ${CONAN_LIBS_BOOST} ${CONAN_LIBS_FMT} ${CMAKE_DL_LIBS} pthread)
set(STRIBOH_LIB_DIRS ${CONAN_LIB_DIRS_BOOST} ${CONAN_LIB_DIRS_FMT} ${CMAKE_DL_LIBS})

add_subdirectory(src/main/cpp/striboh)
add_subdirectory(src/test/cpp)
add_subdirectory(src/test/echo)
# and this adds the doxygen folder as a CMake subdirectory.
add_subdirectory(doxygen)
