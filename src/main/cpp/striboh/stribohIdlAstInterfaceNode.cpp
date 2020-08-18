//
// Created by grobap on 8/14/20.
//

#include <iostream>
#include "stribohIdlAstInterfaceNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {

            InterfaceNode::InterfaceNode(const IdentifierNode& pIdent)
                    : BaseValueNode<std::string>(K_INTERFACE_NODE, pIdent.getValue()) {
                BOOST_LOG_TRIVIAL(trace) << "Creating interface \"" << pIdent << "\".";
            }

            InterfaceNode::InterfaceNode(const InterfaceNode& pOther)
                    : BaseValueNode<std::string>(K_INTERFACE_NODE, pOther.getValue()), mMethods(pOther.mMethods) {
            }

            InterfaceNode::InterfaceNode(InterfaceNode&& pOther)
                    : BaseValueNode<std::string>(K_INTERFACE_NODE, pOther.getValue()), mMethods(pOther.mMethods) {
            }


            InterfaceNode& operator+=(InterfaceNode& pInterfaceNode, const IdentifierNode& pNode) {
                pInterfaceNode.setValue(pNode.getValue());
                BOOST_LOG_TRIVIAL(trace) << "Parsed interface \"" << pInterfaceNode.getIdentifierStr() << "\".";
                return pInterfaceNode;
            }

            InterfaceNode& operator+=(InterfaceNode& pInterfaceNode, const MethodNode& pMethod) {
                pInterfaceNode.getMethods().push_back(pMethod);
                BOOST_LOG_TRIVIAL(trace) << "Parsed method \"" << pInterfaceNode.getMethods().back().getValueStr()
                                         << "\".";
                return pInterfaceNode;
            }


        }
    }
};
