//
// Created by coder.peter.grobarcik@gmail.com on 7/19/20.
//

#ifndef STRIBOH_STRIBOHIDLASTROOTNODE_HPP
#define STRIBOH_STRIBOHIDLASTROOTNODE_HPP

#include <vector>
#include <string>
#include <boost/fusion/tuple.hpp>

#include "stribohIdlAstBaseNode.hpp"
#include "stribohIdlAstImportNode.hpp"
#include "stribohIdlAstImportListNode.hpp"
#include "stribohIdlAstModuleListNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {

            typedef boost::fusion::tuple<ImportListNode, ModuleListNode> RootNodeBase;

            struct RootNode : BaseNode, RootNodeBase {
                typedef ModuleNode value_type;
                std::vector<std::string> mErrors;

                const ImportListNode& getImports() const { return boost::fusion::at_c<0>(*this); }

                ImportListNode& getImports() { return boost::fusion::at_c<0>(*this); }

                const ModuleListNode& getModules() const { return boost::fusion::at_c<1>(*this); }

                ModuleListNode& getModules() { return boost::fusion::at_c<1>(*this); }

                RootNode() {}

                RootNode(const RootNodeBase& pBase) : RootNodeBase(pBase) {}

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

                const std::string&
                getNodeType() const override;

                const std::string&
                getValue() const override;

                int
                getSubNodeCount() const override;

                const BaseNode&
                getSubNode(size_t pIdx) const override;


            };

            std::ostream& operator<<(std::ostream&, const RootNode&);
        }
    }
}


#endif //STRIBOH_STRIBOHIDLASTROOTNODE_HPP
