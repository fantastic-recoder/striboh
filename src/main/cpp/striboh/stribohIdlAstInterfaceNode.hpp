//
// Created by grobap on 8/14/20.
//

#ifndef STRIBOH_STRIBOHIDLASTINTERFACENODE_HPP
#define STRIBOH_STRIBOHIDLASTINTERFACENODE_HPP

#include <string>
#include <boost/uuid/uuid.hpp>
#include "stribohIdlAstBaseNode.hpp"
#include "stribohIdlAstIdentifierNode.hpp"
#include "stribohIdlAstMethodNode.hpp"

namespace striboh {
    namespace idl {
        namespace ast {

            constexpr const char *const K_INTERFACE_NODE = "InterfaceNode";

            struct InterfaceNode : public BaseValueNode<std::string> {
            private:
                std::vector<MethodNode> mMethods;
                boost::uuids::uuid      mUuid;
            public:
                InterfaceNode();

                InterfaceNode(const InterfaceNode& pOther)  = default;

                InterfaceNode(InterfaceNode&& pOther)  = default;

                InterfaceNode(const IdentifierNode& pIdent);

                InterfaceNode(const IdentifierNode& pIdent, const boost::uuids::uuid& pUuid);

                InterfaceNode(const IdentifierNode& pIdent, boost::uuids::uuid&& pUuid);

                InterfaceNode& operator=(InterfaceNode&& pOther) = default;

                InterfaceNode& operator=(const InterfaceNode& pOther) = default;

                const std::string getIdentifierStr() const {
                    return getValue();
                }

                const std::vector<MethodNode>& getMethods() const {
                    return mMethods;
                }

                std::vector<MethodNode>& getMethods() {
                    return mMethods;
                }

                virtual std::string_view
                getValueStr() const final {
                    return getValue();
                }

                const std::string &getName() const;

                const boost::uuids::uuid &getUuid() const {
                    return mUuid;
                }

                void setUuid(const boost::uuids::uuid &pUuid) {
                    mUuid = pUuid;
                }

                virtual std::string_view
                getNodeType() const final {
                    constexpr const char *const K_IDENTIFIER_NODE = "InterfaceNode";
                    return K_IDENTIFIER_NODE;
                }

            };

            InterfaceNode& operator+=(InterfaceNode& pInterfaceNode, const IdentifierNode& pIdentifier);

            InterfaceNode& operator+=(InterfaceNode& pInterfaceNode, const MethodNode& pMethod);

        }
    }
}

#endif //STRIBOH_STRIBOHIDLASTINTERFACENODE_HPP
