#pragma once

#include <string>
#include <iostream>
#include <cmath>
#include "global.h"

struct Coordinates {
    double latitude;
    double longitude;
};

std::istream& operator>>(std::istream& is, Coordinates& coordinates);

class Stop {
public:
    Stop() = default;
    Stop(std::string&& stop_name);
    Stop(std::string&& stop_name, double latitude, double longitude);
    const std::string GetName() const;
    void SetCoordinates(Coordinates&& coords);
    const Coordinates& GetCoordinates() const;
private:
    std::string stop_name;
    Coordinates coordinates;
};

double CalculateDistanceBetweenTwoStops(const Coordinates &pt1, const Coordinates &pt2);