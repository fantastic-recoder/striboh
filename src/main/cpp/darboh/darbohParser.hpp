//
// Created by grobap on 7/18/20.
//

#ifndef STRIBOH_DARBOHPARSER_HPP
#define STRIBOH_DARBOHPARSER_HPP

#include <string>
#include <vector>
#include "darbohAstNode.hpp"

namespace striboh{
        namespace darboh {

            using Includes = std::vector<std::string>;

            AstNode parseIdl(const Includes& pIncludes, const std::string& pInputFile) noexcept;
        }
} // end namespace striboh

#endif //STRIBOH_DARBOHPARSER_HPP
