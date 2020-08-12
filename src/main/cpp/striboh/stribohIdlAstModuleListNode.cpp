//
// Created by coder.peter.grobarcik@gmail.com on 7/30/20.
//

#include "stribohIdlAstModuleListNode.hpp"

const std::string& striboh::idl::ast::ModuleListNode::getNodeType() const {
    static std::string K_NODE_TYPE("ModuleListNode");
    return K_NODE_TYPE;
}

const std::string& striboh::idl::ast::ModuleListNode::getValue() const {
    return BaseNode::getValue();
}

int striboh::idl::ast::ModuleListNode::getSubNodeCount() const {
    return this->size();
}

const striboh::idl::ast::BaseNode& striboh::idl::ast::ModuleListNode::getSubNode(size_t pIdx) const {
    return (*this)[pIdx];
}

