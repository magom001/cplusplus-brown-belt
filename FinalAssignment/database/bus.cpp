#include "bus.h"
#include "parse.h"
#include <unordered_set>
#include <iomanip>

using namespace std;

Bus::Bus(std::string_view bus_number)
        : bus_number(bus_number),
        itinerary_distance(0),
        unique_stops(0) {}


Bus::Bus(string_view bus_number, vector<shared_ptr<Stop>> &&stops)
        : bus_number(bus_number),
          stops(stops),
          itinerary_distance(0),
          unique_stops(0) {
    if (this->stops.front() == this->stops.back()) {
        is_cyclic = true;
    }
}

const string_view Bus::GetBusNumber() const {
    return bus_number;
}

const vector<shared_ptr<Stop>> Bus::GetStops() const {
    return stops;
}

void Bus::SetStops(vector<std::shared_ptr<Stop>>&& stops) {
    this->stops = move(stops);
    if (this->stops.front() == this->stops.back()) {
        is_cyclic = true;
    }
}

size_t Bus::GetNumberOfStops() const {
    if (is_cyclic) {
        return stops.size();
    }

    return stops.size() * 2 - 1;
}

size_t Bus::GetNumberOfUniqueStops() {
    if (GetNumberOfStops() > 0 && unique_stops == 0) {
        unordered_set<shared_ptr<Stop>> temp(stops.begin(), stops.end());
        unique_stops = temp.size();
    }

    return unique_stops;
}

double Bus::CalculateItineraryDistance() {
    if (stops.size() < 2) {
        return 0;
    }

    for (auto it = next(stops.begin()); it != stops.end(); ++it) {
        itinerary_distance += CalculateDistanceBetweenTwoStops(**prev(it), **it);
    }

    if (!is_cyclic) {
        itinerary_distance *= 2.0;
    }

    return itinerary_distance;
}

std::ostream& operator<<(std::ostream& os, Bus& bus) {
    os << "Bus "
        << bus.GetBusNumber()
        << ": "
        << bus.GetNumberOfStops()
        << " stops on route, "
        << bus.GetNumberOfUniqueStops()
        << " unique stops, "
        << setprecision(6)
        << fixed
        << bus.CalculateItineraryDistance()
        << " route length"
        << "\n";
    return os;
}

vector<string_view> GetStopNames(string_view sv) {
    // Limit search to 30 characters
    const char ch = sv.find('>') != sv.npos ? '>' : '-';
    return SplitBy(sv, ch);
}