//
// Created by coder.peter.grobarcik@gmail.com on 7/18/20.
//
#include <gtest/gtest.h>

#include <string>
#include <iostream>
#include <striboh/stribohIdlParser.hpp>
#include <striboh/stribohIdlAstModuleBodyNode.hpp>

namespace {
    static const char *K_TST_IDL_MOD00 = R"K_TST_IDL(
module myFirstModule {
};
)K_TST_IDL";

    static const char *K_TST_IDL_MOD01 = R"K_TST_IDL(
module m0 {
   module m1 {
      module m2 {
      };
   };
};
)K_TST_IDL";

}

using namespace striboh::idl;
using std::cerr;
using std::endl;
using std::string;

TEST(stribohIdlTests, testModule) {
    Includes myIncludes;
    auto myIdlAst = parseIdlStr(myIncludes, K_TST_IDL_MOD00);
    for (int myCnt = 0; myCnt < myIdlAst.getErrors().size(); myCnt++) {
        cerr << myIdlAst.getErrors()[myCnt] << endl;
    }
    EXPECT_EQ(0, myIdlAst.getErrors().size());
    EXPECT_EQ(1, myIdlAst.getModules().size());
    EXPECT_EQ(string("myFirstModule"), myIdlAst.getModules()[0].getIdentifierStr());
    EXPECT_EQ(1, myIdlAst.getModules().size());
}

TEST(stribohIdlTests, testNestedModules) {
    Includes myIncludes;
    auto myIdlAst = parseIdlStr(myIncludes, K_TST_IDL_MOD01);
    for (int myCnt = 0; myCnt < myIdlAst.getErrors().size(); myCnt++) {
        cerr << myIdlAst.getErrors()[myCnt] << endl;
    }
    EXPECT_EQ(0, myIdlAst.getErrors().size());
    EXPECT_EQ(1, myIdlAst.getModules().size());
    const ast::ModuleNode& myM0ModuleNode = myIdlAst.getModules()[0];
    EXPECT_EQ(string("m0"), myM0ModuleNode.getIdentifierStr());
    EXPECT_EQ(1, myM0ModuleNode.getModuleBody().getNodules().size());
    const ast::ModuleNode& myM1ModuleNode = myM0ModuleNode.getModuleBody().getNodules()[0];
    EXPECT_EQ(string("m1"), myM1ModuleNode.getIdentifierStr());
    const ast::ModuleNode& myM2ModuleNode = myM1ModuleNode.getModuleBody().getNodules()[0];
    EXPECT_EQ(string("m2"), myM2ModuleNode.getIdentifierStr());
}
