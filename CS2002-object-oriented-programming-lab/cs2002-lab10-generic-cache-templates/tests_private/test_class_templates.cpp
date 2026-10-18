#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <stdexcept>
#include "generic_cache.hpp"

void test_cache_zero_capacity_exception() {
    bool caught = false;
    try {
        GenericCache<int, int> invalid_cache(0);
    } catch (const std::invalid_argument&) {
        caught = true;
    }
    assert(caught);
}

void test_cache_fifo_eviction() {
    GenericCache<std::string, int> cache(3);
    cache.put("A", 100);
    cache.put("B", 200);
    cache.put("C", 300);

    assert(cache.size() == 3);

    // Adding 4th item should evict A
    cache.put("D", 400);
    assert(cache.size() == 3);
    assert(!cache.contains("A"));
    assert(cache.contains("B"));
    assert(cache.contains("C"));
    assert(cache.contains("D"));

    // Adding 5th item should evict B
    cache.put("E", 500);
    assert(!cache.contains("B"));
    assert(cache.contains("C"));
    assert(cache.contains("D"));
    assert(cache.contains("E"));
}

void test_cache_update_does_not_evict() {
    GenericCache<int, double> cache(2);
    cache.put(1, 1.1);
    cache.put(2, 2.2);

    // Updating key 1 should not change size or trigger eviction
    cache.put(1, 1.99);
    assert(cache.size() == 2);
    assert(cache.get(1).value() == 1.99);
    assert(cache.get(2).value() == 2.2);
}

void test_cache_complex_type() {
    struct Student {
        std::string name;
        int gpa_x10;
        bool operator==(const Student& o) const {
            return name == o.name && gpa_x10 == o.gpa_x10;
        }
    };

    GenericCache<int, Student> student_cache(5);
    student_cache.put(101, {"Alice", 38});
    student_cache.put(102, {"Bob", 35});

    assert(student_cache.contains(101));
    auto s = student_cache.get(101);
    assert(s.has_value());
    assert(s.value().name == "Alice");
    assert(s.value().gpa_x10 == 38);
}

int main() {
    std::cout << "[Private Test] Running Class Templates Test Suite..." << std::endl;
    test_cache_zero_capacity_exception();
    test_cache_fifo_eviction();
    test_cache_update_does_not_evict();
    test_cache_complex_type();
    std::cout << "[Private Test] Class Templates Test Suite PASSED" << std::endl;
    return 0;
}
