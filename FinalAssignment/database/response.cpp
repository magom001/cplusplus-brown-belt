//
// Created by Arkady Magomedov on 27/12/2018.
//

#include "response.h"
#include "json.h"

using namespace std;

Response::Response(size_t request_id) : request_id(request_id) {}

ResponseFailed::ResponseFailed(size_t request_id, string &&error_message)
        : Response(request_id),
          error_message(error_message) {}

void ResponseFailed::Stringify(ostream &os) {
    os << '{';
    os << '"' << "request_id" << '"' << ':';
    os << request_id;
    os << ',';
    os << '"' << "error_message" << '"' << ':';
    os << '"' << error_message << '"';
    os << '}';
}

ResponseStop::ResponseStop(size_t request_id, const set<string> &buses)
        : Response(request_id),
          buses(buses) {}

void ResponseStop::Stringify(ostream &os) {
    os << '{';
    os << '"' << "buses" << '"' << ':';
    Json::Stringify(os, buses.begin(), buses.end());
    os << ',';
    os << '"' << "request_id" << '"' << ':';
    os << request_id;
    os << '}';
}


ResponseBus::ResponseBus(size_t request_id, uint route_length, double curvature, uint stop_count,
                         uint unique_stop_count)
        : Response(request_id),
          route_length(route_length),
          curvature(curvature),
          stop_count(stop_count),
          unique_stop_count(unique_stop_count) {}

void ResponseBus::Stringify(std::ostream &os) {
    os << '{';
    os << '"' << "route_length" << '"' << ':';
    os << route_length << ',';
    os << '"' << "request_id" << '"' << ':';
    os << request_id << ',';
    os << '"' << "curvature" << '"' << ':';
    os << curvature << ',';
    os << '"' << "stop_count" << '"' << ':';
    os << stop_count << ',';
    os << '"' << "unique_stop_count" << '"' << ':';
    os << unique_stop_count;
    os << '}';
}
