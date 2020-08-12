//
// Created by coder.peter.grobarcik@gmail.com on 7/21/20.
//

#ifndef STRIBOH_ASTMODULELISTNODE_HPP
#define STRIBOH_ASTMODULELISTNODE_HPP

#include <string>
#include <boost/fusion/adapted/struct.hpp>

#include "stribohIdlAstModuleNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {
            struct ModuleListNode : BaseNode, std::vector<ModuleNode> {
                const std::string&
                getNodeType() const override;

                const std::string&
                getValue() const override;

                virtual int
                getSubNodeCount() const override;

                virtual const BaseNode&
                getSubNode(size_t pIdx) const override;

            };
        }
    }
}


#endif //STRIBOH_ASTMODULELISTNODE_HPP
