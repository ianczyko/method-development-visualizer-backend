//Author: Anczykowski Igor

#ifndef METHOD_DEVELOPMENT_VISUALIZER_BACKEND_TREE_H
#define METHOD_DEVELOPMENT_VISUALIZER_BACKEND_TREE_H

#include "Node.h"

/// Tree class that implements required Tree algorithms on the Tree structure.
/// @author Igor Anczykowski
class Tree {
    std::shared_ptr<Node> root_node_;
public:
    explicit Tree(const std::shared_ptr<Node> &root_node);
    std::shared_ptr<Node> getRootNode() const;
    std::shared_ptr<Node> findNode(const std::string &node_name) const;
    void removeNode(const std::string &node_name) const;
    void setRootNode(const std::shared_ptr<Node> &root_node);
    void addNode(const std::shared_ptr<Node> &node, const std::string &parent_name);
    void addNodeAuto(const std::shared_ptr<Node> &node);
    std::vector<std::shared_ptr<Node>> getAllNodes();
};


#endif //METHOD_DEVELOPMENT_VISUALIZER_BACKEND_TREE_H
