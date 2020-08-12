add_executable(striboh_idl_tests striboh_idl_tests.cpp)
set(DARBOH_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/main/cpp)
message(STATUS "DARBOH_INCLUDE_DIR=${DARBOH_INCLUDE_DIR}")
message(STATUS "CONAN_INCLUDE_DIRS_GTEST=${CONAN_INCLUDE_DIRS_GTEST}")
#
target_include_directories(striboh_idl_tests PRIVATE ${CONAN_INCLUDE_DIRS_GTEST} ${DARBOH_INCLUDE_DIR})
target_link_libraries(striboh_idl_tests striboh_idl gmock gtest_main gtest boost_filesystem pthread)
add_test(NAME striboh_idl_tests
        COMMAND striboh_idl_tests)

add_custom_target("All_Striboh_tests" DEPENDS striboh_idl_tests)
