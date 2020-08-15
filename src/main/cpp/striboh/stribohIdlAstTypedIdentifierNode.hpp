//
// Created by coder.peter.grobarcik@gmail.com on 7/25/20.
//

#ifndef STRIBOH_STRIBOHIDLASTTYPEDIDENTIFIERNODE_HPP
#define STRIBOH_STRIBOHIDLASTTYPEDIDENTIFIERNODE_HPP

#include <boost/fusion/tuple.hpp>

#include "stribohIdlAstBaseNode.hpp"
#include "stribohIdlAstEBuildinTypes.hpp"
#include "stribohIdlAstIdentifierNode.hpp"
#include "stribohIdlAstTypeNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {

            struct TypedIdentifierNode : public BaseNode, public boost::fusion::tuple<EBuildinTypes, IdentifierNode> {
                TypedIdentifierNode()
                        : BaseNode("TypedIdentifierNode") {}

                TypedIdentifierNode(const TypeNode& pTypeNode)
                        : BaseNode("TypedIdentifierNode") {}

                size_t getSubNodeCount() const override {
                    return 1UL;
                }

                const BaseNode& getSubNode(size_t pIdx) const {
                    return boost::fusion::at_c<1>(*this);
                }

                TypedIdentifierNode& operator=(TypedIdentifierNode&& pIdentifierNode) {
                    boost::fusion::at_c<0>(*this) = boost::fusion::at_c<0>(pIdentifierNode);
                    boost::fusion::at_c<1>(*this) = boost::fusion::at_c<1>(pIdentifierNode);
                    return *this;
                }

                TypedIdentifierNode& operator=(const TypedIdentifierNode& pIdentifierNode) {
                    boost::fusion::at_c<0>(*this) = boost::fusion::at_c<0>(pIdentifierNode);
                    boost::fusion::at_c<1>(*this) = boost::fusion::at_c<1>(pIdentifierNode);
                    return *this;
                }

                TypedIdentifierNode(const TypedIdentifierNode& pIdentifierNode) : BaseNode(
                        pIdentifierNode.getNodeType()) {
                    boost::fusion::at_c<0>(*this) = boost::fusion::at_c<0>(pIdentifierNode);
                    boost::fusion::at_c<1>(*this) = boost::fusion::at_c<1>(pIdentifierNode);
                }

            };
        }
    }
}

#endif //STRIBOH_STRIBOHIDLASTTYPEDIDENTIFIERNODE_HPP
