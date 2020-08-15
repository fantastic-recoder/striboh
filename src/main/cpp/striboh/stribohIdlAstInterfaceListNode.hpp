//
// Created by grobap on 8/2/20.
//

#ifndef STRIBOH_STRIBOHIDLASTINTERFACELISTNODE_HPP
#define STRIBOH_STRIBOHIDLASTINTERFACELISTNODE_HPP

#include "stribohIdlAstBaseNode.hpp"
#include "stribohIdlAstInterfaceNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {
            static const char *const K_INTERFACE_LIST_NODE = "InterfaceListNode";

            struct InterfaceListNode : public BaseListNode<InterfaceNode> {

                InterfaceListNode()
                        :
                        BaseListNode<InterfaceNode>(K_INTERFACE_LIST_NODE) {}

                InterfaceListNode(const InterfaceListNode& pInterfaceListNode)
                        :
                        BaseListNode<InterfaceNode>(K_INTERFACE_LIST_NODE, pInterfaceListNode) {}

                InterfaceListNode(InterfaceListNode&& pInterfaceListNode)
                        :
                        BaseListNode<InterfaceNode>(K_INTERFACE_LIST_NODE, pInterfaceListNode) {}

                InterfaceListNode& operator=(InterfaceListNode&& pInterfaceListNode) {
                    type_t::operator=(pInterfaceListNode);
                    return *this;
                }

                InterfaceListNode& operator=(const InterfaceListNode& pInterfaceListNode) {
                    type_t::operator=(pInterfaceListNode);
                    return *this;
                }

            };

        }
    }
}


#endif //STRIBOH_STRIBOHIDLASTINTERFACELISTNODE_HPP
