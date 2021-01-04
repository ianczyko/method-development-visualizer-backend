//Author: Anczykowski Igor

#include "Tree.hpp"
#include <queue>

Tree::Tree(const std::shared_ptr<Node> &root_node) : root_node_(root_node) {}
std::shared_ptr<Node> Tree::getRootNode() const {
    return this->root_node_;
}
void Tree::setRootNode(const std::shared_ptr<Node> &root_node) {
    this->root_node_ = root_node;
}
std::shared_ptr<Node> Tree::findNode(const std::string &node_name) const {
    std::queue<std::shared_ptr<Node>> q;
    q.push(this->root_node_);
    while (!q.empty()) {
        // See if current node is same as x
        std::shared_ptr<Node> node = q.front();
        if (node->getName() == node_name)
            return node;
        q.pop();
        for(const auto& node_ : node->getChildren()) {
            q.push(node_);
        }
    }
    return nullptr;
}
void Tree::removeNode(const std::string &node_name) const {
    auto parent_of_searched = this->findNode(node_name)->getParent();
    if(parent_of_searched != nullptr){
        parent_of_searched->removeChild(node_name);
    }
}
