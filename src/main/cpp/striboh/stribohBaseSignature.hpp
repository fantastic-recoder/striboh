//
// Created by grobap on 10.09.20.
//

#ifndef STRIBOH_STRIBOHBASESIGNATURE_HPP
#define STRIBOH_STRIBOHBASESIGNATURE_HPP

namespace striboh {
    namespace base {

        /**
         * Operation direction
         */
        enum class EDir {
            K_IN, ///< input parameter
            K_OUT ///< output parameter
        };

        enum class ETypes {
            K_STRING = 10,
            K_INT    = 12
        };

        class InterfaceName;
        class MethodName;
        class ParameterList;

        class Signature {
        public:
            Signature(const InterfaceName& , const MethodName&, const ParameterList& );
        };
    }
}


#endif //STRIBOH_STRIBOHBASESIGNATURE_HPP
