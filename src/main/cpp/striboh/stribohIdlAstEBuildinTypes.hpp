//
// Created by coder.peter.grobarcik@gmail.com on 7/25/20.
//

#ifndef STRIBOH_STRIBOHIDLASTEBUILDINTYPES_HPP
#define STRIBOH_STRIBOHIDLASTEBUILDINTYPES_HPP

#include <string>

namespace striboh {
    namespace idl {
        namespace ast {
            enum struct EBuildinTypes {
                K_INT,
                K_STRING,
                K_VOID,
                K_NONE_TYPE
            };

            const std::string& toString(const EBuildinTypes pType);
        } // ast
    } // idl
} // striboh

#endif //STRIBOH_STRIBOHIDLASTEBUILDINTYPES_HPP
