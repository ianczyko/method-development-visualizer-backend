//Author: Anczykowski Igor

#ifndef METHOD_DEVELOPMENT_VISUALIZER_BACKEND_NODE_HPP
#define METHOD_DEVELOPMENT_VISUALIZER_BACKEND_NODE_HPP


#include <string>
#include <vector>
#include <memory>

class Node : public std::enable_shared_from_this<Node>{
    std::string name_;
    std::string description_;
    std::vector<std::string> aliases_;
    std::vector<std::shared_ptr<Node>> children_;
    std::shared_ptr<Node> parent_;
    void setParent(std::shared_ptr<Node> parent);
public:
    explicit Node(std::string name, std::string description="", std::vector<std::string> aliases = std::vector<std::string>());
    virtual ~Node();

    // Add
    void addAlias(const std::string &alias);
    void addChild(const std::shared_ptr<Node>& node);
    // Remove
    void removeAlias(const std::string &alias);
    void removeChild(const std::string &node_name);
    // Get
    const std::string &getName() const;
    const std::string &getDescription() const;
    const std::vector<std::string> &getAliases() const;
    const std::vector<std::shared_ptr<Node>> &getChildren() const;
    const std::shared_ptr<Node> &getParent() const;
    // Set
    void setName(const std::string &name);
    void setDescription(const std::string &description);
    void setAliases(const std::vector<std::string> &aliases);
};


#endif //METHOD_DEVELOPMENT_VISUALIZER_BACKEND_NODE_HPP
