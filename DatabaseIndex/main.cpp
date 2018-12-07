#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

#include "Database.h"
#include "test_runner.h"

using namespace std;

void TestRangeBoundaries() {
    const int good_karma = 1000;
    const int bad_karma = -10;

    Database db;
    db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
    db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

    int count = 0;
    db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
        ++count;
        return true;
    });

    ASSERT_EQUAL(2, count);
}

void TestTimestampBoundaries() {
    const int ts1 = 1536107260;
    const int ts2 = 1536107280;

    Database db;
    db.Put({"id1", "Hello there", "master", ts1, 1000});
    db.Put({"id2", "O>>-<", "general2", ts2, 1000});

    int count = 0;
    db.RangeByTimestamp(ts1, ts2, [&count](const Record&) {
        ++count;
        return true;
    });

    ASSERT_EQUAL(2, count);
}

void TestSameUser() {
    Database db;
    db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
    db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

    int count = 0;
    db.AllByUser("master", [&count](const Record&) {
        ++count;
        return true;
    });

    ASSERT_EQUAL(2, count);

    count = 0;
    db.AllByUser("arshloch", [&count](const Record&) {
        ++count;
        return true;
    });

    ASSERT_EQUAL(0, count);
}

void TestReplacement() {
    const string final_body = "Feeling sad";

    Database db;
    db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
    db.Erase("id");
    db.Put({"id", final_body, "not-master", 1536107260, -10});

    auto record = db.GetById("id");
    ASSERT(record != nullptr);
    ASSERT_EQUAL(final_body, record->title);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestRangeBoundaries);
    RUN_TEST(tr, TestSameUser);
    RUN_TEST(tr, TestTimestampBoundaries);
    RUN_TEST(tr, TestReplacement);
    return 0;
}