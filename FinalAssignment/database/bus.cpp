#include "bus.h"
#include "parse.h"
#include <unordered_set>
#include <iomanip>

using namespace std;

Bus::Bus(string &&bus_number) : bus_number(bus_number) {}

const string &Bus::GetBusNumber() const {
    return this->bus_number;
}

double Bus::CalculateRouteDistance() const {
    if (bus_stops.size() < 2) {
        return 0.0;
    }

    double distance = 0.0;

    for (auto it = next(bus_stops.begin()); it != bus_stops.end(); ++it) {
        distance += CalculateDistanceBetweenTwoStops((*prev(it))->GetCoordinates(), (*it)->GetCoordinates());
    }

    return IsCyclic() ? distance : distance * 2.0;
}

size_t Bus::GetNumberOfStops() const {
    if (IsCyclic()) {
        return bus_stops.size();
    }

    return bus_stops.size() * 2 - 1;
}

size_t Bus::GetNumberOfUniqueStops() const {
    unordered_set<shared_ptr<Stop>> temp(bus_stops.begin(), bus_stops.end());
    return temp.size();
}

void Bus::SetIsCyclic(bool flag) {
    is_cyclic = flag;
}

const bool Bus::IsCyclic() const {
    return is_cyclic;
}

void Bus::SetBusStops(vector<shared_ptr<Stop>> &&stops) {
    bus_stops = stops;
}

ostream& operator<<(ostream& os, Bus& bus) {
    os << "Bus "
       << bus.GetBusNumber()
       << ": "
       << bus.GetNumberOfStops()
       << " stops on route, "
       << bus.GetNumberOfUniqueStops()
       << " unique stops, "
       << setprecision(6)
       << fixed
       << bus.CalculateRouteDistance()
       << " route length"
       << "\n";

    return os;
}

bool operator<(const Bus b1, const Bus b2) {
    return b1.GetBusNumber() < b2.GetBusNumber();
}