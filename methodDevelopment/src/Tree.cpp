//Author: Anczykowski Igor

#include "Tree.hpp"
#include <queue>
#include <algorithm>

/// Constructor that initializes all the private attributes.
/// @param root_node Root node of the initialized tree.
Tree::Tree(const std::shared_ptr<Node> &root_node) : root_node_(root_node) {} //NOLINT
std::shared_ptr<Node> Tree::getRootNode() const {
    return this->root_node_;
}

/// Sets the root_node_ attribute.
/// @param root_node Root node of the initialized tree.
void Tree::setRootNode(const std::shared_ptr<Node> &root_node) {
    this->root_node_ = root_node;
}

/// Finds the node in a tree using its identifier (node_name).
///
/// This algorithm uses a Breadth-first search algorithm.
/// @param node_name Name of the Node to be found.
std::shared_ptr<Node> Tree::findNode(const std::string &node_name) const {
    std::queue<std::shared_ptr<Node>> q;
    q.push(this->root_node_);
    // BFS algorithm
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

/// Removes the node from a tree using its identifier (node_name).
///
/// This requires the findNode() method.
/// @param node_name Name of the Node to be removed.
void Tree::removeNode(const std::string &node_name) const {
    auto parent_of_searched = this->findNode(node_name)->getParent();
    if(parent_of_searched != nullptr){
        parent_of_searched->removeChild(node_name);
    }
}

/// Returns a list of Nodes from the tree.
///
/// The Nodes are ordered the same to the Breadth-first search algorithm.
std::vector<std::shared_ptr<Node>> Tree::getAllNodes() {
    std::vector<std::shared_ptr<Node>> all_nodes;
    std::queue<std::shared_ptr<Node>> q;
    q.push(this->root_node_);
    // BFS algorithm
    while (!q.empty()) {
        std::shared_ptr<Node> node = q.front();
        q.pop();
        all_nodes.push_back(node);
        for(const auto& node_ : node->getChildren()) {
            q.push(node_);
        }
    }
    return all_nodes;
}

/// Adds a Node to a tree.
///
/// This requires the findNode() method. if parent_name is empty, then it sets node as root.
/// @param node Node object to be added.
/// @param parent_name Name of the parent of the node to be added.
void Tree::addNode(const std::shared_ptr<Node> &node, const std::string &parent_name) {
    if(parent_name.empty()){
        this->setRootNode(node);
        return;
    }
    auto parent = this->findNode(parent_name);
    parent->addChild(node);
}

/// Adds a Node to a tree automatically without considering its parent_name_ attribute.
///
/// todo: more info.
/// @param node Node object to be added.
void Tree::addNodeAuto(const std::shared_ptr<Node> &node) {
    const auto & nodes = this->getAllNodes();
    auto parent = *std::max_element( nodes.begin(), nodes.end(),
        [&node](const std::shared_ptr<Node> &a, const std::shared_ptr<Node> &b) {
            int a_score = a->rateNameSimilarity(node);
            int b_score = b->rateNameSimilarity(node);
            if(a_score == b_score) return a->getNameCleaned().length() > b->getNameCleaned().length();
            return a_score < b_score;
        });
    node->setParent(parent);
    parent->addChild(node);
}
