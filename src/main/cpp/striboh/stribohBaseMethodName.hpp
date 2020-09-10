//
// Created by grobap on 09.09.20.
//

#ifndef STRIBOH_STRIBOHBASEMETHODNAME_HPP
#define STRIBOH_STRIBOHBASEMETHODNAME_HPP

#include <string>

namespace striboh {
    namespace base {


        class MethodName {
            const std::string_view mName;
        public:
            explicit MethodName(std::string_view pName ):mName(pName){}
        };

    }
}


#endif //STRIBOH_STRIBOHBASEMETHODNAME_HPP
