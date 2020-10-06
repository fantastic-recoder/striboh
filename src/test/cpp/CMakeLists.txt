set(STRIBOH_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/main/cpp)
message(STATUS "STRIBOH_INCLUDE_DIR=${STRIBOH_INCLUDE_DIR}")
message(STATUS "CONAN_INCLUDE_DIRS_GTEST=${CONAN_INCLUDE_DIRS_GTEST}")

set(STRIBOH_LIBS boost_log boost_filesystem boost_system boost_thread fmt pthread)
add_executable(striboh_idl_tests striboh_idl_tests.cpp)
target_include_directories(striboh_idl_tests PRIVATE ${CONAN_INCLUDE_DIRS_GTEST} ${STRIBOH_INCLUDE_DIR})
target_link_libraries(striboh_idl_tests striboh_idl gmock gtest_main gtest ${STRIBOH_LIBS})
add_test(NAME striboh_idl_tests COMMAND striboh_idl_tests)


add_executable(striboh_test_echo_server striboh_test_echo_server.cpp)
target_include_directories(striboh_test_echo_server PRIVATE ${CONAN_INCLUDE_DIRS_GTEST} ${STRIBOH_INCLUDE_DIR})
target_link_libraries(striboh_test_echo_server striboh_base striboh_idl ${STRIBOH_LIBS})

add_executable(striboh_base_tests striboh_base_tests.cpp)
target_include_directories(striboh_base_tests PRIVATE ${CONAN_INCLUDE_DIRS_GTEST} ${STRIBOH_INCLUDE_DIR})
target_link_libraries(striboh_base_tests striboh_base striboh_idl gmock gtest_main gtest ${STRIBOH_LIBS})
add_test(NAME striboh_base_tests COMMAND striboh_idl_tests)

add_dependencies(striboh_base_tests striboh_test_echo_server)

add_custom_target("All_Striboh_tests" DEPENDS striboh_test_echo_server striboh_idl_tests striboh_base_tests)
