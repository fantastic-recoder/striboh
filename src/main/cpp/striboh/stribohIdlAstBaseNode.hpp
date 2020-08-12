//
// Created by coder.peter.grobarcik@gmail.com on 7/24/20.
//

#ifndef STRIBOH_STRIBOHIDLASTBASENODE_HPP
#define STRIBOH_STRIBOHIDLASTBASENODE_HPP

#include <iomanip>

namespace manip {
    struct LocationInfoPrinter;
}


namespace striboh {
    namespace idl {
        namespace ast {

            /**
             * Ann AST nodes derives from here.
             */
            struct BaseNode {
                unsigned line, column, length;

                manip::LocationInfoPrinter printLoc() const;

                virtual const std::string&
                getNodeType() const = 0;

                virtual const std::string&
                getValue() const;

                virtual int
                getSubNodeCount() const;

                virtual const BaseNode&
                getSubNode(size_t pIdx) const;

                void
                printAstNode(const int pIndent, std::ostream& pOstream) const;
            };

        } // ast
    } // idl
} // striboh


#endif //STRIBOH_STRIBOHIDLASTBASENODE_HPP
