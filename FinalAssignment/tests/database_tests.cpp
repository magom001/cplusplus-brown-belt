#include <catch2/catch.hpp>

#include "database.h"
#include <string_view>
#include "bus.h"
#include <vector>
#include <memory>

using namespace std;

TEST_CASE( "Database tests" ) {
    SECTION ( "database stores correctly shared pointers to stops") {
        Database db;
        auto stop1_ptr = make_shared<Stop>("stop#001");
        db.AddStop(move(stop1_ptr));
        auto found_stop1 = db.GetStop("stop#001");
        REQUIRE(found_stop1 != nullptr);
        CHECK(found_stop1->name == "stop#001");
        CHECK(found_stop1->lat == 0.0);
        CHECK(found_stop1->lon == 0.0);
    }
    SECTION ( "should create a new stop or update the object managed by a smart pointer" ) {
        Database db;
        vector<shared_ptr<Stop>> stops;
        auto stop1_ptr = make_shared<Stop>("stop#001");
        auto temp = db.AddStop(move(stop1_ptr));
        stops.push_back(move(temp));
        auto found_stop1 = db.GetStop("stop#001");
        REQUIRE(found_stop1 != nullptr);
        CHECK(found_stop1->name == "stop#001");
        CHECK(found_stop1->lat == 0.0);
        CHECK(found_stop1->lon == 0.0);

        auto new_stop1_ptr = make_shared<Stop>("stop#001", 1.0, 1.0);
        db.AddStop(new_stop1_ptr);
        REQUIRE(stops.size() == 1);
        CHECK(stops[0]->name == "stop#001");
        CHECK(stops[0]->lat == 1.0);

        auto another_get_call = db.GetStop("stop#001");
        REQUIRE(another_get_call->lat == 1.0);
        REQUIRE(another_get_call->lon == 1.0);
    }
    SECTION ( "add a bus") {
        Database db;
        string bus_number = "bus#001";

        vector<string_view> stop_names = {"stop_1", "stop_2", "stop_3"};
        auto bus_ptr = db.AddBus(bus_number, move(stop_names));
        CHECK(bus_ptr->GetBusNumber() == "bus#001");

        auto bus1_stops = bus_ptr->GetStops();
        CHECK(bus1_stops.size() == 3);
        CHECK(bus1_stops[0]->lat == 0);
        CHECK(bus1_stops[0]->lon == 0);

        auto stop = make_shared<Stop>("stop_1", 99, 100);
        db.AddStop(stop);

        CHECK(bus1_stops[0]->lat == 99);
        CHECK(bus1_stops[0]->lon == 100);
        CHECK(bus1_stops[1]->lat == 0);
        CHECK(bus1_stops[1]->lon == 0);
    }
}