//
// Created by grobap on 7/21/20.
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

                const std::string& getFilename() const {
                    return mFilename;
                }
            };
        }
    }
}

BOOST_FUSION_ADAPT_STRUCT(striboh::idl::ast::ImportNode, (std::string, mFilename))

#endif //STRIBOH_ASTNODEIMPORT_HPP
