#include "database.h"
#include "algorithm"
#include "parse.h"

using namespace std;

Database::Database() {
    stops.reserve(2000);
    bus_routes.reserve(2000);
}

size_t Database::GetNumberOfStops() const { return stops.size(); }
size_t Database::GetNumberOfBusRoutes() const { return bus_routes.size(); }

const shared_ptr<Bus> Database::TryGetBus(string_view bus_number) const {
    try {
        return bus_routes.at(string(Strip(bus_number)));
    } catch(...) {
        return nullptr;
    }
}

shared_ptr<Bus> Database::GetBus(string_view bus_number) {
    try {
        return bus_routes.at(string(Strip(bus_number)));
    } catch(...) {
        string number(Strip(bus_number));

        auto bus_ptr = make_shared<Bus>(move(number));
        bus_routes[bus_ptr->GetBusNumber()] = bus_ptr;

        return bus_ptr;
    }
}

shared_ptr<Stop> Database::GetStop(string_view stop_name) {
    try {
        return stops.at(string(Strip(stop_name)));
    } catch(...) {
        string name(Strip(stop_name));

        auto stop_ptr = make_shared<Stop>(move(name));
        stops[stop_ptr->GetName()] = stop_ptr;

        return stop_ptr;
    }
}

void Database::InsertBusItinerary(istream &is) {
    string bus_number;
    getline(is, bus_number, ':');

    auto bus_ptr = GetBus(bus_number);

    string stop_names;
    getline(is, stop_names);

    const char delimiter = (stop_names).find('>') != string::npos ? '>' : '-';

    // Кольцевой маршрут вводится с '>', некольцевой с '-'
    if(delimiter == '>') {
        bus_ptr->SetIsCyclic(true);
    }

    auto bus_names = SplitBy(stop_names, delimiter);
    vector<shared_ptr<Stop>> stops(bus_names.size());
    transform(bus_names.begin(), bus_names.end(), stops.begin(), [this](string_view s){
       return GetStop(s);
    });

    bus_ptr->SetBusStops(move(stops));
};


void Database::InsertStop(istream& is) {
    string stop_name;
    getline(is, stop_name, ':');
    auto stop_ptr = GetStop(stop_name);
    Coordinates coords;
    is >> coords;

    stop_ptr->SetCoordinates(move(coords));
};