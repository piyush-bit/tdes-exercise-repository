#include "generic_cache.hpp"

// ============================================================================
// Function Template: findMaxMetric
// ============================================================================

template <typename T>
T findMaxMetric(const std::vector<T>& metrics) {
    // TODO: Implement findMaxMetric template function.
    // 1. Check if metrics vector is empty. If empty, throw std::invalid_argument.
    // 2. Find and return the maximum element in metrics.
    (void)metrics;
    throw std::invalid_argument("findMaxMetric not implemented");
}

// ============================================================================
// Class Template: GenericCache
// ============================================================================

template <typename K, typename V>
GenericCache<K, V>::GenericCache(size_t capacity) : capacity_(capacity) {
    // TODO: Implement constructor.
    // Check if capacity == 0, throw std::invalid_argument if so.
    if (capacity == 0) {
        throw std::invalid_argument("Capacity must be greater than 0");
    }
}

template <typename K, typename V>
void GenericCache<K, V>::put(const K& key, const V& value) {
    // TODO: Implement put operation.
    // Insert or update key-value pair.
    // If key is new and cache is at capacity, evict the oldest inserted key.
    (void)key;
    (void)value;
}

template <typename K, typename V>
std::optional<V> GenericCache<K, V>::get(const K& key) const {
    // TODO: Implement get operation.
    // Return std::optional<V> with value if found, or std::nullopt if key does not exist.
    (void)key;
    return std::nullopt;
}

template <typename K, typename V>
bool GenericCache<K, V>::contains(const K& key) const {
    // TODO: Implement contains operation.
    // Return true if key exists in cache, false otherwise.
    (void)key;
    return false;
}

template <typename K, typename V>
size_t GenericCache<K, V>::size() const {
    // TODO: Implement size operation.
    // Return current number of cached items.
    return 0;
}

template <typename K, typename V>
size_t GenericCache<K, V>::capacity() const {
    // TODO: Implement capacity operation.
    // Return maximum capacity of cache.
    return capacity_;
}

template <typename K, typename V>
void GenericCache<K, V>::clear() {
    // TODO: Implement clear operation.
    // Clear all entries in cache.
}
