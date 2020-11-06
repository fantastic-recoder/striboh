//
// Created by grobap on 09.09.20.
//

#ifndef STRIBOH_STRIBOHBASEMETHOD_HPP
#define STRIBOH_STRIBOHBASEMETHOD_HPP

#include <string>
#include "stribohBaseParameters.hpp"

namespace striboh {
    namespace base {

        class Broker;

        class Context {
        public:
            Context( Broker& pBroker): mBroker(pBroker) {}
            Broker& getBroker() { return mBroker; }
            const Broker& getBroker() const { return mBroker; }
        private:
            Broker& mBroker;
        };

        class Method {
        public:
            typedef InvocationMessage(*MethodGlue_t)(const InvocationMessage&, Context ) ;

            explicit Method(std::string pName, ParameterList pParameters, MethodGlue_t pImplementation )
            : mName(pName), mImplementation(pImplementation)
            {}

            const std::string &getName() const {
                return mName;
            }

            InvocationMessage invoke(const InvocationMessage& pIns, Context pCtx) {
                if(mImplementation)
                    return mImplementation(pIns,pCtx);
                return InvocationMessage(EInvocationType::K_RETURN);
            }
        private:
            const std::string mName;
            MethodGlue_t mImplementation;
        };

    }
}


#endif //STRIBOH_STRIBOHBASEMETHOD_HPP
