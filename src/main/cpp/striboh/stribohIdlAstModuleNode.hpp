//
// Created by grobap on 7/24/20.
//

#ifndef STRIBOH_STRIBOHIDLASTMODULENODE_HPP
#define STRIBOH_STRIBOHIDLASTMODULENODE_HPP

#include <string>
#include <boost/fusion/adapted/struct.hpp>

#include "stribohIdlAstBaseNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {
            struct ModuleNode : public BaseNode {
                std::string mModuleName;
            };
        }
    }
}

BOOST_FUSION_ADAPT_STRUCT(striboh::idl::ast::ModuleNode, (std::string, mModuleName))

#endif //STRIBOH_STRIBOHIDLASTMODULENODE_HPP
