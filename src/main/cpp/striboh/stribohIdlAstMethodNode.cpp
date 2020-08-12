//
// Created by coder.peter.grobarcik@gmail.com on 7/30/20.
//

#include <string>

#include "stribohIdlAstMethodNode.hpp"

const std::string& striboh::idl::ast::MethodNode::getNodeType() const {
    static std::string K_NODE_TYPE("MethodNode");
    return K_NODE_TYPE;
}

const std::string& striboh::idl::ast::MethodNode::getValue() const {
    return BaseNode::getValue();
}

int striboh::idl::ast::MethodNode::getSubNodeCount() const {
    return this->size();
}

const striboh::idl::ast::BaseNode& striboh::idl::ast::MethodNode::getSubNode(size_t pIdx) const {
    return (*this)[pIdx];
}
