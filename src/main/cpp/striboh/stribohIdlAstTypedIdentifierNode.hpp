//
// Created by coder.peter.grobarcik@gmail.com on 7/25/20.
//

#ifndef STRIBOH_STRIBOHIDLASTTYPEDIDENTIFIERNODE_HPP
#define STRIBOH_STRIBOHIDLASTTYPEDIDENTIFIERNODE_HPP

#include <boost/fusion/tuple.hpp>

#include "stribohIdlAstBaseNode.hpp"
#include "stribohIdlAstEBuildinTypes.hpp"
#include "stribohIdlAstIdentifierNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {
            typedef boost::fusion::tuple<EBuildinTypes, IdentifierNode> TypedIdentifierBase;

            struct TypedIdentifierNode : BaseNode, TypedIdentifierBase {

                const std::string&
                getNodeType() const override;

                const std::string&
                getValue() const override;

                int
                getSubNodeCount() const override;

                const BaseNode&
                getSubNode(size_t pIdx) const override;

            };
        }
    }
}

#endif //STRIBOH_STRIBOHIDLASTTYPEDIDENTIFIERNODE_HPP
