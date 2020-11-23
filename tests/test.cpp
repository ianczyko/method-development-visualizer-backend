//Author: Anczykowski Igor

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/Node.hpp"
#include <iostream>
#include <sstream>

TEST_CASE( "Node", "[node]" ) {
    SECTION("Node creation empty") {
        Node node("SHADE");
        REQUIRE(node.getName() == "SHADE");
        REQUIRE(node.getDescription().empty());
        REQUIRE(node.getAliases().empty());
    }
    SECTION("Node creation desc") {
        Node node("SHADE", "Description...");
        REQUIRE(node.getName() == "SHADE");
        REQUIRE(node.getDescription() == "Description...");
        REQUIRE(node.getAliases().empty());
    }
    SECTION("Node creation desc and aliases") {
        std::vector<std::string> aliases;
        aliases.emplace_back("shade");
        aliases.emplace_back("Shade");
        Node node("SHADE", "Description...", aliases);
        REQUIRE(node.getName() == "SHADE");
        REQUIRE(node.getDescription() == "Description...");
        REQUIRE(node.getAliases().at(0) == "shade");
        REQUIRE(node.getAliases().at(1) == "Shade");
    }
    SECTION("Node setter") {
        std::vector<std::string> aliases;
        aliases.emplace_back("shade");
        aliases.emplace_back("Shade");
        Node node("SHADE", "Description...", aliases);
        REQUIRE(node.getName() == "SHADE");
        REQUIRE(node.getDescription() == "Description...");
        REQUIRE(node.getAliases().at(0) == "shade");
        REQUIRE(node.getAliases().at(1) == "Shade");
        aliases.emplace_back("shaDE");
        node.setAliases(aliases);
        node.setDescription("Description2");
        node.setName("SHADE_NAME");
        REQUIRE(node.getName() == "SHADE_NAME");
        REQUIRE(node.getDescription() == "Description2");
        REQUIRE(node.getAliases().at(0) == "shade");
        REQUIRE(node.getAliases().at(1) == "Shade");
        REQUIRE(node.getAliases().at(2) == "shaDE");
    }
    SECTION("Node add/remove alias") {
        std::vector<std::string> aliases;
        Node node("SHADE", "Description...", aliases);
        REQUIRE(node.getAliases().empty());
        node.addAlias("Shade");
        REQUIRE(node.getAliases().at(0) == "Shade");
        node.addAlias("shade");
        REQUIRE(node.getAliases().at(1) == "shade");
        node.addAlias("shaDE");
        REQUIRE(node.getAliases().at(2) == "shaDE");
        node.removeAlias("shade");
        REQUIRE(node.getAliases().at(0) == "Shade");
        REQUIRE(node.getAliases().at(1) == "shaDE");
    }
    SECTION("Node add/remove children") {
        auto node = std::make_shared<Node>("node");
        auto node_1 = std::make_shared<Node>("node_1");
        auto node_2 = std::make_shared<Node>("node_2");
        auto node_3 = std::make_shared<Node>("node_3");

        REQUIRE( node->getChildren().empty() );
        node->addChild(node_1);
        REQUIRE( node->getChildren().at(0)->getName() == "node_1" );
        node->addChild(node_2);
        REQUIRE( node->getChildren().at(0)->getName() == "node_1" );
        REQUIRE( node->getChildren().at(1)->getName() == "node_2" );
        node->addChild(node_3);
        REQUIRE( node->getChildren().at(0)->getName() == "node_1" );
        REQUIRE( node->getChildren().at(1)->getName() == "node_2" );
        REQUIRE( node->getChildren().at(2)->getName() == "node_3" );
        node->removeChild("node_2");
        REQUIRE( node->getChildren().at(0)->getName() == "node_1" );
        REQUIRE( node->getChildren().at(1)->getName() == "node_3" );
    }
    SECTION("Node ownership transfer") {
        auto node = std::make_shared<Node>("node");
        {
            auto node_1 = std::make_shared<Node>("node_1");
            REQUIRE(node->getChildren().empty());
            node->addChild(node_1);
            REQUIRE(node->getChildren().at(0)->getName() == "node_1");
        }
        REQUIRE(node->getChildren().at(0)->getName() == "node_1");
    }
}
