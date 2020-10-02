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
            typedef void(*MethodGlue_t)( const ParameterValues&, ParameterValues&, Context ) ;

            explicit Method(std::string pName, ParameterList pParameters, MethodGlue_t pImplementation )
            : mName(pName), mImplementation(pImplementation)
            {}

            const std::string &getName() const {
                return mName;
            }

            void invoke(const ParameterValues& pIns, ParameterValues& pOut, Context pCtx) {
                if(mImplementation)
                    mImplementation(pIns,pOut,pCtx);
            }
        private:
            const std::string mName;
            MethodGlue_t mImplementation;
        };

    }
}


#endif //STRIBOH_STRIBOHBASEMETHOD_HPP
