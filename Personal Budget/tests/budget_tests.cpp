#include <catch2/catch.hpp>
#include <sstream>
#include <numeric>

#include "budget.h"

using namespace std;

TEST_CASE("Budget tests") {
    SECTION("Should assign income to correct days") {
        Budget budget;
        Date from(2000, 1, 3);
        Date to(2000, 1, 3);
        budget.Earn(from, to, 10);

        REQUIRE(budget.ComputeIncome({2000, 1, 1}, {2000, 1, 2}) == 0);
        REQUIRE(budget.ComputeIncome(from, to) == 10);
        REQUIRE(budget.ComputeIncome({2000, 1, 4}, {2000, 1, 12}) == 0);
    }

    SECTION("Should pay taxes correctly") {
        Budget budget;
        Date from(2000, 1, 3);
        Date to(2000, 1, 3);
        budget.Earn(from, to, 10);
        budget.PayTax({2000, 1, 1}, {2000, 2, 1});

        REQUIRE(budget.ComputeIncome({2000, 1, 1}, {2000, 1, 2}) == 0);
        REQUIRE(budget.ComputeIncome(from, to) == 10.0*0.87);
        REQUIRE(budget.ComputeIncome({2000, 1, 4}, {2000, 1, 12}) == 0);
    }

}