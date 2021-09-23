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

                ModuleListNode &getModules() {
                    return getSubNode1();
                }

                const ModuleListNode &getModules() const {
                    return getSubNode1();
                }

                const InterfaceListNode &getInterfaces() const {
                    return getSubNode2();
                }

                InterfaceListNode &getInterfaces() {
                    return getSubNode2();
                }

                ModuleBodyNode &operator+=(const InterfaceListNode &pInterfaceList);

                ModuleBodyNode &operator+=(const ModuleListNode &pModuleListNode);

                virtual std::string_view
                getNodeType() const final {
                    constexpr const char *const K_IDENTIFIER_NODE = "InterfaceListNode";
                    return K_IDENTIFIER_NODE;
                }
            };

        }
    }
}


#endif //STRIBOH_STRIBOHIDLASTMODULEBODYNODE_HPP
