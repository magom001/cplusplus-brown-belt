#pragma once

#include <string>
#include <iostream>
#include <cmath>
#include <set>
#include <vector>
#include <memory>
#include <utility>
#include <unordered_map>
#include <set>
#include "global.h"
#include "bus.h"

class Bus;

//template<typename T>
//struct shared_ptr_compare {
//    bool operator() (const std::shared_ptr<T>& b1, const std::shared_ptr<T>& b2) const {
//        return std::less<T>()(*b1, *b2);
//    }
//};

struct Coordinates {
    Coordinates() = default;
    Coordinates(double, double);
    double latitude;
    double longitude;
};

std::istream &operator>>(std::istream &, Coordinates &);

struct Distance {
    double between_coordinates = 0.0;
    uint by_road = 0;
    Distance &operator+=(const Distance &);
};

class Stop {
public:
    Stop() = default;
    Stop(std::string &&);
    Stop(std::string &&, double, double);

public:
    const std::string GetName() const;
    void SetCoordinates(Coordinates &&);
    const Coordinates &GetCoordinates() const;
public:
    void AddDistanceToAnotherStop(const std::string &, uint);
    void TryAddDistanceToAnotherStop(const std::string &, uint);
    uint GetDistanceToStop(const std::string &) const;
public:
    void AddBus(std::string_view);
    const std::set<std::string>& GetBuses() const;
private:
    std::set<std::string> buses;
    std::string stop_name;
    Coordinates coordinates;
    std::unordered_map<std::string, uint> distances_to_stops;
};

std::ostream& operator<<(std::ostream &, Stop &);

double CalculateDistanceBetweenCoordinates(const Coordinates &, const Coordinates &);
Distance CalculateDistanceBetweenStops(const Stop &, const Stop &);