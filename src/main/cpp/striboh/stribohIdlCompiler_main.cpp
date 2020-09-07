//
// Created by coder.peter.grobarcik@gmail.com on 7/18/20.
//
#include <string>
#include <vector>
#include <iostream>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

#include "stribohIdlParser.hpp"


using std::string;
using std::vector;
using striboh::idl::ast::RootNode;

namespace po=boost::program_options;
namespace fs=boost::filesystem;

int main(int pArgc, char* pArgv[]) {
// Declare the supported options.
    po::options_description myOptDesc(fs::basename(pArgv[0])+string(" options"));
    po::positional_options_description myPosOpt;
    myPosOpt.add("input-file", -1);

    myOptDesc.add_options()
            ("help", "produce help message")
            ("include-path,I", po::value<vector<string>>(), "include directory")
            ("input-file", po::value<vector<string>>(), "input file")
            ("dump-tree,d","dump the resulting AST tree.")
            ("verbose,v", po::value<int>(), "verbose logging 0..5")
            ;
    po::variables_map myVarMap;
    po::store(po::command_line_parser (pArgc, pArgv).options(myOptDesc).positional(myPosOpt).run(), myVarMap);
    po::notify(myVarMap);

    if (myVarMap.count("verbose")) {
        auto myVerbose=myVarMap["verbose"].as< int >();
        if(myVerbose<0 || myVerbose>5) {
            BOOST_LOG_TRIVIAL(fatal) << "Verbose value " << myVerbose << " is out of range 0-5!";
            return 2;
        }
        switch(myVerbose) {
            case 0:
                boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::trace);
            break;
            case 1:
                boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::debug);
                break;
            case 2:
                boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);
                break;
            case 3:
                boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::warning);
                break;
            case 4:
                boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::error);
                break;
            case 5:
                boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::fatal);
                break;
        }
    } else {
        boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);
    }
    if (myVarMap.count("help")) {
        BOOST_LOG_TRIVIAL(info) << myOptDesc;
        return 1;
    }
    vector<string> myIncludes;
    if (myVarMap.count("include-path")) {
        myIncludes = myVarMap["include-path"].as<vector<string> >();
        BOOST_LOG_TRIVIAL(info) << "Include paths are:";
        for (auto myInclude: myIncludes) {
            BOOST_LOG_TRIVIAL(info) << myInclude;
        }
    }
    vector<RootNode> myParsedIdls;
    if (myVarMap.count("input-file"))
    {
        auto myInputs=myVarMap["input-file"].as< vector<string> >();
        for(const auto& myInput:myInputs) {
            BOOST_LOG_TRIVIAL(info) << "Processing " << myInput;
            try {
                const RootNode myParseIdl = striboh::idl::parseIdlFile(myIncludes, fs::path(myInput));
                if (!myParseIdl.hasErrors()) {
                    BOOST_LOG_TRIVIAL(info)
                        << "Parsing of \"" << myInput << "\" succeeded\n";
                    myParsedIdls.push_back(myParseIdl);
                } else {
                    for (string myError: myParseIdl.getErrors()) {
                        BOOST_LOG_TRIVIAL(error)
                            << myError << "\n";
                    }
                }
            } catch( std::exception& pExc ) {
                BOOST_LOG_TRIVIAL(fatal)
                    << "Something unexpected happened ... " << pExc.what();
            }
        }
    }
    if(myVarMap.count("dump-tree"))
    {
        for( auto& myNode:myParsedIdls) {
            BOOST_LOG_TRIVIAL(info)
                << myNode;
        }
    }
    return 0;
}
