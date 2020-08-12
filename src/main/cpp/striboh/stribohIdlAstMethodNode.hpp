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
            struct MethodNode : BaseNode, std::vector<TypedIdentifierNode> {
                const std::string&
                getNodeType() const override;

                const std::string&
                getValue() const override;

                virtual int
                getSubNodeCount() const override;

                virtual const BaseNode&
                getSubNode(size_t pIdx) const override;

            };
        }
    }
}

#endif //STRIBOH_STRIBOHIDLASTMETHODNODE_HPP
