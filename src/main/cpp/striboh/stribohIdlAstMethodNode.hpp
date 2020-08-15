//
// Created by coder.peter.grobarcik@gmail.com on 7/25/20.
//

#ifndef STRIBOH_STRIBOHIDLASTMETHODNODE_HPP
#define STRIBOH_STRIBOHIDLASTMETHODNODE_HPP

#include <vector>

#include "stribohIdlAstBaseNode.hpp"
#include "stribohIdlAstTypedIdentifierNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {

            constexpr const char *const K_METHOD_NODE = "MethodNode";

            struct MethodNode : BaseListNode<TypedIdentifierNode> {
                MethodNode() : BaseListNode<TypedIdentifierNode>(K_METHOD_NODE) {}
            };
        }
    }
}

#endif //STRIBOH_STRIBOHIDLASTMETHODNODE_HPP
