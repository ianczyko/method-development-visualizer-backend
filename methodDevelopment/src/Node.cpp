//Author: Anczykowski Igor

#include "Node.hpp"

#include <utility>

Node::Node(std::string name, std::string description, std::vector<std::string> aliases) : name_(std::move(
        name)), description_(std::move(description)), aliases_(std::move(aliases)) {}
void Node::setName(const std::string &name) {
    this->name_ = name;
}
void Node::setDescription(const std::string &description) {
    this->description_ = description;
}
void Node::setAliases(const std::vector<std::string> &aliases) {
    this->aliases_ = aliases;
}
void Node::setParent(std::shared_ptr<Node> parent) {
    this->parent_ = std::move(parent);
}
const std::string &Node::getName() const {
    return this->name_;
}
const std::string &Node::getDescription() const {
    return this->description_;
}
const std::vector<std::string> &Node::getAliases() const {
    return this->aliases_;
}
const std::vector<std::shared_ptr<Node>> &Node::getChildren() const {
    return this->children_;
}
const std::shared_ptr<Node> &Node::getParent() const {
    return this->parent_;
}
void Node::addAlias(const std::string &alias) {
    this->aliases_.push_back(alias);
}
void Node::removeAlias(const std::string &alias) {
    for(unsigned i=0; i<this->aliases_.size(); i++){
        if(this->aliases_[i] == alias) this->aliases_.erase(this->aliases_.begin() + i);
    }
}
void Node::addChild(const std::shared_ptr<Node>& node) {
    node->setParent(shared_from_this());
    this->children_.push_back(node);
}
void Node::removeChild(const std::string &nodeName) {
    for(unsigned i=0; i<this->children_.size(); i++){
        if(this->children_[i]->getName() == nodeName) this->children_.erase(this->children_.begin() + i);
    }
}
Node::~Node() = default;


