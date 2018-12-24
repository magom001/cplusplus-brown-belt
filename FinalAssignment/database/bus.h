#pragma once

#include <iostream>
#include <string_view>
#include <vector>
#include <memory>
#include "stop.h"

class Bus {
public:
    Bus(std::string&& bus_number);
    const std::string& GetBusNumber() const;
    double CalculateRouteDistance() const;
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
