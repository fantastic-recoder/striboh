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
            struct ImportNode : BaseNode {
                std::string mFilename;

                ImportNode() {}

                ImportNode(const std::string& pFilename)
                        : mFilename(pFilename) {}

                const std::string& getNodeType() const override;

                const std::string& getFilename() const {
                    return mFilename;
                }

                const std::string& getValue() const override {
                    return getFilename();
                }
            };
        }
    }
}


#endif //STRIBOH_ASTNODEIMPORT_HPP
