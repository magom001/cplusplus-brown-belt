#include <catch2/catch.hpp>
#include <sstream>
#include <vector>
#include <algorithm>
#include "database.h"

using namespace std;

template<typename MemFunc>
void RunMemberFunction(const vector<string> &input, Database& db, MemFunc memFunc) {
    auto func = mem_fn(memFunc);

    stringstream ss;
    for(const auto& s: input) {
        ss.str(s);
        func(db, ss);
        ss.clear();
        ss.str("");
    }
}

TEST_CASE("Distance tests") {
    SECTION("test new format") {
        Database db;

        vector<string> stops = {
                "Tolstopaltsevo: 55.611087, 37.20829, 3900m to Marushkino",
                "Marushkino: 55.595884, 37.209755, 9900m to Rasskazovka",
                "Rasskazovka: 55.632761, 37.333324",
                "Biryulyovo Zapadnoye: 55.574371, 37.6517, 7500m to Rossoshanskaya ulitsa, 1800m to Biryusinka, 2400m to Universam",
                "Biryusinka: 55.581065, 37.64839, 750m to Universam",
                "Universam: 55.587655, 37.645687, 5600m to Rossoshanskaya ulitsa, 900m to Biryulyovo Tovarnaya",
                "Biryulyovo Tovarnaya: 55.592028, 37.653656, 1300m to Biryulyovo Passazhirskaya",
                "Biryulyovo Passazhirskaya: 55.580999, 37.659164, 1200m to Biryulyovo Zapadnoye",
                "Rossoshanskaya ulitsa: 55.595579, 37.605757",
                "Prazhskaya: 55.611678, 37.603831"
        };

        vector<string> buses = {
                "256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye",
                "750: Tolstopaltsevo - Marushkino - Rasskazovka",
                "828: Biryulyovo Zapadnoye > Universam > Rossoshanskaya ulitsa > Biryulyovo Zapadnoye",
        };

        RunMemberFunction(stops, db, &Database::InsertStop);
        RunMemberFunction(buses, db, &Database::InsertBusItinerary);

        REQUIRE(db.GetNumberOfStops() == 10);

        auto bus_256 = db.TryGetBus("256");
        REQUIRE(bus_256->GetBusNumber() == "256");

        auto distance_256 = bus_256->CalculateDistance();
        CHECK(distance_256.by_road == 5950);
        CHECK(distance_256.by_road/distance_256.between_coordinates == Approx(1.361239).epsilon(0.0001));

        auto bus_750 = db.TryGetBus("750");
        REQUIRE(bus_750->GetBusNumber() == "750");
        auto distance_750 = bus_750->CalculateDistance();
        CHECK(distance_750.by_road == 27600);
        CHECK(distance_750.by_road/distance_750.between_coordinates == Approx(1.318084).epsilon(0.0001));
    }
}