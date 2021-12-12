message(STATUS "Python include dirs:${Python3_INCLUDE_DIRS}.")
message(STATUS "Python include libs:${Python3_LIBRARIES}.")

set(STRIBOH_LIBS_INCLUDES ${CONAN_INCLUDE_DIRS_NAMEDTYPE} ${CONAN_INCLUDE_DIRS_NLOHMANN_JSON}
        ${CONAN_INCLUDE_DIRS_FMT} ${CONAN_INCLUDE_DIRS_BOOST} ${Python3_INCLUDE_DIRS})

add_library(striboh_idl_library STATIC stribohIdlParser.cpp stribohIdlParser.hpp stribohIdlAstRootNode.cpp stribohIdlAstRootNode.hpp stribohIdlAstBaseNode.hpp stribohIdlAstModuleNode.cpp stribohIdlAstModuleNode.hpp stribohIdlAstIdentifierNode.hpp stribohIdlAstImportListNode.hpp stribohIdlAstMethodNode.hpp stribohIdlAstTypeNode.hpp stribohIdlAstEBuildinTypes.hpp stribohIdlAstTypedIdentifierNode.hpp stribohIdlAstNode.hpp stribohIdlAstBaseNode.cpp stribohIdlAstImportListNode.cpp stribohIdlAstMethodNode.cpp stribohIdlAstModuleListNode.cpp stribohIdlAstTypedIdentifierNode.cpp stribohIdlAstImportNode.hpp stribohIdlAstImportNode.cpp stribohIdlAstTypeNode.cpp stribohIdlAstIdentifierNode.cpp stribohIdlAstInterfaceListNode.cpp stribohIdlAstInterfaceListNode.hpp stribohIdlAstModuleBodyNode.cpp stribohIdlAstModuleBodyNode.hpp stribohIdlAstInterfaceNode.cpp stribohIdlAstInterfaceNode.hpp stribohIdlAstVisitor.hpp stribohBaseExceptionsFileNotFound.hpp stribohBaseExceptionsFileNotFound.cpp stribohIdlEGenerateParts.hpp)
target_include_directories(striboh_idl_library PUBLIC ${STRIBOH_LIBS_INCLUDES} ${CONAN_INCLUDE_DIRS_PYBIND11})

add_library(striboh_base_library STATIC stribohBaseBroker.cpp stribohBaseTransportByWebSockets.cpp stribohBaseTransportByWebSockets.hpp stribohBaseBroker.cpp stribohBaseBroker.hpp stribohBaseTransportIFace.cpp stribohBaseTransportIFace.hpp stribohBaseTransportInProcess.cpp stribohBaseTransportInProcess.hpp stribohBaseInterface.cpp stribohBaseInterface.hpp stribohBaseMethod.cpp stribohBaseMethod.hpp stribohBaseMessage.cpp stribohBaseMessage.hpp stribohBaseSignature.cpp stribohBaseSignature.hpp stribohBaseBuffer.cpp stribohBaseBuffer.hpp stribohBaseBeastServer.cpp stribohBaseBeastServer.hpp stribohBaseLogIface.hpp stribohBaseLogBoostImpl.cpp stribohBaseLogBoostImpl.hpp stribohBaseBrokerIface.hpp stribohBaseBrokerIface.cpp stribohBaseServerIface.cpp stribohBaseServerIface.hpp stribohBaseUtils.cpp stribohBaseUtils.hpp stribohBaseClient.cpp stribohBaseClient.hpp stribohBaseEServerState.hpp stribohBaseMethodName.hpp stribohBaseInstanceId.hpp stribohBaseParameterList.cpp stribohBaseParameterList.hpp stribohBaseEMessageParsingError.hpp stribohBaseExceptionsInMessageParserError.cpp stribohBaseExceptionsInMessageParserError.hpp stribohBaseServantBase.cpp stribohBaseServantBase.hpp stribohBaseProxyBase.cpp stribohBaseProxyBase.hpp stribohBaseProxyBase.hpp stribohBaseAddress.cpp stribohBaseAddress.hpp)
target_include_directories(striboh_base_library PUBLIC ${STRIBOH_LIBS_INCLUDES} ${CONAN_INCLUDE_DIRS_MSGPACK} ${CONAN_INCLUDE_DIRS_SML} ${CONAN_INCLUDE_DIRS_TAOCPP-PEGTL} ..)

# Without this, any build libraries automatically have names "lib{x}.so"
set(CMAKE_SHARED_MODULE_PREFIX "")
# Add a shared module - modules are intended to be imported at runtime.
add_library(stribohIdl MODULE stribohIdlPyModule.cpp stribohIdlCompiler.cpp stribohIdlCompiler.hpp)
set_target_properties(stribohIdl PROPERTIES LINK_OPTIONS LINKER:-shared )
target_link_libraries(stribohIdl ${PYTHON_LIBRARIES} boost_program_options striboh_base_library striboh_idl_library
        ${CONAN_LIBS_BOOST} ${CONAN_LIBS_FMT} pthread ${CMAKE_DL_LIBS})
target_include_directories(stribohIdl PRIVATE ${CONAN_INCLUDE_DIRS_PYBIND11} ${STRIBOH_LIBS_INCLUDES})
target_link_directories(stribohIdl PRIVATE ${CONAN_LIB_DIRS_FMT} ${CONAN_LIB_DIRS_BOOST})

########################################################################################################################
# Backends
########################################################################################################################
configure_file(striboh_backend_cpp.py ${striboh_BINARY_DIR}/bin/striboh_backend_cpp.py COPYONLY)
configure_file(striboh_backend_angular.py ${striboh_BINARY_DIR}/bin/striboh_backend_angular.py COPYONLY)

########################################################################################################################
# Frontend
########################################################################################################################
configure_file(striboh_idl.py ${striboh_BINARY_DIR}/bin/striboh_idl.py COPYONLY)
add_custom_target(striboh_idl.py ALL DEPENDS ${striboh_BINARY_DIR}/bin/striboh_idl.py)
add_dependencies(striboh_idl.py stribohIdl)
