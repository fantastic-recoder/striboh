# Finds and loads settings from an external project.
# "QUIET" makes it so that CMake won't complain in case Doxygen isn't present.
# More information at https://cmake.org/cmake/help/latest/command/find_package.html
find_package(Doxygen QUIET)

# Here we set a list of images that can/will be used in the documentation.
# For now we only have a logo to use.
set(DOCS_IMAGES
        logo.png
        )

# While "DOCS_RESOURCES" contains all the other lists so that the file moving can be done with only one call in CMake.
set(DOCS_RESOURCES
        ${DOCS_IMAGES}
        )

if (DOXYGEN_FOUND)
    # Input directory of header files from which the documentation will be formed.
    set(DOXYGEN_INPUT_DIR ${CMAKE_SOURCE_DIR}/src/main/cpp/striboh)
    # Output directory for built documentation.
    # "CMAKE_BINARY_DIR" is usually a directory named "out" located in the root of the project.
    set(DOXYGEN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/docs)
    # "DOXYGEN_INDEX_FILE" is the path to the documentation homepage html file.
    set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.html)
    # The following is used to always force Doxygen to try a run regardless if one was already performed.
    set(DOXYGEN_FAKE_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/__index.html)

    # The 2 following lines just specify the input path for the template Doxygen options.
    # Whilst the 2nd specifies the output for when the place holder data has already been filled in.
    set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYFILE_OUT ${DOXYGEN_OUTPUT_DIR}/Doxyfile)

    set(DOXYGEN_PROJECT_LOGO ${DOXYGEN_OUTPUT_DIR}/logo.png)

    #Replace variables inside @@ with the current values
    configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)
    # Here we use CMake to manually create the Doxygen output directory since it doesn't do it itself.
    file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})
    # Copy the needed resources like the logo for instance into the output directory.
    file(COPY ${DOCS_RESOURCES} DESTINATION ${DOXYGEN_OUTPUT_DIR})

    # More information at https://cmake.org/cmake/help/latest/command/add_custom_command.html
    add_custom_command(
            OUTPUT
            ${DOXYGEN_INDEX_FILE}
            ${DOXYGEN_FAKE_INDEX_FILE}
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
            MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
            COMMENT "Generating docs")

    # More information at https://cmake.org/cmake/help/latest/command/add_custom_target.html
    add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})
else ()
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
