#pragma once

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <string_view>
#include <vector>
#include <memory>

#include "bus.h"
#include "stop.h"



class Database {
public:
    Database();
    std::shared_ptr<Stop> GetStop(const std::string_view stop_name);
    std::shared_ptr<Stop> AddStop(std::shared_ptr<Stop> stop_ptr);
    std::shared_ptr<Bus> AddBus(std::string_view bus_name, std::vector<std::string_view>&& stop_names);
    std::shared_ptr<Bus> GetBus(std::string_view bus_number);
private:
    std::unordered_map<std::string_view, std::shared_ptr<Bus>> buses;
    mutable std::unordered_map<std::string_view, std::shared_ptr<Stop>> stops;
};