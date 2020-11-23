//Author: Anczykowski Igor

#ifndef METHOD_DEVELOPMENT_VISUALIZER_BACKEND_TREE_HPP
#define METHOD_DEVELOPMENT_VISUALIZER_BACKEND_TREE_HPP

#include "Node.hpp"

class Tree {
    std::shared_ptr<Node> root_node;
public:
    explicit Tree(const std::shared_ptr<Node> &rootNode);
    std::shared_ptr<Node> getRootNode() const;
    std::shared_ptr<Node> findNode(const std::string &nodeName) const;
    void removeNode(const std::string &nodeName) const;
    void setRootNode(const std::shared_ptr<Node> &rootNode);
};


#endif //METHOD_DEVELOPMENT_VISUALIZER_BACKEND_TREE_HPP
