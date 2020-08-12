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

namespace striboh {
    namespace idl {
        namespace ast {
            using std::vector;
            using std::string;
            using boost::fusion::at_c;

            std::ostream& operator<<(std::ostream& pOstream, const RootNode& pNode) {
                pNode.printAstNode(0, pOstream);
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

            const std::string& RootNode::getNodeType() const {
                static string K_NODE_TYPE("RootNode");
                return K_NODE_TYPE;
            }

            const std::string& RootNode::getValue() const {
                static string K_RET_V("Root");
                return K_RET_V;
            }

            int RootNode::getSubNodeCount() const {
                return getModules().size() + getImports().size();
            }

            const BaseNode& RootNode::getSubNode(size_t pIdx) const {
                const size_t myImportListSize = getImports().size();
                if (pIdx < myImportListSize)
                    return getImports()[pIdx];
                const size_t mySize = getSubNodeCount();
                if (pIdx >= mySize) {
                    throw std::range_error(str(
                            boost::format("Index % is out of range, max is %")
                            % pIdx
                            % mySize
                                           )
                    );
                }
                return getModules()[pIdx - myImportListSize];
            }
        }
    } // end idl
} // end striboh

