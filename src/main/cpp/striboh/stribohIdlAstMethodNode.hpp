//
// Created by grobap on 7/25/20.
//

#ifndef STRIBOH_STRIBOHIDLASTMETHODNODE_HPP
#define STRIBOH_STRIBOHIDLASTMETHODNODE_HPP

#include <vector>

#include "stribohIdlAstBaseNode.hpp"
#include "stribohIdlAstTypedIdentifierNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {
            struct MethodNode : BaseNode, std::vector<TypedIdentifierNode> {
            };
        }
    }
}

#endif //STRIBOH_STRIBOHIDLASTMETHODNODE_HPP
