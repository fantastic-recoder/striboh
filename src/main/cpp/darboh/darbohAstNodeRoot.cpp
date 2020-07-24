//
// Created by grobap on 7/19/20.
//

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <boost/foreach.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/config/warning_disable.hpp>
#include "darbohParser.hpp"
#include "darbohAstNodeRoot.hpp"
#include "darbohAstNodeImport.hpp"

namespace {
    inline void
    printAstNode(const int pIndent, const striboh::darboh::AstNodeImport &pNode2Print, std::ostream &pOstream) {
        std::string myIdent;
        for (int ii = 0; ii < pIndent; ii++) {
            myIdent += '\t';
        }
        pOstream << myIdent << "AstNodeImport:{" << std::endl;
        pOstream << myIdent << "\tfilename:" << pNode2Print.mFilename << std::endl;
        pOstream << myIdent << "}" << std::endl;
    }

    inline void
    printAstNode(const int pIndent, const striboh::darboh::AstNodeRoot &pNode2Print, std::ostream &pOstream) {
        std::string myIdent;
        for (int ii = 0; ii < pIndent; ii++) {
            myIdent += '\t';
        }
        pOstream << myIdent << "AstNodeRoot:{" << std::endl;
        for (const auto &myChildNode: pNode2Print) {
            printAstNode(pIndent + 1, myChildNode, pOstream);
        }
        pOstream << myIdent << "}" << std::endl;
    }


}
namespace striboh {
    namespace darboh {

        using std::vector;
        using std::string;

        std::ostream &operator<<(std::ostream &pOstream, const AstNodeRoot &pNode) {
            printAstNode(0, pNode, pOstream);
        }

        void AstNodeRoot::mergeSubtree(const AstNodeRoot &pSubtree) {
            getErrors().insert(getErrors().begin(),pSubtree.getErrors().begin(),pSubtree.getErrors().end());
        }
    } // end darboh
} // end striboh
