#include "Common.h"
#include <unordered_map>
#include <list>
#include <mutex>

using namespace std;

class LruCache : public ICache {
public:
    LruCache(
            shared_ptr<IBooksUnpacker> books_unpacker,
            const Settings& settings
    ): unpacker(books_unpacker), settings(settings) {}

    BookPtr GetBook(const string& book_name) override {
        lock_guard<mutex> lock(lock_);

        if (cache.find(book_name) == cache.end()) {
            // 1. Get a pointer to the book
            shared_ptr<IBook> book_ptr = move(unpacker->UnpackBook(book_name));

            // 2. Get book's size
            auto book_size = GetBookSize(book_ptr);

            // 3. If book's size is greater than max_memory do not update the cache
            if (book_size > settings.max_memory) {
                return move(book_ptr);
            }

            // 4. Otherwise get current cache size
            auto current_cache_size = this->GetCacheSize();

            // 5. If there is enough space in cache, cache the book
            if ((book_size + current_cache_size) <= settings.max_memory) {
                CacheBook(move(book_ptr), book_size);
            } else {
                // 6. Free cache
                FreeMemory(book_size);
                CacheBook(move(book_ptr), book_size);
            }
        }

        // Move book to front
        MoveBookToFront(book_name);
        return rang.front();
    }

private:
    void MoveBookToFront(const string& book_name) {
        auto book_it = cache[book_name];
        if (book_it != rang.begin()) {
            rang.splice(rang.begin(), rang, book_it, next(book_it));
        }
    }

    void CacheBook(const shared_ptr<IBook> book_ptr, const size_t book_size) {
        this->IncrementCacheSize(book_size);
        rang.push_front(move(book_ptr));
        cache[book_ptr->GetName()] = rang.begin();
    }

    const size_t GetBookSize(const shared_ptr<const IBook> book_ptr) const {
        return (book_ptr->GetContent()).size();
    }

    const size_t GetCacheSize() const {
        return this->cache_size;
    }

    void IncrementCacheSize(size_t size) {
        this->cache_size += size;
    }

    void DecrementCacheSize(size_t size) {
        this->IncrementCacheSize(-size);
    }

    void FreeMemory(size_t size) {
        while((settings.max_memory - GetCacheSize()) < size) {
            auto last_book = move(rang.back());
            rang.pop_back();
            cache.erase(last_book->GetName());
            DecrementCacheSize(GetBookSize(last_book));
        }
    }

private:
    shared_ptr<IBooksUnpacker> unpacker;
    const Settings settings;

    unordered_map<string, list<BookPtr>::iterator> cache;
    list<BookPtr> rang;

    size_t cache_size = 0;

    mutex lock_;
};


unique_ptr<ICache> MakeCache(
        shared_ptr<IBooksUnpacker> books_unpacker,
        const ICache::Settings& settings
) {
    return make_unique<LruCache>(move(books_unpacker), settings);
}