//
// Created by grobap on 7/24/20.
//

#ifndef STRIBOH_STRIBOHIDLASTMODULENODE_HPP
#define STRIBOH_STRIBOHIDLASTMODULENODE_HPP

#include <string>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/fusion/tuple.hpp>

#include "stribohIdlAstBaseNode.hpp"
#include "stribohIdlAstIdentifierNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {
            struct ModuleNode : BaseNode {
                IdentifierNode mIdentifier;

                ModuleNode() {}

                ModuleNode(const IdentifierNode& pIdent)
                        :
                        mIdentifier(pIdent) {}
            };
        }
    }
}

#endif //STRIBOH_STRIBOHIDLASTMODULENODE_HPP
