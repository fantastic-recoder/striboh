//
// Created by grobap on 09.09.20.
//

#ifndef STRIBOH_STRIBOHBASEMESSAGE_HPP
#define STRIBOH_STRIBOHBASEMESSAGE_HPP

#include <string>

namespace striboh {
    namespace base {

        class HoldInterface;
        class HoldMethod;
        class HoldParameters;

        class Message {
        public:
            Message(HoldInterface, HoldMethod, HoldParameters);
        };

    }

}


#endif //STRIBOH_STRIBOHBASEMESSAGE_HPP
