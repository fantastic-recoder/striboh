//
// Created by coder.peter.grobarcik@gmail.com on 7/30/20.
//

#include "stribohIdlAstBaseNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {

            void
            BaseNode::printAstNode(const int pIndent, std::ostream& pOstream) const {
                std::string myIdent;
                for (int ii = 0; ii < pIndent; ii++) {
                    myIdent += '\t';
                }
                pOstream << myIdent << getNodeType() << ":{" << std::endl;
                pOstream << myIdent << "\tvalue:" << getValue() << std::endl;
                const size_t mySubNodeCount = getSubNodeCount();
                for (size_t myI = 0; myI < mySubNodeCount; myI++) {
                    getSubNode(myI).printAstNode(pIndent + 1, pOstream);
                }
                pOstream << myIdent << "}" << std::endl;
            }

            const std::string&
            BaseNode::getValue() const {
                static std::string K_EMPTY("**empty**");
                return K_EMPTY;
            }

            int
            BaseNode::getSubNodeCount() const {
                return 0;
            }

            const BaseNode&
            BaseNode::getSubNode(size_t pIdx) const {
                return *this;
            }

        }
    }
}
