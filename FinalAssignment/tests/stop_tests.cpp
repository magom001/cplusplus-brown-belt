#include <catch2/catch.hpp>

#include <sstream>
#include "stop.h"
#include "profiler.h"

using namespace std;

TEST_CASE( "Stop tests" ) {
    SECTION ( "instantiation ") {
        istringstream iss("Tolstopaltsevo: 55.611087, 37.20829");
        Stop s1;
        iss >> s1;
        CHECK(s1.name == "Tolstopaltsevo");
        CHECK(s1.lat == 55.611087);
        CHECK(s1.lon == 37.20829);
    }
    SECTION ( "distance between two stops" ) {
        Stop Tolstopaltsevo{"Tolstopaltsevo", 55.611087, 37.20829};
        Stop Marushkino{"Marushkino", 55.595884, 37.209755};
        Stop Rasskazovka{"Rasskazovka", 55.632761, 37.333324};
        Stop Biryulyovo_Zapadnoye{"Biryulyovo Zapadnoye", 55.574371, 37.6517};
        Stop Biryusinka{"Biryusinka", 55.581065, 37.64839};
        Stop Universam{"Universam", 55.587655, 37.645687};
        Stop Biryulyovo_Tovarnaya{"Biryulyovo Tovarnaya", 55.592028, 37.653656};
        Stop Biryulyovo_Passazhirskaya{"Biryulyovo Passazhirskaya", 55.580999, 37.659164};

        double distance_750 = 0.0;
        distance_750 += CalculateDistanceBetweenTwoStops(Tolstopaltsevo, Marushkino);
        distance_750 += CalculateDistanceBetweenTwoStops(Marushkino, Rasskazovka);
        distance_750 *= 2;
        CHECK( distance_750 == Approx(20939.5).epsilon(0.0001));

        double distance_256 = 0.0;
        distance_256 += CalculateDistanceBetweenTwoStops(Biryulyovo_Zapadnoye, Biryusinka);
        distance_256 += CalculateDistanceBetweenTwoStops(Biryusinka, Universam);
        distance_256 += CalculateDistanceBetweenTwoStops(Universam, Biryulyovo_Tovarnaya);
        distance_256 += CalculateDistanceBetweenTwoStops(Biryulyovo_Tovarnaya, Biryulyovo_Passazhirskaya);
        distance_256 += CalculateDistanceBetweenTwoStops(Biryulyovo_Passazhirskaya, Biryulyovo_Zapadnoye);
        CHECK( distance_256 == Approx(4371.02).epsilon(0.0001));
    }
    SECTION ( "distance should be the same regardless of the stops order") {
        Stop Tolstopaltsevo{"Tolstopaltsevo", 55.611087, 37.20829};
        Stop Marushkino{"Marushkino", 55.595884, 37.209755};
        REQUIRE(CalculateDistanceBetweenTwoStops(Tolstopaltsevo, Marushkino)
        == CalculateDistanceBetweenTwoStops(Marushkino, Tolstopaltsevo));
    }
    SECTION ( "measure CalculateDistanceBetweenTwoStops execution time") {
        Stop Tolstopaltsevo{"Tolstopaltsevo", 55.611087, 37.20829};
        Stop Marushkino{"Marushkino", 55.595884, 37.209755};
        LOG_DURATION("running time of CalculateDistanceBetweenTwoStops 2000000 times")
        for(auto i = 0; i < 2000000; ++i) {
            CalculateDistanceBetweenTwoStops(Tolstopaltsevo, Marushkino);
        }
    }
}