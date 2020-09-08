//
// Created by grobap on 08.09.20.
//

#ifndef STRIBOH_STRIBOHBASETRANSPORTIFACE_HPP
#define STRIBOH_STRIBOHBASETRANSPORTIFACE_HPP

namespace striboh {
    namespace base {
        class TransportIFace {
            void send();
        protected:
            virtual void doSend() =0;
        };

    }
}


#endif //STRIBOH_STRIBOHBASETRANSPORTIFACE_HPP
