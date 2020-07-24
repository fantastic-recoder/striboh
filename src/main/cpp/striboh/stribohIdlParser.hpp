//
// Created by grobap on 7/18/20.
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

        ast::RootNode
        parseIdl(const Includes& pIncludes, const boost::filesystem::path&, const std::string& pInputFile) noexcept;
    }
} // end namespace striboh

#endif //STRIBOH_STRIBOHIDLPARSER_HPP
