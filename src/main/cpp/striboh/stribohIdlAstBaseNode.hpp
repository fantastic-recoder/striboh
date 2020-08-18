//
// Created by coder.peter.grobarcik@gmail.com on 7/24/20.
//

#ifndef STRIBOH_STRIBOHIDLASTBASENODE_HPP
#define STRIBOH_STRIBOHIDLASTBASENODE_HPP

#include <string>
#include <vector>
#include <iomanip>
#include <boost/format.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/log/trivial.hpp>

namespace manip {
    struct LocationInfoPrinter;
}


namespace striboh {
    namespace idl {
        namespace ast {

            /**
             * Ann AST nodes derives from here.
             */
            struct BaseNode {
                unsigned line, column, length;
                const std::string mNodeTypeName;

                manip::LocationInfoPrinter printLoc() const;

                BaseNode(const std::string& pName) : mNodeTypeName(pName) {
                }

                virtual const std::string&
                getNodeType() const {
                    return mNodeTypeName;
                }

                virtual std::string
                getValueStr() const;

                virtual size_t
                getSubNodeCount() const;

                virtual const BaseNode&
                getSubNode(size_t pIdx) const;

                void
                printAstNode(const int pIndent, std::ostream& pOstream) const;

                virtual ~BaseNode();

            };

            template<class TNodeValue>
            class BaseValueNode : public BaseNode {
                TNodeValue mValue;
            public:

                BaseValueNode& operator=(BaseValueNode&& pBaseValueNode) {
                    mValue = std::move(pBaseValueNode.mValue);
                    return *this;
                }

                BaseValueNode& operator=(const BaseValueNode& pBaseValueNode) {
                    mValue = pBaseValueNode.mValue;
                    return *this;
                }

                BaseValueNode(const BaseValueNode& pBaseValueNode) :
                        BaseNode(pBaseValueNode.mNodeTypeName),
                        mValue(pBaseValueNode.mValue) {}

                BaseValueNode(BaseValueNode&& pBaseValueNode) :
                        BaseNode(pBaseValueNode.mNodeTypeName),
                        mValue(pBaseValueNode.mValue) {}

                BaseValueNode(const std::string& pNodeName) :
                        BaseNode(pNodeName) {}

                BaseValueNode(const std::string& pNodeName, const TNodeValue& pSubNode) :
                        BaseNode(pNodeName), mValue(pSubNode) {}


                template<typename TVal2Str>
                std::string
                toStr(const TVal2Str& pVal2Str) const {
                    std::ostringstream oOStrStream;
                    oOStrStream << pVal2Str;
                    return oOStrStream.str();
                }

                std::string
                getValueStr() const override {
                    return toStr(mValue);
                }

                const TNodeValue&
                getValue() const {
                    return mValue;
                }

                void
                setValue(const TNodeValue& pValue) {
                    mValue = pValue;
                }

                size_t
                getSubNodeCount() const override {
                    return 0L;
                }

                const BaseNode&
                getSubNode(size_t) const override {
                    return *this;
                }

                virtual ~BaseValueNode() {
                }
            };

            template<class TNode>
            class BaseListNode : public BaseNode, public std::vector<TNode> {
            public:

                typedef std::vector<TNode> type_t;

                BaseListNode(const std::string& pTypeName)
                        : BaseNode(pTypeName) {}

                BaseListNode(const std::string& pTypeName, const std::vector<TNode>& pSubNodes)
                        : BaseNode(pTypeName), std::vector<TNode>(pSubNodes) {}

                BaseListNode(const std::string& pTypeName, std::vector<TNode>&& pSubNodes)
                        : BaseNode(pTypeName), std::vector<TNode>(pSubNodes) {}

                BaseListNode& operator=(const std::vector<TNode>& pSubNodes) {
                    std::vector<TNode>::clear();
                    insert(pSubNodes.begin(), pSubNodes.end());
                }

                size_t
                getSubNodeCount() const override {
                    return this->size();
                }

                const BaseNode&
                getSubNode(size_t pIdx) const override {
                    return (*this)[pIdx];
                }

                virtual ~BaseListNode() {}
            };

            template<class TSubNode1, class TSubNode2>
            class BaseTupleNode : public BaseNode, public boost::fusion::tuple<TSubNode1, TSubNode2> {
            public:
                typedef ::boost::fusion::tuple<TSubNode1, TSubNode2> type_t;

                BaseTupleNode(const std::string& pNodeName)
                        : BaseNode(pNodeName) {}

                BaseTupleNode(const std::string& pNodeName, const type_t& pTuple)
                        : BaseNode(pNodeName), type_t(pTuple) {}

                BaseTupleNode(const std::string& pNodeName, const TSubNode1& pSubNode1)
                        : BaseNode(pNodeName) {
                    getSubNode1() = pSubNode1;
                }

                BaseTupleNode(const std::string& pNodeName, TSubNode1&& pSubNode1)
                        : BaseNode(pNodeName), type_t(pSubNode1) {}

                BaseTupleNode(const std::string& pNodeName, const TSubNode2& pSubNode2)
                        : BaseNode(pNodeName) {
                    getSubNode2() = pSubNode2;
                }

                BaseTupleNode(const std::string& pNodeName, TSubNode2&& pSubNode2)
                        : BaseNode(pNodeName), type_t(pSubNode2) {}

                TSubNode1& getSubNode1() {
                    return boost::fusion::at_c<0>(*this);
                }

                const TSubNode1& getSubNode1() const {
                    return boost::fusion::at_c<0>(*this);
                }

                TSubNode2& getSubNode2() {
                    return boost::fusion::at_c<1>(*this);
                }

                const TSubNode2& getSubNode2() const {
                    return boost::fusion::at_c<1>(*this);
                }


                size_t getSubNodeCount() const override {
                    return getSubNode1().size() + getSubNode2().size();
                }

                const BaseNode& getSubNode(size_t pIdx) const {
                    const size_t myImportListSize = getSubNode1().size();
                    if (pIdx < myImportListSize)
                        return getSubNode1()[pIdx];
                    const size_t mySize = getSubNodeCount();
                    if (pIdx >= mySize) {
                        throw std::range_error(str(
                                boost::format("Index % is out of range, max is %")
                                % pIdx
                                % mySize
                                               )
                        );
                    }
                    return getSubNode2()[pIdx - myImportListSize];
                }
            };
        } // ast
    } // idl
} // striboh


#endif //STRIBOH_STRIBOHIDLASTBASENODE_HPP
