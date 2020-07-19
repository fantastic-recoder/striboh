add_executable(darboh_test_preprocessor darboh_test_preprocessor.cpp)
set(DARBOH_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/main/cpp)
message( STATUS "DARBOH_INCLUDE_DIR=${DARBOH_INCLUDE_DIR}")
target_include_directories(darboh_test_preprocessor PRIVATE  ${DARBOH_INCLUDE_DIR})
target_link_libraries(darboh_test_preprocessor gmock gtest_main gtest pthread)
add_test(NAME darboh_test_preprocessor
        COMMAND darboh_test_preprocessor )
