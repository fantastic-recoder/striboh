//
// Created by coder.peter.grobarcik@gmail.com on 7/21/20.
//

#ifndef STRIBOH_ASTNODEIMPORT_HPP
#define STRIBOH_ASTNODEIMPORT_HPP

#include <string>
#include <boost/fusion/adapted/struct.hpp>

#include "stribohIdlAstBaseNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {

            constexpr const char *const K_IMPORT_NODE = "ImportNode";

            struct ImportNode : public BaseValueNode<std::string> {

                ImportNode() : BaseValueNode<std::string>(K_IMPORT_NODE) {}

                ImportNode(const std::string& pFilename) : BaseValueNode<std::string>(K_IMPORT_NODE, pFilename) {}

                const std::string getFilename() const {
                    return getValueStr();
                }

                virtual ~ImportNode() {
                }
            };
        }
    }
}


#endif //STRIBOH_ASTNODEIMPORT_HPP
