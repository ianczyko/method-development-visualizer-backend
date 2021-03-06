//Author: Anczykowski Igor

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>

using namespace boost::unit_test;
using namespace boost::unit_test_framework;

#include "../src/Node.h"
#include "../src/Tree.h"
#include <iostream>

BOOST_AUTO_TEST_SUITE( Node_suite ) //NOLINT
    BOOST_AUTO_TEST_CASE( Node_creation_empty ) { //NOLINT
        Node node("SHADE");
        BOOST_REQUIRE(node.getName() == "SHADE");
        BOOST_REQUIRE(node.getDescription().empty());
        BOOST_REQUIRE(node.getAliases().empty());
    }
    BOOST_AUTO_TEST_CASE( Node_creation_desc ) { //NOLINT
        Node node("SHADE", "Description...");
        BOOST_REQUIRE(node.getName() == "SHADE");
        BOOST_REQUIRE(node.getDescription() == "Description...");
        BOOST_REQUIRE(node.getAliases().empty());
    }
    BOOST_AUTO_TEST_CASE( Node_creation_desc_and_aliases ) { //NOLINT
        std::vector<std::string> aliases;
        aliases.emplace_back("shade");
        aliases.emplace_back("Shade");
        Node node("SHADE", "Description...", aliases);
        BOOST_REQUIRE(node.getName() == "SHADE");
        BOOST_REQUIRE(node.getDescription() == "Description...");
        BOOST_REQUIRE(node.getAliases().at(0) == "shade");
        BOOST_REQUIRE(node.getAliases().at(1) == "Shade");
    }
    BOOST_AUTO_TEST_CASE( Node_setter ) { //NOLINT
        std::vector<std::string> aliases;
        aliases.emplace_back("shade");
        aliases.emplace_back("Shade");
        Node node("SHADE", "Description...", aliases);
        aliases.emplace_back("shaDE");
        node.setAliases(aliases);
        node.setDescription("Description2");
        node.setName("SHADE_NAME");
        BOOST_REQUIRE(node.getName() == "SHADE_NAME");
        BOOST_REQUIRE(node.getDescription() == "Description2");
        BOOST_REQUIRE(node.getAliases().at(0) == "shade");
        BOOST_REQUIRE(node.getAliases().at(1) == "Shade");
        BOOST_REQUIRE(node.getAliases().at(2) == "shaDE");
    }
    BOOST_AUTO_TEST_CASE( Node_name_cleaning_case ) { //NOLINT
        Node node("ShadE");
        BOOST_REQUIRE(node.getName() == "ShadE");
        BOOST_REQUIRE(node.getNameCleaned() == "shade");
    }
    BOOST_AUTO_TEST_CASE( Node_name_cleaning_special ) { //NOLINT
        Node node("aBc d-E.");
        BOOST_REQUIRE(node.getName() == "aBc d-E.");
        BOOST_REQUIRE(node.getNameCleaned() == "abcde");
    }
    BOOST_AUTO_TEST_CASE( Node_rate_name_similarity_normal ) { //NOLINT
        auto node_parent = std::make_shared<Node>("DE");
        auto node_child = std::make_shared<Node>("SHADE");
        BOOST_REQUIRE(node_parent->rateNameSimilarity(node_child) == 2);
    }
    BOOST_AUTO_TEST_CASE( Node_rate_name_similarity_case ) { //NOLINT
        auto node_parent = std::make_shared<Node>("DE");
        auto node_child = std::make_shared<Node>("Shade");
        BOOST_REQUIRE(node_parent->rateNameSimilarity(node_child) == 2);
    }
    BOOST_AUTO_TEST_CASE( Node_rate_name_similarity_special ) { //NOLINT
        auto node_parent = std::make_shared<Node>("DE");
        auto node_child = std::make_shared<Node>("sha-de");
        BOOST_REQUIRE(node_parent->rateNameSimilarity(node_child) == 2);
    }
    BOOST_AUTO_TEST_CASE( Node_rate_name_similarity_no_similarity ) { //NOLINT
        auto node_parent = std::make_shared<Node>("DE");
        auto node_child = std::make_shared<Node>("foo");
        BOOST_REQUIRE(node_parent->rateNameSimilarity(node_child) == 0);
    }
    BOOST_AUTO_TEST_CASE( Node_rate_name_similarity_no_similarity_edge_case ) { //NOLINT
        auto node_parent = std::make_shared<Node>("JADE");
        auto node_child = std::make_shared<Node>("SHADE");
        BOOST_REQUIRE(node_parent->rateNameSimilarity(node_child) == 0);
    }
    BOOST_AUTO_TEST_CASE( Node_add_and_remove_alias ) { //NOLINT
        std::vector<std::string> aliases;
        Node node("SHADE", "Description...", aliases);
        BOOST_REQUIRE(node.getAliases().empty());
        node.addAlias("Shade");
        BOOST_REQUIRE(node.getAliases().at(0) == "Shade");
        node.addAlias("shade");
        BOOST_REQUIRE(node.getAliases().at(1) == "shade");
        node.addAlias("shaDE");
        BOOST_REQUIRE(node.getAliases().at(2) == "shaDE");
        node.removeAlias("shade");
        BOOST_REQUIRE(node.getAliases().at(0) == "Shade");
        BOOST_REQUIRE(node.getAliases().at(1) == "shaDE");
    }
    BOOST_AUTO_TEST_CASE( Node_add_and_remove_children ) { //NOLINT
        auto node = std::make_shared<Node>("node");
        auto node_1 = std::make_shared<Node>("node_1");
        auto node_2 = std::make_shared<Node>("node_2");
        auto node_3 = std::make_shared<Node>("node_3");

        BOOST_REQUIRE( node->getChildren().empty() );
        BOOST_REQUIRE( node->getParent() == nullptr );
        node->addChild(node_1);
        BOOST_REQUIRE( node->getChildren().at(0)->getName() == "node_1" );
        node->addChild(node_2);
        BOOST_REQUIRE( node->getChildren().at(0)->getName() == "node_1" );
        BOOST_REQUIRE( node->getChildren().at(1)->getName() == "node_2" );
        node->addChild(node_3);
        BOOST_REQUIRE( node->getChildren().at(0)->getName() == "node_1" );
        BOOST_REQUIRE( node->getChildren().at(1)->getName() == "node_2" );
        BOOST_REQUIRE( node->getChildren().at(2)->getName() == "node_3" );
        node->removeChild("node_2");
        BOOST_REQUIRE( node->getChildren().at(0)->getName() == "node_1" );
        BOOST_REQUIRE( node->getChildren().at(1)->getName() == "node_3" );
    }
    BOOST_AUTO_TEST_CASE( Node_parent ) { //NOLINT
        auto node = std::make_shared<Node>("node");
        auto node_1 = std::make_shared<Node>("node_1");
        auto node_2 = std::make_shared<Node>("node_2");
        auto node_3 = std::make_shared<Node>("node_3");

        node_2->addChild(node_3);

        BOOST_REQUIRE( node->getChildren().empty() );
        BOOST_REQUIRE( node->getParent() == nullptr );
        node->addChild(node_1);
        BOOST_REQUIRE( node->getChildren().at(0)->getName() == "node_1" );
        BOOST_REQUIRE( node->getChildren().at(0)->getParent()->getName() == "node" );
        node->addChild(node_2);
        BOOST_REQUIRE( node->getChildren().at(0)->getName() == "node_1" );
        BOOST_REQUIRE( node->getChildren().at(1)->getName() == "node_2" );
        BOOST_REQUIRE( node->getChildren().at(0)->getParent()->getName() == "node" );
        BOOST_REQUIRE( node->getChildren().at(1)->getParent()->getName() == "node" );

        BOOST_REQUIRE( node->getChildren().at(1)->getChildren().at(0)->getParent()->getName() == "node_2" );
    }
    BOOST_AUTO_TEST_CASE( Node_ownership_transfer ) { //NOLINT
        auto node = std::make_shared<Node>("node");
        {
            auto node_1 = std::make_shared<Node>("node_1");
            BOOST_REQUIRE(node->getChildren().empty());
            node->addChild(node_1);
            BOOST_REQUIRE(node->getChildren().at(0)->getName() == "node_1");
        }
        BOOST_REQUIRE(node->getChildren().at(0)->getName() == "node_1");
    }

BOOST_AUTO_TEST_SUITE_END() //NOLINT
BOOST_AUTO_TEST_SUITE( Tree_suite ) //NOLINT
    BOOST_AUTO_TEST_CASE( Tree_creation ) { //NOLINT
        auto node = std::make_shared<Node>("node");
        Tree tree(node);
        BOOST_REQUIRE(tree.getRootNode()->getName() == "node");
    }
    BOOST_AUTO_TEST_CASE( Tree_set_root ) { //NOLINT
        auto node = std::make_shared<Node>("node");
        auto node_1 = std::make_shared<Node>("node_1");
        Tree tree(node);
        BOOST_REQUIRE(tree.getRootNode()->getName() == "node");
        tree.setRootNode(node_1);
        BOOST_REQUIRE(tree.getRootNode()->getName() == "node_1");
    }
    BOOST_AUTO_TEST_CASE( Tree_find_node ) { //NOLINT
        auto node = std::make_shared<Node>("node");
        auto node_1 = std::make_shared<Node>("node_1");
        auto node_1_1 = std::make_shared<Node>("node_1_1");
        auto node_1_2 = std::make_shared<Node>("node_1_2");
        auto node_2 = std::make_shared<Node>("node_2");
        auto node_3 = std::make_shared<Node>("node_3");
        node_1->addChild(node_1_1);
        node_1->addChild(node_1_2);
        node->addChild(node_1);
        node->addChild(node_2);
        node->addChild(node_3);
        Tree tree(node);
        BOOST_REQUIRE(tree.findNode("node")->getName() == "node");
        BOOST_REQUIRE(tree.findNode("node that do not exists") == nullptr);
        BOOST_REQUIRE(tree.findNode("node_1")->getName() == "node_1");
        BOOST_REQUIRE(tree.findNode("node_1_1")->getName() == "node_1_1");
    }
    BOOST_AUTO_TEST_CASE( Tree_remove_node ) { //NOLINT
        auto node = std::make_shared<Node>("node");
        auto node_1 = std::make_shared<Node>("node_1");
        auto node_1_1 = std::make_shared<Node>("node_1_1");
        auto node_1_2 = std::make_shared<Node>("node_1_2");
        auto node_2 = std::make_shared<Node>("node_2");
        auto node_3 = std::make_shared<Node>("node_3");
        node_1->addChild(node_1_1);
        node_1->addChild(node_1_2);
        node->addChild(node_1);
        node->addChild(node_2);
        node->addChild(node_3);
        Tree tree(node);
        BOOST_REQUIRE(tree.findNode("node")->getName() == "node");
        BOOST_REQUIRE(tree.findNode("node_1")->getName() == "node_1");
        BOOST_REQUIRE(tree.findNode("node_1_1")->getName() == "node_1_1");
        tree.removeNode("node_1_1");
        BOOST_REQUIRE(tree.findNode("node")->getName() == "node");
        BOOST_REQUIRE(tree.findNode("node_1")->getName() == "node_1");
        BOOST_REQUIRE(tree.findNode("node_1_1") == nullptr);
        tree.removeNode("node_1");
        BOOST_REQUIRE(tree.findNode("node")->getName() == "node");
        BOOST_REQUIRE(tree.findNode("node_1") == nullptr);
        BOOST_REQUIRE(tree.findNode("node_1_1") == nullptr);
        BOOST_REQUIRE(tree.findNode("node_1_2") == nullptr);
    }
    BOOST_AUTO_TEST_CASE( Tree_remove_node_root ) { //NOLINT
        auto node = std::make_shared<Node>("node");
        auto node_1 = std::make_shared<Node>("node_1");
        node->addChild(node_1);
        Tree tree(node);
        tree.removeNode("node");
        BOOST_REQUIRE(tree.getRootNode() == nullptr);
    }
    BOOST_AUTO_TEST_CASE( Tree_get_all_nodes ) { //NOLINT
        auto node = std::make_shared<Node>("node");
        auto node_1 = std::make_shared<Node>("node_1");
        auto node_1_1 = std::make_shared<Node>("node_1_1");
        auto node_1_2 = std::make_shared<Node>("node_1_2");
        auto node_2 = std::make_shared<Node>("node_2");
        auto node_3 = std::make_shared<Node>("node_3");
        node_1->addChild(node_1_1);
        node_1->addChild(node_1_2);
        node->addChild(node_1);
        node->addChild(node_2);
        node->addChild(node_3);
        Tree tree(node);
        auto all_nodes = tree.getAllNodes();
        BOOST_REQUIRE(all_nodes[0]->getName() == "node");
        BOOST_REQUIRE(all_nodes[1]->getName() == "node_1");
        BOOST_REQUIRE(all_nodes[2]->getName() == "node_2");
        BOOST_REQUIRE(all_nodes[3]->getName() == "node_3");
        BOOST_REQUIRE(all_nodes[4]->getName() == "node_1_1");
        BOOST_REQUIRE(all_nodes[5]->getName() == "node_1_2");
    }
    BOOST_AUTO_TEST_CASE( Tree_add_node ) { //NOLINT
        auto node = std::make_shared<Node>("node");
        auto node_1 = std::make_shared<Node>("node_1");
        auto node_1_1 = std::make_shared<Node>("node_1_1");
        auto node_1_2 = std::make_shared<Node>("node_1_2");
        auto node_2 = std::make_shared<Node>("node_2");
        auto node_3 = std::make_shared<Node>("node_3");
        Tree tree(nullptr);
        tree.addNode(node, ""); // special case - add root by empty string as parent
        tree.addNode(node_1, "node");
        tree.addNode(node_2, "node");
        tree.addNode(node_3, "node");
        tree.addNode(node_1_1, "node_1");
        tree.addNode(node_1_2, "node_1");
        auto root = tree.getRootNode();
        BOOST_CHECK(root->getChildren()[0]->getName() == "node_1");
        BOOST_CHECK(root->getChildren()[1]->getName() == "node_2");
        BOOST_CHECK(root->getChildren()[2]->getName() == "node_3");
        BOOST_REQUIRE(root->getChildren()[0]->getName() == "node_1");
        BOOST_CHECK(root->getChildren()[0]->getChildren()[0]->getName() == "node_1_1");
        BOOST_CHECK(root->getChildren()[0]->getChildren()[1]->getName() == "node_1_2");
    }
    BOOST_AUTO_TEST_CASE( Tree_add_node_non_existing ) { //NOLINT
        auto node = std::make_shared<Node>("node");
        auto node_1 = std::make_shared<Node>("node_1");
        Tree tree(nullptr);
        tree.addNode(node, ""); // special case - add root by empty string as parent
        tree.addNode(node_1, "node_non_existing");
        auto root = tree.getRootNode();
        BOOST_CHECK(root->getChildren().empty());
    }
    BOOST_AUTO_TEST_CASE( Tree_add_node_auto ) { //NOLINT
        auto node_de = std::make_shared<Node>("DE");
        auto node_shade = std::make_shared<Node>("SHADE");
        auto node_ilshade = std::make_shared<Node>("ILSHADE");
        auto node_xshade = std::make_shared<Node>("XSHADE");
        Tree tree(node_de);
        tree.addNodeAuto(node_shade);
        tree.addNodeAuto(node_ilshade);
        tree.addNodeAuto(node_xshade);
        auto root = tree.getRootNode();
        BOOST_CHECK(root->getChildren()[0]->getName() == "SHADE");
        BOOST_CHECK(root->getChildren()[0]->getChildren()[0]->getName() == "ILSHADE");
        BOOST_CHECK(root->getChildren()[0]->getChildren()[0]->getParent()->getName() == "SHADE");
        BOOST_CHECK(root->getChildren()[0]->getChildren()[1]->getName() == "XSHADE");
    }
    BOOST_AUTO_TEST_CASE( Tree_add_node_auto_root ) { //NOLINT
        auto node_de = std::make_shared<Node>("DE");
        Tree tree(nullptr);
        tree.addNodeAuto(node_de);
        auto root = tree.getRootNode();
        BOOST_CHECK(root == node_de);
    }
BOOST_AUTO_TEST_SUITE_END() //NOLINT
