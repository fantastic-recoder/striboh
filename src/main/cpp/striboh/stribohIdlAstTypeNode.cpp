//
// Created by grobap on 7/31/20.
//

#include "stribohIdlAstTypeNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {
            using std::string;

            std::string TypeNode::getValueStr() const {
                return toString(getType());
            }
        }
    }
}