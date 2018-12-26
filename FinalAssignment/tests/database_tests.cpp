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
        stringstream ss(" Marushkino: 55.595884, 37.209755 \n");
        db.InsertStop(ss);

        auto ptr_2 = db.GetStop("Marushkino ");
        REQUIRE(ptr_1 == ptr_2);
        CHECK(ptr_1->GetCoordinates().latitude == Approx(55.595884).epsilon(0.0001));
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

        CHECK(stop_ptr->GetCoordinates().latitude == Approx(55.595884).epsilon(0.0001));
        REQUIRE(stop_ptr->GetCoordinates().longitude == Approx(37.209755).epsilon(0.0001));
    }
    SECTION("should create a new stop for each stop name in the input") {
        Database db;
        auto ptr_1 = db.GetStop("   Marushkino");
        stringstream ss(" Marushkino: 55.595884, 37.209755, 9900m to Rasskazovka \n");
        db.InsertStop(ss);

        auto ptr_2 = db.GetStop("Marushkino ");
        REQUIRE(ptr_1 == ptr_2);
        CHECK(ptr_1->GetCoordinates().latitude == Approx(55.595884).epsilon(0.0001));
        REQUIRE(ptr_1->GetCoordinates().longitude == Approx(37.209755).epsilon(0.0001));
        REQUIRE(db.GetNumberOfStops() == 2);
        REQUIRE(ptr_1->GetDistanceToStop("Rasskazovka") == 9900);

        auto ptr_3 = db.GetStop("Rasskazovka");
        REQUIRE(ptr_3->GetDistanceToStop("Marushkino") == 9900);
    }
    SECTION("test stops creation in stop input") {
        Database db;
        stringstream ss1(" Universam: 55.587655, 37.645687, 5600m to Rossoshanskaya ulitsa, 900m to Biryulyovo Tovarnaya\n");
        db.InsertStop(ss1);
        auto ptr_universam = db.GetStop("Universam");

        CHECK(ptr_universam->GetCoordinates().latitude == Approx(55.587655).epsilon(0.0001));
        REQUIRE(ptr_universam->GetCoordinates().longitude == Approx(37.645687).epsilon(0.0001));
        REQUIRE(db.GetNumberOfStops() == 3);
        REQUIRE(ptr_universam->GetDistanceToStop("Rossoshanskaya ulitsa") == 5600);
        REQUIRE(ptr_universam->GetDistanceToStop("Biryulyovo Tovarnaya") == 900);

        auto ptr_rossoshanskaya = db.GetStop("Rossoshanskaya ulitsa");
        REQUIRE(ptr_rossoshanskaya->GetDistanceToStop("Universam") == 5600);

        stringstream ss2(" Rossoshanskaya ulitsa: 55.595579, 37.605757\n");
        db.InsertStop(ss2);

        REQUIRE(db.GetNumberOfStops() == 3);
        REQUIRE(ptr_rossoshanskaya->GetDistanceToStop("Universam") == 5600);
        CHECK(ptr_rossoshanskaya->GetCoordinates().latitude == Approx(55.595579).epsilon(0.0001));
        REQUIRE(ptr_rossoshanskaya->GetCoordinates().longitude == Approx(37.605757).epsilon(0.0001));

        stringstream ss3(" Biryulyovo Tovarnaya: 55.592028, 37.653656, 1300m to Biryulyovo Passazhirskaya, 950m to Universam\n");
        db.InsertStop(ss3);

        auto ptr_biryulyovo = db.GetStop("Biryulyovo Tovarnaya");
        REQUIRE(db.GetNumberOfStops() == 4);
        REQUIRE(ptr_biryulyovo->GetDistanceToStop("Universam") == 950);
    }
    SECTION("if distance for 2 stops is provided in different various inputs, explicit must prevail") {
        Database db;
        auto ptr_1 = db.GetStop("   Marushkino");
        stringstream ss1(" Marushkino: 55.595884, 37.209755, 9900m to Rasskazovka \n");
        db.InsertStop(ss1);

        stringstream ss2("Rasskazovka: 55.60, 37.22, 10000m to Marushkino \n");
        db.InsertStop(ss2);

        REQUIRE(db.GetNumberOfStops() == 2);
        REQUIRE(ptr_1->GetDistanceToStop("Rasskazovka") == 9900);

        auto ptr_3 = db.GetStop("Rasskazovka");
        REQUIRE(ptr_3->GetDistanceToStop("Marushkino") == 10000);
    }
}