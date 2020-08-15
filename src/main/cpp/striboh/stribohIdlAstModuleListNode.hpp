//
// Created by coder.peter.grobarcik@gmail.com on 7/21/20.
//

#ifndef STRIBOH_ASTMODULELISTNODE_HPP
#define STRIBOH_ASTMODULELISTNODE_HPP

#include <string>
#include <boost/fusion/adapted/struct.hpp>

#include "stribohIdlAstModuleNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {

            static const char *const K_MODULE_LIST_NODE = "ModuleListNode";

            struct ModuleListNode : BaseListNode<ModuleNode> {
                ModuleListNode()
                        : BaseListNode<ModuleNode>(K_MODULE_LIST_NODE) {}

                ModuleListNode(const ModuleListNode& pModuleListNode)
                        : BaseListNode<ModuleNode>(K_MODULE_LIST_NODE, pModuleListNode) {}

                ModuleListNode(ModuleListNode&& pModuleListNode)
                        : BaseListNode<ModuleNode>(K_MODULE_LIST_NODE, pModuleListNode) {}

                ModuleListNode& operator=(const ModuleListNode& pModuleListNode) {
                    type_t::operator=(pModuleListNode);
                    return *this;
                }

                ModuleListNode& operator=(ModuleListNode&& pModuleListNode) {
                    type_t::operator=(pModuleListNode);
                    return *this;
                }
            };
        }
    }
}


#endif //STRIBOH_ASTMODULELISTNODE_HPP
