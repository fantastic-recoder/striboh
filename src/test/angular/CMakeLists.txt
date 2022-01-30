set(IdlName NgServer)

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/NgServer.hpp
        COMMAND ${Python3_EXECUTABLE} ${striboh_BINARY_DIR}/bin/striboh_idl.py --backend cpp --servant --out-dir ${CMAKE_CURRENT_BINARY_DIR} --stdout ${CMAKE_CURRENT_SOURCE_DIR}/NgServer.striboh.idl
        DEPENDS ${Python3_EXECUTABLE} ${striboh_BINARY_DIR}/bin/striboh_idl.py ${striboh_BINARY_DIR}/bin/striboh_backend_cpp.py ${CMAKE_CURRENT_SOURCE_DIR}/NgServer.striboh.idl
        COMMENT "Generating code with ${Python3_EXECUTABLE} ${striboh_BINARY_DIR}/bin/striboh_idl.py --backend cpp --out-dir ${CMAKE_CURRENT_BINARY_DIR} --stdout ${CMAKE_CURRENT_SOURCE_DIR}/NgServer.striboh.idl"
)

set(TS_OUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ng-hello-world/src/app)

add_custom_command(
        OUTPUT ${TS_OUT_DIR}/ng_server.service.ts
        COMMAND ${Python3_EXECUTABLE} ${striboh_BINARY_DIR}/bin/striboh_idl.py --backend angular --client --out-dir ${TS_OUT_DIR} --stdout ${CMAKE_CURRENT_SOURCE_DIR}/NgServer.striboh.idl
        DEPENDS ${Python3_EXECUTABLE} ${striboh_BINARY_DIR}/bin/striboh_idl.py ${striboh_BINARY_DIR}/bin/striboh_backend_angular.py ${CMAKE_CURRENT_SOURCE_DIR}/NgServer.striboh.idl
        COMMENT "Generating code with ${Python3_EXECUTABLE} ${striboh_BINARY_DIR}/bin/striboh_idl.py --backend angular --out-dir ${TS_OUT_DIR} --stdout ${CMAKE_CURRENT_SOURCE_DIR}/NgServer.striboh.idl"
)

add_executable(striboh_ng_server striboh_ng_server.cpp ${CMAKE_CURRENT_BINARY_DIR}/NgServer.hpp ${TS_OUT_DIR}/ng_server.service.ts)
target_include_directories(striboh_ng_server PRIVATE ${CONAN_INCLUDE_DIRS_GTEST} ${STRIBOH_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(striboh_ng_server striboh_base_library striboh_idl_library ${STRIBOH_LIBS})
target_link_directories(striboh_ng_server PRIVATE ${CONAN_LIB_DIRS_GTEST} ${STRIBOH_LIB_DIRS})
add_dependencies(striboh_ng_server ${STRIBOH_PY_MOD})
