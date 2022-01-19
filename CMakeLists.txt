cmake_minimum_required(VERSION 3.10)
project(striboh)

set(CMAKE_CXX_STANDARD 20)
set(MSGPACK_CXX17 ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
set(CONAN_REVISIONS_ENABLED 1)
if (MSVC)
    set(CONAN_DISABLE_CHECK_COMPILER 1) # allow new shiny VS versions
    # warning level 4 and all warnings as errors
    add_compile_options(/bigobj /W3 )
    add_compile_options(/bigobj)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-std=c++2a -fPIC -Wall -Wextra -pedantic)
endif()

########################################################################################################################
# Conan start
# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake")
endif()
include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_install(PATH_OR_REFERENCE ${CMAKE_SOURCE_DIR}
        BUILD missing
        REMOTE conancenter
        SETTINGS ${settings})

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(TARGETS)
    message(STATUS "Conan configuration ${CMAKE_CMAKE_BINARY_DIR}/conanbuildinfo.cmake read in.")
else()
    message(FATAL_ERROR "The file ${CMAKE_SOURCE_DIR}/conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()
# Conan end
########################################################################################################################

enable_testing()

find_package(Threads)


if (MSVC)
    set(Boost_INCLUDE_DIR "C:/Boost/include/boost-1_78")
    add_definitions( -DBOOST_ALL_NO_LIB )
    add_definitions( -DBOOST_ALL_DYN_LINK )
    add_definitions( -DBOOST_LIB_DIAGNOSTIC )
    find_package(Boost 1.78.0 REQUIRED COMPONENTS filesystem program_options log log_setup iostreams)
    if(${Boost_FOUND})
        message(STATUS "Boost ${Boost_DIR} found!")
        include_directories(${Boost_INCLUDE_DIRS})
    else()
        message(FATAL_ERROR "Failed to find boost!")
    endif()
endif()

find_package(Python3 3.8 REQUIRED COMPONENTS Interpreter Development)

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
set(STRIBOH_LIBS ${CONAN_LIBS_BOOST} ${CONAN_LIBS_FMT} Threads::Threads ${Python3_LIBRARIES} ${CMAKE_DL_LIBS} ${Boost_LIBRARIES})
set(STRIBOH_LIB_DIRS ${CONAN_LIB_DIRS_BOOST} ${CONAN_LIB_DIRS_FMT} ${CMAKE_DL_LIBS} ${Python3_LIBRARY_DIRS})
set(STRIBOH_INCLUDE_DIRS ${CONAN_INCLUDE_DIRS_NAMEDTYPE} ${CONAN_INCLUDE_DIRS_NLOHMANN_JSON} ${CONAN_INCLUDE_DIRS_FMT}
        ${CONAN_INCLUDE_DIRS_BOOST} ${Python3_INCLUDE_DIRS} ${STRIBOH_INCLUDE_DIR}
        ${CONAN_INCLUDE_DIRS_PYBIND11} ${Boost_INCLUDE_DIRS}) #

message(STATUS "STRIBOH_LIB_DIRS=${STRIBOH_LIB_DIRS}")
add_subdirectory(src/main/cpp/striboh)
add_subdirectory(src/test/cpp)
add_subdirectory(src/test/echo)
add_subdirectory(src/test/angular)
# and this adds the doxygen folder as a CMake subdirectory.
add_subdirectory(doxygen)
