//
// Created by coder.peter.grobarcik@gmail.com on 7/19/20.
//

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <boost/foreach.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/format.hpp>
#include "stribohIdlParser.hpp"
#include "stribohIdlAstRootNode.hpp"
#include "stribohIdlAstImportNode.hpp"

namespace {
    static const std::string K_ROOT_VAL = "<root>";
}

namespace striboh {
    namespace idl {
        namespace ast {
            using std::vector;
            using std::string;
            using boost::fusion::at_c;

            std::ostream& operator<<(std::ostream& pOstream, const RootNode& pNode) {
                pNode.printAstNode(0, pOstream);
                return pOstream;
            }

            void RootNode::mergeSubtree(const RootNode& pSubtree) {
                getErrors().insert(getErrors().begin(),
                                   pSubtree.getErrors().begin(),
                                   pSubtree.getErrors().end());
                getImports().insert(getImports().begin(),
                                    pSubtree.getImports().begin(),
                                    pSubtree.getImports().end());
                getModules().insert(getModules().begin(),
                                    pSubtree.getModules().begin(),
                                    pSubtree.getModules().end());
            }

            std::string RootNode::getValueStr() const {
                return K_ROOT_VAL;
            }

        }
    } // end idl
} // end striboh

