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

            struct InterfaceNode : public BaseValueNode<std::string> {
                InterfaceNode()
                        : BaseValueNode<std::string>(K_INTERFACE_NODE) {}

                InterfaceNode(const InterfaceNode& pOther)
                        : BaseValueNode<std::string>(K_INTERFACE_NODE, pOther.getValue()) {}

                InterfaceNode(InterfaceNode&& pOther)
                        : BaseValueNode<std::string>(K_INTERFACE_NODE, pOther.getValue()) {}

                InterfaceNode& operator=(InterfaceNode&& pOther) {
                    setValue(pOther.getValue());
                    return *this;
                }

                InterfaceNode& operator=(const InterfaceNode& pOther) {
                    setValue(pOther.getValue());
                    return *this;
                }

                const std::string getIdentifierStr() const {
                    return getValue();
                }
            };
        }
    }
}

#endif //STRIBOH_STRIBOHIDLASTINTERFACENODE_HPP
