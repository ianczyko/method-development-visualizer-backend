//Author: Anczykowski Igor

#include "Tree.hpp"
#include <queue>

Tree::Tree(const std::shared_ptr<Node> &rootNode) : root_node(rootNode) {}
std::shared_ptr<Node> Tree::getRootNode() const {
    return root_node;
}
void Tree::setRootNode(const std::shared_ptr<Node> &rootNode) {
    root_node = rootNode;
}
std::shared_ptr<Node> Tree::findNode(const std::string &nodeName) const {
    std::queue<std::shared_ptr<Node>> q;
    q.push(this->root_node);
    while (!q.empty()) {
        // See if current node is same as x
        std::shared_ptr<Node> node = q.front();
        if (node->getName() == nodeName)
            return node;
        q.pop();
        for(const auto& node_ : node->getChildren()) {
            q.push(node_);
        }
    }
    return nullptr;
}
void Tree::removeNode(const std::string &nodeName) const {
    auto parent_of_searched = this->findNode(nodeName)->getParent();
    if(parent_of_searched != nullptr){
        parent_of_searched->removeChild(nodeName);
    }
}
