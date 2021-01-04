//Author: Anczykowski Igor

#ifndef METHOD_DEVELOPMENT_VISUALIZER_BACKEND_TREE_HPP
#define METHOD_DEVELOPMENT_VISUALIZER_BACKEND_TREE_HPP

#include "Node.hpp"

class Tree {
    std::shared_ptr<Node> root_node_;
public:
    explicit Tree(const std::shared_ptr<Node> &root_node);
    std::shared_ptr<Node> getRootNode() const;
    std::shared_ptr<Node> findNode(const std::string &node_name) const;
    void removeNode(const std::string &node_name) const;
    void setRootNode(const std::shared_ptr<Node> &root_node);
};


#endif //METHOD_DEVELOPMENT_VISUALIZER_BACKEND_TREE_HPP
