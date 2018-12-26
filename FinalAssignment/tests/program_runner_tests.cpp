#include <catch2/catch.hpp>

#include <sstream>
#include "program_runner.h"

using namespace std;

TEST_CASE( "Program runner tests" ) {
    SECTION (" test default case Part C ") {
        stringstream iss;
        stringstream oss;
        iss << 13 << "\n";
        iss << "Stop Tolstopaltsevo: 55.611087, 37.20829, 3900m to Marushkino\n";
        iss << "Stop Marushkino: 55.595884, 37.209755, 9900m to Rasskazovka\n";
        iss << "Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye\n";
        iss << "Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka\n";
        iss << "Stop Rasskazovka: 55.632761, 37.333324\n";
        iss << "Stop Biryulyovo Zapadnoye: 55.574371, 37.6517, 7500m to Rossoshanskaya ulitsa, 1800m to Biryusinka, 2400m to Universam\n";
        iss << "Stop Biryusinka: 55.581065, 37.64839, 750m to Universam\n";
        iss << "Stop Universam: 55.587655, 37.645687, 5600m to Rossoshanskaya ulitsa, 900m to Biryulyovo Tovarnaya\n";
        iss << "Stop Biryulyovo Tovarnaya: 55.592028, 37.653656, 1300m to Biryulyovo Passazhirskaya\n";
        iss << "Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164, 1200m to Biryulyovo Zapadnoye\n";
        iss << "Bus 828: Biryulyovo Zapadnoye > Universam > Rossoshanskaya ulitsa > Biryulyovo Zapadnoye\n";
        iss << "Stop Rossoshanskaya ulitsa: 55.595579, 37.605757\n";
        iss << "Stop Prazhskaya: 55.611678, 37.603831\n";
        iss << 6 << "\n";
        iss << "Bus 256\n";
        iss << "Bus 750\n";
        iss << "Bus 751\n";
        iss << "Stop Samara\n";
        iss << "Stop Prazhskaya\n";
        iss << "Stop Biryulyovo Zapadnoye\n";

        stringstream expected_output;
        expected_output << "Bus 256: 6 stops on route, 5 unique stops, 5950 route length, 1.361239 curvature\n";
        expected_output << "Bus 750: 5 stops on route, 3 unique stops, 27600 route length, 1.318084 curvature\n";
        expected_output << "Bus 751: not found\n";
        expected_output << "Stop Samara: not found\n";
        expected_output << "Stop Prazhskaya: no buses\n";
        expected_output << "Stop Biryulyovo Zapadnoye: buses 256 828 \n";

        Start(iss, oss);

        CHECK(oss.str() == expected_output.str());
    }
}