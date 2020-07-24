//
// Created by grobap on 7/18/20.
//

#ifndef STRIBOH_DARBOHPARSER_HPP
#define STRIBOH_DARBOHPARSER_HPP

#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include "darbohAstNodeRoot.hpp"

namespace striboh{
        namespace darboh {

            using Includes = std::vector<std::string>;

            AstNodeRoot parseIdl(const Includes &pIncludes, const boost::filesystem::path&, const std::string &pInputFile) noexcept;
        }
} // end namespace striboh

#endif //STRIBOH_DARBOHPARSER_HPP
