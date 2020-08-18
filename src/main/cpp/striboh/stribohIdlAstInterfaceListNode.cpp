//
// Created by grobap on 8/2/20.
//

#include <iostream>
#include "stribohIdlAstInterfaceListNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {

            InterfaceListNode& operator+=(InterfaceListNode& pInterfaceListNode, const InterfaceNode& pInterfaceNode) {
                pInterfaceListNode.push_back(pInterfaceNode);
                return pInterfaceListNode;
            }
        }
    }
}

