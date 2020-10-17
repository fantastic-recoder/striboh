//
// Created by grobap on 8/14/20.
//

#ifndef STRIBOH_STRIBOHIDLASTINTERFACENODE_HPP
#define STRIBOH_STRIBOHIDLASTINTERFACENODE_HPP

#include <string>
#include "stribohIdlAstBaseNode.hpp"
#include "stribohIdlAstIdentifierNode.hpp"
#include "stribohIdlAstMethodNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {

            constexpr const char *const K_INTERFACE_NODE = "InterfaceNode";

            struct InterfaceNode : public BaseValueNode<std::string> {
                InterfaceNode()
                        : BaseValueNode<std::string>(K_INTERFACE_NODE) {}

                InterfaceNode(const InterfaceNode& pOther);

                InterfaceNode(InterfaceNode&& pOther);

                InterfaceNode(const IdentifierNode& pIdent);

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

                const std::vector<MethodNode>& getMethods() const {
                    return mMethods;
                }

                std::vector<MethodNode>& getMethods() {
                    return mMethods;
                }

                virtual std::string
                getValueStr() const {
                    return getValue();
                }

                const std::string &getName() const;

            private:
                std::vector<MethodNode> mMethods;
            };

            InterfaceNode& operator+=(InterfaceNode& pInterfaceNode, const IdentifierNode& pIdentifier);

            InterfaceNode& operator+=(InterfaceNode& pInterfaceNode, const MethodNode& pMethod);

        }
    }
}

#endif //STRIBOH_STRIBOHIDLASTINTERFACENODE_HPP
