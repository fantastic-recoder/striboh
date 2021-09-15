message(STATUS "STRIBOH_INCLUDE_DIR=${STRIBOH_INCLUDE_DIR}")
message(STATUS "CONAN_INCLUDE_DIRS_GTEST=${CONAN_INCLUDE_DIRS_GTEST} ${CONAN_INCLUDE_DIRS_FMT}")

add_library(striboh_test_utils striboh_test_utils.hpp striboh_test_utils.cpp)
target_include_directories(striboh_test_utils PRIVATE ${CONAN_INCLUDE_DIRS_GTEST} ${CONAN_INCLUDE_DIRS_FMT} ${STRIBOH_INCLUDE_DIR})

add_executable(striboh_idl_tests striboh_idl_tests.cpp)
target_include_directories(striboh_idl_tests PRIVATE ${CONAN_INCLUDE_DIRS_GTEST} ${STRIBOH_INCLUDE_DIR})
target_include_directories(striboh_idl_tests PRIVATE ${CONAN_INCLUDE_DIRS_CHAISCRIPT})
target_link_libraries(striboh_idl_tests striboh_base_library striboh_idl_library ${CONAN_LIBS_GTEST} ${STRIBOH_LIBS})
target_link_directories(striboh_idl_tests PRIVATE ${CONAN_LIB_DIRS_GTEST} ${STRIBOH_LIB_DIRS})
add_test(NAME striboh_idl_tests COMMAND striboh_idl_tests)

add_executable(striboh_test_echo_server striboh_test_echo_server.cpp striboh_test_echo_server_common.hpp)
target_include_directories(striboh_test_echo_server PRIVATE ${CONAN_INCLUDE_DIRS_GTEST} ${STRIBOH_INCLUDE_DIR})
target_link_libraries(striboh_test_echo_server striboh_base_library striboh_idl_library ${CONAN_LIBS_GTEST} ${STRIBOH_LIBS})
target_link_directories(striboh_test_echo_server PRIVATE ${CONAN_LIB_DIRS_GTEST} ${STRIBOH_LIB_DIRS})

add_executable(striboh_base_tests striboh_base_tests.cpp striboh_test_echo_server_common.hpp)
target_include_directories(striboh_base_tests PRIVATE ${CONAN_INCLUDE_DIRS_GTEST} ${STRIBOH_INCLUDE_DIR})
target_link_libraries(striboh_base_tests striboh_base_library striboh_idl_library striboh_test_utils ${CONAN_LIBS_GTEST} ${STRIBOH_LIBS})
target_link_directories(striboh_base_tests PRIVATE ${CONAN_LIB_DIRS_GTEST} ${STRIBOH_LIB_DIRS})
add_test(NAME striboh_base_tests COMMAND striboh_idl_tests)

add_dependencies(striboh_base_tests striboh_test_echo_server)

add_custom_target("All_Striboh_tests" DEPENDS striboh_test_echo_server striboh_idl_tests striboh_base_tests)

