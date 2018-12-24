#include <catch2/catch.hpp>

#include <sstream>
#include "program_runner.h"

using namespace std;

TEST_CASE( "Program runner tests" ) {
    SECTION (" test default case ") {
        stringstream iss;
        stringstream oss;
        iss << 10 << "\n";
        iss << "Stop Tolstopaltsevo: 55.611087, 37.20829\n";
        iss << "Stop Marushkino: 55.595884, 37.209755\n";
        iss
                << "Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye\n";
        iss << "Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka\n";
        iss << "Stop Rasskazovka: 55.632761, 37.333324\n";
        iss << "Stop Biryulyovo Zapadnoye: 55.574371, 37.6517\n";
        iss << "Stop Biryusinka: 55.581065, 37.64839\n";
        iss << "Stop Universam: 55.587655, 37.645687\n";
        iss << "Stop Biryulyovo Tovarnaya: 55.592028, 37.653656\n";
        iss << "Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164\n";
        iss << 3 << "\n";
        iss << "Bus 256\n";
        iss << "Bus 750\n";
        iss << "Bus 751\n";

        stringstream expected_output;
        expected_output << "Bus 256: 6 stops on route, 5 unique stops, 4371.017264 route length\n";
        expected_output << "Bus 750: 5 stops on route, 3 unique stops, 20939.483047 route length\n";
        expected_output << "Bus 751: not found\n";

        Start(iss, oss);

        CHECK(oss.str() == expected_output.str());
    }

    SECTION (" test without space in input case ") {
        stringstream iss;
        stringstream oss;
        iss << 12 << "\n";
        iss << "Stop    Tolstopaltsevo   : 55.611087, 37.20829\n";
        iss << "Stop Marushkino: 55.595884, 37.209755    \n";
        iss
                << "Bus    256   :Biryulyovo Zapadnoye>Biryusinka>Universam>      Biryulyovo Tovarnaya        >Biryulyovo Passazhirskaya>Biryulyovo Zapadnoye\n";
        iss << "Bus    750   : Tolstopaltsevo-Marushkino-Rasskazovka\n";
        iss
                << "Bus    751   :Biryulyovo Zapadnoye>Biryusinka>Universam>      Biryulyovo Tovarnaya        >Biryulyovo Passazhirskaya>Biryulyovo Zapadnoye\n";
        iss << "Stop Rasskazovka: 55.632761, 37.333324\n";
        iss << "Stop Biryulyovo Zapadnoye: 55.574371  , 37.6517\n";
        iss << "Stop Biryusinka:55.581065,37.64839\n";
        iss << "Stop Universam:     55.587655,    37.645687    \n";
        iss << "Stop Biryulyovo Tovarnaya: 55.592028, 37.653656\n";
        iss << "Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164\n";
        iss << "Bus Weird bus name: Weird stop - Another Weird stop\n";
        iss << 6 << "\n";
        iss << "Bus     256   \n";
        iss << "Bus   750   \n";
        iss << "Bus 751\n";
        iss << "Bus Weird bus name   \n";
        iss << "Bus 1\n";
        iss << "Bus 1\n";

        stringstream expected_output;
        expected_output << "Bus 256: 6 stops on route, 5 unique stops, 4371.017264 route length\n";
        expected_output << "Bus 750: 5 stops on route, 3 unique stops, 20939.483047 route length\n";
        expected_output << "Bus 751: 6 stops on route, 5 unique stops, 4371.017264 route length\n";
        expected_output << "Bus Weird bus name: 3 stops on route, 2 unique stops, 0.000000 route length\n";
        expected_output << "Bus 1: not found\n";
        expected_output << "Bus 1: not found\n";

        Start(iss, oss);

        CHECK(oss.str() == expected_output.str());
    }

    SECTION (" test default case 2 ") {
        stringstream iss;
        stringstream oss;
        iss << 13 << "\n";
        iss << "Stop Tolstopaltsevo: 55.611087, 37.20829\n";
        iss << "Stop Marushkino: 55.595884, 37.209755\n";
        iss << "Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye\n";
        iss << "Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka\n";
        iss << "Stop Rasskazovka: 55.632761, 37.333324\n";
        iss << "Stop Biryulyovo Zapadnoye: 55.574371, 37.6517\n";
        iss << "Stop Biryusinka: 55.581065, 37.64839\n";
        iss << "Stop Universam: 55.587655, 37.645687\n";
        iss << "Stop Biryulyovo Tovarnaya: 55.592028, 37.653656\n";
        iss << "Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164\n";
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
        expected_output << "Bus 256: 6 stops on route, 5 unique stops, 4371.017264 route length\n";
        expected_output << "Bus 750: 5 stops on route, 3 unique stops, 20939.483047 route length\n";
        expected_output << "Bus 751: not found\n";
        expected_output << "Stop Samara: not found\n";
        expected_output << "Stop Prazhskaya: no buses\n";
        expected_output << "Stop Biryulyovo Zapadnoye: buses 256 828 \n";

        Start(iss, oss);

        CHECK(oss.str() == expected_output.str());
    }
}