//
// Created by coder.peter.grobarcik@gmail.com on 7/24/20.
//

#ifndef STRIBOH_STRIBOHIDLASTIDENTIFIERNODE_HPP
#define STRIBOH_STRIBOHIDLASTIDENTIFIERNODE_HPP

#include<string>
#include <boost/fusion/adapted/struct.hpp>

#include "stribohIdlAstBaseNode.hpp"


namespace striboh {
    namespace idl {
        namespace ast {
            constexpr const char *const K_IDENTIFIER_NODE = "IdentifierNode";

            struct IdentifierNode : BaseValueNode<std::string> {

                IdentifierNode();

                explicit IdentifierNode(const std::string& pIdentifierName);

                virtual size_t size() const {
                    return 1L;
                }

            };

            inline std::ostream& operator<<(std::ostream& pOstream, const IdentifierNode& pNode) {
                pOstream << pNode.getValue();
                return pOstream;
            }

        }
    }
}

#endif //STRIBOH_STRIBOHIDLASTIDENTIFIERNODE_HPP
