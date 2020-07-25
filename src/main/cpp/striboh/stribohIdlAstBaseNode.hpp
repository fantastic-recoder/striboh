//
// Created by grobap on 7/24/20.
//

#ifndef STRIBOH_STRIBOHIDLASTBASENODE_HPP
#define STRIBOH_STRIBOHIDLASTBASENODE_HPP

#include <iomanip>

namespace manip { struct LocationInfoPrinter; }

namespace striboh {
    namespace idl {
        namespace ast {
            struct BaseNode {
                unsigned line, column, length;

                manip::LocationInfoPrinter printLoc() const;
            };
        }
    }
}

#endif //STRIBOH_STRIBOHIDLASTBASENODE_HPP
