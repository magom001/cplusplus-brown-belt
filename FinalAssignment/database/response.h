#pragma once

#include <ostream>
#include <string>
#include <set>
#include "json.h"

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