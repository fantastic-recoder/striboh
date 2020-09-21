//
// Created by grobap on 09.09.20.
//
#include <boost/log/trivial.hpp>

#include "stribohBaseInterfaceName.hpp"

namespace striboh {
    namespace base {
        Interface::Interface(std::initializer_list<Method> pMethodList) {
            std::copy(pMethodList.begin(),pMethodList.end(),std::back_inserter(mMethods));
            BOOST_LOG_TRIVIAL(debug) << "We have " << mMethods.size() << ".";
        }

        Interface::Methods_t::iterator
        Interface::findMethod(const std::string &pMethodName) {
            return std::find_if(mMethods.begin(),mMethods.end(), [pMethodName]( const Method& pMethod)->bool {
                if(pMethod.getName().compare(pMethodName)==0) {
                    return true;
                }
                return false;
            });
        }

        Interface::Methods_t::iterator
        Interface::end() {
            return mMethods.end();
        }

    }
}
