//
// Created by coder.peter.grobarcik@gmail.com on 7/18/20.
//

#ifndef STRIBOH_STRIBOHIDLPARSER_HPP
#define STRIBOH_STRIBOHIDLPARSER_HPP

#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include "stribohIdlAstRootNode.hpp"

namespace striboh {
    namespace idl {

        using Includes = std::vector<std::string>;

        /**
         * Parse the supplied input file.
         * @param pIncludes vector of include directories.
         * @param pInputFile file to parse.
         * @return The parsed input file as AST tree.
         */
        ast::RootNode
        parseIdlFile(const Includes& pIncludes, const boost::filesystem::path& pInputFile) noexcept;

        /**
         * Parse the supplied string.
         * @param pIncludes vector of include directories.
         * @param pInputStr string to parse.
         * @return The parsed input string as AST tree.
         */
        ast::RootNode
        parseIdlStr(const Includes& pIncludes, const std::string& pInputStr) noexcept;
    }
} // end namespace striboh

#endif //STRIBOH_STRIBOHIDLPARSER_HPP
