//Author: Anczykowski Igor

#include "Node.hpp"

#include <utility>

/// Constructor that initializes all the private attributes.
/// @param name Name of the node to create (used internally as an identifier)
/// @param description Description of the node.
/// @param aliases A list of aliases of the node.
Node::Node(std::string name, std::string description, std::vector<std::string> aliases) : name_(std::move(
        name)), description_(std::move(description)), aliases_(std::move(aliases)) {}

/// Sets the name_ attribute.
/// @param name Name to set for the node. (used internally as an identifier)
void Node::setName(const std::string &name) {
    this->name_ = name;
}

/// Sets the description_ attribute.
/// @param description Description to set for the node.
void Node::setDescription(const std::string &description) {
    this->description_ = description;
}

/// Sets the aliases_ attribute.
/// @param aliases List of aliases to set for the node.
void Node::setAliases(const std::vector<std::string> &aliases) {
    this->aliases_ = aliases;
}

/// Sets the parent_ attribute.
/// @param parent Parent to set for the node.
void Node::setParent(std::shared_ptr<Node> parent) {
    this->parent_ = std::move(parent);
}

/// Gets the name_ attribute.
const std::string &Node::getName() const {
    return this->name_;
}

/// Gets the description_ attribute.
const std::string &Node::getDescription() const {
    return this->description_;
}

/// Gets the aliases_ attribute.
const std::vector<std::string> &Node::getAliases() const {
    return this->aliases_;
}

/// Gets the children_ attribute.
const std::vector<std::shared_ptr<Node>> &Node::getChildren() const {
    return this->children_;
}

/// Gets the parent_ attribute.
const std::shared_ptr<Node> &Node::getParent() const {
    return this->parent_;
}

/// Appends the list of aliases (aliases_).
/// @param alias Alias to append the aliases_ list.
void Node::addAlias(const std::string &alias) {
    this->aliases_.push_back(alias);
}

/// Removes an element from the list of aliases (aliases_).
/// @param alias Alias to remove from the aliases_ list.
void Node::removeAlias(const std::string &alias) {
    for(unsigned i=0; i<this->aliases_.size(); ++i){
        if(this->aliases_[i] == alias) this->aliases_.erase(this->aliases_.begin() + i);
    }
}

/// Appends the list of children (children_).
/// @param node Node to append the children_ list.
void Node::addChild(const std::shared_ptr<Node>& node) {
    node->setParent(shared_from_this());
    this->children_.push_back(node);
}

/// Removes a node from the list of children (children_).
/// @param nodeName Node to remove from the children_ list.
void Node::removeChild(const std::string &nodeName) {
    for(unsigned i=0; i<this->children_.size(); ++i){
        if(this->children_[i]->getName() == nodeName) this->children_.erase(this->children_.begin() + i);
    }
}
Node::~Node() = default;


