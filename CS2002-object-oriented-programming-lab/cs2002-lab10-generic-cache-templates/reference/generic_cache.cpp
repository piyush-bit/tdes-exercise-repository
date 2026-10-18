#include "generic_cache.hpp"

// ============================================================================
// Function Template: findMaxMetric
// ============================================================================

template <typename T>
T findMaxMetric(const std::vector<T>& metrics) {
    if (metrics.empty()) {
        throw std::invalid_argument("metrics vector cannot be empty");
    }
    return *std::max_element(metrics.begin(), metrics.end());
}

// ============================================================================
// Class Template: GenericCache
// ============================================================================

template <typename K, typename V>
GenericCache<K, V>::GenericCache(size_t capacity) : capacity_(capacity) {
    if (capacity == 0) {
        throw std::invalid_argument("Capacity must be greater than 0");
    }
}

template <typename K, typename V>
void GenericCache<K, V>::put(const K& key, const V& value) {
    auto it = cache_.find(key);
    if (it != cache_.end()) {
        it->second = value;
        return;
    }

    if (cache_.size() >= capacity_) {
        K oldest = key_order_.front();
        key_order_.pop_front();
        cache_.erase(oldest);
    }

    cache_[key] = value;
    key_order_.push_back(key);
}

template <typename K, typename V>
std::optional<V> GenericCache<K, V>::get(const K& key) const {
    auto it = cache_.find(key);
    if (it != cache_.end()) {
        return it->second;
    }
    return std::nullopt;
}

template <typename K, typename V>
bool GenericCache<K, V>::contains(const K& key) const {
    return cache_.find(key) != cache_.end();
}

template <typename K, typename V>
size_t GenericCache<K, V>::size() const {
    return cache_.size();
}

template <typename K, typename V>
size_t GenericCache<K, V>::capacity() const {
    return capacity_;
}

template <typename K, typename V>
void GenericCache<K, V>::clear() {
    cache_.clear();
    key_order_.clear();
}
