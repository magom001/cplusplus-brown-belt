#pragma once

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <memory>
#include "bus.h"
#include "stop.h"

class Database {
public:
    Database();
public:
    void InsertBusItinerary(std::istream& is);
    void InsertStop(std::istream& is);
    const std::shared_ptr<Bus> TryGetBus(std::string_view) const;
    const std::shared_ptr<Stop> TryGetStop(std::string_view) const;
    std::shared_ptr<Stop> GetStop(std::string_view stop_name);
    size_t GetNumberOfStops() const;
    size_t GetNumberOfBusRoutes() const;
private:

    std::shared_ptr<Bus> GetBus(std::string_view bus_number);
    std::unordered_map<std::string, std::shared_ptr<Bus>> bus_routes;
    std::unordered_map<std::string, std::shared_ptr<Stop>> stops;
};