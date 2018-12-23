#include "stop.h"
#include "parse.h"
#include <cmath>

using namespace std;

Stop::Stop(string_view name): name(name), lat(0.0), lon(0.0){}
Stop::Stop(string_view name, latitude lat, longitude lon): name(name), lat(lat), lon(lon){}

bool operator==(const Stop &stop1, const Stop &stop2) {
    return stop1.name == stop2.name;
}

bool operator<(const Stop &stop1, const Stop &stop2) {
    return stop1.name < stop2.name;
}

istream &operator>>(istream &is, Stop &stop) {
    string name;
    getline(is, name, ':');
    stop.name = Strip(name);
    is >> stop.lat;
    is.ignore(1);
    is >> stop.lon;
    return is;
}


size_t StopHasher::operator()(Stop const &s) const {
    return std::hash<std::string>()(s.name);
}


double CalculateDistanceBetweenTwoStops(const Stop &stop1, const Stop &stop2) {
    return acos(sin(stop1.lat * RAD) * sin(stop2.lat * RAD) +
                cos(stop1.lat * RAD) * cos(stop2.lat * RAD) * cos(stop1.lon * RAD - stop2.lon * RAD)) * EARTH_RADIUS;
}