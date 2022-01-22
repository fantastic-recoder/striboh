cmake_minimum_required(VERSION 3.10)
project(striboh)

set(CMAKE_CXX_STANDARD 17)
set(MSGPACK_CXX17 ON)
set(CONAN_REVISIONS_ENABLED 1)
if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
    set(CONAN_DISABLE_CHECK_COMPILER 1) # allow new shiny VS versions
    # _WIN32_WINNT=0x0A00 == Windows 10 Boost HAS to be compiled according define=BOOST_USE_WINAPI_VERSION=0x0A00
    add_compile_options(/D_WIN32_WINNT=0x0A00)
    set(BCrypt_LIBRARIES bcrypt)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-std=c++2a -fPIC -Wall -Wextra -pedantic)
endif()

########################################################################################################################
# Conan start
# Download automatically, you can also just copy the conan.cmake file
# see https://github.com/conan-io/cmake-conan
#
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
########################################################################################################################
# include in-source Boost
add_subdirectory(src/main/cpp/boost)
# Boost end
###############################################################################

###############################################################################
# Python
find_package(Python3 3.8 REQUIRED COMPONENTS Interpreter Development)
# Python end
###############################################################################

set(STRIBOH_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/main/cpp)
set(STRIBOH_LIBS ${CONAN_LIBS_FMT} Threads::Threads ${Python3_LIBRARIES} ${CMAKE_DL_LIBS}
        Boost::program_options Boost::log ${BCrypt_LIBRARIES}) #${Boost_LIBRARIES} ${CONAN_LIBS_BOOST}
set(STRIBOH_LIB_DIRS ${CONAN_LIB_DIRS_FMT} ${CMAKE_DL_LIBS} ${Python3_LIBRARY_DIRS}) # ${CONAN_LIB_DIRS_BOOST} ${Boost_LIBRARY_DIRS}
set(STRIBOH_INCLUDE_DIRS ${CONAN_INCLUDE_DIRS_NAMEDTYPE} ${CONAN_INCLUDE_DIRS_NLOHMANN_JSON} ${CONAN_INCLUDE_DIRS_FMT}
        ${Python3_INCLUDE_DIRS} ${STRIBOH_INCLUDE_DIR} ${CONAN_INCLUDE_DIRS_MSGPACK}
        ${CONAN_INCLUDE_DIRS_PYBIND11}
        ${boost_asio_SOURCE_DIR}/include
        ${boost_archive_SOURCE_DIR}/include
        ${boost_config_SOURCE_DIR}/include
        ${boost_endian_SOURCE_DIR}/include
        ${boost_format_SOURCE_DIR}/include
        ${boost_logic_SOURCE_DIR}/include
        ${boost_predef_SOURCE_DIR}/include
        ${boost_property_tree_SOURCE_DIR}/include
        ${boost_process_SOURCE_DIR}/include
        ${boost_random_SOURCE_DIR}/include
        ${boost_system_SOURCE_DIR}/include
        ${boost_spirit_SOURCE_DIR}/include
        ${boost_serialization_SOURCE_DIR}/include
        ${boost_tti_SOURCE_DIR}/include
        ${boost_multi_index_SOURCE_DIR}/include
        ${boost_msm_SOURCE_DIR}/include
        ${boost_foreach_SOURCE_DIR}/include
        ${boost_uuid_SOURCE_DIR}/include
        ${boost_winapi_SOURCE_DIR}/include
        ${boost_variant_SOURCE_DIR}/include
        ${boost_beast_SOURCE_DIR}/include)
set(STRIBOH_PY_MOD stribohmodule)

message(STATUS "STRIBOH_LIB_DIRS=${STRIBOH_LIB_DIRS}")
# and this adds the doxygen folder as a CMake subdirectory.
add_subdirectory(doxygen)
# Sources (by type maven like)
add_subdirectory(src/main/cpp/striboh)
add_subdirectory(src/test/cpp)
add_subdirectory(src/test/echo)
add_subdirectory(src/test/angular)
