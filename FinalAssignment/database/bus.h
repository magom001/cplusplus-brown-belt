#pragma once

#include <iostream>
#include <string_view>
#include <vector>
#include <memory>
#include "stop.h"

class Bus {
public:
    Bus() = delete;
    Bus(std::string_view bus_number);
    Bus(std::string_view bus_number, std::vector<std::shared_ptr<Stop>>&& stops);

    const std::string_view GetBusNumber() const;

    const std::vector<std::shared_ptr<Stop>> GetStops() const;
    void SetStops(std::vector<std::shared_ptr<Stop>>&& stops);

    double CalculateItineraryDistance();

    size_t GetNumberOfStops() const;

    size_t GetNumberOfUniqueStops();

private:
    std::string_view bus_number;
    std::vector<std::shared_ptr<Stop>> stops;
    double itinerary_distance ;
    bool is_cyclic = false;
    size_t unique_stops;
};

std::ostream& operator<<(std::ostream& os, Bus& bus);

std::vector<std::string_view> GetStopNames(std::string_view sv);