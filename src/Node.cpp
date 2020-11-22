//Autor: Anczykowski Igor

#include "Node.hpp"

#include <utility>

Node::Node(std::string name, std::string description, std::vector<std::string> aliases) : name(std::move(
        name)), description(std::move(description)), aliases(std::move(aliases)) {}
void Node::setName(const std::string &name) {
    this->name = name;
}
void Node::setDescription(const std::string &description) {
    this->description = description;
}
void Node::setAliases(const std::vector<std::string> &aliases) {
    this->aliases = aliases;
}
const std::string &Node::getName() const {
    return this->name;
}
const std::string &Node::getDescription() const {
    return this->description;
}
const std::vector<std::string> &Node::getAliases() const {
    return this->aliases;
}
void Node::addAlias(const std::string &alias) {
    this->aliases.push_back(alias);
}
void Node::removeAlias(const std::string &alias) {
    for(unsigned i=0; i<this->aliases.size(); i++){
        if(this->aliases[i] == alias) this->aliases.erase(this->aliases.begin() + i);
    }
}
