//
// Created by coder.peter.grobarcik@gmail.com on 7/18/20.
//

#include "stribohIdlParser.hpp"
#include "stribohIdlAstRootNode.hpp"
#include "stribohIdlAstImportNode.hpp"
#include "stribohIdlAstIdentifierNode.hpp"
#include "stribohIdlAstModuleNode.hpp"
#include "stribohIdlAstModuleListNode.hpp"
#include "stribohIdlAstModuleBodyNode.hpp"
#include "stribohIdlAstMethodNode.hpp"
#include "stribohIdlAstTypeNode.hpp"
#include "stribohIdlAstEBuildinTypes.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/support_line_pos_iterator.hpp>
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

        namespace fusion = boost::fusion;
        namespace qi = boost::spirit::qi;
        namespace ascii = boost::spirit::ascii;
        namespace fs = boost::filesystem;
        namespace phx = boost::phoenix;

        using std::string;
        using std::vector;
        using std::ostream;
        using boost::format;
        using qi::lit;
        using qi::lexeme;
        using qi::as_string;
        using qi::alnum;
        using qi::alpha;
        using qi::on_error;
        using qi::on_success;
        using qi::fail;
        using qi::error_handler;
        using ascii::char_;
        using boost::spirit::get_line;
        using boost::spirit::get_column;
        using namespace qi::labels;

        using phx::at_c;
        using phx::push_back;


        struct error_handler_f {
            typedef qi::error_handler_result result_type;

            template<typename T1, typename T2, typename T3, typename T4>
            qi::error_handler_result operator()(T1 b, T2 e, T3 where, T4 const& what) const {
                BOOST_LOG_TRIVIAL(error) << "Error: expecting " << what << " in line " << get_line(where) << ": \n"
                                         << std::string(b, e) << "\n"
                                         << std::setw(std::distance(b, where)) << '^' << "---- here\n";
                return qi::fail;
            }
        };

        template<typename It>
        struct annotation_f {
            typedef void result_type;

            constexpr annotation_f() {
                throw std::runtime_error("annotation_f() is not defined!");
            }

            constexpr annotation_f(const It& pFirst) : mFirst(pFirst) {}

            It const mFirst;

            template<typename Val, typename First, typename Last>
            void operator()(Val& v, First f, Last l) const {
                BOOST_LOG_TRIVIAL(trace) << "annotating " << typeid(v).name() << " '" << std::string(f, l) << "'";
                do_annotate(v, f, l, mFirst);
            }

        private:
            void static do_annotate(ast::BaseNode& pNode, It pIt, It pLast, It pFirst) {
                using std::distance;
                pNode.line = get_line(pIt);
                pNode.column = get_column(pFirst, pIt);
                pNode.length = distance(pIt, pLast);
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

            IdlGrammar(Iterator pFirst) : IdlGrammar::base_type(idl),
                                          annotate(pFirst) {

                keywordInterface = lit("interface");
                keywordModule = lit("module");
                semiColon = lit(';');
                openBlock = lit('{');
                closeBlock = lit('}');
                keywordImport = lit("import");
                keywordString = lit("string");
                keywordInt = lit("int");

                identifier %= as_string[alpha >> *(alnum | char_("_"))];

                quoted_file_name %= lexeme['"' >> (+(char_ - '"')) >> '"'];

                import = keywordImport >> quoted_file_name >> semiColon;

                importList = *import;

                type = keywordString[_val = ast::EBuildinTypes::STRING] | keywordInt[_val = ast::EBuildinTypes::INT];

                typedIdentifier = type >> identifier;

                method = typedIdentifier
                        >> lit('(')
                        >> typedIdentifier >> *(lit(',') >> typedIdentifier)
                        >> lit(')')
                        >> semiColon;

                interface = keywordInterface
                        >> identifier[_val += _1]
                        >> openBlock
                        >> +(method[_val += _1])
                        >> closeBlock
                        >> semiColon;

                interfaceList %= *(interface);

                moduleBody = moduleList >> interfaceList;

                module %= keywordModule >> identifier
                                        >> openBlock
                                        >> moduleBody[_val += _1]
                                        >> closeBlock >> semiColon;

                moduleList %= *module;

                idl %= importList >> moduleList;

                on_error<fail>(idl, handler(_1, _2, _3, _4));
                on_error<fail>(import, handler(_1, _2, _3, _4));
                on_error<fail>(module, handler(_1, _2, _3, _4));
                on_error<fail>(method, handler(_1, _2, _3, _4));
                on_error<fail>(type, handler(_1, _2, _3, _4));

                auto set_location_info = annotate(_val, _1, _3);
                on_success(identifier, set_location_info);
                on_success(import, set_location_info);
                on_success(module, set_location_info);
                on_success(method, set_location_info);
                on_success(type, set_location_info);

                BOOST_SPIRIT_DEBUG_NODES((keywordInterface)(keywordModule)(semiColon)(identifier)(module)(import))

            }

            phx::function<error_handler_f> handler;
            phx::function<annotation_f<Iterator>> annotate;

            qi::rule<Iterator, ast::RootNode(), ascii::space_type> idl;
            qi::rule<Iterator, ast::ImportNode(), ascii::space_type> import;
            qi::rule<Iterator, std::string(), ascii::space_type> quoted_file_name;
            qi::rule<Iterator, ast::IdentifierNode(), ascii::space_type> identifier;
            qi::rule<Iterator, ast::ModuleNode(), ascii::space_type> module;
            qi::rule<Iterator, ast::ModuleBodyNode(), ascii::space_type> moduleBody;
            qi::rule<Iterator, ast::MethodNode(), ascii::space_type> method;
            qi::rule<Iterator, ast::TypeNode(), ascii::space_type> type;
            qi::rule<Iterator, ast::TypedIdentifierNode(), ascii::space_type> typedIdentifier;
            qi::rule<Iterator, ast::ImportListNode(), ascii::space_type> importList;
            qi::rule<Iterator, ast::ModuleListNode(), ascii::space_type> moduleList;
            qi::rule<Iterator, ast::InterfaceListNode(), ascii::space_type> interfaceList;
            qi::rule<Iterator, ast::InterfaceNode(), ascii::space_type> interface;
            qi::rule<Iterator> keywordInterface, keywordModule, semiColon, openBlock, closeBlock, keywordImport,
                    keywordString, keywordInt;


        }; // end IdlGrammar

        std::string readFile(const Includes& pIncludes, const fs::path& pInputFile, ast::RootNode& pIdlDoc) {
            auto myFilename = fs::absolute(pInputFile);
            if (!fs::exists(myFilename)) {
                pIdlDoc.pushBackError(str(format("File %s does not exists.") % myFilename));
            }
            std::ifstream myImportFileStream(myFilename.string(), std::ios::in);
            if (!myImportFileStream) {
                pIdlDoc.pushBackError(str(format("Failed to open %s.") % myFilename));
            } else {
                string myLine, myFileContent;
                while (std::getline(myImportFileStream, myLine)) {
                    myFileContent += "\n";
                    myFileContent += myLine;
                }
                return myFileContent;
            }
            return "";
        }

        bool doParse(const Includes& pIncludes, string::const_iterator& pIter, string::const_iterator& pEnd,
                     ast::RootNode& pIdlDoc) {
            using boost::spirit::ascii::space;
            const IdlGrammar<string::const_iterator> theIdlGrammar(pIter);
            const bool myParsedSuccess
                    = phrase_parse(pIter, pEnd, theIdlGrammar, space, pIdlDoc);
            if (myParsedSuccess && pIter == pEnd) {
                for (auto myImportNode : pIdlDoc.getImports()) {
                    fs::path myFilename(myImportNode.getFilename());
                    auto myImportIdl = parseIdlFile(pIncludes, myFilename);
                    pIdlDoc.mergeSubtree(myImportIdl);
                }
                return true;
            }
            return false;
        }

        ast::RootNode
        parseIdlStr(const Includes& pIncludes, const string& pInputStr) noexcept {
            string::const_iterator myIter = pInputStr.begin();
            string::const_iterator myEnd = pInputStr.end();
            ast::RootNode myIdlDoc;
            doParse(pIncludes, myIter, myEnd, myIdlDoc);
            return myIdlDoc;
        }

        ast::RootNode
        parseIdlFile(const Includes& pIncludes, const fs::path& pInputFile) noexcept {
            ast::RootNode myIdlDoc;
            string myInputFileContent = readFile(pIncludes, pInputFile, myIdlDoc);
            string::const_iterator myIter = myInputFileContent.begin();
            string::const_iterator myEnd = myInputFileContent.end();
            if (myIdlDoc.getErrors().empty()) {
                doParse(pIncludes, myIter, myEnd, myIdlDoc);
            } else {
                std::string::const_iterator some = myIter + std::min(30, int(myEnd - myIter));
                std::string context(myIter, (some > myEnd) ? myEnd : some);
                std::stringstream myErr;
                myErr << "Parsing of " << pInputFile << " failed, stopped at: \"" << context << "...\".";
                myIdlDoc.pushBackError(myErr.str());
            }
            return myIdlDoc;
        }
    }
} // end namespace striboh