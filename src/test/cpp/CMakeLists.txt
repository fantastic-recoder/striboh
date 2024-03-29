message(STATUS "STRIBOH_INCLUDE_DIRS=${STRIBOH_INCLUDE_DIRS}")
message(STATUS "CONAN_INCLUDE_DIRS_GTEST=${CONAN_INCLUDE_DIRS_GTEST}")
message(STATUS "STRIBOH_LIBS=${STRIBOH_LIBS}")

configure_file(in.striboh_build_constants.hpp ${CMAKE_BINARY_DIR}/striboh_build_constants.hpp)

add_executable(striboh_idl_tests striboh_idl_tests.cpp)
target_include_directories(striboh_idl_tests PRIVATE ${CONAN_INCLUDE_DIRS_GTEST} ${STRIBOH_INCLUDE_DIRS})
target_link_libraries(striboh_idl_tests striboh_idl_library striboh_base_library ${CONAN_LIBS_GTEST} ${STRIBOH_LIBS} ${Python3_LIBRARIES})
target_link_directories(striboh_idl_tests PRIVATE ${CONAN_LIB_DIRS_GTEST} ${STRIBOH_LIB_DIRS})
add_test(NAME striboh_idl_tests COMMAND striboh_idl_tests)

add_executable(striboh_message_tests striboh_message_tests.cpp)
target_include_directories(striboh_message_tests PRIVATE ${CONAN_INCLUDE_DIRS_GTEST} ${STRIBOH_INCLUDE_DIRS})
target_link_libraries(striboh_message_tests striboh_idl_library striboh_base_library ${CONAN_LIBS_GTEST} ${STRIBOH_LIBS} ${Python3_LIBRARIES})
target_link_directories(striboh_message_tests PRIVATE ${CONAN_LIB_DIRS_GTEST} ${STRIBOH_LIB_DIRS})
add_test(NAME striboh_message_tests COMMAND striboh_message_tests)

add_executable(striboh_test_echo_server striboh_test_echo_server.cpp striboh_test_echo_server_common.hpp)
add_dependencies(striboh_test_echo_server ${STRIBOH_PY_MOD})
target_include_directories(striboh_test_echo_server PRIVATE ${CONAN_INCLUDE_DIRS_GTEST} ${STRIBOH_INCLUDE_DIRS} ${CMAKE_BINARY_DIR})
target_link_libraries(striboh_test_echo_server striboh_idl_library striboh_base_library ${STRIBOH_LIBS} ${CONAN_LIBS_GTEST} )#
target_link_directories(striboh_test_echo_server PRIVATE ${CONAN_LIB_DIRS_GTEST} ${STRIBOH_LIB_DIRS})

add_library(striboh_test_utils STATIC striboh_test_utils.cpp striboh_test_utils.hpp)
target_include_directories(striboh_test_utils PUBLIC ${STRIBOH_INCLUDE_DIRS} ${CMAKE_BINARY_DIR})

add_executable(striboh_base_tests striboh_base_tests.cpp striboh_test_echo_server_common.hpp striboh_test_utils.hpp)
add_dependencies(striboh_base_tests ${STRIBOH_PY_MOD})
target_include_directories(striboh_base_tests PRIVATE ${CONAN_INCLUDE_DIRS_GTEST} ${STRIBOH_INCLUDE_DIRS})
target_link_libraries(striboh_base_tests PRIVATE striboh_base_library striboh_idl_library ${CONAN_LIBS_GTEST}
        ${STRIBOH_LIBS} striboh_test_utils)
target_link_directories(striboh_base_tests PRIVATE ${CONAN_LIB_DIRS_GTEST} ${STRIBOH_LIB_DIRS})
add_test(NAME striboh_base_tests COMMAND striboh_base_tests)
add_dependencies(striboh_base_tests striboh_test_echo_server)

add_executable(striboh_broker_tests striboh_broker_tests.cpp striboh_test_echo_server_common.hpp striboh_test_utils.hpp)
add_dependencies(striboh_broker_tests ${STRIBOH_PY_MOD})
target_include_directories(striboh_broker_tests PRIVATE ${CONAN_INCLUDE_DIRS_GTEST} ${STRIBOH_INCLUDE_DIRS})
target_link_libraries(striboh_broker_tests PRIVATE striboh_base_library striboh_idl_library ${CONAN_LIBS_GTEST}
        ${STRIBOH_LIBS} striboh_test_utils)
target_link_directories(striboh_broker_tests PRIVATE ${CONAN_LIB_DIRS_GTEST} ${STRIBOH_LIB_DIRS})
add_test(NAME striboh_broker_tests COMMAND striboh_broker_tests)
add_dependencies(striboh_broker_tests striboh_test_echo_server)

add_executable(striboh_address_tests striboh_test_address.cpp)
add_dependencies(striboh_address_tests ${STRIBOH_PY_MOD})
target_include_directories(striboh_address_tests PRIVATE ${CONAN_INCLUDE_DIRS_GTEST} ${STRIBOH_INCLUDE_DIRS})
target_link_libraries(striboh_address_tests striboh_base_library ${CONAN_LIBS_GTEST} ${STRIBOH_LIBS})
target_link_directories(striboh_address_tests PRIVATE ${CONAN_LIB_DIRS_GTEST} ${STRIBOH_LIB_DIRS})
add_test(NAME striboh_address_tests COMMAND striboh_address_tests)

