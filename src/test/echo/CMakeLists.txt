set(IdlName Echo)

message(STATUS "STRIBOH_INCLUDE_DIRS=${STRIBOH_INCLUDE_DIRS}.")

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Echo.hpp ${CMAKE_CURRENT_BINARY_DIR}/EchoClt.hpp
        COMMAND striboh_python ${striboh_BINARY_DIR}/bin/striboh_idl.py --backend cpp --servant --client --out-dir ${CMAKE_CURRENT_BINARY_DIR} --stdout ${CMAKE_CURRENT_SOURCE_DIR}/Echo.striboh.idl
        DEPENDS striboh_python ${striboh_BINARY_DIR}/bin/striboh_idl.py ${striboh_BINARY_DIR}/bin/striboh_backend_cpp.py ${CMAKE_CURRENT_SOURCE_DIR}/Echo.striboh.idl
        COMMENT "Generating code with ${Python3_EXECUTABLE} ${striboh_BINARY_DIR}/bin/striboh_idl.py --backend cpp --servant --client --out-dir ${CMAKE_CURRENT_BINARY_DIR} --stdout ${CMAKE_CURRENT_SOURCE_DIR}/Echo.striboh.idl"
)

add_executable(striboh_generated_echo_server striboh_generated_echo_server.cpp ${CMAKE_CURRENT_BINARY_DIR}/Echo.hpp)
target_include_directories(striboh_generated_echo_server PRIVATE ${STRIBOH_INCLUDE_DIRS} ${CONAN_INCLUDE_DIRS_GTEST} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(striboh_generated_echo_server striboh_base_library striboh_idl_library ${STRIBOH_LIBS})
target_link_directories(striboh_generated_echo_server PRIVATE ${CONAN_LIB_DIRS_GTEST} ${STRIBOH_LIB_DIRS})

add_executable(striboh_generated_echo_tests striboh_generated_echo_tests.cpp ${CMAKE_CURRENT_BINARY_DIR}/EchoClt.hpp)
add_dependencies(striboh_generated_echo_tests striboh_generated_echo_server ${STRIBOH_PY_MOD})
target_include_directories(striboh_generated_echo_tests PRIVATE ${CONAN_INCLUDE_DIRS_GTEST} ${STRIBOH_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(striboh_generated_echo_tests striboh_base_library striboh_idl_library striboh_test_utils ${CONAN_LIBS_GTEST} ${STRIBOH_LIBS})
target_link_directories(striboh_generated_echo_tests PRIVATE ${CONAN_LIB_DIRS_GTEST} ${STRIBOH_LIB_DIRS})

add_test(NAME striboh_generated_echo_tests COMMAND striboh_generated_echo_tests)

