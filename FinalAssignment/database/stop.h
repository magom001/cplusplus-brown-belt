#pragma once

#include <string>
#include <iostream>
#include <cmath>
#include <set>
#include <memory>
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
    double latitude;
    double longitude;
};

std::istream &operator>>(std::istream &, Coordinates &);

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
    void AddBus(const std::string&);
    const std::set<std::string>& GetBuses() const;
private:
    std::set<std::string> buses;
    std::string stop_name;
    Coordinates coordinates;
};

std::ostream& operator<<(std::ostream &, Stop &);

double CalculateDistanceBetweenTwoStops(const Coordinates &, const Coordinates &);