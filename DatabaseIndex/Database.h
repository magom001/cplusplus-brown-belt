#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <list>

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
        if (id_index.find(record.id) == id_index.end()) {
            const auto new_rec_it = storage_.insert(storage_.end(), record);
            id_index[record.id] = new_rec_it;

            UpdateIndices(record, new_rec_it);
            return true;
        }

        return false;
    };

    const Record* GetById(const string& id) const {
        try {
            return &(*id_index.at(id));
        } catch(exception& ex) {
            return nullptr;
        }
    };

    bool Erase(const string& id) {
        const auto r_it = id_index.find(id);
        if (r_it == id_index.end()) {
            return false;
        }

        RemoveIndices(*(*r_it).second,(*r_it).second);
        storage_.erase((*r_it).second);
        id_index.erase(id);

        return true;
    };

    template <typename Callback>
    void RangeByTimestamp(int low, int high, const Callback& callback) const {
        auto lower_bound = timestamp_index.lower_bound(low);
        auto upper_bound = timestamp_index.upper_bound(high);
        for (auto it = lower_bound; it != upper_bound; ++it) {
            const auto& rec_ptrs = (*it).second;
            for ( auto rec_ptr : rec_ptrs) {
                bool fetchNext = callback(*rec_ptr);

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
            const auto& rec_ptrs = (*it).second;
            for ( auto rec_ptr : rec_ptrs) {
                bool fetchNext = callback(*rec_ptr);

                if (!fetchNext) {
                    return;
                }
            }
        }
    };

    template <typename Callback>
    void AllByUser(const string& user, const Callback& callback) const {
        try {
            for (auto rec_ptr: user_index.at(user)) {
                bool fetchNext = callback(*rec_ptr);

                if (!fetchNext) {
                    return;
                }
            }
        } catch(exception& ex) {
            return;
        }
    };

private:
    void UpdateIndices(const Record& r, list<Record>::iterator it) {
         karma_index[r.karma].insert(&(*it));
         timestamp_index[r.timestamp].insert(&(*it));
        user_index[r.user].insert(&(*it));
    }

    void RemoveIndices(const Record& r, list<Record>::iterator it) {
         karma_index[r.karma].erase(&(*it));
         timestamp_index[r.timestamp].erase(&(*it));
        user_index[r.user].erase(&(*it));
    }

    list<Record> storage_ = {};
    unordered_map<ID, Record> db_ = {};
    unordered_map<ID, list<Record>::iterator> id_index = {};
    unordered_map<User, unordered_set<Record*>> user_index = {};
    map<Karma, unordered_set<Record*>> karma_index = {};
    map<Timestamp, unordered_set<Record*>> timestamp_index{};
};
