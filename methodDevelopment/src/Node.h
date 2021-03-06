//Author: Anczykowski Igor

#ifndef METHOD_DEVELOPMENT_VISUALIZER_BACKEND_NODE_H
#define METHOD_DEVELOPMENT_VISUALIZER_BACKEND_NODE_H


#include <string>
#include <vector>
#include <memory>

/// Node class that models a single node in a Tree.
/// @author Igor Anczykowski
class Node : public std::enable_shared_from_this<Node>{
    std::string name_;
    std::string description_;
    std::vector<std::string> aliases_;
    std::vector<std::shared_ptr<Node>> children_;
    std::shared_ptr<Node> parent_;
public:
    explicit Node(std::string name, std::string description="", std::vector<std::string> aliases = std::vector<std::string>());
    virtual ~Node();
    int rateNameSimilarity(const std::shared_ptr<Node> &other_node) const;

    // Add
    void addAlias(const std::string &alias);
    void addChild(const std::shared_ptr<Node>& node);
    // Remove
    void removeAlias(const std::string &alias);
    void removeChild(const std::string &node_name);
    // Get
    std::string getNameCleaned() const;
    const std::string &getName() const;
    const std::string &getDescription() const;
    const std::vector<std::string> &getAliases() const;
    const std::vector<std::shared_ptr<Node>> &getChildren() const;
    const std::shared_ptr<Node> &getParent() const;
    // Set
    void setName(const std::string &name);
    void setDescription(const std::string &description);
    void setAliases(const std::vector<std::string> &aliases);
    void setParent(std::shared_ptr<Node> parent);
};


#endif //METHOD_DEVELOPMENT_VISUALIZER_BACKEND_NODE_H
