#include <catch2/catch.hpp>
#include <sstream>
#include "bus.h"

using namespace std;

TEST_CASE("Bus tests") {
    auto tolstopaltsevo_ptr = make_shared<Stop>("Tolstopaltsevo", 55.611087, 37.20829);
    auto marushkino_ptr = make_shared<Stop>("Marushkino", 55.595884, 37.209755);
    auto rasskazovka_ptr = make_shared<Stop>("Rasskazovka", 55.632761, 37.333324);
    auto biryulyovo_zapadnoye_ptr = make_shared<Stop>("Biryulyovo Zapadnoye", 55.574371, 37.6517);
    auto biryusinka_ptr = make_shared<Stop>("Biryusinka", 55.581065, 37.64839);
    auto universam_ptr = make_shared<Stop>("Universam", 55.587655, 37.645687);
    auto biryulyovo_tovarnaya_ptr = make_shared<Stop>("Biryulyovo Tovarnaya", 55.592028, 37.653656);
    auto biryulyovo_passazhirskaya_ptr = make_shared<Stop>("Biryulyovo Passazhirskaya", 55.580999, 37.659164);

    SECTION("CalculateRouteDistance tests") {
        Bus b256("256");
        vector<shared_ptr<Stop>> stops256 = {
                biryulyovo_zapadnoye_ptr,
                biryusinka_ptr,
                universam_ptr,
                biryulyovo_tovarnaya_ptr,
                biryulyovo_passazhirskaya_ptr,
                biryulyovo_zapadnoye_ptr
        };
        b256.SetIsCyclic(true);
        b256.SetBusStops(move(stops256));

        REQUIRE(b256.CalculateRouteDistance() == Approx(4371.017264).epsilon(0.0001));
        REQUIRE(b256.GetNumberOfStops() == 6);
        REQUIRE(b256.GetNumberOfUniqueStops() == 5);

        Bus b750("750");
        vector<shared_ptr<Stop>> stops750 = {
                tolstopaltsevo_ptr,
                marushkino_ptr,
                rasskazovka_ptr
        };

        b750.SetBusStops(move(stops750));

        REQUIRE(b750.CalculateRouteDistance() == Approx(20939.483047).epsilon(0.0001));
        REQUIRE(b750.GetNumberOfStops() == 5);
        REQUIRE(b750.GetNumberOfUniqueStops() == 3);
    }
}