//Autor: Anczykowski Igor

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <sstream>

TEST_CASE( "Template setup", "[template]" ) {
    SECTION( "template" ) {
        REQUIRE( true == true );
    }
}

