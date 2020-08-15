//
// Created by coder.peter.grobarcik@gmail.com on 7/30/20.
//

#include <boost/fusion/tuple.hpp>

#include "stribohIdlAstTypedIdentifierNode.hpp"

namespace {
    static const std::string K_INT("INT");
    static const std::string K_STRING("STRING");
    static const std::string K_NONE("NONE");

}
namespace striboh {
    namespace idl {
        namespace ast {
            using std::vector;
            using std::string;
            using boost::fusion::at_c;

            const std::string& toString(const EBuildinTypes pType) {
                switch (pType) {
                    case EBuildinTypes::INT:
                        return K_INT;
                    case EBuildinTypes::STRING:
                        return K_STRING;
                    default:
                    case EBuildinTypes::NONE:
                        return K_NONE;
                }
            }

        }
    }
}
