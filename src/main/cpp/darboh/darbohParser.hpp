//
// Created by grobap on 7/18/20.
//

#ifndef STRIBOH_DARBOHPARSER_HPP
#define STRIBOH_DARBOHPARSER_HPP

#include <string>
#include <vector>

namespace striboh{
        namespace darboh {

            class AstNode;

            AstNode &parse(const std::string &pIdlCode);

            struct PreprocessedInput {
                std::string mInput;
            };

            using Includes = std::vector<std::string>;

            PreprocessedInput
            parseIdl(const Includes& pIncludes, const std::string& pInputFile) noexcept;
        }
} // end namespace striboh

#endif //STRIBOH_DARBOHPARSER_HPP
