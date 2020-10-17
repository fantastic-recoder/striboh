//
// Created by grobap on 8/2/20.
//

#ifndef STRIBOH_STRIBOHIDLASTMODULEBODYNODE_HPP
#define STRIBOH_STRIBOHIDLASTMODULEBODYNODE_HPP


#include "stribohIdlAstBaseNode.hpp"
#include "stribohIdlAstModuleListNode.hpp"
#include "stribohIdlAstInterfaceListNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {
            constexpr const char *const K_MODULE_BODY_NODE = "ModuleBodyNode";

            struct ModuleBodyNode : public BaseTupleNode<ModuleListNode, InterfaceListNode> {

                ModuleBodyNode() :
                        BaseTupleNode<ModuleListNode, InterfaceListNode>(K_MODULE_BODY_NODE) {}

                ModuleBodyNode(const ModuleBodyNode& pModuleBody) :
                        BaseTupleNode<ModuleListNode, InterfaceListNode>(K_MODULE_BODY_NODE, pModuleBody) {}

                ModuleBodyNode(const ModuleListNode& pModuleList) :
                        BaseTupleNode<ModuleListNode, InterfaceListNode>(K_MODULE_BODY_NODE, pModuleList) {
                }

                ModuleBodyNode(const InterfaceListNode& pInterfaceList) :
                        BaseTupleNode<ModuleListNode, InterfaceListNode>(K_MODULE_BODY_NODE, pInterfaceList) {
                }

                ModuleBodyNode(ModuleListNode&& pModuleList) :
                        BaseTupleNode<ModuleListNode, InterfaceListNode>(K_MODULE_BODY_NODE, pModuleList) {
                }

                ModuleBodyNode& operator=(const ModuleListNode& pModuleList) {
                    getSubNode1() = pModuleList;
                    return *this;
                }

                ModuleBodyNode& operator=(ModuleListNode&& pModuleList) {
                    getSubNode1() = pModuleList;
                    return *this;
                }

                ModuleBodyNode& operator=(ModuleBodyNode&& pModuleBody) {
                    type_t::operator=(pModuleBody);
                    return *this;
                }

                ModuleBodyNode& operator=(const ModuleBodyNode& pModuleBody) {
                    type_t::operator=(pModuleBody);
                    return *this;
                }

                ModuleListNode& getModules() {
                    return getSubNode1();
                }

                const ModuleListNode& getModules() const {
                    return getSubNode1();
                }

                const InterfaceListNode& getInterfaces() const {
                    return getSubNode2();
                }
                InterfaceListNode& getInterfaces() {
                    return getSubNode2();
                }
            };

        }
    }
}


#endif //STRIBOH_STRIBOHIDLASTMODULEBODYNODE_HPP
