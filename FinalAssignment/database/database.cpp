#include "database.h"
#include "algorithm"
#include "parse.h"

using namespace std;

Database::Database() {
    stops.reserve(2000);
    buses.reserve(2000);
}

shared_ptr<Stop> Database::GetStop(const string_view stop_name) {
    try {
        return stops.at(stop_name);
    } catch(...) {
        return AddStop(make_shared<Stop>(stop_name));
    }
}

shared_ptr<Stop> Database::AddStop(shared_ptr<Stop> stop_ptr) {
    try {
        auto ptr = stops.at(stop_ptr->name);
        ptr->lat = stop_ptr->lat;
        ptr->lon = stop_ptr->lon;
        return ptr;
    } catch(...) {
        auto [it, is_inserted] = stops.insert({stop_ptr->name, move(stop_ptr)});
        return (*it).second;
    }
}

shared_ptr<Bus> Database::AddBus(string_view bus_number, vector<string_view>&& stop_names) {
    vector<shared_ptr<Stop>> bus_stops(stop_names.size());
    transform(stop_names.begin(), stop_names.end(), bus_stops.begin(),
            [this](string_view s) -> shared_ptr<Stop> { return GetStop(s); });

    auto stripped_bus_number = Strip(bus_number);
    auto bus_ptr = make_shared<Bus>(stripped_bus_number, move(bus_stops));
    auto [it, is_updated] = buses.insert_or_assign(stripped_bus_number, move(bus_ptr));
    return (*it).second;
}

shared_ptr<Bus> Database::GetBus(string_view bus_number) {
    try {
        return buses.at(bus_number);
    } catch(...) {
        return nullptr;
    }
}