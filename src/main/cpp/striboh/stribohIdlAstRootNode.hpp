//
// Created by grobap on 7/19/20.
//

#ifndef STRIBOH_STRIBOHIDLASTROOTNODE_HPP
#define STRIBOH_STRIBOHIDLASTROOTNODE_HPP

#include <vector>
#include <string>

#include "stribohIdlAstBaseNode.hpp"
#include "stribohIdlAstImportNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {

            class RootNode : public std::vector<ImportNode>, BaseNode {
                std::vector<std::string> mErrors;
            public:
                const std::vector<std::string>& getErrors() const {
                    return mErrors;
                }

                std::vector<std::string>& getErrors() {
                    return mErrors;
                }

                void pushBackError(const std::string& pError) {
                    mErrors.push_back(pError);
                }

                bool hasErrors() const { return !mErrors.empty(); }

                void mergeSubtree(const RootNode& pSubtree);
            };

            std::ostream& operator<<(std::ostream&, const RootNode&);
        }
    }
}
#endif //STRIBOH_STRIBOHIDLASTROOTNODE_HPP
