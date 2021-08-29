message(STATUS "Striboh conan libs: ${CONAN_LIBS}.")

configure_file(striboh_backend.cpp.chai ${striboh_BINARY_DIR}/share/striboh/striboh_backend.cpp.chai COPYONLY)

set(STRIBOH_LIBS_INCLUDES ${CONAN_INCLUDE_DIRS_NAMEDTYPE} ${CONAN_INCLUDE_DIRS_NLOHMANN_JSON} ${CONAN_INCLUDE_DIRS_FMT} ${CONAN_INCLUDE_DIRS_CHAISCRIPT})

add_library(striboh_idl_library STATIC stribohIdlParser.cpp stribohIdlParser.hpp stribohIdlAstRootNode.cpp stribohIdlAstRootNode.hpp stribohIdlAstBaseNode.hpp stribohIdlAstModuleNode.cpp stribohIdlAstModuleNode.hpp stribohIdlAstIdentifierNode.hpp stribohIdlAstImportListNode.hpp stribohIdlAstMethodNode.hpp stribohIdlAstTypeNode.hpp stribohIdlAstEBuildinTypes.hpp stribohIdlAstTypedIdentifierNode.hpp stribohIdlAstNode.hpp stribohIdlAstBaseNode.cpp stribohIdlAstImportListNode.cpp stribohIdlAstMethodNode.cpp stribohIdlAstModuleListNode.cpp stribohIdlAstTypedIdentifierNode.cpp stribohIdlAstImportNode.hpp stribohIdlAstImportNode.cpp stribohIdlAstTypeNode.cpp stribohIdlAstIdentifierNode.cpp stribohIdlAstInterfaceListNode.cpp stribohIdlAstInterfaceListNode.hpp stribohIdlAstModuleBodyNode.cpp stribohIdlAstModuleBodyNode.hpp stribohIdlAstInterfaceNode.cpp stribohIdlAstInterfaceNode.hpp stribohIdlAstVisitor.hpp stribohIdlAstVisitorServantBackend.cpp stribohIdlAstVisitorServantBackend.hpp stribohIdlAstVisitorClientBackend.cpp stribohIdlAstVisitorClientBackend.hpp stribohBaseExceptionsFileNotFound.hpp stribohBaseExceptionsFileNotFound.cpp )
target_include_directories(striboh_idl_library PUBLIC ${STRIBOH_LIBS_INCLUDES})

add_library(striboh_base_library STATIC stribohBaseBroker.cpp stribohBaseTransportByWebSockets.cpp stribohBaseTransportByWebSockets.hpp stribohBaseBroker.cpp stribohBaseBroker.hpp stribohBaseTransportIFace.cpp stribohBaseTransportIFace.hpp stribohBaseTransportInProcess.cpp stribohBaseTransportInProcess.hpp stribohBaseInterface.cpp stribohBaseInterface.hpp stribohBaseMethod.cpp stribohBaseMethod.hpp stribohBaseMessage.cpp stribohBaseMessage.hpp stribohBaseSignature.cpp stribohBaseSignature.hpp stribohBaseBuffer.cpp stribohBaseBuffer.hpp stribohBaseBeastServer.cpp stribohBaseBeastServer.hpp stribohBaseLogIface.hpp stribohBaseLogBoostImpl.cpp stribohBaseLogBoostImpl.hpp stribohBaseBrokerIface.hpp stribohBaseBrokerIface.cpp stribohBaseServerIface.cpp stribohBaseServerIface.hpp stribohBaseUtils.cpp stribohBaseUtils.hpp stribohBaseClient.cpp stribohBaseClient.hpp stribohBaseEServerState.hpp stribohBaseMethodName.hpp stribohBaseInstanceId.hpp stribohBaseParameterList.cpp stribohBaseParameterList.hpp stribohBaseEMessageParsingError.hpp stribohBaseExceptionsInMessageParserError.cpp stribohBaseExceptionsInMessageParserError.hpp stribohBaseServantBase.cpp stribohBaseServantBase.hpp stribohBaseProxyBase.cpp stribohBaseProxyBase.hpp stribohBaseProxyBase.hpp)
target_include_directories(striboh_base_library PUBLIC ${STRIBOH_LIBS_INCLUDES} ..)

add_executable(striboh_idl_compiler stribohIdlCompiler_main.cpp stribohIdlAstErrorNode.hpp stribohIdlCompiler.cpp stribohIdlCompiler.hpp)
target_include_directories(striboh_idl_compiler PRIVATE ${CONAN_INCLUDE_DIRS_CHAISCRIPT})
target_link_libraries(striboh_idl_compiler striboh_base_library striboh_idl_library
        ${CONAN_LIBS_BOOST} ${CONAN_LIBS_FMT} pthread ${CMAKE_DL_LIBS})
target_link_directories(striboh_idl_compiler PRIVATE ${CONAN_LIB_DIRS_FMT} ${CONAN_LIB_DIRS_BOOST})

#Without this, any build libraries automatically have names "lib{x}.so"
set(CMAKE_SHARED_MODULE_PREFIX "")
# Add a shared module - modules are intended to be imported at runtime.
add_library(stribohIdl MODULE stribohIdlPyModule.cpp stribohIdlCompiler.cpp stribohIdlCompiler.hpp)
set_target_properties(stribohIdl PROPERTIES LINK_OPTIONS LINKER:-shared )
target_link_libraries(stribohIdl ${PYTHON_LIBRARIES} boost_program_options striboh_base_library striboh_idl_library
        ${CONAN_LIBS_BOOST} ${CONAN_LIBS_FMT} pthread ${CMAKE_DL_LIBS})
target_include_directories(stribohIdl PRIVATE ${CONAN_INCLUDE_DIRS_PYBIND11} ${PYTHON_INCLUDE_DIRS} ${STRIBOH_LIBS_INCLUDES})
target_link_directories(stribohIdl PRIVATE ${CONAN_LIB_DIRS_FMT} ${CONAN_LIB_DIRS_BOOST})

configure_file(striboh_idl.py ${striboh_BINARY_DIR}/bin/striboh_idl.py COPYONLY)
add_custom_target(striboh_idl.py ALL DEPENDS ${striboh_BINARY_DIR}/bin/striboh_idl.py)
add_dependencies(striboh_idl.py stribohIdl)
