//
// Created by coder.peter.grobarcik@gmail.com on 7/21/20.
//

#ifndef STRIBOH_IDL_AST_IMPORT_NODE
#define STRIBOH_IDL_AST_IMPORT_NODE

#include "stribohIdlAstImportNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {

            const std::string& ImportNode::getNodeType() const {
                static std::string K_NODE_TYPE("ImportNode");
                return K_NODE_TYPE;
            }
        }
    }
}


#endif //STRIBOH_ASTNODEIMPORT_HPP
