//
// Created by grobap on 7/21/20.
//

#ifndef STRIBOH_ASTNODEIMPORT_HPP
#define STRIBOH_ASTNODEIMPORT_HPP

namespace striboh {
    namespace darboh {
        struct AstNodeImport {
            std::string mFilename;

            AstNodeImport(const std::string &pFilename) : mFilename(pFilename) {}

            AstNodeImport() {}

            const std::string & filename() const {
                return mFilename;
            }
        };
    }
}


#endif //STRIBOH_ASTNODEIMPORT_HPP
