//
// Created by grobap on 7/18/20.
//
#include <string>
#include <vector>
#include <iostream>
#include <boost/program_options.hpp>

#include "darbohParser.hpp"

using std::string;
using std::vector;
using std::cout;

namespace po=boost::program_options;

int main(int pArgc, char* pArgv[]) {
// Declare the supported options.
    po::options_description myOptDesc("Darboh options");
    po::positional_options_description myPosOpt;
    myPosOpt.add("input-file", -1);

    myOptDesc.add_options()
            ("help", "produce help message")
            ("include-path,I", po::value<vector<string>>(), "include directory")
            ("input-file", po::value<vector<string>>(), "input file")
            ("parseIdl-only,p", po::value<bool>(),"stop right after preprocessing input.")
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
    if (myVarMap.count("input-file"))
    {
        auto myInputs=myVarMap["input-file"].as< vector<string> >();
        for(const auto& myInput:myInputs) {
            cout << "Processing " << myInput << "\n";
            striboh::darboh::parseIdl(myIncludes, "import \"" + myInput + "\"" );
        }
    }

    return 0;
}
