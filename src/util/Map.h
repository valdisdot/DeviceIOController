#ifndef MAP_H
#define MAP_H

#include <map>
#include <string.h>

template <typename T>
struct CommonComparator {
    bool operator()(const T& a, const T& b) const {
        return a < b;
    }
};

struct CStringComparator {
    bool operator()(const char* a, const char* b) const {
        return strcmp(a, b) < 0;
    }
};

template <typename K, typename V, typename comparator = std::less<K>>
class Map {
   private:
    std::map<K, V, comparator> stdMap;

   public:
    void put(const K& key, const V& value) {
        remove(key);
        stdMap[key] = value;
    }

    void remove(const K& key) {
        typename std::map<K, V, comparator>::iterator it = stdMap.find(key);
        if (it != stdMap.end()) {
            stdMap.erase(it);
        }
    }

    bool containsKey(const K& key) {
        return stdMap.find(key) != stdMap.end();
    }

    V* get(const K& key) {
        typename std::map<K, V, comparator>::iterator it = stdMap.find(key);
        if (it != stdMap.end()) {
            return &(it->second);
        }
        return nullptr;
    }

    V* getOrDefault(const K& key, V* defaultValue) {
        typename std::map<K, V, comparator>::iterator it = stdMap.find(key);
        return (it != stdMap.end()) ? &(it->second) : defaultValue;
    }

    void clear() {
        stdMap.clear();
    }

    bool isEmpty() {
        return stdMap.empty();
    }

    int size() {
        return stdMap.size();
    }
};

#endif // MAP_H
