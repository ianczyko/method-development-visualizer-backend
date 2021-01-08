//Author: Anczykowski Igor
#include <boost/python.hpp>
#include <utility>
#include "src/Tree.hpp"
using namespace boost::python;

class NodePy {
    std::string name_;
    std::string parent_name_;
    std::string description_;
    list aliases_;
public:
    NodePy(std::string name, std::string parent_name, std::string description, list aliases)
    :   name_(std::move(name)),
        parent_name_(std::move(parent_name)),
        description_(std::move(description)),
        aliases_(std::move(std::move(aliases)))
    {};
    explicit NodePy(const std::shared_ptr<Node> &node)
    :   name_(node->getName()),
        description_(node->getDescription()),
        aliases_()
    {
        if(node->getParent() != nullptr){
            this->parent_name_ = node->getParent()->getName();
        }
        for(const auto &alias : node->getAliases()){
            this->aliases_.append(alias);
        }
    };
    std::shared_ptr<Node> toNode(){
        auto node = std::make_shared<Node>(this->name_);
        node->setDescription(this->description_);
        for(int i=0; i<len(this->aliases_); ++i){
            std::string alias = extract<std::string>(this->aliases_[i]);
            node->addAlias(alias);
        }
        return node;
    }
    std::string getParentName() const {
        return this->parent_name_;
    }
    std::string getName() const {
        return this->name_;
    }
    std::string getDescription() const {
        return this->description_;
    }
    list getAliases() const {
        return this->aliases_;
    }
};


class TreePyManager {
    Tree tree_;
public:
    TreePyManager(): tree_(nullptr){};
    void buildTree(const list &nodes){
        for(int i=0; i<len(nodes); ++i){
            NodePy node_py = extract<NodePy>(nodes[i]);
            this->tree_.addNode(node_py.toNode(), node_py.getParentName());
        }
    }
    list getTree(){
        list tree_list;
        auto nodes = this->tree_.getAllNodes();
        for(const auto &node : nodes){
            tree_list.append(NodePy(node));
        }
        return tree_list;
    }
    NodePy findNode(const std::string& name){
        auto foundNode = this->tree_.findNode(name);
        return NodePy(foundNode);
    }
    void manualAdd(NodePy node_py){
        this->tree_.addNode(node_py.toNode(), node_py.getParentName());
    }
    void removeNode(const std::string& name){
        this->tree_.removeNode(name);
    }
};

BOOST_PYTHON_MODULE(method_development)
{
    class_<NodePy>("NodePy", init<std::string, std::string, std::string, list>())
        .def("getName", &NodePy::getName)
        .def("getDescription", &NodePy::getDescription)
        .def("getAliases", &NodePy::getAliases)
        .def("getParentName", &NodePy::getParentName)
    ;
    class_<TreePyManager>("TreePyManager")
        .def("buildTree", &TreePyManager::buildTree)
        .def("getTree", &TreePyManager::getTree)
        .def("findNode", &TreePyManager::findNode)
        .def("removeNode", &TreePyManager::removeNode)
        .def("manualAdd", &TreePyManager::manualAdd)
    ;
}