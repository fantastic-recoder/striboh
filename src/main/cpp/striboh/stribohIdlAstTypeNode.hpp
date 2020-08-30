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
            struct TypeNode : public BaseNode {
                EBuildinTypes mBuildinType = EBuildinTypes::NONE;

                TypeNode() : BaseNode("TypeNode") {}

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
                    return *this;
                }


                std::string
                getValueStr() const override;

            };
        }
    }
}
#endif //STRIBOH_STRIBOHIDLASTTYPENODE_HPP
