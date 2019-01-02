#pragma once

#include <ostream>
#include <string>
#include <set>
#include <vector>
#include <variant>
#include "json.h"
#include "graph.h"
#include "router.h"

using Minutes = double;

struct Item {
     Item(Graph::EDGE_TYPE edge_type, std::string name, Minutes time, size_t span);
    Graph::EDGE_TYPE edge_type;
    std::string name;
    Minutes time;
    size_t span = 0;
};

using Items = std::vector<Item>;

// Stringify values
class Response: public Json::IStringifiable {
public:
    explicit Response(size_t request_id);
    virtual ~Response() = default;
protected:
    size_t request_id;
};

class ResponseFailed : public Response {
public:
    explicit ResponseFailed(size_t request_id, std::string &&error_message = "not found");
    void Stringify(std::ostream &) override;
private:
    std::string error_message;
};

class ResponseStop : public Response {
public:
    explicit ResponseStop(size_t request_id, const std::set<std::string>& buses);
    void Stringify(std::ostream &) override;
private:
    const std::set<std::string>& buses;
};

class ResponseBus : public Response {
public:
    explicit ResponseBus(size_t request_id, uint, double, uint, uint);
    void Stringify(std::ostream &) override;
private:
    uint route_length;
    double curvature;
    uint stop_count;
    uint unique_stop_count;
};

class ResponseRoute : public Response {
public:
    explicit ResponseRoute(size_t request_id, Minutes total_time, Items items);
    void Stringify(std::ostream &) override;
private:
    Minutes total_time;
    Items items;
};