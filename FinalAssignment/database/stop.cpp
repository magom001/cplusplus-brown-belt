#include "stop.h"

using namespace std;

Stop::Stop(string &&stop_name) : stop_name(stop_name), coordinates({0.0, 0.0}) {}
Stop::Stop(std::string&& stop_name, double latitude, double longitude) : stop_name(stop_name), coordinates({latitude, longitude}) {}

const string Stop::GetName() const {
    return this->stop_name;
}

const Coordinates &Stop::GetCoordinates() const {
    return coordinates;
}

void Stop::SetCoordinates(Coordinates &&coords) {
    coordinates = coords;
}


istream &operator>>(istream &is, Coordinates &coordinates) {
    string latitude, longitude;
    getline(is, latitude, ',');
    coordinates.latitude = stod(latitude);
    is >> coordinates.longitude;
    return is;
}

double CalculateDistanceBetweenTwoStops(const Coordinates &pt1, const Coordinates &pt2) {
    return acos(sin(pt1.latitude * RAD) * sin(pt2.latitude * RAD) +
                cos(pt1.latitude * RAD) * cos(pt2.latitude * RAD) * cos(abs(pt1.longitude * RAD - pt2.longitude * RAD))) *
                EARTH_RADIUS;
}