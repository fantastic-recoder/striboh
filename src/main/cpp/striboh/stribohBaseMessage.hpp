//
// Created by grobap on 09.09.20.
//

#ifndef STRIBOH_STRIBOHBASEMESSAGE_HPP
#define STRIBOH_STRIBOHBASEMESSAGE_HPP

#include <string>

#include "stribohBaseParameters.hpp"

namespace striboh {
    namespace base {

        class Signature;
        class ParameterValues;

        class Message {
        public:
            Message();

            Message(const Message&)=default;

            Message(Message&&)=default;

            Message(const Signature&, const ParameterValues& );

            Message& add(const ParameterValues& pValues);

        private:
            ParameterValues mValues;
        };

    }

}


#endif //STRIBOH_STRIBOHBASEMESSAGE_HPP
