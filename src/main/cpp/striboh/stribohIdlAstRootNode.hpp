//
// Created by coder.peter.grobarcik@gmail.com on 7/19/20.
//

#ifndef STRIBOH_STRIBOHIDLASTROOTNODE_HPP
#define STRIBOH_STRIBOHIDLASTROOTNODE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <boost/fusion/tuple.hpp>

#include "stribohIdlAstBaseNode.hpp"
#include "stribohIdlAstImportNode.hpp"
#include "stribohIdlAstImportListNode.hpp"
#include "stribohIdlAstModuleListNode.hpp"

#include <boost/type_index.hpp>

namespace striboh {
    namespace idl {

        struct AstVisitor;

        namespace ast {

            struct RootNode : public BaseTupleNode<ImportListNode, ModuleListNode> {
                RootNode() {}

                typedef ModuleNode value_type;
                std::vector<std::string> mErrors;

                const ImportListNode& getImports() const { return getSubNode1(); }

                ImportListNode& getImports() { return getSubNode1(); }

                const ModuleListNode& getModules() const { return getSubNode2(); }

                ModuleListNode& getModules() { return getSubNode2(); }

                const std::vector<std::string>& getErrors() const {
                    return mErrors;
                }

                std::vector<std::string>& getErrors() {
                    return mErrors;
                }

                void pushBackError(const std::string& pError) {
                    mErrors.push_back(pError);
                }

                bool hasErrors() const { return !mErrors.empty(); }

                void mergeSubtree(const RootNode& pSubtree);

                std::string_view
                getValueStr() const final;

                void visit(striboh::idl::AstVisitor &pVisitor);

                void visitModules(AstVisitor &pVisitor, const ModuleListNode &pModules) const;

                RootNode& operator += (const ModuleBodyNode& );

                RootNode& operator += (const std::vector<std::string>& );

                virtual std::string_view
                getNodeType() const final {
                    constexpr const char *const K_IDENTIFIER_NODE = "RootNode";
                    return K_IDENTIFIER_NODE;
                }
            };

            std::ostream& operator<<(std::ostream& pOstream, const RootNode& pNode) ;
        }
    }
}


#endif //STRIBOH_STRIBOHIDLASTROOTNODE_HPP
