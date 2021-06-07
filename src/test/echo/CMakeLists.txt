set(IdlName Echo)

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/Echo.hpp ${CMAKE_CURRENT_SOURCE_DIR}/EchoClt.hpp
        COMMAND ${striboh_BINARY_DIR}/bin/striboh_idl_compiler --backend cpp --servant --client --out-dir ${CMAKE_CURRENT_SOURCE_DIR} --stdout ${CMAKE_CURRENT_SOURCE_DIR}/Echo.striboh.idl
        DEPENDS ${striboh_BINARY_DIR}/bin/striboh_idl_compiler ${CMAKE_CURRENT_SOURCE_DIR}/Echo.striboh.idl
        COMMENT "Generating code with ${striboh_BINARY_DIR}/bin/striboh_idl_compiler ${CMAKE_CURRENT_SOURCE_DIR}/Echo.striboh.idl."
)

add_executable(striboh_generated_echo_server striboh_generated_echo_server.cpp Echo.hpp)
target_include_directories(striboh_generated_echo_server PRIVATE ${CONAN_INCLUDE_DIRS_GTEST} ${STRIBOH_INCLUDE_DIR})
target_link_libraries(striboh_generated_echo_server striboh_base_library striboh_idl_library ${STRIBOH_LIBS})

add_executable(striboh_generated_echo_tests striboh_generated_echo_tests.cpp EchoClt.hpp)
target_include_directories(striboh_generated_echo_tests PRIVATE ${CONAN_INCLUDE_DIRS_GTEST} ${STRIBOH_INCLUDE_DIR})
target_link_libraries(striboh_generated_echo_tests striboh_base_library striboh_idl_library gmock gtest_main gtest ${STRIBOH_LIBS})
add_test(NAME striboh_generated_echo_tests COMMAND striboh_generated_echo_tests)

