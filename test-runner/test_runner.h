//
// Created by a.magomedov on 21.08.2018.
//
#pragma once
#ifndef TEST_RUNNER_TEST_RUNNER_H
#define TEST_RUNNER_TEST_RUNNER_H


#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

#define ASSERT_EQUAL(x, y) {                                        \
    std::ostringstream assertion_error_hint;                        \
    assertion_error_hint << #x << " != " << #y << ", "              \
    <<__FILE__ << ":" << __LINE__;                                  \
    AssertEqual(x, y , assertion_error_hint.str());                 \
    }                                                               \

#define ASSERT(x) {                             \
    std::ostringstream os;                      \
    os << #x << " is false, "                   \
    <<__FILE__ << ":" << __LINE__;              \
    Assert(x, os.str());                        \
    }                                           \

#define RUN_TEST(tr, func) \
    tr.RunTest(func, #func)

template<class T>
ostream &operator<<(ostream &os, const set<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template<class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << "{";
    bool first = true;
    for (const auto &kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T>
ostream &operator<<(ostream &os, const vector<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T &t, const U &u,
                 const string &hint) {
    if (t != u) {
        ostringstream os_assert_equal_stream;
        os_assert_equal_stream << "Assertion failed: " << t <<
           " != " << u
           << " hint: " << hint;
        throw runtime_error(os_assert_equal_stream.str());
    }
}

void Assert(bool b, const string &hint);

class TestRunner {
public:
    template<class TestFunc>
    void RunTest(TestFunc func, const string &test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (runtime_error &e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
    }

    ~TestRunner();

private:
    int fail_count = 0;
};


#endif //TEST_RUNNER_TEST_RUNNER_H
