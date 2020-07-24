//
// Created by grobap on 7/24/20.
//

#ifndef STRIBOH_STRIBOHIDLASTIDENTIFIERNODE_HPP
#define STRIBOH_STRIBOHIDLASTIDENTIFIERNODE_HPP

#include <string>
#include <boost/fusion/adapted/struct.hpp>

#include "stribohIdlAstBaseNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {
            struct IdentifierNode : BaseNode {
                std::string mIdentifierName;
            };
        }
    }
}

BOOST_FUSION_ADAPT_STRUCT(striboh::idl::ast::IdentifierNode, (std::string, mIdentifierName))

#endif //STRIBOH_STRIBOHIDLASTIDENTIFIERNODE_HPP
