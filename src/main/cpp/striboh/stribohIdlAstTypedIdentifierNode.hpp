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

                size_t getSubNodeCount() const override {
                    return 1UL;
                }

                const BaseNode& getSubNode(size_t pIdx) const {
                    return boost::fusion::at_c<1>(*this);
                }

                const std::string& getName() const {
                    return boost::fusion::at_c<1>(*this).getValue();
                }

                EBuildinTypes getType() const {
                    return boost::fusion::at_c<0>(*this);
                }

                const std::string& getTypeString() const {
                    return toString(boost::fusion::at_c<0>(*this));
                }

                virtual std::string
                getValueStr() const override {
                    return getName();
                }

            };
        }
    }
}

#endif //STRIBOH_STRIBOHIDLASTTYPEDIDENTIFIERNODE_HPP
