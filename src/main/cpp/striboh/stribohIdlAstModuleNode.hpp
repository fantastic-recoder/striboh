//
// Created by coder.peter.grobarcik@gmail.com on 7/24/20.
//

#ifndef STRIBOH_STRIBOHIDLASTMODULENODE_HPP
#define STRIBOH_STRIBOHIDLASTMODULENODE_HPP

#include <string>
#include <memory>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/fusion/tuple.hpp>

#include "stribohIdlAstBaseNode.hpp"
#include "stribohIdlAstIdentifierNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {

            class ModuleBodyNode;

            constexpr const char *const K_MODULE_NODE = "ModuleNode";

            struct ModuleNode : public BaseValueNode<IdentifierNode> {

                ModuleNode();

                ModuleNode(const ModuleNode& pModuleNode);

                ModuleNode(const IdentifierNode& pIdent);

                const std::string& getIdentifierStr() const;

                const ModuleBodyNode& getModuleBody() const;

                ModuleBodyNode& getModuleBody();

                void addModuleBody(const ModuleBodyNode&);

                ModuleNode& operator=(const ModuleNode&);

                virtual ~ModuleNode();

            private:
                std::unique_ptr<ModuleBodyNode> mBody;
            };

            ModuleNode& operator+=(ModuleNode&, const ModuleBodyNode&);

        }
    }
}

#endif //STRIBOH_STRIBOHIDLASTMODULENODE_HPP
