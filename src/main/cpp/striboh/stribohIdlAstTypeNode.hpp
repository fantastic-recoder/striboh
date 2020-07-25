//
// Created by grobap on 7/25/20.
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

                operator EBuildinTypes&() {
                    return mBuildinType;
                }

                TypeNode& operator=(const EBuildinTypes pType) {
                    mBuildinType = pType;
                }
            };
        }
    }
}
#endif //STRIBOH_STRIBOHIDLASTTYPENODE_HPP
