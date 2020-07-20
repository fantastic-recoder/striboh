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
#include "darbohAstNode.hpp"

namespace {
    void printAstNode( const int pIndent, const striboh::darboh::AstNode& pNode2Print, std::ostream& pOstream ) {
        std::string myIdent;
        for( int ii=0; ii<pIndent; ii++ ) {
            myIdent += '\t';
        }
        pOstream << myIdent << "AstNode: " << pNode2Print.name() << std::endl;
        pOstream << myIdent << "{" << std::endl;
        for( const auto & myChildNode: pNode2Print) {
            printAstNode(pIndent+1,myChildNode,pOstream);
        }
        pOstream << myIdent << "}" << std::endl;
    }

}
namespace striboh {
    namespace darboh {

        using std::vector;
        using std::string;

        void AstNode::insert(iterator pIt, const char& pC) {
            pIt->mName.push_back(pC);
        }

        void AstNode::insert(iterator pWhere, const AstNode& pWhat) {
            vector<AstNode>::insert(pWhere,pWhat);
        }
;
        void AstNode::insert(iterator pWhere, const std::__cxx11::string& pWhat) {
            vector<AstNode>::insert(pWhere,AstNode(pWhat));
        }

        std::ostream& operator << (std::ostream& pOstream, const AstNode& pNode ) {
            printAstNode(0,pNode,pOstream);
        }

    } // end darboh
} // end striboh
