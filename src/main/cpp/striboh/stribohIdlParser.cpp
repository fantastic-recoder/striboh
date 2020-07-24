//
// Created by grobap on 7/18/20.
//

#include "stribohIdlParser.hpp"
#include "stribohIdlAstRootNode.hpp"
#include "stribohIdlAstImportNode.hpp"
#include "stribohIdlAstIdentifierNode.hpp"

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
    namespace idl {

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

        struct error_handler_f {
            typedef qi::error_handler_result result_type;

            template<typename T1, typename T2, typename T3, typename T4>
            qi::error_handler_result operator()(T1 b, T2 e, T3 where, T4 const& what) const {
                std::cerr << "Error: expecting " << what << " in line " << get_line(where) << ": \n"
                          << std::string(b, e) << "\n"
                          << std::setw(std::distance(b, where)) << '^' << "---- here\n";
                return qi::fail;
            }
        };

        template<typename It>
        struct annotation_f {
            typedef void result_type;

            annotation_f(It first) : first(first) {}

            It const first;

            template<typename Val, typename First, typename Last>
            void operator()(Val& v, First f, Last l) const {
                std::cerr << "\nannotating " << typeid(v).name() << " '" << std::string(f, l) << "'\n";
                do_annotate(v, f, l, first);
            }

        private:
            void static do_annotate(ast::BaseNode& li, It f, It l, It first) {
                using std::distance;
                li.line = get_line(f);
                li.column = get_column(first, f);
                li.length = distance(f, l);
            }

            static void do_annotate(...) { std::cerr << "(not having LocationInfo)\n"; }
        };

        /**
         * @see http://coliru.stacked-crooked.com/a/b69dcdf4c5a81715
         *
         * @tparam Iterator
         */
        template<typename Iterator>
        struct IdlGrammar : qi::grammar<Iterator, ast::RootNode(), ascii::space_type> {

            IdlGrammar() : IdlGrammar::base_type(idl) {
                using qi::lit;
                using qi::lexeme;
                using qi::as_string;
                using qi::alnum;
                using qi::alpha;
                using ascii::char_;
                using ascii::string;
                using namespace qi::labels;

                using phoenix::at_c;
                using phoenix::push_back;

                KeywordInterface = lit("interface");
                KeywordModule = lit("module");
                SemiColon = lit(';');

                Identifier = as_string[alpha >> *(alnum | char_("_"))];

                quoted_file_name %= lexeme['"' >> (+(char_ - '"')) >> '"'];

                import %= lit("import") >> quoted_file_name;

                idl %= (*import) /*>> body*/;
            }

            qi::rule<Iterator, ast::RootNode(), ascii::space_type> idl;
            qi::rule<Iterator, ast::ImportNode(), ascii::space_type> import;
            qi::rule<Iterator, string(), ascii::space_type> quoted_file_name;
            qi::rule<Iterator, ast::IdentifierNode()> Identifier;
            qi::rule<Iterator> KeywordInterface, KeywordModule, SemiColon;
/*
            on_error<fail>(ast::ModuleNode, handler(_1, _2, _3, _4));
            on_error<fail>(ast::ImportNode, handler(_1, _2, _3, _4));

            auto set_location_info = annotate(_val, _1, _3);
            on_success(ast::IdentifierNode,    set_location_info);
            on_success(ast::ImportNode, set_location_info);
            on_success(ast::ModuleNode,    set_location_info);

            BOOST_SPIRIT_DEBUG_NODES((KeywordInterface)(KeywordModule)(SemiColon)(Identifier))
*/
        }; // end IdlGrammar

        static const IdlGrammar<std::string::const_iterator> theIdlGrammar;

        /**
         * Parse the supplied input file.
         * @param pIncludes vector of include directories.
         * @param pInputFile file to parse.
         * @return
         */
        ast::RootNode parseIdl(const vector<string>& pIncludes, const fs::path& pInputFile,
                               const string& pInputFileContens) noexcept {
            using boost::spirit::ascii::space;
            std::string::const_iterator myIter = pInputFileContens.begin();
            std::string::const_iterator myEnd = pInputFileContens.end();
            ast::RootNode myIdlDoc;
            const bool myParsedSuccess
                    = phrase_parse(myIter, myEnd, theIdlGrammar, space, myIdlDoc);
            if (myParsedSuccess && myIter == myEnd) {
                for (auto myImportNode : myIdlDoc) {
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