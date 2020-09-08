//
// Created by grobap on 08.09.20.
//

#ifndef STRIBOH_STRIBOHBASETRANSPORTBYWEBSOCKETS_HPP
#define STRIBOH_STRIBOHBASETRANSPORTBYWEBSOCKETS_HPP

#include "stribohBaseTransportIFace.hpp"

namespace striboh {
    namespace base {
        class TransportByWebSockets : public TransportIFace {
        private:
            virtual void doSend() override;
            void doAccept();
        };

    }
}


#endif //STRIBOH_STRIBOHBASETRANSPORTBYWEBSOCKETS_HPP
