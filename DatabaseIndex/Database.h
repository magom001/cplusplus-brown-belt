#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>

#include <iostream>

using namespace std;
using User = string;
using ID = string;
using Karma = int;
using Timestamp = int;

struct Record {
    string id;
    string title;
    string user;
    int timestamp;
    int karma;
};

class Database {
public:
    bool Put(const Record& record) {
        const auto [it, wasInserted] = db_.insert({record.id, record});
        if (wasInserted) {
            UpdateIndices(record);
        }

        return wasInserted;
    };

    const Record* GetById(const string& id) const {
        try {
            return &db_.at(id);
        } catch(exception& ex) {
            return nullptr;
        }
    };

    bool Erase(const string& id) {
        const auto& r = db_.find(id);

        if (r == db_.end()) {
            return false;
        }

        RemoveIndices((*r).second);

        db_.erase(r);

        return true;
    };

    template <typename Callback>
    void RangeByTimestamp(int low, int high, const Callback& callback) const {
        auto lower_bound = timestamp_index.lower_bound(low);
        auto upper_bound = timestamp_index.upper_bound(high);
        for (auto it = lower_bound; it != upper_bound; ++it) {
            const auto& ids = (*it).second;
            for ( auto id : ids) {
                bool fetchNext = callback(*GetById(id));

                if (!fetchNext) {
                    return;
                }
            }
        }
    };

    template <typename Callback>
    void RangeByKarma(int low, int high, const Callback& callback) const {
        auto lower_bound = karma_index.lower_bound(low);
        auto upper_bound = karma_index.upper_bound(high);
        for (auto it = lower_bound; it != upper_bound; ++it) {
            const auto& ids = (*it).second;
            for ( auto id : ids) {
                bool fetchNext = callback(*GetById(id));

                if (!fetchNext) {
                    return;
                }
            }
        }
    };

    template <typename Callback>
    void AllByUser(const string& user, const Callback& callback) const {
        try {
            for (auto id: user_index.at(user)) {
                bool fetchNext = callback(*GetById(id));

                if (!fetchNext) {
                    return;
                }
            }
        } catch(exception& ex) {
            return;
        }
    };

private:
    void UpdateIndices(const Record& r) {
        karma_index[r.karma].insert(r.id);
        timestamp_index[r.timestamp].insert(r.id);
        user_index[r.user].insert(r.id);
    }

    void RemoveIndices(const Record& r) {
        karma_index[r.karma].erase(r.id);
        timestamp_index[r.timestamp].erase(r.id);
        user_index[r.user].erase(r.id);
    }

    unordered_map<ID, Record> db_ = {};
    unordered_map<User, unordered_set<ID>> user_index = {};
    map<Karma, unordered_set<ID>> karma_index = {};
    map<Timestamp, unordered_set<ID>> timestamp_index{};
};
