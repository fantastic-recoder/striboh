message(STATUS "Darboh conan libs: ${CONAN_LIBS}.")
add_executable(darboh darboh_main.cpp darbohParser.cpp darbohParser.hpp darbohAstNode.cpp darbohAstNode.hpp)
target_link_libraries(darboh boost_program_options)
