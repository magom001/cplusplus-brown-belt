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
    }SECTION("GetStop should ignore white space") {
        Database db;
        auto ptr_1 = db.GetStop("stop with many words in name");
        auto ptr_2 = db.GetStop("   stop with many words in name       ");

        REQUIRE(db.GetNumberOfStops() == 1);

        CHECK(ptr_1.get() == ptr_2.get());
        CHECK(ptr_1 == ptr_2);
        REQUIRE(ptr_1->GetName() == "stop with many words in name");
        REQUIRE(ptr_1->GetName() == "stop with many words in name");
    }SECTION("Stop must be unique") {
        Database db;
        auto ptr_1 = db.GetStop("   Marushkino");
        stringstream ss(" Marushkino: 55.595884, 37.209755 \n");
        db.InsertStop(ss);

        auto ptr_2 = db.GetStop("Marushkino ");
        REQUIRE(ptr_1 == ptr_2);
        CHECK(ptr_1->GetCoordinates().latitude == Approx(55.595884).epsilon(0.0001));
        REQUIRE(ptr_1->GetCoordinates().longitude == Approx(37.209755).epsilon(0.0001));
        REQUIRE(db.GetNumberOfStops() == 1);
    }SECTION("Should handle correctly bus routes") {
        Database db;
        stringstream ss(
                " 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye\n");
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
    }SECTION("should create a new stop for each stop name in the input") {
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
    }SECTION("test stops creation in stop input") {
        Database db;
        stringstream ss1(
                " Universam: 55.587655, 37.645687, 5600m to Rossoshanskaya ulitsa, 900m to Biryulyovo Tovarnaya\n");
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

        stringstream ss3(
                " Biryulyovo Tovarnaya: 55.592028, 37.653656, 1300m to Biryulyovo Passazhirskaya, 950m to Universam\n");
        db.InsertStop(ss3);

        auto ptr_biryulyovo = db.GetStop("Biryulyovo Tovarnaya");
        REQUIRE(db.GetNumberOfStops() == 4);
        REQUIRE(ptr_biryulyovo->GetDistanceToStop("Universam") == 950);
    }SECTION("if distance for 2 stops is provided in different various inputs, explicit must prevail") {
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
    }SECTION("testing json stop request") {
        Database db;
        stringstream ss;
        ss.str(R"data(
{
  "base_requests": [
    {
      "type": "Stop",
      "road_distances": {
        "Marushkino": 3900
      },
      "longitude": 37.20829,
      "name": "Tolstopaltsevo",
      "latitude": 55.611087
    }
  ]
}
)data");

        auto document = Json::Load(ss);
        auto rootNode = document.GetRoot();
        auto rootNodeMap = rootNode.AsMap();
        auto base_requests = rootNodeMap.at("base_requests").AsArray();
        db.HandleBaseRequests(move(base_requests));

        REQUIRE(db.GetNumberOfStops() == 2);

        auto tolstopaltsevo_ptr = db.GetStop("Tolstopaltsevo");
        REQUIRE(tolstopaltsevo_ptr->GetCoordinates().latitude == 55.611087);
        REQUIRE(tolstopaltsevo_ptr->GetCoordinates().longitude == 37.20829);
        REQUIRE(tolstopaltsevo_ptr->GetDistanceToStop("Marushkino") == 3900);

        auto marushkino_ptr = db.GetStop("Marushkino");
        REQUIRE(marushkino_ptr->GetDistanceToStop("Tolstopaltsevo") == 3900);
    }SECTION("testing json bus request") {
        Database db;
        stringstream ss;
        ss.str(R"data(
{
  "base_requests": [
{
      "type": "Bus",
      "name": "828",
      "stops": [
        "Biryulyovo Zapadnoye",
        "Universam",
        "Rossoshanskaya ulitsa",
        "Biryulyovo Zapadnoye"
      ],
      "is_roundtrip": true
    },
 {
      "type": "Bus",
      "name": "750",
      "stops": [
        "Tolstopaltsevo",
        "Marushkino",
        "Rasskazovka"
      ],
      "is_roundtrip": false
    }
  ]
}
)data");

        auto document = Json::Load(ss);
        auto rootNode = document.GetRoot();
        auto rootNodeMap = rootNode.AsMap();
        auto base_requests = rootNodeMap.at("base_requests").AsArray();
        db.HandleBaseRequests(move(base_requests));

        REQUIRE(db.GetNumberOfStops() == 6);
        REQUIRE(db.GetNumberOfBusRoutes() == 2);
    }

    SECTION("testing general json request processing") {
        Database db;
        stringstream ss(R"input({"base_requests": [{"type": "Stop", "name": "Tolstopaltsevo", "latitude": 55.611087, "longitude": 37.20829, "road_distances": {"Marushkino": 3900}}, {"type": "Stop", "name": "Marushkino", "latitude": 55.595884, "longitude": 37.209755, "road_distances": {"Rasskazovka": 9900}}, {"type": "Bus", "name": "256", "stops": ["Biryulyovo Zapadnoye", "Biryusinka", "Universam", "Biryulyovo Tovarnaya", "Biryulyovo Passazhirskaya", "Biryulyovo Zapadnoye"], "is_roundtrip": true}, {"type": "Bus", "name": "750", "stops": ["Tolstopaltsevo", "Marushkino", "Rasskazovka"], "is_roundtrip": false}, {"type": "Stop", "name": "Rasskazovka", "latitude": 55.632761, "longitude": 37.333324, "road_distances": {}}, {"type": "Stop", "name": "Biryulyovo Zapadnoye", "latitude": 55.574371, "longitude": 37.6517, "road_distances": {"Biryusinka": 1800, "Universam": 2400, "Rossoshanskaya ulitsa": 7500}}, {"type": "Stop", "name": "Biryusinka", "latitude": 55.581065, "longitude": 37.64839, "road_distances": {"Universam": 750}}, {"type": "Stop", "name": "Universam", "latitude": 55.587655, "longitude": 37.645687, "road_distances": {"Biryulyovo Tovarnaya": 900, "Rossoshanskaya ulitsa": 5600}}, {"type": "Stop", "name": "Biryulyovo Tovarnaya", "latitude": 55.592028, "longitude": 37.653656, "road_distances": {"Biryulyovo Passazhirskaya": 1300}}, {"type": "Stop", "name": "Biryulyovo Passazhirskaya", "latitude": 55.580999, "longitude": 37.659164, "road_distances": {"Biryulyovo Zapadnoye": 1200}}, {"type": "Bus", "name": "828", "stops": ["Biryulyovo Zapadnoye", "Universam", "Rossoshanskaya ulitsa", "Biryulyovo Zapadnoye"], "is_roundtrip": true}, {"type": "Stop", "name": "Rossoshanskaya ulitsa", "latitude": 55.595579, "longitude": 37.605757, "road_distances": {}}, {"type": "Stop", "name": "Prazhskaya", "latitude": 55.611678, "longitude": 37.603831, "road_distances": {}}], "stat_requests": [{"id": 451694523, "type": "Bus", "name": "256"}, {"id": 811342727, "type": "Bus", "name": "750"}, {"id": 1167950742, "type": "Bus", "name": "751"}, {"id": 1171045629, "type": "Stop", "name": "Samara"}, {"id": 865859656, "type": "Stop", "name": "Prazhskaya"}, {"id": 1772591914, "type": "Stop", "name": "Biryulyovo Zapadnoye"}]})input");

        auto document = Json::Load(ss);
        auto rootNode = document.GetRoot();
        auto rootNodeMap = rootNode.AsMap();
        auto base_requests = rootNodeMap.at("base_requests").AsArray();
        db.HandleBaseRequests(move(base_requests));

        REQUIRE(db.GetNumberOfStops() == 10);
        REQUIRE(db.GetNumberOfBusRoutes() == 3);

        auto stat_requests = rootNodeMap.at("stat_requests").AsArray();
        auto responses = db.HandleStatRequests(move(stat_requests));

        REQUIRE(responses.size() == 6);
        stringstream output;
        Json::Stringify(output, responses[0]);

        REQUIRE(output.str() ==
                R"response({"route_length":5950,"request_id":451694523,"curvature":1.36124,"stop_count":6,"unique_stop_count":5})response");

        output.clear();
        output.str("");
        Json::Stringify(output, responses[1]);
        REQUIRE(output.str() ==
                R"response({"route_length":27600,"request_id":811342727,"curvature":1.31808,"stop_count":5,"unique_stop_count":3})response");

        output.clear();
        output.str("");
        Json::Stringify(output, responses.begin(), next(next(responses.begin())));
        REQUIRE(output.str() ==
                R"response([{"route_length":5950,"request_id":451694523,"curvature":1.36124,"stop_count":6,"unique_stop_count":5},{"route_length":27600,"request_id":811342727,"curvature":1.31808,"stop_count":5,"unique_stop_count":3}])response");

        output.clear();
        output.str("");
        Json::Stringify(output, responses[2]);
        REQUIRE(output.str() ==
                R"response({"request_id":1167950742,"error_message":"not found"})response");

        output.clear();
        output.str("");
        Json::Stringify(output, responses[3]);
        REQUIRE(output.str() ==
                R"response({"request_id":1171045629,"error_message":"not found"})response");

        output.clear();
        output.str("");
        Json::Stringify(output, responses[4]);
        REQUIRE(output.str() ==
                R"response({"buses":[],"request_id":865859656})response");

        output.clear();
        output.str("");
        Json::Stringify(output, responses[5]);
        REQUIRE(output.str() ==
                R"response({"buses":["256","828"],"request_id":1772591914})response");
    }


}