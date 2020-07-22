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

        struct AstNodeRoot : public std::vector<AstNodeImport> {
        };

        std::ostream &operator<<(std::ostream &, const AstNodeRoot &);
    }
}
#endif //STRIBOH_DARBOHASTNODEROOT_HPP
