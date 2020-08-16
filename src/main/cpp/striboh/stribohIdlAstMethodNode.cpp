//
// Created by coder.peter.grobarcik@gmail.com on 7/30/20.
//
#include <exception>

#include "stribohIdlAstMethodNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {

            using std::runtime_error;

            const std::string& MethodNode::getMethodName() const {
                if (empty()) {
                    throw runtime_error("Empty method.");
                }
                return (*this)[0].getIdentifierName();
            }
        }
    }
}
