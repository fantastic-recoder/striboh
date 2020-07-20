//
// Created by grobap on 7/19/20.
//

#ifndef STRIBOH_DARBOHASTNODE_HPP
#define STRIBOH_DARBOHASTNODE_HPP

#include <vector>
#include <string>

namespace striboh {
    namespace darboh {

        class AstNode : public std::vector<AstNode>{
            std::string mName;                           // tag name

        public:

            const std::string& name() const noexcept  {
                return mName;
            }

            void setName( const std::string& pName) {
                mName=pName;
            }

            AstNode() noexcept {}

            AstNode(const std::string& pNodeName) : mName(pNodeName) {
            }

            AstNode(const vector<AstNode>& pChildren) : vector<AstNode>(pChildren) {
            }

            AstNode(std::string::const_iterator pBegin, std::string::const_iterator pEnd)  : mName(pBegin, pEnd){
            }

            void insert(iterator pIt, const char& pC);

            void insert(iterator pWhere, const AstNode& pWhat);

            void insert(iterator pWhere, const std::string& pWhat);

        };

        std::ostream& operator << (std::ostream& , const AstNode&  );
    }
}
#endif //STRIBOH_DARBOHASTNODE_HPP
