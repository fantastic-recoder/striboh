//
// Created by grobap on 09.09.20.
//

#include "stribohBaseParameters.hpp"

namespace striboh {
    namespace base {

        ParameterList::ParameterList(std::vector<ParameterDesc>) {

        }

        void ParameterValues::unpack() {
            msgpack::unpacker myUnpacker;
            myUnpacker.reserve_buffer(mPackedBuffer.size());
            memcpy(myUnpacker.buffer(), mPackedBuffer.data(), mPackedBuffer.size());
            myUnpacker.buffer_consumed(mPackedBuffer.size());

            // now starts streaming deserialization.
            msgpack::object_handle oh;
            ETypes myType;
            bool mHasNext=myUnpacker.next(oh);
            while(mHasNext) {
                int myTypeVal=0;
                oh.get().convert(myTypeVal);
                myType = ETypes(myTypeVal);
                if (myType == ETypes::K_STRING) {
                    mHasNext = myUnpacker.next(oh);
                    unpackString(myType, oh );
                } else {
                    // skip unknown value
                    mHasNext=myUnpacker.next(oh);
                }
                mHasNext=myUnpacker.next(oh);
            };
            mIsUnpacked = true;
        }

        void ParameterValues::unpackString(const ETypes &myType, msgpack::object_handle &oh) {
            std::string myVal;
            oh.get().convert(myVal);
            mTypes.push_back(myType);
            mValues.push_back(myVal);
        }

    }
}