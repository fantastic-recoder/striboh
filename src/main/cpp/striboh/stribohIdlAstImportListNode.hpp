//
// Created by grobap on 7/25/20.
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
            struct ImportListNode : BaseNode, std::vector<ImportNode> {
            };
        }
    }
}

#endif //STRIBOH_STRIBOHIDLASTIMPORTLISTNODE_HPP
