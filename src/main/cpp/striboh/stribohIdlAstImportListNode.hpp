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
            struct ImportListNode : BaseNode, std::vector<ImportNode> {
                const std::string&
                getNodeType() const override;

                virtual int
                getSubNodeCount() const override;

                virtual const BaseNode&
                getSubNode(size_t pIdx) const override;

            };
        }
    }
}

#endif //STRIBOH_STRIBOHIDLASTIMPORTLISTNODE_HPP
