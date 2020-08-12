//
// Created by grobap on 7/31/20.
//

#include "stribohIdlAstIdentifierNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {


            const std::string& IdentifierNode::getNodeType() const {
                static std::string K_TYPE("IdentifierNode");
                return K_TYPE;
            }
        }
    }
}