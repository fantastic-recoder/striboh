//
// Created by grobap on 8/14/20.
//

#ifndef STRIBOH_STRIBOHIDLASTINTERFACENODE_HPP
#define STRIBOH_STRIBOHIDLASTINTERFACENODE_HPP

#include "stribohIdlAstBaseNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {

            constexpr const char *const K_INTERFACE_NODE = "InterfaceNode";

            struct InterfaceNode : public BaseNode {
                InterfaceNode() : BaseNode(K_INTERFACE_NODE) {}

                InterfaceNode(const InterfaceNode&) : BaseNode(K_INTERFACE_NODE) {}

                InterfaceNode(InterfaceNode&&) : BaseNode(K_INTERFACE_NODE) {}

                InterfaceNode& operator=(InterfaceNode&&) {
                    return *this;
                }

                InterfaceNode& operator=(const InterfaceNode&) {
                    return *this;
                }

            };
        }
    }
}

#endif //STRIBOH_STRIBOHIDLASTINTERFACENODE_HPP
