//
// Created by coder.peter.grobarcik@gmail.com on 7/21/20.
//

#ifndef STRIBOH_IDL_AST_IMPORT_NODE
#define STRIBOH_IDL_AST_IMPORT_NODE

#include "stribohIdlAstImportNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {

            ImportNode& operator += ( ImportNode& pNode, const std::string& pFileName) {
                BOOST_LOG_TRIVIAL(debug) << "Import file " << pFileName << " parsed.";
                pNode.setValue(pFileName);
                BOOST_LOG_TRIVIAL(debug) << "ImportNode " << pNode.getFilename() << " named.";
                return pNode;
            }
        }
    }
}


#endif //STRIBOH_ASTNODEIMPORT_HPP
