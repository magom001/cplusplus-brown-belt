#include <catch2/catch.hpp>
#include <sstream>
#include "stop.h"

using namespace std;

TEST_CASE("Coordinates tests") {
    SECTION("Order of coordinates should not matter") {
        Coordinates coord1{55.611087, 37.20829};
        Coordinates coord2{55.595884, 37.209755};
        REQUIRE(CalculateDistanceBetweenTwoStops(coord1, coord2) == CalculateDistanceBetweenTwoStops(coord2, coord1));
    }
    SECTION("Distance between equal coordinates is 0") {
        Coordinates coord1{55.611087, 37.20829};
        REQUIRE(CalculateDistanceBetweenTwoStops(coord1, coord1) == 0.0);
    }
}