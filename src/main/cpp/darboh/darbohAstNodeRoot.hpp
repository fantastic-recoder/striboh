//
// Created by grobap on 7/19/20.
//

#ifndef STRIBOH_DARBOHASTNODEROOT_HPP
#define STRIBOH_DARBOHASTNODEROOT_HPP

#include <vector>
#include <string>

#include "darbohAstNodeImport.hpp"

namespace striboh {
    namespace darboh {

        class AstNodeImport;

        class AstNodeRoot : public std::vector<AstNodeImport> {
            std::vector<std::string> mErrors;
        public:
            const std::vector <std::string> &getErrors() const {
                return mErrors;
            }

            std::vector <std::string> &getErrors() {
                return mErrors;
            }

            void pushBackError( const std::string& pError ) {
                mErrors.push_back(pError);
            }

            bool hasErrors() const { return !mErrors.empty(); }

            void mergeSubtree( const AstNodeRoot& pSubtree );
        };

        std::ostream &operator<<(std::ostream &, const AstNodeRoot &);
    }
}
#endif //STRIBOH_DARBOHASTNODEROOT_HPP
