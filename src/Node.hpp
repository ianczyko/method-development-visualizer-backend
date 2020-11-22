//Autor: Anczykowski Igor

#ifndef METHOD_DEVELOPMENT_VISUALIZER_BACKEND_NODE_HPP
#define METHOD_DEVELOPMENT_VISUALIZER_BACKEND_NODE_HPP


#include <string>
#include <vector>

class Node {
    std::string name;
    std::string description;
    std::vector<std::string> aliases;
public:
    Node(std::string name, std::string description="", std::vector<std::string> aliases = std::vector<std::string>());
    void addAlias(const std::string &alias);
    void removeAlias(const std::string &alias);
    // Setters
    const std::string &getName() const;
    const std::string &getDescription() const;
    const std::vector<std::string> &getAliases() const;
    // Getters
    void setName(const std::string &name);
    void setDescription(const std::string &description);
    void setAliases(const std::vector<std::string> &aliases);
};


#endif //METHOD_DEVELOPMENT_VISUALIZER_BACKEND_NODE_HPP
