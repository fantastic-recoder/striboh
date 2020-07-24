//
// Created by grobap on 7/21/20.
//

#ifndef STRIBOH_ASTNODEIMPORT_HPP
#define STRIBOH_ASTNODEIMPORT_HPP

namespace striboh {
    namespace idl {
        namespace ast {
            struct ImportNode {
                std::string mFilename;

                ImportNode(const std::string& pFilename) : mFilename(pFilename) {}

                ImportNode() {}

                const std::string& filename() const {
                    return mFilename;
                }
            };
        }
    }
}


#endif //STRIBOH_ASTNODEIMPORT_HPP
