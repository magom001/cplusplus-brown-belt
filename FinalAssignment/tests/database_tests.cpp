#include <catch2/catch.hpp>
#include <sstream>
#include "database.h"

using namespace std;

TEST_CASE("Database tests") {
    SECTION("GetStop must always return the same pointer") {
        Database db;
        auto ptr_1 = db.GetStop("stop");
        auto ptr_2 = db.GetStop("stop");

        //REQUIRE(ptr_1 == ptr_2);
        REQUIRE(ptr_1->GetName() == "stop");
        REQUIRE(ptr_1->GetName() == "stop");
        REQUIRE(db.GetNumberOfStops() == 1);
    }
    SECTION("GetStop should ignore white space") {
        Database db;
        auto ptr_1 = db.GetStop("stop with many words in name");
        auto ptr_2 = db.GetStop("   stop with many words in name       ");

        REQUIRE(db.GetNumberOfStops() == 1);

        CHECK(ptr_1.get() == ptr_2.get());
        CHECK(ptr_1 == ptr_2);
        REQUIRE(ptr_1->GetName() == "stop with many words in name");
        REQUIRE(ptr_1->GetName() == "stop with many words in name");
    }
    SECTION("Stop must be unique") {
        Database db;
        auto ptr_1 = db.GetStop("   Marushkino");
        stringstream ss(" Marushkino: 55.595884, 37.209755\n");
        db.InsertStop(ss);

        auto ptr_2 = db.GetStop("Marushkino ");
        REQUIRE(ptr_1 == ptr_2);
        REQUIRE(ptr_1->GetCoordinates().latitude == Approx(55.595884).epsilon(0.0001));
        REQUIRE(ptr_1->GetCoordinates().longitude == Approx(37.209755).epsilon(0.0001));
        REQUIRE(db.GetNumberOfStops() == 1);
    }
    SECTION("Should handle correctly bus routes") {
        Database db;
        stringstream ss(" 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye\n");
        db.InsertBusItinerary(ss);

        REQUIRE(db.GetNumberOfStops() == 5);
        REQUIRE(db.GetNumberOfBusRoutes() == 1);

        ss.clear();
        ss.str("750: Tolstopaltsevo - Marushkino - Rasskazovka\n");
        db.InsertBusItinerary(ss);

        REQUIRE(db.GetNumberOfBusRoutes() == 2);
        REQUIRE(db.GetNumberOfStops() == 8);

        ss.clear();
        ss.str("  weird bus name  : Tolstopaltsevo - Marushkino - Rasskazovka\n");
        db.InsertBusItinerary(ss);

        REQUIRE(db.GetNumberOfBusRoutes() == 3);
        REQUIRE(db.GetNumberOfStops() == 8);

        ss.clear();
        ss.str(" Marushkino: 55.595884, 37.209755\n");
        db.InsertStop(ss);

        auto stop_ptr = db.GetStop("Marushkino");

        REQUIRE(stop_ptr->GetCoordinates().latitude == Approx(55.595884).epsilon(0.0001));
        REQUIRE(stop_ptr->GetCoordinates().longitude == Approx(37.209755).epsilon(0.0001));
    }
}