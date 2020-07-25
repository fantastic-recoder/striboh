//
// Created by grobap on 7/25/20.
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

            };
        }
    }
}

#endif //STRIBOH_STRIBOHIDLASTTYPEDIDENTIFIERNODE_HPP
