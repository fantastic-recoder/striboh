//
// Created by coder.peter.grobarcik@gmail.com on 7/24/20.
//

#ifndef STRIBOH_STRIBOHIDLASTIDENTIFIERNODE_HPP
#define STRIBOH_STRIBOHIDLASTIDENTIFIERNODE_HPP

#include <string>
#include <boost/fusion/adapted/struct.hpp>

#include "stribohIdlAstBaseNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {
            struct IdentifierNode : BaseNode {

                IdentifierNode() {}

                IdentifierNode(const std::string& pIdentifierName)
                        : mIdentifierName(pIdentifierName) {}

                const std::string& getNodeType() const override;

                const std::string& getValue() const override {
                    return mIdentifierName;
                }

                std::string mIdentifierName;
            };
        }
    }
}

#endif //STRIBOH_STRIBOHIDLASTIDENTIFIERNODE_HPP
