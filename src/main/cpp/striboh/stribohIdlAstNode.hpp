//
// Created by coder.peter.grobarcik@gmail.com on 7/25/20.
//

#ifndef STRIBOH_STRIBOHIDLASTNODE_HPP
#define STRIBOH_STRIBOHIDLASTNODE_HPP

namespace striboh {
    namespace idl {
        namespace ast {
            enum struct ENodeTypes {
                IMPORT, MODULE, INTERFACE, METHOD, IDENTIFIER, TYPE
            };

            class Node {
            public:
                Node& operator=(const ENodeTypes& pType) {
                    mType = pType;
                    return *this;
                }

            private:
                ENodeTypes mType;
            };
        }
    }
}
#endif //STRIBOH_STRIBOHIDLASTNODE_HPP
