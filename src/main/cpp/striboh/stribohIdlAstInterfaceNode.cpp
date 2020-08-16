//
// Created by grobap on 8/14/20.
//

#include <iostream>
#include "stribohIdlAstInterfaceNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {

            using std::cout;
            using std::endl;

            InterfaceNode::InterfaceNode(const IdentifierNode& pIdent)
                    : BaseValueNode<std::string>(K_INTERFACE_NODE, pIdent.getValue()) {
                cout << "Creating interface \"" << pIdent << "\"." << endl;
            }

            InterfaceNode::InterfaceNode(const InterfaceNode& pOther)
                    : BaseValueNode<std::string>(K_INTERFACE_NODE, pOther.getValue()), mMethods(pOther.mMethods) {
            }

            InterfaceNode::InterfaceNode(InterfaceNode&& pOther)
                    : BaseValueNode<std::string>(K_INTERFACE_NODE, pOther.getValue()), mMethods(pOther.mMethods) {
            }


            InterfaceNode& operator+=(InterfaceNode& pInterfaceNode, const IdentifierNode& pNode) {
                pInterfaceNode.setValue(pNode.getValue());
                cout << "Parsed interface \"" << pInterfaceNode.getIdentifierStr() << "\"." << endl;
                return pInterfaceNode;
            }

            InterfaceNode& operator+=(InterfaceNode& pInterfaceNode, const MethodNode& pMethod) {
                pInterfaceNode.getMethods().push_back(pMethod);
                cout << "Parsed method \"" << pInterfaceNode.getMethods().back().getValueStr() << "\"." << endl;
                return pInterfaceNode;
            }


        }
    }
};
