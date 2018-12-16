#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>

using namespace std;

template<class T>
class ObjectPool {
public:
    T *Allocate() {
        if (!free_.empty()) {
            auto temp = free_.front();
            free_.pop();
            busy_.insert(temp);
            return temp;
        }
        T *temp = new T();
        busy_.insert(temp);
        return temp;
    };

    T *TryAllocate() {
        if (!free_.empty()) {
            return this->Allocate();
        }

        return nullptr;
    };

    void Deallocate(T *object) {
        if (auto temp_it = busy_.find(object); temp_it != busy_.end()) {
            free_.push(*temp_it);
            busy_.erase(temp_it);
        } else {
            throw invalid_argument("invalid argument");
        }
    };

    ~ObjectPool() {
        for (auto x : busy_) {
            delete x;
        }
        busy_.clear();

        while(!free_.empty()) {
            delete free_.front();
            free_.pop();
        }

    };

private:
    queue<T *> free_ = {};
    set<T *> busy_ = {};
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}