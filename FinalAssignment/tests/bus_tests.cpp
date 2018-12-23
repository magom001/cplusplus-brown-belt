#include <catch2/catch.hpp>

#include <sstream>
#include <vector>
#include <string_view>
#include "bus.h"
#include "stop.h"
#include "database.h"

using namespace std;

auto tolstopaltsevo_ptr = make_shared<Stop>("Tolstopaltsevo", 55.611087, 37.20829);
auto marushkino_ptr = make_shared<Stop>("Marushkino", 55.595884, 37.209755);
auto rasskazovka_ptr = make_shared<Stop>("Rasskazovka", 55.632761, 37.333324);
auto biryulyovo_zapadnoye_ptr = make_shared<Stop>("Biryulyovo Zapadnoye", 55.574371, 37.6517);
auto biryusinka_ptr = make_shared<Stop>("Biryusinka", 55.581065, 37.64839);
auto universam_ptr = make_shared<Stop>("Universam", 55.587655, 37.645687);
auto biryulyovo_tovarnaya_ptr = make_shared<Stop>("Biryulyovo Tovarnaya", 55.592028, 37.653656);
auto biryulyovo_passazhirskaya_ptr = make_shared<Stop>("Biryulyovo Passazhirskaya", 55.580999, 37.659164);

TEST_CASE("Bus class tests") {
    SECTION("SplitByDelim test >") {
        string s = " Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye";
        auto stop_names = GetStopNames(s);
        REQUIRE(stop_names.size() == 6);
        CHECK(stop_names[0] == "Biryulyovo Zapadnoye");
        CHECK(stop_names[1] == "Biryusinka");
        CHECK(stop_names[2] == "Universam");
        CHECK(stop_names[3] == "Biryulyovo Tovarnaya");
        CHECK(stop_names[4] == "Biryulyovo Passazhirskaya");
        CHECK(stop_names[5] == "Biryulyovo Zapadnoye");
    }
    SECTION("SplitByDelim test -") {
        string s = " Tolstopaltsevo - Marushkino - Rasskazovka";
        auto stop_names = GetStopNames(s);
        REQUIRE(stop_names.size() == 3);
        CHECK(stop_names[0] == "Tolstopaltsevo");
        CHECK(stop_names[1] == "Marushkino");
        CHECK(stop_names[2] == "Rasskazovka");
    }
    SECTION("SplitByDelim one stop only") {
        string s = " Tolstopaltsevo";
        auto stop_names = GetStopNames(s);
        REQUIRE(stop_names.size() == 1);
        CHECK(stop_names[0] == "Tolstopaltsevo");
    }
    SECTION(" calculate distance of a cyclic route") {
        vector<shared_ptr<Stop>> stops = {biryulyovo_zapadnoye_ptr,
                                          biryusinka_ptr,
                                          universam_ptr,
                                          biryulyovo_tovarnaya_ptr,
                                          biryulyovo_passazhirskaya_ptr,
                                          biryulyovo_zapadnoye_ptr
                                          };
        const string bus_number = "256";
        Bus *b = new Bus(bus_number, move(stops));
        CHECK( b->CalculateItineraryDistance() == Approx(4371.02).epsilon(0.0001));
    }
    SECTION(" calculate distance of a non cyclic route") {
        vector<shared_ptr<Stop>> stops = {tolstopaltsevo_ptr,
                                          marushkino_ptr,
                                          rasskazovka_ptr
                                          };
        const string bus_number = "750";
        Bus *b = new Bus(bus_number, move(stops));
        CHECK( b->CalculateItineraryDistance() == Approx(20939.5).epsilon(0.0001));
    }
    SECTION(" display total tumber of stops, total number of unique stops ") {
        vector<shared_ptr<Stop>> stops_256 = {biryulyovo_zapadnoye_ptr,
                                              biryusinka_ptr,
                                              universam_ptr,
                                              biryulyovo_tovarnaya_ptr,
                                              biryulyovo_passazhirskaya_ptr,
                                              biryulyovo_zapadnoye_ptr
                                            };
        const string bus_number_256 = "256";
        Bus *b256 = new Bus(bus_number_256, move(stops_256));
        REQUIRE(b256->GetNumberOfStops() == 6);
        REQUIRE(b256->GetNumberOfUniqueStops() == 5);

        vector<shared_ptr<Stop>> stops_750 = {tolstopaltsevo_ptr,
                                              marushkino_ptr,
                                              rasskazovka_ptr
                                            };
        const string bus_number_750 = "750";
        Bus *b750 = new Bus(bus_number_750, move(stops_750));

        REQUIRE(b750->GetNumberOfStops() == 5);
        REQUIRE(b750->GetNumberOfUniqueStops() == 3);

        vector<shared_ptr<Stop>> dummies = {marushkino_ptr,
                                          marushkino_ptr,
                                          marushkino_ptr,
                                          marushkino_ptr,
                                          marushkino_ptr
                                        };
        const string dummy_bus = "dummy";
        Bus *dummy = new Bus(dummy_bus, move(dummies));
        REQUIRE(dummy->GetNumberOfStops() == 5);
        REQUIRE(dummy->GetNumberOfUniqueStops() == 1);
    }
    SECTION( " should correctly output the bus info ") {
        ostringstream oss;
        ostringstream output_oss;
        vector<shared_ptr<Stop>> stops_256 = {biryulyovo_zapadnoye_ptr,
                                              biryusinka_ptr,
                                              universam_ptr,
                                              biryulyovo_tovarnaya_ptr,
                                              biryulyovo_passazhirskaya_ptr,
                                              biryulyovo_zapadnoye_ptr
        };
        const string bus_number_256 = "256";
        Bus *b256 = new Bus(bus_number_256, move(stops_256));

        oss << *b256;
        output_oss << "Bus 256: 6 stops on route, 5 unique stops, 4371.017264 route length" << "\n";

        vector<shared_ptr<Stop>> stops_750 = {tolstopaltsevo_ptr,
                                              marushkino_ptr,
                                              rasskazovka_ptr
        };
        const string bus_number_750 = "750";
        Bus *b750 = new Bus(bus_number_750, move(stops_750));
        oss << *b750;
        output_oss << "Bus 750: 5 stops on route, 3 unique stops, 20939.483047 route length" << "\n";

        vector<shared_ptr<Stop>> dummies = {marushkino_ptr,
                                            marushkino_ptr,
                                            marushkino_ptr,
                                            marushkino_ptr,
                                            marushkino_ptr
        };
        const string dummy_bus = "dummy";
        Bus *dummy = new Bus(dummy_bus, move(dummies));

        oss << *dummy;
        output_oss << "Bus dummy: 5 stops on route, 1 unique stops, 0.000000 route length" << "\n";

        REQUIRE(oss.str() == output_oss.str());
    }
}