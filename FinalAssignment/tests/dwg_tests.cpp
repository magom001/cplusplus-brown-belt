#include <catch2/catch.hpp>
#include <iostream>
#include <fstream>
#include "database.h"
#include "graph.h"
#include <unordered_map>
#include "router.h"

using namespace std;
using namespace Graph;
using namespace Catch::Matchers;

TEST_CASE("Graph tests") {
//    SECTION("route example 2 simulation") {
//        const double BUS_SPEED = 30.0*1000.0/60;
//        const double BUS_WAIT_TIME = 2.0;
//
//        const size_t BIRYULYOVO_ZAPADNOYE = 0;
//        const size_t BIRYULYOVO_TOVARNAYA = 1;
//        const size_t UNIVERSAM = 2;
//        const size_t BIRYUSINKA = 3;
//        const size_t APTEKA = 4;
//        const size_t TETS_26 = 5;
//        const size_t POKROVSKAYA = 6;
//        const size_t PRAZHSKAYA = 7;
//        const size_t ROSSOSHANSKAYA_ULITSA = 8;
//        const size_t BIRYULYOVO_ZAPADNOYE_BUS = 9;
//        const size_t BIRYULYOVO_TOVARNAYA_BUS = 10;
//        const size_t UNIVERSAM_BUS = 11;
//        const size_t BIRYUSINKA_BUS = 12;
//        const size_t APTEKA_BUS = 13;
//        const size_t TETS_26_BUS = 14;
//        const size_t POKROVSKAYA_BUS = 15;
//        const size_t PRAZHSKAYA_BUS = 16;
//        const size_t ROSSOSHANSKAYA_ULITSA_BUS = 17;
//
//        vector<Edge<double>> edges = {
//                {BIRYULYOVO_ZAPADNOYE, BIRYULYOVO_ZAPADNOYE_BUS, BUS_WAIT_TIME},
//                {BIRYULYOVO_TOVARNAYA, BIRYULYOVO_TOVARNAYA_BUS, BUS_WAIT_TIME},
//                {UNIVERSAM, UNIVERSAM_BUS, BUS_WAIT_TIME},
//                {BIRYUSINKA, BIRYUSINKA_BUS, BUS_WAIT_TIME},
//                {APTEKA, APTEKA_BUS, BUS_WAIT_TIME},
//                {TETS_26, TETS_26_BUS, BUS_WAIT_TIME},
//                {POKROVSKAYA, POKROVSKAYA_BUS, BUS_WAIT_TIME},
//                {PRAZHSKAYA, PRAZHSKAYA_BUS, BUS_WAIT_TIME},
//                {ROSSOSHANSKAYA_ULITSA, ROSSOSHANSKAYA_ULITSA_BUS, BUS_WAIT_TIME},
//                // Bus 297 TODO: CREATE EDGES FOR EACH PAIR OF STOPS
//                {BIRYULYOVO_ZAPADNOYE_BUS, BIRYULYOVO_TOVARNAYA, 2600.0/BUS_SPEED},
//                {BIRYULYOVO_TOVARNAYA_BUS, UNIVERSAM, 890.0/BUS_SPEED},
//                {BIRYULYOVO_TOVARNAYA_BUS, BIRYUSINKA, (890.0 +760)/BUS_SPEED},
//                {BIRYULYOVO_TOVARNAYA_BUS, APTEKA, (890.0 + 760 + 210)/BUS_SPEED},
//                {BIRYULYOVO_TOVARNAYA_BUS, BIRYULYOVO_ZAPADNOYE, (890.0 + 760 + 210 + 1420)/BUS_SPEED},
//                {UNIVERSAM_BUS, BIRYUSINKA, 760.0/BUS_SPEED},
//                {BIRYUSINKA_BUS, APTEKA, 210.0/BUS_SPEED},
//                {APTEKA_BUS, BIRYULYOVO_ZAPADNOYE, 1420.0/BUS_SPEED},
//                // Bus 635 TODO: CREATE EDGES FOR EACH PAIR OF STOPS
//                {BIRYULYOVO_TOVARNAYA_BUS, UNIVERSAM, 890.0/BUS_SPEED},
//                {UNIVERSAM_BUS, BIRYUSINKA, 760.0/BUS_SPEED},
//                {BIRYUSINKA_BUS, TETS_26, 400.0/BUS_SPEED},
//                {TETS_26_BUS, POKROVSKAYA, 2850.0/BUS_SPEED},
//                {POKROVSKAYA_BUS, PRAZHSKAYA, 2260.0/BUS_SPEED},
//                {PRAZHSKAYA_BUS, POKROVSKAYA, 2260.0/BUS_SPEED},
//                {POKROVSKAYA_BUS, TETS_26, 2850.0/BUS_SPEED},
//                {TETS_26_BUS, BIRYUSINKA, 400.0/BUS_SPEED},
//                {BIRYUSINKA_BUS, UNIVERSAM, 760.0/BUS_SPEED},
//                {UNIVERSAM_BUS, BIRYULYOVO_TOVARNAYA, 1380.0/BUS_SPEED},
//                // Bus 828
//                {BIRYULYOVO_ZAPADNOYE_BUS, TETS_26, 1100.0/BUS_SPEED},
//                {BIRYULYOVO_ZAPADNOYE_BUS, BIRYUSINKA, 1500.0/BUS_SPEED},
//                {BIRYULYOVO_ZAPADNOYE_BUS, UNIVERSAM, 2260.0/BUS_SPEED},
//                {BIRYULYOVO_ZAPADNOYE_BUS, POKROVSKAYA, 4720.0/BUS_SPEED},
//                // TODO: CREATE EDGES FOR EACH PAIR OF STOPS
//                {TETS_26_BUS, BIRYUSINKA, 400.0/BUS_SPEED},
//                {BIRYUSINKA_BUS, UNIVERSAM, 760.0/BUS_SPEED},
//                {UNIVERSAM_BUS, POKROVSKAYA, 2460.0/BUS_SPEED},
//                {POKROVSKAYA_BUS, ROSSOSHANSKAYA_ULITSA, 3140.0/BUS_SPEED},
//                {ROSSOSHANSKAYA_ULITSA_BUS, POKROVSKAYA, 3210.0/BUS_SPEED},
//                {POKROVSKAYA_BUS, UNIVERSAM, 2460.0/BUS_SPEED},
//                {UNIVERSAM_BUS, BIRYUSINKA, 760.0/BUS_SPEED},
//                {BIRYUSINKA_BUS, TETS_26, 400.0/BUS_SPEED},
//                {TETS_26_BUS, BIRYULYOVO_ZAPADNOYE, 1100.0/BUS_SPEED}
//        };
//
//        DirectedWeightedGraph<double> dwg(edges.size());
//        for (const auto& edge: edges) {
//            dwg.AddEdge(edge);
//        };
//
//        Router router(dwg);
//
//        auto route = router.BuildRoute(BIRYULYOVO_ZAPADNOYE, APTEKA);
//        REQUIRE(route);
//        REQUIRE(route->weight == 7.42);
//
//        route = router.BuildRoute(BIRYULYOVO_ZAPADNOYE, POKROVSKAYA);
//        REQUIRE(route);
//        REQUIRE(route->weight == 11.44);
//
//        route = router.BuildRoute(BIRYULYOVO_TOVARNAYA, POKROVSKAYA);
//        REQUIRE(route);
//        REQUIRE(route->weight == 10.7);
//
//        route = router.BuildRoute(BIRYULYOVO_TOVARNAYA, BIRYULYOVO_ZAPADNOYE);
//        REQUIRE(route);
//        REQUIRE(route->weight == Approx(8.56));
//
//        size_t from = BIRYULYOVO_TOVARNAYA;
//        size_t to =   BIRYULYOVO_ZAPADNOYE;
//        if (auto route = router.BuildRoute(from, to)) {
//            cout << "Edge count: " << route->edge_count << endl;
//            cout << "Route weight: " << route->weight << endl;
//
//            for(size_t x = 0; x < route->edge_count; ++x) {
//                auto part = router.GetRouteEdge(route->id, x);
//                auto edge = dwg.GetEdge(part);
//                cout << edge.from << "->" << edge.to << ":" << edge.weight << endl;
//                from = edge.to;
//            }
//        }
//
//    }
//    SECTION("route example 3 simulation") {
//        const double BUS_SPEED = 30.0*1000.0/60;
//        const double BUS_WAIT_TIME = 2.0;
//
//        const size_t ZAGORIE = 0;
//        const size_t ZAGORIE_BUS = 1;
//        const size_t LIPETSKAYA_46 = 2;
//        const size_t LIPETSKAYA_46_BUS = 3;
//        const size_t LIPETSKAYA_40 = 4;
//        const size_t LIPETSKAYA_40_BUS = 5;
//        const size_t MOSKVORECHYE = 6;
//        const size_t MOSKVORECHYE_BUS = 7;
//
//        const unordered_map<size_t, string> bus_stops = {
//                {ZAGORIE, "Zagorie"},
//                {ZAGORIE_BUS, "Zagorie wait"},
//                {LIPETSKAYA_46, "Lipetskaya 46"},
//                {LIPETSKAYA_46_BUS, "Lipetskaya 46 wait"},
//                {LIPETSKAYA_40, "Lipetskaya 40"},
//                {LIPETSKAYA_40_BUS, "Lipetskaya 40 wait"},
//                {MOSKVORECHYE, "Moskvorechye"},
//                {MOSKVORECHYE_BUS, "Moskvorechye wait"}
//        };
//
//        vector<Edge<double>> edges = {
//                {ZAGORIE, ZAGORIE_BUS, BUS_WAIT_TIME},
//                {LIPETSKAYA_46, LIPETSKAYA_46_BUS, BUS_WAIT_TIME},
//                {LIPETSKAYA_40, LIPETSKAYA_40_BUS, BUS_WAIT_TIME},
//                {MOSKVORECHYE, MOSKVORECHYE_BUS, BUS_WAIT_TIME},
//
//                // TODO: CREATE EDGES FOR EACH PAIR OF STOPS
//                {ZAGORIE_BUS, LIPETSKAYA_46, 230.0/BUS_SPEED},
//                {ZAGORIE_BUS, LIPETSKAYA_40, (390 + 230.0)/BUS_SPEED},
//                {ZAGORIE_BUS, LIPETSKAYA_46, (390 + 230.0 + 1090)/BUS_SPEED},
//                {ZAGORIE_BUS, MOSKVORECHYE, (390 + 230.0 + 1090 + 12400)/BUS_SPEED},
//                {ZAGORIE_BUS, ZAGORIE, (390 + 230.0 + 1090 + 12400 + 10000)/BUS_SPEED},
//                {LIPETSKAYA_46_BUS, LIPETSKAYA_40, 390.0/BUS_SPEED},
//                {LIPETSKAYA_46_BUS, LIPETSKAYA_46, (390.0 + 1090)/BUS_SPEED},
//                {LIPETSKAYA_46_BUS, MOSKVORECHYE, (390.0 + 1090 + 12400)/BUS_SPEED},
//                {LIPETSKAYA_46_BUS, ZAGORIE, (390.0 + 1090 + 12400 + 10000)/BUS_SPEED},
//                {LIPETSKAYA_40_BUS, LIPETSKAYA_40, 1090.0/BUS_SPEED},
//                {LIPETSKAYA_40_BUS, LIPETSKAYA_46, (1090.0 + 380)/BUS_SPEED},
//                {LIPETSKAYA_40_BUS, MOSKVORECHYE, (1090.0 + 380 + 12400)/BUS_SPEED},
//                {LIPETSKAYA_40_BUS, ZAGORIE, (1090.0 + 380 + 12400 + 10000)/BUS_SPEED},
//                {LIPETSKAYA_40_BUS, LIPETSKAYA_46, (1090.0 + 380)/BUS_SPEED},
//                {LIPETSKAYA_40_BUS, MOSKVORECHYE, (1090.0 + 380 + 12400)/BUS_SPEED},
//                {LIPETSKAYA_40_BUS, ZAGORIE, (1090.0 + 380 + 12400 + 10000)/BUS_SPEED},
//                {LIPETSKAYA_46_BUS, MOSKVORECHYE, 12400.0/BUS_SPEED},
//                {LIPETSKAYA_46_BUS, ZAGORIE, (12400.0 + 10000)/BUS_SPEED},
//                {MOSKVORECHYE_BUS, ZAGORIE, 10000.0/BUS_SPEED}
//        };
//
//        DirectedWeightedGraph<double> dwg(edges.size());
//        for (const auto& edge: edges) {
//            dwg.AddEdge(edge);
//        };
//
//        Router router(dwg);
//
//        auto route = router.BuildRoute(ZAGORIE, MOSKVORECHYE);
//        REQUIRE(route);
//        REQUIRE(route->weight == 29.26);
//
//        route = router.BuildRoute(MOSKVORECHYE, ZAGORIE);
//        REQUIRE(route);
//        REQUIRE(route->weight == 22);
//
//        route = router.BuildRoute(LIPETSKAYA_40, LIPETSKAYA_40);
//        REQUIRE(route);
//        REQUIRE(route->weight == 0);
//
//        size_t from = ZAGORIE;
//        size_t to =   MOSKVORECHYE;
////        if (auto route = router.BuildRoute(from, to)) {
////            cout << "Edge count: " << route->edge_count << endl;
////            cout << "Route weight: " << route->weight << endl;
////
////            for(size_t x = 0; x < route->edge_count; ++x) {
////                auto part = router.GetRouteEdge(route->id, x);
////                auto edge = dwg.GetEdge(part);
////                cout << bus_stops.at(edge.from) << "->" << bus_stops.at(edge.to) << ":" << edge.weight << endl;
////                from = edge.to;
////            }
////        }
//    }
    SECTION(" testing example 3 routes ") {
        string filename = "../../tests/part_e_example3.json";
        ifstream fs(filename);

        if (!fs.is_open()) {
            cout << "Failed to open file" << endl;
        }

        Database db;
        auto document = Json::Load(fs);
        auto rootNode = document.GetRoot();
        auto rootNodeMap = rootNode.AsMap();
        auto base_requests = rootNodeMap.at("base_requests").AsArray();

        if(auto it = rootNodeMap.find("routing_settings"); it != rootNodeMap.end()) {
            auto routing_settings = (*it).second.AsMap();
            double bus_wait_time = routing_settings.at("bus_wait_time").AsDouble();
            double bus_velocity = routing_settings.at("bus_velocity").AsDouble();
            RoutingSettings rs(bus_wait_time, bus_velocity);
            db.SetRoutingSettings(move(rs));
        }

        db.HandleBaseRequests(move(base_requests));

        db.BuildGraph();

        REQUIRE(db.GetNumberOfStops() == 4);

        auto router = db.GetRouter();
        if (router) {
            size_t from = db.GetStop("Zagorye")->GetIndex();
            size_t to =   db.GetStop("Moskvorechye")->GetIndex();

            if (auto route = db.GetRouter()->BuildRoute(from, to)) {
//                cout << "Edge count: " << route->edge_count << endl;
//                cout << "Route weight: " << route->weight << endl;
                REQUIRE(route->weight == 29.26);
//                for(size_t x = 0; x < route->edge_count; ++x) {
//                    auto part = db.GetRouter()->GetRouteEdge(route->id, x);
//                    auto edge = db.GetGraph()->GetEdge(part);
//                    cout << "Edge: " << edge.name << " " << edge.span << endl;
//                }
            }

            from = db.GetStop("Moskvorechye")->GetIndex();
            to =   db.GetStop("Zagorye")->GetIndex();

            if (auto route = db.GetRouter()->BuildRoute(from, to)) {
//                cout << "Edge count: " << route->edge_count << endl;
//                cout << "Route weight: " << route->weight << endl;
                REQUIRE(route->weight == Approx(22));
//                for(size_t x = 0; x < route->edge_count; ++x) {
//                    auto part = db.GetRouter()->GetRouteEdge(route->id, x);
//                    auto edge = db.GetGraph()->GetEdge(part);
//                    cout << "Edge: " << edge.name << " " << edge.span << endl;
//                }
            }

            from = db.GetStop("Lipetskaya ulitsa 40")->GetIndex();
            to =   db.GetStop("Lipetskaya ulitsa 40")->GetIndex();

            if (auto route = db.GetRouter()->BuildRoute(from, to)) {
//                cout << "Edge count: " << route->edge_count << endl;
//                cout << "Route weight: " << route->weight << endl;
                REQUIRE(route->weight == Approx(0));
//                for(size_t x = 0; x < route->edge_count; ++x) {
//                    auto part = db.GetRouter()->GetRouteEdge(route->id, x);
//                    auto edge = db.GetGraph()->GetEdge(part);
//                    cout << "Edge: " << edge.name << " " << edge.span << endl;
//                }
            }
        }
    }

    SECTION(" testing example 1 routes ") {
        string filename = "../../tests/part_e_example1.json";
        ifstream fs(filename);

        if (!fs.is_open()) {
            cout << "Failed to open file" << endl;
        }

        Database db;
        auto document = Json::Load(fs);
        auto rootNode = document.GetRoot();
        auto rootNodeMap = rootNode.AsMap();
        auto base_requests = rootNodeMap.at("base_requests").AsArray();

        if(auto it = rootNodeMap.find("routing_settings"); it != rootNodeMap.end()) {
            auto routing_settings = (*it).second.AsMap();
            double bus_wait_time = routing_settings.at("bus_wait_time").AsDouble();
            double bus_velocity = routing_settings.at("bus_velocity").AsDouble();
            RoutingSettings rs(bus_wait_time, bus_velocity);
            db.SetRoutingSettings(move(rs));
        }

        db.HandleBaseRequests(move(base_requests));

        db.BuildGraph();

        REQUIRE(db.GetNumberOfStops() == 4);

        auto router = db.GetRouter();
        if (router) {
            size_t from = db.GetStop("Biryulyovo Zapadnoye")->GetIndex();
            size_t to =   db.GetStop("Universam")->GetIndex();

            if (auto route = db.GetRouter()->BuildRoute(from, to)) {
//                cout << "Edge count: " << route->edge_count << endl;
//                cout << "Route weight: " << route->weight << endl;
                REQUIRE(route->weight == 11.235);
                REQUIRE(route->edge_count == 2);
                auto edge1_id = db.GetRouter()->GetRouteEdge(route->id, 0);
                auto edge1 = db.GetGraph()->GetEdge(edge1_id);
                REQUIRE(edge1.weight == 6);
                REQUIRE(edge1.edge_type == Graph::EDGE_TYPE::WAIT);

                auto edge2_id = db.GetRouter()->GetRouteEdge(route->id, 1);
                auto edge2 = db.GetGraph()->GetEdge(edge2_id);
                REQUIRE(edge2.weight == 5.235);
                REQUIRE(edge2.edge_type == Graph::EDGE_TYPE::BUS);
                REQUIRE(edge2.name == "297");
                REQUIRE(edge2.span == 2);
//                for(size_t x = 0; x < route->edge_count; ++x) {
//                    auto part = db.GetRouter()->GetRouteEdge(route->id, x);
//                    auto edge = db.GetGraph()->GetEdge(part);
//                    cout << "Edge: " << edge.name << " " << edge.span << endl;
//                }
            }

            from = db.GetStop("Biryulyovo Zapadnoye")->GetIndex();
            to =   db.GetStop("Prazhskaya")->GetIndex();

            if (auto route = db.GetRouter()->BuildRoute(from, to)) {
//                cout << "Edge count: " << route->edge_count << endl;
//                cout << "Route weight: " << route->weight << endl;
                REQUIRE(route->weight == 24.21);
                REQUIRE(route->edge_count == 4);

                auto edge1_id = db.GetRouter()->GetRouteEdge(route->id, 0);
                auto edge1 = db.GetGraph()->GetEdge(edge1_id);
                REQUIRE(edge1.weight == 6);
                REQUIRE(edge1.edge_type == Graph::EDGE_TYPE::WAIT);
                REQUIRE(edge1.name == "Biryulyovo Zapadnoye");

                auto edge2_id = db.GetRouter()->GetRouteEdge(route->id, 1);
                auto edge2 = db.GetGraph()->GetEdge(edge2_id);
                REQUIRE(edge2.weight == Approx(3.9));
                REQUIRE(edge2.edge_type == Graph::EDGE_TYPE::BUS);
                REQUIRE(edge2.name == "297");
                REQUIRE(edge2.span == 1);

                auto edge3_id = db.GetRouter()->GetRouteEdge(route->id, 2);
                auto edge3 = db.GetGraph()->GetEdge(edge3_id);
                REQUIRE(edge3.weight == 6);
                REQUIRE(edge3.edge_type == Graph::EDGE_TYPE::WAIT);
                REQUIRE(edge3.name == "Biryulyovo Tovarnaya");

                auto edge4_id = db.GetRouter()->GetRouteEdge(route->id, 3);
                auto edge4 = db.GetGraph()->GetEdge(edge4_id);
                REQUIRE(edge4.weight == Approx(8.31));
                REQUIRE(edge4.edge_type == Graph::EDGE_TYPE::BUS);
                REQUIRE(edge4.name == "635");
                REQUIRE(edge4.span == 2);
            }
        }
    }
}