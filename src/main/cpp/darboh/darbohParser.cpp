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
#include <boost/filesystem.hpp>
#include <boost/format.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>


namespace striboh {
    namespace darboh {

        using std::string;
        using std::vector;
        using std::cout;
        using std::cerr;
        using std::endl;
        using std::ostream;
        using boost::format;

        namespace fusion = boost::fusion;
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;
        namespace ascii = boost::spirit::ascii;
        namespace fs = boost::filesystem;

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
        AstNodeRoot parseIdl(const vector<string> &pIncludes, const fs::path& pInputFile, const string &pInputFileContens) noexcept {
            using boost::spirit::ascii::space;
            DarbohGrammar<std::string::const_iterator> myIdlGrammar;
            std::string::const_iterator myIter = pInputFileContens.begin();
            std::string::const_iterator myEnd = pInputFileContens.end();
            AstNodeRoot myIdlDoc;
            const bool myParsedSuccess
                    = phrase_parse(myIter, myEnd, myIdlGrammar, space, myIdlDoc);
            if (myParsedSuccess && myIter == myEnd) {
                for( auto myImportNode : myIdlDoc) {
                    fs::path myFilename(myImportNode.filename());
                    myFilename = fs::absolute(myFilename);
                    if (! fs::exists(myFilename) ) {
                        myIdlDoc.pushBackError(str(format("File %s does not exists.")%myFilename));
                        return myIdlDoc;
                    }
                    std::ifstream myImportFileStream(myFilename.string(), std::ios::in);
                    if(!myImportFileStream) {
                        myIdlDoc.pushBackError(str(format("Failed to open %s.")%myFilename));
                    } else {
                        string myLine, myFileContens;
                        while (std::getline(myImportFileStream, myLine)) {
                            myFileContens += "\n";
                            myFileContens += myLine;
                        }
                        auto myImportIdl = parseIdl(pIncludes, myFilename, myFileContens);
                        myIdlDoc.mergeSubtree(myImportIdl);
                    }
                }
            }
            else
            {
                std::string::const_iterator some = myIter + std::min(30, int(myEnd - myIter));
                std::string context(myIter, (some>myEnd)?myEnd:some);
                std::stringstream myErr;
                myErr << "Parsing of " << pInputFile << " failed, stopped at: \"" << context << "...\".";
                myIdlDoc.pushBackError(myErr.str());
            }
            return myIdlDoc;
        }
    }
} // end namespace striboh