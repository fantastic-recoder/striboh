set(IdlName Echo)
message("Generated echo server.")
add_custom_command(
        OUTPUT generated_echo_server/${IdlName}Servant.hpp
        COMMAND striboh_idl_compiler ${IdlName}.striboh.idl
        DEPENDS striboh_idl_compiler ${IdlName}.striboh.idl
        COMMENT "Generating code for ${IdlName}."
)

add_executable(striboh_generated_echo_server striboh_generated_echo_server.cpp generated_echo_server/EchoServant.hpp)
target_include_directories(striboh_generated_echo_server PRIVATE ${CONAN_INCLUDE_DIRS_GTEST} ${STRIBOH_INCLUDE_DIR})
target_link_libraries(striboh_generated_echo_server striboh_base_library striboh_idl_library ${STRIBOH_LIBS})


