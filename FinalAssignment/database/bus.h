#pragma once

#include <iostream>
#include <string_view>
#include <vector>
#include <memory>
#include <utility>
#include "stop.h"

class Stop;
class Bus;
struct Distance;

class Bus {
public:
    Bus(std::string&& bus_number);
    const std::string& GetBusNumber() const;
    double CalculateRouteDistance() const;
    const Distance CalculateDistance() const;
    void SetBusStops(std::vector<std::shared_ptr<Stop>>&& stops);
    const bool IsCyclic() const;
    void SetIsCyclic(bool flag);
    size_t GetNumberOfStops() const;
    size_t GetNumberOfUniqueStops() const;
private:
    bool is_cyclic = false;
    std::string bus_number;
    std::vector<std::shared_ptr<Stop>> bus_stops;
};

std::ostream& operator<<(std::ostream& os, Bus& bus);
bool operator<(const Bus, const Bus);