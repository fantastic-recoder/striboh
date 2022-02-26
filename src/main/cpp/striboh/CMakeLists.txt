message(STATUS "Python include dirs:${Python3_INCLUDE_DIRS}.")
message(STATUS "Python include libs:${Python3_LIBRARIES}.")
message(STATUS "PythonStriboh include libs:${STRIBOH_INCLUDE_DIR}.")
message(STATUS "STRIBOH_LIBS=${STRIBOH_LIBS}.")

########################################################################################################################
# Libs
########################################################################################################################
add_library(striboh_idl_library STATIC stribohIdlParser.cpp stribohIdlParser.hpp stribohIdlAstRootNode.cpp stribohIdlAstRootNode.hpp stribohIdlAstBaseNode.hpp stribohIdlAstModuleNode.cpp stribohIdlAstModuleNode.hpp stribohIdlAstIdentifierNode.hpp stribohIdlAstImportListNode.hpp stribohIdlAstMethodNode.hpp stribohIdlAstTypeNode.hpp stribohIdlAstEBuildinTypes.hpp stribohIdlAstTypedIdentifierNode.hpp stribohIdlAstNode.hpp stribohIdlAstBaseNode.cpp stribohIdlAstImportListNode.cpp stribohIdlAstMethodNode.cpp stribohIdlAstModuleListNode.cpp stribohIdlAstTypedIdentifierNode.cpp stribohIdlAstImportNode.hpp stribohIdlAstImportNode.cpp stribohIdlAstTypeNode.cpp stribohIdlAstIdentifierNode.cpp stribohIdlAstInterfaceListNode.cpp stribohIdlAstInterfaceListNode.hpp stribohIdlAstModuleBodyNode.cpp stribohIdlAstModuleBodyNode.hpp stribohIdlAstInterfaceNode.cpp stribohIdlAstInterfaceNode.hpp stribohIdlAstVisitor.hpp stribohBaseExceptionsFileNotFound.hpp stribohBaseExceptionsFileNotFound.cpp stribohIdlEGenerateParts.hpp)
target_include_directories(striboh_idl_library PUBLIC ${STRIBOH_INCLUDE_DIRS} ) # ${CONAN_INCLUDE_DIRS_PYBIND11}
target_link_libraries(striboh_idl_library ${STRIBOH_LIBS})
target_link_directories(striboh_idl_library PUBLIC ${STRIBOH_LIB_DIRS})

add_library(striboh_base_library STATIC stribohBaseBroker.cpp stribohBaseTransportByWebSockets.cpp stribohBaseTransportByWebSockets.hpp stribohBaseBroker.cpp stribohBaseBroker.hpp stribohBaseTransportIFace.cpp stribohBaseTransportIFace.hpp stribohBaseTransportInProcess.cpp stribohBaseTransportInProcess.hpp stribohBaseInterface.cpp stribohBaseInterface.hpp stribohBaseMethod.cpp stribohBaseMethod.hpp stribohBaseMessage.cpp stribohBaseMessage.hpp stribohBaseSignature.cpp stribohBaseSignature.hpp stribohBaseBuffer.cpp stribohBaseBuffer.hpp stribohBaseBeastServer.cpp stribohBaseBeastServer.hpp stribohBaseLogIface.hpp stribohBaseLogBoostImpl.cpp stribohBaseLogBoostImpl.hpp stribohBaseBrokerIface.hpp stribohBaseBrokerIface.cpp stribohBaseServerIface.cpp stribohBaseServerIface.hpp stribohBaseUtils.cpp stribohBaseUtils.hpp stribohBaseClient.cpp stribohBaseClient.hpp stribohBaseEBrokerState.hpp stribohBaseMethodName.hpp stribohBaseInstanceId.hpp stribohBaseParameterList.cpp stribohBaseParameterList.hpp stribohBaseEMessageParsingError.hpp stribohBaseExceptionsInMessageParserError.cpp stribohBaseExceptionsInMessageParserError.hpp stribohBaseServantBase.cpp stribohBaseServantBase.hpp stribohBaseProxyBase.cpp stribohBaseProxyBase.hpp stribohBaseProxyBase.hpp stribohBaseAddress.cpp stribohBaseAddress.hpp stribohBase.hpp stribohBaseResolvedResult.hpp)
target_include_directories(striboh_base_library PUBLIC ${STRIBOH_INCLUDE_DIRS} ${CONAN_INCLUDE_DIRS_MSGPACK} ${CONAN_INCLUDE_DIRS_SML} ${CONAN_INCLUDE_DIRS_TAOCPP-PEGTL})
target_link_libraries(striboh_base_library ${STRIBOH_LIBS})
target_link_directories(striboh_base_library PUBLIC ${STRIBOH_LIB_DIRS})

########################################################################################################################
# IDL Backends
########################################################################################################################
configure_file(striboh_backend_cpp.py ${striboh_BINARY_DIR}/bin/striboh_backend_cpp.py COPYONLY)
configure_file(striboh_backend_angular.py ${striboh_BINARY_DIR}/bin/striboh_backend_angular.py COPYONLY)

########################################################################################################################
# Frontend
########################################################################################################################
configure_file(striboh_idl.py ${striboh_BINARY_DIR}/bin/striboh_idl.py)

set(striboh_idl_python_scripts ${striboh_BINARY_DIR}/bin/striboh_backend_cpp.py ${striboh_BINARY_DIR}/bin/striboh_backend_angular.py)

########################################################################################################################
# Striboh Python module
########################################################################################################################
# Without this, any build libraries automatically have names "lib{x}.so"
set(CMAKE_SHARED_MODULE_PREFIX "")
set(STRIBOH_IDL_COMPILER_SRCS stribohIdlPyModule.cpp stribohIdlCompiler.cpp stribohIdlCompiler.hpp)
# Add a shared module - modules are intended to be imported at runtime.
pybind11_add_module(${STRIBOH_PY_MOD} MODULE ${STRIBOH_IDL_COMPILER_SRCS} ${striboh_idl_python_scripts})
target_include_directories(${STRIBOH_PY_MOD} PRIVATE ${STRIBOH_INCLUDE_DIRS})
target_link_libraries(${STRIBOH_PY_MOD} PUBLIC ${Python3_LIBRARIES} striboh_base_library striboh_idl_library
        ${STRIBOH_LIBS} pybind11::module pybind11::windows_extras)

target_link_directories(${STRIBOH_PY_MOD} PRIVATE ${STRIBOH_LIB_DIRS} ${Python3_LIBRARY_DIRS} ${CONAN_LIB_DIRS_FMT})

########################################################################################################################
# Striboh Python embedded interpreter
########################################################################################################################
add_executable(striboh_python stribohIdlPyMain.cpp ${STRIBOH_IDL_COMPILER_SRCS})
target_include_directories(striboh_python PRIVATE ${STRIBOH_INCLUDE_DIRS})
target_link_libraries(striboh_python ${Python3_LIBRARIES} striboh_base_library striboh_idl_library ${STRIBOH_LIBS})
target_link_directories(${STRIBOH_PY_MOD} PRIVATE ${STRIBOH_LIB_DIRS} ${Python3_LIBRARY_DIRS} ${CONAN_LIB_DIRS_FMT})

########################################################################################################################
# Python end
########################################################################################################################
