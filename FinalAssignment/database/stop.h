#pragma once

#include <string>
#include <string_view>
#include <iostream>

#define PI 3.1415926535
#define EARTH_RADIUS 6371000.0
#define RAD PI/180.0

using latitude=double;
using longitude=double;

struct Stop {
    Stop() = default;
    Stop(std::string_view name);
    Stop(std::string_view name, latitude lat, longitude lon);
    std::string name;
    latitude lat;
    longitude lon;
};

bool operator==(const Stop& stop1, const Stop& stop2);
bool operator<(const Stop& stop1, const Stop& stop2);
std::istream& operator>>(std::istream& is, Stop& stop);

struct StopHasher {
    size_t operator()(Stop const& s) const;
};

double CalculateDistanceBetweenTwoStops(const Stop& stop1, const Stop& stop2);