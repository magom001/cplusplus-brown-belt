#pragma once
#include <iostream>
#include "database.h"
#include "bus.h"
#include "stop.h"
#include "parse.h"

using namespace std;

void HandleDbCreationCommands(istream& is, Database& db) {
    string op_code;
    is >> op_code;

    if (op_code == "Stop") {
        Stop s;
        is >> s;
        db.AddStop(make_shared<Stop>(s));
    } else if(op_code == "Bus") {
        string *bus_number = new string();
        string line;

        getline(is, *bus_number, ':');
        getline(is, line);

        auto stop_names = GetStopNames(line);
        db.AddBus(*bus_number, move(stop_names));
    }
}

void HandleDbRequests(istream& is, ostream &os, Database& db) {
    string op_code;
    is >> op_code;
    if(op_code == "Bus") {
        string bus_number;
        getline(is, bus_number);

        auto trimmed_bus_number = Strip(bus_number);

        auto bus_ptr = db.GetBus(trimmed_bus_number);
        if(bus_ptr) {
            os << *bus_ptr;
        } else {
            os << "Bus " << trimmed_bus_number << ": not found\n";
        }
    }
}

void Start(istream &is, ostream &os) {
    Database db;
    size_t op_counter;
    is >> op_counter;

    for (auto i = 0; i < op_counter; ++i) {
        HandleDbCreationCommands(is, db);
    }

    is >> op_counter;
    for (auto i = 0; i < op_counter; ++i) {
        HandleDbRequests(is, os, db);
    }
}