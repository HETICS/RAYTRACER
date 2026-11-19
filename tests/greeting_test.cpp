#include <catch2/catch_test_macros.hpp>

#include "greeting.h"

TEST_CASE("greeting addresses the given name") {
    REQUIRE(greeting("World") == "Hello, World!");
}

TEST_CASE("greeting keeps an empty name empty") {
    REQUIRE(greeting("") == "Hello, !");
}
