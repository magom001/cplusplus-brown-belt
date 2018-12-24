#include <catch2/catch.hpp>
#include <sstream>
#include <memory>
#include "stop.h"
#include "bus.h"

using namespace std;

TEST_CASE("Stop tests") {
    SECTION("should store buses in a set and output in alphabetical order") {
       Stop s;

       auto b1 = make_shared<Bus>("bus 1");
       auto b3 = make_shared<Bus>("bus 3");
       auto b2 = make_shared<Bus>("bus 2");

       s.AddBus(b1->GetBusNumber());
       s.AddBus(b3->GetBusNumber());
       s.AddBus(b2->GetBusNumber());
       s.AddBus(b2->GetBusNumber());
       s.AddBus(b2->GetBusNumber());

       auto buses = s.GetBuses();
       stringstream ss;
       for ( auto b : buses) {
           ss << b << " ";
       }

       REQUIRE(ss.str() == "bus 1 bus 2 bus 3 ");
    }
}