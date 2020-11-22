//Autor: Anczykowski Igor

#ifndef METHOD_DEVELOPMENT_VISUALIZER_BACKEND_NODE_HPP
#define METHOD_DEVELOPMENT_VISUALIZER_BACKEND_NODE_HPP


#include <string>
#include <vector>
#include <memory>

class Node {
    std::string name;
    std::string description;
    std::vector<std::string> aliases;
    std::vector<std::shared_ptr<Node>> children;
public:
    explicit Node(std::string name, std::string description="", std::vector<std::string> aliases = std::vector<std::string>());
    void addAlias(const std::string &alias);
    void removeAlias(const std::string &alias);
    void addChild(const std::shared_ptr<Node>& node);
    void removeChild(const std::string &nodeName);
    // Getters
    const std::string &getName() const;
    const std::string &getDescription() const;
    const std::vector<std::string> &getAliases() const;
    const std::vector<std::shared_ptr<Node>> &getChildren() const;
    // Setters
    void setName(const std::string &name);
    void setDescription(const std::string &description);
    void setAliases(const std::vector<std::string> &aliases);
    void setChildren(const std::vector<std::shared_ptr<Node>> &children);
};


#endif //METHOD_DEVELOPMENT_VISUALIZER_BACKEND_NODE_HPP
