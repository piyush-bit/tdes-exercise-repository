#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include "generic_cache.hpp"

void test_function_templates_public() {
    std::cout << "[Public Test] Testing findMaxMetric function template..." << std::endl;

    // Test with int
    std::vector<int> int_metrics = {10, 45, 99, 23, 87};
    assert(findMaxMetric(int_metrics) == 99);

    // Test with double
    std::vector<double> double_metrics = {3.14, 2.71, 9.81, 1.41};
    assert(findMaxMetric(double_metrics) == 9.81);

    // Test with string
    std::vector<std::string> string_metrics = {"apple", "banana", "zebra", "cherry"};
    assert(findMaxMetric(string_metrics) == "zebra");

    // Test empty vector exception
    std::vector<int> empty_vec;
    bool exception_thrown = false;
    try {
        findMaxMetric(empty_vec);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);

    std::cout << "  -> findMaxMetric public tests PASSED" << std::endl;
}

void test_class_template_int_string() {
    std::cout << "[Public Test] Testing GenericCache<int, std::string>..." << std::endl;

    GenericCache<int, std::string> cache(3);
    assert(cache.size() == 0);
    assert(cache.capacity() == 3);
    assert(!cache.contains(1));

    cache.put(1, "one");
    cache.put(2, "two");
    assert(cache.size() == 2);
    assert(cache.contains(1));
    assert(cache.contains(2));

    auto val1 = cache.get(1);
    assert(val1.has_value());
    assert(val1.value() == "one");

    auto val_missing = cache.get(99);
    assert(!val_missing.has_value());

    // Update existing key
    cache.put(1, "ONE_UPDATED");
    assert(cache.size() == 2);
    assert(cache.get(1).value() == "ONE_UPDATED");

    // Eviction test (capacity = 3)
    cache.put(3, "three"); // cache now has 1, 2, 3
    assert(cache.size() == 3);
    cache.put(4, "four");  // should evict key 1 (oldest)
    assert(cache.size() == 3);
    assert(!cache.contains(1));
    assert(cache.contains(2));
    assert(cache.contains(3));
    assert(cache.contains(4));

    cache.clear();
    assert(cache.size() == 0);
    assert(!cache.contains(2));

    std::cout << "  -> GenericCache<int, std::string> public tests PASSED" << std::endl;
}

void test_class_template_double_string() {
    std::cout << "[Public Test] Testing GenericCache<double, std::string>..." << std::endl;

    GenericCache<double, std::string> cache(2);
    cache.put(1.5, "sensor_a");
    cache.put(2.5, "sensor_b");

    assert(cache.contains(1.5));
    assert(cache.get(2.5).value() == "sensor_b");

    std::cout << "  -> GenericCache<double, std::string> public tests PASSED" << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << " Running CS2002 Lab 10 Public Tests" << std::endl;
    std::cout << "========================================" << std::endl;

    test_function_templates_public();
    test_class_template_int_string();
    test_class_template_double_string();

    std::cout << "========================================" << std::endl;
    std::cout << " ALL PUBLIC TESTS PASSED SUCCESSFULLY!" << std::endl;
    std::cout << "========================================" << std::endl;
    return 0;
}
