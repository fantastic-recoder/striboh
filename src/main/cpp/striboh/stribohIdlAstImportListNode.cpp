//
// Created by coder.peter.grobarcik@gmail.com on 7/30/20.
//

#include "stribohIdlAstImportListNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {

            using std::string;

            const string& ImportListNode::getNodeType() const {
                static string K_NODE_TYPE("ImportListNode");
                return K_NODE_TYPE;
            }

            const BaseNode& ImportListNode::getSubNode(size_t pIdx) const {
                return (*this)[pIdx];
            }

            int ImportListNode::getSubNodeCount() const {
                return this->size();
            }
        }
    }
}