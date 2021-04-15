set(IdlName Echo)

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/EchoServant.hpp
        COMMAND ${striboh_BINARY_DIR}/bin/striboh_idl_compiler --backend cpp --servant ${CMAKE_CURRENT_SOURCE_DIR}/Echo.striboh.idl --output-file ${CMAKE_CURRENT_SOURCE_DIR}/Echo.hpp
        DEPENDS ${striboh_BINARY_DIR}/bin/striboh_idl_compiler ${CMAKE_CURRENT_SOURCE_DIR}/Echo.striboh.idl
        COMMENT "Generating code with ${striboh_BINARY_DIR}/bin/striboh_idl_compiler ${CMAKE_CURRENT_SOURCE_DIR}/Echo.striboh.idl."
)

add_executable(striboh_generated_echo_server striboh_generated_echo_server.cpp EchoServant.hpp)
target_include_directories(striboh_generated_echo_server PRIVATE ${CONAN_INCLUDE_DIRS_GTEST} ${STRIBOH_INCLUDE_DIR})
target_link_libraries(striboh_generated_echo_server striboh_base_library striboh_idl_library ${STRIBOH_LIBS})
