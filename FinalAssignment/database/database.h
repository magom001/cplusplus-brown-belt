#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "bus.h"
#include "stop.h"
#include "response.h"
#include "json.h"
#include "graph.h"
#include "router.h"

struct RoutingSettings {
    RoutingSettings() = default;
    RoutingSettings(double, double);
    double bus_wait_time;
    double bus_velocity;
};

class Database {
public:
    Database();
public:
    void InsertBusItinerary(std::istream& is);
    void InsertStop(std::istream& is);
    const std::shared_ptr<Bus> TryGetBus(std::string_view) const;
    const std::shared_ptr<Stop> TryGetStop(std::string_view) const;
    std::vector<std::shared_ptr<Response>> HandleStatRequests(std::vector<Json::Node>) const;
    void HandleBaseRequests(std::vector<Json::Node>);
    std::shared_ptr<Stop> GetStop(std::string_view stop_name);
    size_t GetNumberOfStops() const;
    size_t GetNumberOfBusRoutes() const;
public:
    void SetRoutingSettings(RoutingSettings&&);
    void BuildGraph();
    const std::shared_ptr<Graph::Router<double>> GetRouter() const;
    const std::shared_ptr<Graph::DirectedWeightedGraph<double>> GetGraph() const;
private:
    std::shared_ptr<Graph::DirectedWeightedGraph<double>> dwg;
    std::shared_ptr<Graph::Router<double>> router;
    RoutingSettings routing_settings;
private:
    template<typename T>
    void InsertBus(std::string&& bus_number, std::vector<T>&& stop_names, bool is_roundtrip) {
        auto bus_ptr = GetBus(bus_number);
        bus_ptr->SetIsCyclic(is_roundtrip);
        std::vector<std::shared_ptr<Stop>> stops(stop_names.size());
        transform(stop_names.begin(), stop_names.end(), stops.begin(), [this, &bus_ptr, bus_number](T s) {
            auto stop_ptr = GetStop(std::string_view(s));
            stop_ptr->AddBus(bus_number);
            auto x = stop_ptr->GetBuses();
            return stop_ptr;
        });

        bus_ptr->SetBusStops(move(stops));
    }
    void HandleBaseStopRequest(std::map<std::string, Json::Node> &&);
    void HandleBaseBusRequest(std::map<std::string, Json::Node> &&);
    std::shared_ptr<Response> HandleStatStopRequest(std::map<std::string, Json::Node> &&) const;
    std::shared_ptr<Response> HandleStatBusRequest(std::map<std::string, Json::Node> &&) const;
    std::shared_ptr<Response> HandleRouteRequest(std::map<std::string, Json::Node> &&) const;
    std::shared_ptr<Bus> GetBus(std::string_view bus_number);
    std::unordered_map<std::string, std::shared_ptr<Bus>> bus_routes;
    std::unordered_map<std::string, std::shared_ptr<Stop>> stops;
};