#pragma once
#include <iostream>
#include "database.h"
#include "json.h"

namespace Json {
    using namespace std;

    void Start(istream &is, ostream &os) {
        Database db;
        auto document = Json::Load(is);
        auto rootNode = document.GetRoot();
        auto rootNodeMap = rootNode.AsMap();
        auto base_requests = rootNodeMap.at("base_requests").AsArray();

        db.HandleBaseRequests(move(base_requests));
        auto stat_requests = rootNodeMap.at("stat_requests").AsArray();
        auto responses = db.HandleStatRequests(move(stat_requests));

        Json::Stringify(os, responses.begin(), responses.end());
    }
}
