//
// Created by grobap on 7/21/20.
//

#ifndef STRIBOH_ASTMODULELISTNODE_HPP
#define STRIBOH_ASTMODULELISTNODE_HPP

#include <string>
#include <boost/fusion/adapted/struct.hpp>

#include "stribohIdlAstModuleNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {
            struct ModuleListNode : BaseNode, std::vector<ModuleNode> {
            };
        }
    }
}


#endif //STRIBOH_ASTMODULELISTNODE_HPP
