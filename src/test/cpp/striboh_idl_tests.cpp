//
// Created by coder.peter.grobarcik@gmail.com on 7/18/20.
//
#include <gtest/gtest.h>

#include <string>
#include <iostream>
#include <striboh/stribohIdlParser.hpp>

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
    EXPECT_EQ(string("myFirstModule"), myIdlAst.getModules()[0].getValue());
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
    //TODO: Modules can have submodules EXPECT_EQ(1, myIdlAst.getModules()[0].get.size());
}
