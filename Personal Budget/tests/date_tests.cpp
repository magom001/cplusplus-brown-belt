#include <catch2/catch.hpp>
#include <sstream>

#include "date.h"

using namespace std;

TEST_CASE("Date tests") {
    SECTION("Calculate difference between dates") {
        Date d1(2000, 1, 2);
        Date d2(2000, 1, 6);
        Date d3(2000, 1, 1);
        Date d4(2001, 1, 1);

        REQUIRE(ComputeDaysDiff(d2, d1) == 4);
        REQUIRE(ComputeDaysDiff(d4, d3) == 366);

        Date d2000(2000, 1, 1);
        Date d2100(2100, 1, 1);

        REQUIRE(ComputeDaysDiff(d2100, d2000) == 36525);
    }

    SECTION("Test operator>>") {
        stringstream ss("2019-01-01");

        Date d;
        Date expected(2019, 1, 1);
        ss >> d;

        REQUIRE(ComputeDaysDiff(expected, d) == 0);
    }
}