//
// Created by grobap on 7/18/20.
//

#include "darbohParser.hpp"
#include "darbohAstNodeRoot.hpp"
#include "darbohAstNodeImport.hpp"

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
#include <algorithm>

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

        template <typename Iterator>
        struct DarbohGrammar : qi::grammar<Iterator, AstNodeRoot(), ascii::space_type> {

            DarbohGrammar() : DarbohGrammar::base_type(idl) {
                using qi::lit;
                using qi::lexeme;
                using ascii::char_;
                using ascii::string;
                using namespace qi::labels;

                using phoenix::at_c;
                using phoenix::push_back;

                quoted_file_name %= lexeme['"' >> (+(char_ - '"')) >> '"'];

                import %= lit("import") >> quoted_file_name;

                idl %= (*import) /*>> body*/;
            }

            qi::rule<Iterator, AstNodeRoot(), ascii::space_type> idl;
            qi::rule<Iterator, AstNodeImport(), ascii::space_type> import;
            qi::rule<Iterator, string(), ascii::space_type> quoted_file_name;
        }; // end DarbohGrammar

        /**
         * Parse the supplied input file.
         * @param pIncludes vector of include directories.
         * @param pInputFile file to parse.
         * @return
         */
        AstNodeRoot parseIdl(const vector<string> &pIncludes, const string &pInputFile) noexcept {
            using boost::spirit::ascii::space;
            std::string::const_iterator myIter = pInputFile.begin();
            std::string::const_iterator myEnd = pInputFile.end();
            AstNodeRoot myIdlDoc;
            DarbohGrammar<std::string::const_iterator> myIdlGrammar;
            bool r = phrase_parse(myIter, myEnd, myIdlGrammar, space, myIdlDoc);

            if (r && myIter == myEnd) {
                std::cout << "-------------------------\n";
                std::cout << "Parsing succeeded\n";
                std::cout << "-------------------------\n";
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
            return myIdlDoc;
        }
    }
} // end namespace striboh