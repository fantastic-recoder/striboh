message(STATUS "Darboh conan libs: ${CONAN_LIBS}.")
add_executable(darboh darboh_main.cpp darbohParser.cpp darbohParser.hpp darbohAstNodeRoot.cpp darbohAstNodeRoot.hpp)
target_link_libraries(darboh boost_program_options)
