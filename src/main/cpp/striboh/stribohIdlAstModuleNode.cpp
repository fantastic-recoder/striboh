//
// Created by coder.peter.grobarcik@gmail.com on 7/24/20.
//

#include "stribohIdlAstModuleNode.hpp"

const std::string& striboh::idl::ast::ModuleNode::getNodeType() const {
    static std::string K_NODE_TYPE("ModuleNode");
    return K_NODE_TYPE;
}

