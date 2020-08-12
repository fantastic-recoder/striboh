//
// Created by coder.peter.grobarcik@gmail.com on 7/25/20.
//

#ifndef STRIBOH_STRIBOHIDLASTTYPENODE_HPP
#define STRIBOH_STRIBOHIDLASTTYPENODE_HPP

#include "stribohIdlAstBaseNode.hpp"
#include "stribohIdlAstEBuildinTypes.hpp"

namespace striboh {
    namespace idl {
        namespace ast {
            struct TypeNode : BaseNode {
                EBuildinTypes mBuildinType = EBuildinTypes::NONE;

                operator const EBuildinTypes() const {
                    return mBuildinType;
                }

                EBuildinTypes& getType() {
                    return mBuildinType;
                }

                const EBuildinTypes getType() const {
                    return mBuildinType;
                }

                operator EBuildinTypes&() {
                    return mBuildinType;
                }

                TypeNode& operator=(const EBuildinTypes pType) {
                    mBuildinType = pType;
                }

                virtual const std::string&
                getNodeType() const override;

                virtual const std::string&
                getValue() const override;

            };
        }
    }
}
#endif //STRIBOH_STRIBOHIDLASTTYPENODE_HPP
