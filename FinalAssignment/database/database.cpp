#include "database.h"
#include <algorithm>
#include <utility>
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
    } catch (...) {
        return nullptr;
    }
}

const shared_ptr<Stop> Database::TryGetStop(string_view stop_name) const {
    try {
        return stops.at(string(Strip(stop_name)));
    } catch (...) {
        return nullptr;
    }
}

shared_ptr<Bus> Database::GetBus(string_view bus_number) {
    try {
        return bus_routes.at(string(Strip(bus_number)));
    } catch (...) {
        string number(Strip(bus_number));

        auto bus_ptr = make_shared<Bus>(move(number));
        bus_routes[bus_ptr->GetBusNumber()] = bus_ptr;

        return bus_ptr;
    }
}

shared_ptr<Stop> Database::GetStop(string_view stop_name) {
    try {
        return stops.at(string(Strip(stop_name)));
    } catch (...) {
        string name(Strip(stop_name));

        auto stop_ptr = make_shared<Stop>(move(name));
        stops[stop_ptr->GetName()] = stop_ptr;

        return stop_ptr;
    }
}

void Database::InsertBusItinerary(istream &is) {
    string bus_number;
    getline(is, bus_number, ':');

    // auto bus_ptr = GetBus(bus_number);

    string stop_names;
    getline(is, stop_names);

    const char delimiter = (stop_names).find('>') != string::npos ? '>' : '-';

    // Кольцевой маршрут вводится с '>', некольцевой с '-'
    bool is_roundtrip = false;
    if (delimiter == '>') {
        is_roundtrip = true;
    }

    auto stop_names_vector = SplitBy(stop_names, delimiter);

    InsertBus(move(bus_number), move(stop_names_vector), is_roundtrip);
//    vector<shared_ptr<Stop>> stops(bus_names.size());
//    transform(bus_names.begin(), bus_names.end(), stops.begin(), [this, &bus_ptr](string_view s) {
//        auto stop_ptr = GetStop(s);
//        stop_ptr->AddBus(bus_ptr->GetBusNumber());
//        return stop_ptr;
//    });

    // bus_ptr->SetBusStops(move(stops));
};

pair<string_view, uint> ParseDistanceToStop(string_view sv) {
    auto m_char_pos = sv.find('m');
    return {sv.substr(m_char_pos + 5, sv.size()), stoul(string(sv.substr(0, m_char_pos)))};
}

void Database::InsertStop(istream &is) {
    string stop_name;
    getline(is, stop_name, ':');
    auto stop_ptr = GetStop(stop_name);

    // get the rest of the input
    string stop_info_string;
    getline(is, stop_info_string);

    // split the string by ,
    auto stop_info = SplitBy(stop_info_string, ',');

    // first two elements must be latitude and longitude
    double latitude = stod(string(stop_info[0]));
    double longitude = stod(string(stop_info[1]));

    Coordinates coords(latitude, longitude);
    stop_ptr->SetCoordinates(move(coords));

    // the rest, if any, must be distance
    for (auto it = stop_info.begin() + 2; it != stop_info.end(); ++it) {
        auto distance_to_stop = ParseDistanceToStop(*it);
        auto another_stop = GetStop(distance_to_stop.first);

        stop_ptr->AddDistanceToAnotherStop(another_stop->GetName(), distance_to_stop.second);
        another_stop->TryAddDistanceToAnotherStop(stop_ptr->GetName(), distance_to_stop.second);
    }
}

vector<shared_ptr<Response>> Database::HandleStatRequests(vector<Json::Node> requests) const {
    vector<shared_ptr<Response>> responses;
    responses.reserve(requests.size());

    for (const auto &r: requests) {
        auto request_body = r.AsMap();
        const auto& type = request_body.at("type").AsString();

        if (type == "Stop") {
            responses.push_back(HandleStatStopRequest(move(request_body)));
        } else if (type == "Bus") {
            responses.push_back(HandleStatBusRequest(move(request_body)));
        }
    }

    return responses;
}

void Database::HandleBaseRequests(vector<Json::Node> requests) {
    for (const auto &r: requests) {
        auto request_body = r.AsMap();
        auto type = request_body.at("type").AsString();

        if (type == "Stop") {
            HandleBaseStopRequest(move(request_body));
        } else if (type == "Bus") {
            HandleBaseBusRequest(move(request_body));
        }
    }
}

void Database::HandleBaseStopRequest(map<string, Json::Node> &&request) {
    auto stop_ptr = GetStop(move(request.at("name").AsString()));
    const auto road_distances = move(request.at("road_distances").AsMap());
    for (const auto &stop: road_distances) {
        uint distance = stop.second.AsInt();
        auto another_stop = GetStop(stop.first);

        stop_ptr->AddDistanceToAnotherStop(another_stop->GetName(), distance);
        another_stop->TryAddDistanceToAnotherStop(stop_ptr->GetName(), distance);
    }

    Coordinates coords(request.at("latitude").AsDouble(), request.at("longitude").AsDouble());
    stop_ptr->SetCoordinates(move(coords));
}

void Database::HandleBaseBusRequest(map<string, Json::Node> &&request) {
    auto bus_number = request.at("name").AsString();
    bool is_roundtrip = request.at("is_roundtrip").AsBool();

    auto stop_nodes = move(request.at("stops").AsArray());
    vector<string> stops;
    stops.reserve(stop_nodes.size());

    for (const auto &node: stop_nodes) {
        stops.push_back(node.AsString());
    }


    InsertBus(move(bus_number), move(stops), is_roundtrip);
}

shared_ptr<Response> Database::HandleStatStopRequest(map<string, Json::Node> &&request) const {
    auto stop_ptr = TryGetStop(request.at("name").AsString());

    if (stop_ptr) {
        return make_shared<ResponseStop>(request.at("id").AsInt(), stop_ptr->GetBuses());
    } else {
        return make_shared<ResponseFailed>(request.at("id").AsInt());
    }
}

shared_ptr<Response> Database::HandleStatBusRequest(map<string, Json::Node> &&request) const {
    auto bus_ptr = TryGetBus(request.at("name").AsString());

    if (bus_ptr) {
        Distance d = bus_ptr->CalculateDistance();
        auto stop_count = bus_ptr->GetNumberOfStops();
        auto unique_stop_count = bus_ptr->GetNumberOfUniqueStops();
        return make_shared<ResponseBus>(request.at("id").AsInt(), d.by_road, d.by_road/d.between_coordinates, stop_count, unique_stop_count);
    } else {
        return make_shared<ResponseFailed>(request.at("id").AsInt());
    }
};