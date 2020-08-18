//
// Created by coder.peter.grobarcik@gmail.com on 7/18/20.
//
#include <gtest/gtest.h>

#include <string>
#include <iostream>
#include <striboh/stribohIdlParser.hpp>
#include <striboh/stribohIdlAstModuleBodyNode.hpp>
#include <boost/log/trivial.hpp>

using namespace striboh::idl;
using std::endl;
using std::string;


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


    void printErrors(const ast::RootNode& myIdlAst) {
        for (int myCnt = 0; myCnt < myIdlAst.getErrors().size(); myCnt++) {
            BOOST_LOG_TRIVIAL(error) << myIdlAst.getErrors()[myCnt];
        }
    }

}

TEST(stribohIdlTests, testModule) {
    Includes myIncludes;
    auto myIdlAst = parseIdlStr(myIncludes, K_TST_IDL_MOD00);
    printErrors(myIdlAst);
    EXPECT_EQ(0, myIdlAst.getErrors().size());
    ASSERT_EQ(1, myIdlAst.getModules().size());
    EXPECT_EQ(string("myFirstModule"), myIdlAst.getModules()[0].getIdentifierStr());
    EXPECT_EQ(1, myIdlAst.getModules().size());
}

TEST(stribohIdlTests, testNestedModules) {
    Includes myIncludes;
    auto myIdlAst = parseIdlStr(myIncludes, K_TST_IDL_MOD01);
    printErrors(myIdlAst);
    EXPECT_EQ(0, myIdlAst.getErrors().size());
    ASSERT_EQ(1, myIdlAst.getModules().size());
    const ast::ModuleNode& myM0ModuleNode = myIdlAst.getModules()[0];
    EXPECT_EQ(string("m0"), myM0ModuleNode.getIdentifierStr());
    ASSERT_EQ(1, myM0ModuleNode.getModuleBody().getModules().size());
    const ast::ModuleNode& myM1ModuleNode = myM0ModuleNode.getModuleBody().getModules()[0];
    EXPECT_EQ(string("m1"), myM1ModuleNode.getIdentifierStr());
    const ast::ModuleNode& myM2ModuleNode = myM1ModuleNode.getModuleBody().getModules()[0];
    EXPECT_EQ(string("m2"), myM2ModuleNode.getIdentifierStr());
}

namespace {
    static const char *K_TST_IDL_MOD02 = R"K_TST_IDL(
module m001 {
};

module m002 {
  module m10 {
  };
};
)K_TST_IDL";

}
TEST(stribohIdlTests, testSerialModules) {
    Includes myIncludes;
    auto myIdlAst = parseIdlStr(myIncludes, K_TST_IDL_MOD02);
    printErrors(myIdlAst);
    EXPECT_EQ(0, myIdlAst.getErrors().size());
    unsigned const long mySize = myIdlAst.getModules().size();
    ASSERT_EQ(2, mySize);

    const ast::ModuleNode& myM00ModuleNode = myIdlAst.getModules()[0];
    EXPECT_EQ(string("m001"), myM00ModuleNode.getIdentifierStr());
    EXPECT_EQ(0, myM00ModuleNode.getModuleBody().getModules().size());

    const ast::ModuleNode& myM01ModuleNode = myIdlAst.getModules()[1];
    EXPECT_EQ(string("m002"), myM01ModuleNode.getIdentifierStr());
    ASSERT_EQ(1, myM01ModuleNode.getModuleBody().getModules().size());

    const ast::ModuleNode& myM10ModuleNode = myM01ModuleNode.getModuleBody().getModules()[0];
    EXPECT_EQ(string("m10"), myM10ModuleNode.getIdentifierStr());
}

namespace {
    static const char *K_TST_IDL_INT00 = R"K_TST_IDL(
module mod0 {
   module mod1 {
      interface HelloWorld {
         string echo( string p0 );
      };
   };
};
)K_TST_IDL";

}

TEST(stribohIdlTests, testHelloWorldInterface) {
    Includes myIncludes;
    auto myIdlAst = parseIdlStr(myIncludes, K_TST_IDL_INT00);
    printErrors(myIdlAst);
    EXPECT_EQ(0, myIdlAst.getErrors().size());
    unsigned const long mySize = myIdlAst.getModules().size();
    ASSERT_EQ(1, mySize);

    const ast::ModuleNode& myM0ModuleNode = myIdlAst.getModules()[0];
    EXPECT_EQ(string("mod0"), myM0ModuleNode.getIdentifierStr());
    EXPECT_EQ(1, myM0ModuleNode.getModuleBody().getModules().size());

    const ast::ModuleNode& myM1ModuleNode = myM0ModuleNode.getModuleBody().getModules()[0];
    EXPECT_EQ(string("mod1"), myM1ModuleNode.getIdentifierStr());
    EXPECT_EQ(1UL, myM1ModuleNode.getModuleBody().getInterfaces().size());
    const ast::InterfaceNode& myHelloWorldIFace = myM1ModuleNode.getModuleBody().getInterfaces()[0];
    EXPECT_EQ(string("HelloWorld"), myHelloWorldIFace.getIdentifierStr());
    ASSERT_EQ(1UL, myHelloWorldIFace.getMethods().size());

    const auto myMethod1 = myHelloWorldIFace.getMethods()[0];
    EXPECT_EQ(string("echo"), myMethod1.getMethodName());
}