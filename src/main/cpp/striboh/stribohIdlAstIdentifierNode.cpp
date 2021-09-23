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


            IdentifierNode::IdentifierNode() noexcept {
                BOOST_LOG_TRIVIAL(trace) << "Creating empty identifier";
            }

            IdentifierNode::IdentifierNode(const std::string& pIdentifierName)
                    : BaseValueNode<std::string>(pIdentifierName) {
                BOOST_LOG_TRIVIAL(trace) << "Creating identifier \"" << getValue() << "\".";
            }

        }
    }
}