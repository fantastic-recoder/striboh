//
// Created by coder.peter.grobarcik@gmail.com on 7/18/20.
//
#include <string>
#include <vector>
#include <iostream>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include "stribohIdlParser.hpp"


using std::string;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;
using striboh::idl::ast::RootNode;

namespace po=boost::program_options;
namespace fs=boost::filesystem;

int main(int pArgc, char* pArgv[]) {
// Declare the supported options.
    po::options_description myOptDesc("Darboh options");
    po::positional_options_description myPosOpt;
    myPosOpt.add("input-file", -1);

    myOptDesc.add_options()
            ("help", "produce help message")
            ("include-path,I", po::value<vector<string>>(), "include directory")
            ("input-file", po::value<vector<string>>(), "input file")
            ("dump-tree,d","dump the resulting AST tree.")
            ;
    po::variables_map myVarMap;
    po::store(po::command_line_parser (pArgc, pArgv).options(myOptDesc).positional(myPosOpt).run(), myVarMap);
    po::notify(myVarMap);

    if (myVarMap.count("help")) {
        cout << myOptDesc << "\n";
        return 1;
    }
    vector<string> myIncludes;
    if (myVarMap.count("include-path"))
    {
        myIncludes = myVarMap["include-path"].as< vector<string> >();
        cout << "Include paths are:\n";
        for( auto myInclude: myIncludes) {
            cout << myInclude << "\n";
        }
    }
    vector<RootNode> myParsedIdls;
    if (myVarMap.count("input-file"))
    {
        auto myInputs=myVarMap["input-file"].as< vector<string> >();
        for(const auto& myInput:myInputs) {
            cout << "Processing " << myInput << "\n";
            try {
                const RootNode myParseIdl = striboh::idl::parseIdlFile(myIncludes, fs::path(myInput));
                if (!myParseIdl.hasErrors()) {
                    std::cout << "-------------------------\n";
                    std::cout << "Parsing of \"" << myInput << "\" succeeded\n";
                    std::cout << "-------------------------\n";
                    myParsedIdls.push_back(myParseIdl);
                } else {
                    for (string myError: myParseIdl.getErrors()) {
                        cerr << "-------------------------\n";
                        cerr << myError << endl;
                        cerr << "-------------------------\n";
                    }
                }
            } catch( std::exception& pExc ) {
                cerr << "Something unexpected happened ... " << pExc.what() << endl;
            }
        }
    }
    if(myVarMap.count("dump-tree"))
    {
        for( auto& myNode:myParsedIdls) {
            cout << myNode;
        }
    }
    return 0;
}
