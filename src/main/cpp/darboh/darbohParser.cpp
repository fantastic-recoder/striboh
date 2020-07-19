//
// Created by grobap on 7/18/20.
//

#include "darbohParser.hpp"
/*=============================================================================
    Copyright (c) 2001-2010 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
///////////////////////////////////////////////////////////////////////////////
//
//  A mini XML-like parser
//
//  [ JDG March 25, 2007 ]   spirit2
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/foreach.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace striboh {
    namespace darboh {

        using std::string;
        using std::vector;
        using std::cout;
        using std::endl;
        using std::ostream;

        namespace fusion = boost::fusion;
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;
        namespace ascii = boost::spirit::ascii;

        struct AstNode : public vector<AstNode>{
            std::string mName;                           // tag name

            AstNode() {}

            AstNode(const string& pNodeName) : mName(pNodeName) {
            }

            AstNode(const vector<AstNode>& pChildren) : vector<AstNode>(pChildren) {
            }

            AstNode(string::const_iterator pBegin,string::const_iterator pEnd)  : mName(pBegin,pEnd){
            }

            void insert(std::vector<AstNode>::iterator pIt, const char& pC) {
                pIt->mName.push_back(pC);
            }

            void insert(vector<AstNode>::iterator pWhere, const AstNode& pWhat) {
                vector<AstNode>::insert(pWhere,pWhat);
            }

            void insert(vector<AstNode>::iterator pWhere, const string& pWhat) {
                vector<AstNode>::insert(pWhere,AstNode(pWhat));
            }
        };

        ostream& operator << ( ostream& pCout, const AstNode& pNode ) {
            pCout << "Name:\"" << pNode.mName << "\"";
        }

        void processImport( const std::vector<char> pIn) {
            cout << "Import: " << string(pIn.begin(),pIn.end()) << endl;
        }

        template <typename Iterator>
        struct DarbohGrammar : qi::grammar<Iterator, AstNode(), ascii::space_type>
        {

            DarbohGrammar() : DarbohGrammar::base_type(idl)
            {
                using qi::lit;
                using qi::lexeme;
                using ascii::char_;
                using ascii::string;
                using namespace qi::labels;

                using phoenix::at_c;
                using phoenix::push_back;

                quoted_file_name = lexeme['"' >> (+(char_ - '"'))[&processImport] >> '"'];

                import = lit("import")  >> quoted_file_name;

                idl = (*import) /*>> body*/;
            }

            qi::rule<Iterator, AstNode(), ascii::space_type> idl;
            qi::rule<Iterator, vector<string>(), ascii::space_type> import;
            qi::rule<Iterator, string(), ascii::space_type> quoted_file_name;
        }; // end DarbohGrammar

        /**
         * Parse the supplied input file.
         * @param pIncludes vector of include directories.
         * @param pInputFile file to parse.
         * @return
         */
        PreprocessedInput parseIdl(const vector<string>& pIncludes, const string &pInputFile) noexcept {
            PreprocessedInput myRetVal;
            using boost::spirit::ascii::space;
            std::string::const_iterator myIter = pInputFile.begin();
            std::string::const_iterator myEnd = pInputFile.end();
            AstNode myIdlDoc;
            DarbohGrammar<std::string::const_iterator> myIdlGrammar;
            bool r = phrase_parse(myIter, myEnd, myIdlGrammar, space, myIdlDoc);

            if (r && myIter == myEnd)
            {
                std::cout << "-------------------------\n";
                std::cout << "Parsing succeeded\n";
                std::cout << "-------------------------\n";
                //client::mini_xml_printer printer;
                //printer(ast);
            }
            else
            {
                std::string::const_iterator some = myIter + std::min(30, int(myEnd - myIter));
                std::string context(myIter, (some>myEnd)?myEnd:some);
                std::cout << "-------------------------\n";
                std::cout << "Parsing failed\n";
                std::cout << "stopped at: \"" << context << "...\"\n";
                std::cout << "-------------------------\n";
            }
            return myRetVal;
        }
    }
} // end namespace striboh