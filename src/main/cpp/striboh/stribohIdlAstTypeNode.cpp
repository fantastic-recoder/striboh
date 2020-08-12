//
// Created by grobap on 7/31/20.
//

#include "stribohIdlAstTypeNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {
            using std::string;

            const std::string& ast::TypeNode::getNodeType() const {
                static string K_NODE_TYPE("TypeNode");
                return K_NODE_TYPE;
            }

            const std::string& TypeNode::getValue() const {
                return toString(getType());
            }
        }
    }
}