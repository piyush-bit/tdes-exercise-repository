#ifndef GENERIC_CACHE_HPP
#define GENERIC_CACHE_HPP

#include <vector>
#include <unordered_map>
#include <deque>
#include <string>
#include <stdexcept>
#include <optional>
#include <algorithm>
#include <cstddef>

// Function Template: findMaxMetric
// Finds and returns the maximum metric value in a vector of elements.
// Throws std::invalid_argument if the metrics vector is empty.
template <typename T>
T findMaxMetric(const std::vector<T>& metrics);

// Class Template: GenericCache
// A generic key-value cache with bounded capacity and FIFO eviction strategy.
template <typename K, typename V>
class GenericCache {
private:
    std::unordered_map<K, V> cache_;
    std::deque<K> key_order_;
    size_t capacity_;

public:
    // Constructor specifying maximum capacity (default = 100).
    // Throws std::invalid_argument if capacity == 0.
    explicit GenericCache(size_t capacity = 100);

    // Insert or update key-value pair.
    // If key exists, update value.
    // If new key and cache is at capacity, evict oldest key before insertion.
    void put(const K& key, const V& value);

    // Retrieve value for key. Returns std::optional<V> (std::nullopt if missing).
    std::optional<V> get(const K& key) const;

    // Check if key exists in cache.
    bool contains(const K& key) const;

    // Return current number of cached elements.
    size_t size() const;

    // Return maximum capacity of cache.
    size_t capacity() const;

    // Remove all cached items.
    void clear();
};

#include "generic_cache.cpp"

#endif // GENERIC_CACHE_HPP
