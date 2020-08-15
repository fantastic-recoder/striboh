//
// Created by grobap on 7/31/20.
//

#include <iostream>
#include "stribohIdlAstIdentifierNode.hpp"

using std::cout;
using std::endl;

namespace striboh {
    namespace idl {
        namespace ast {


            IdentifierNode::IdentifierNode()
                    : BaseValueNode<std::string>(K_IDENTIFIER_NODE) {
                cout << "Creating empty identifier" << endl;
            }

            IdentifierNode::IdentifierNode(const std::string& pIdentifierName)
                    : BaseValueNode<std::string>(K_IDENTIFIER_NODE, pIdentifierName) {
                cout << "Creating identifier \"" << getValue() << "\"." << endl;
            }

        }
    }
}