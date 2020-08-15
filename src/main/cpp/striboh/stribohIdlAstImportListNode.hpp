//
// Created by coder.peter.grobarcik@gmail.com on 7/25/20.
//

#ifndef STRIBOH_STRIBOHIDLASTIMPORTLISTNODE_HPP
#define STRIBOH_STRIBOHIDLASTIMPORTLISTNODE_HPP

#include <string>
#include <boost/fusion/adapted/struct.hpp>

#include "stribohIdlAstBaseNode.hpp"
#include "stribohIdlAstImportNode.hpp"


namespace striboh {
    namespace idl {
        namespace ast {

            constexpr const char *const K_IMPORT_LIST_NODE = "ImportListNode";

            struct ImportListNode : BaseListNode<ImportNode> {
                ImportListNode() : BaseListNode<ImportNode>(K_IMPORT_LIST_NODE) {}
            };
        }
    }
}

#endif //STRIBOH_STRIBOHIDLASTIMPORTLISTNODE_HPP
