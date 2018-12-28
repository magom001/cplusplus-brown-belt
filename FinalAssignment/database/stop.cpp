#include "stop.h"
#include "parse.h"
#include <iterator>

using namespace std;

Distance &Distance::operator+=(const Distance &rhs) {
    this->between_coordinates += rhs.between_coordinates;
    this->by_road += rhs.by_road;
    return *this;
}

Stop::Stop(string &&stop_name) : stop_name(stop_name), coordinates({0.0, 0.0}) {}
Stop::Stop(string&& stop_name, double latitude, double longitude) : stop_name(stop_name), coordinates({latitude, longitude}) {}

const string Stop::GetName() const {
    return this->stop_name;
}

const Coordinates &Stop::GetCoordinates() const {
    return coordinates;
}

void Stop::SetCoordinates(Coordinates &&coords) {
    coordinates = coords;
}

void Stop::AddBus(string_view bus_number) {
    this->buses.insert(string(Strip(bus_number)));
}

void Stop::AddDistanceToAnotherStop(const std::string &stop_name, uint distance) {
    distances_to_stops[stop_name] = distance;
}

void Stop::TryAddDistanceToAnotherStop(const std::string &stop_name, uint distance) {
    try {
        distances_to_stops.at(stop_name);
    } catch(...) {
        distances_to_stops[stop_name] = distance;
    }
}

uint Stop::GetDistanceToStop(const std::string &stop_name) const {
    return distances_to_stops.at(stop_name);
}

const std::set<std::string>& Stop::GetBuses() const {
    return buses;
}

Coordinates::Coordinates(double latitude, double longitude): latitude(latitude), longitude(longitude) {};

istream &operator>>(istream &is, Coordinates &coordinates) {
    string latitude, longitude;
    getline(is, latitude, ',');
    coordinates.latitude = stod(latitude);
    // getline(is, longitude, ',');
    is >> coordinates.longitude;
    // coordinates.longitude = stod(longitude);

    return is;
}

std::ostream& operator<<(std::ostream &os, Stop& stop) {
    os << "Stop "
        << stop.GetName()
        << ": ";
    if (stop.GetBuses().size() == 0) {
        os << "no buses";
    } else {
        os << "buses ";
        copy(stop.GetBuses().begin(), stop.GetBuses().end(), ostream_iterator<string>(os, " "));
    }
    os << "\n";

    return os;
}

double CalculateDistanceBetweenCoordinates(const Coordinates &pt1, const Coordinates &pt2) {
    return acos(sin(pt1.latitude * RAD) * sin(pt2.latitude * RAD) +
                cos(pt1.latitude * RAD) * cos(pt2.latitude * RAD) * cos(abs(pt1.longitude * RAD - pt2.longitude * RAD))) *
                EARTH_RADIUS;
}

Distance CalculateDistanceBetweenStops(const Stop &s1, const Stop &s2) {
    return {CalculateDistanceBetweenCoordinates(s1.GetCoordinates(), s2.GetCoordinates()), s1.GetDistanceToStop(s2.GetName())};
}