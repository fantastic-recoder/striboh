//
// Created by grobap on 03.10.20.
//

#ifndef STRIBOH_STRIBOHBASENAMETREENODE_HPP
#define STRIBOH_STRIBOHBASENAMETREENODE_HPP

class NameTreeNode {
public:
    typedef std::vector<NameTreeNode> ChildNodes_t;

    NameTreeNode() = default;

    explicit NameTreeNode(const std::string pName ):mName(pName) {}

    const std::string &getName() const {
        return mName;
    }

    void setName(const std::string &pName) {
        mName = pName;
    }

    const std::vector<NameTreeNode> &getChildNodes() const {
        return mChildNodes;
    }

    std::vector<NameTreeNode> & getChildNodes() {
        return mChildNodes;
    }

    void setChildNodes(const std::vector<NameTreeNode> &pChildNodes) {
        mChildNodes = pChildNodes;
    }

private:
    ChildNodes_t mChildNodes;
    std::string mName;
};

#endif //STRIBOH_STRIBOHBASENAMETREENODE_HPP
