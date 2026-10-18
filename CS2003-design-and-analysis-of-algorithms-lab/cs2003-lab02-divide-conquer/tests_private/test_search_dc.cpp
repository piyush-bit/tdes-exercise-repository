#include "divide_conquer.hpp"
#include <iostream>
#include <vector>
#include <cassert>

void test_empty_and_bounds() {
    std::cout << "[PRIVATE SEARCH] Testing empty vector and out-of-bound ranges..." << std::endl;
    std::vector<Order> empty_v;
    assert(binary_search_dc(empty_v, 100, 0, -1) == -1);

    std::vector<Order> v = {
        Order(10, "A", 100.0, 10, true),
        Order(20, "B", 200.0, 20, false)
    };

    assert(binary_search_dc(v, 10, 1, 0) == -1);
    assert(binary_search_dc(v, 10, -1, 1) == -1);
    assert(binary_search_dc(v, 10, 0, 5) == -1);

    std::cout << "[PASS] Empty & bounds test passed." << std::endl;
}

void test_single_element() {
    std::cout << "[PRIVATE SEARCH] Testing single element vector..." << std::endl;
    std::vector<Order> v = { Order(42, "BTC", 50000.0, 1, true) };

    assert(binary_search_dc(v, 42, 0, 0) == 0);
    assert(binary_search_dc(v, 99, 0, 0) == -1);
    assert(binary_search_dc(v, 10, 0, 0) == -1);

    std::cout << "[PASS] Single element test passed." << std::endl;
}

void test_boundary_and_gaps() {
    std::cout << "[PRIVATE SEARCH] Testing boundaries and gaps..." << std::endl;
    std::vector<Order> v = {
        Order(100, "A", 10.0, 1, true),
        Order(200, "B", 20.0, 2, true),
        Order(300, "C", 30.0, 3, true),
        Order(400, "D", 40.0, 4, true),
        Order(500, "E", 50.0, 5, true)
    };
    int right = static_cast<int>(v.size()) - 1;

    // Boundaries
    assert(binary_search_dc(v, 100, 0, right) == 0);
    assert(binary_search_dc(v, 500, 0, right) == 4);
    assert(binary_search_dc(v, 300, 0, right) == 2);

    // Gaps and outside range
    assert(binary_search_dc(v, 50, 0, right) == -1);
    assert(binary_search_dc(v, 600, 0, right) == -1);
    assert(binary_search_dc(v, 250, 0, right) == -1);

    std::cout << "[PASS] Boundaries & gaps test passed." << std::endl;
}

void test_large_search() {
    std::cout << "[PRIVATE SEARCH] Testing large binary search (5000 items)..." << std::endl;
    const int N = 5000;
    std::vector<Order> orders;
    orders.reserve(N);

    for (int i = 0; i < N; ++i) {
        orders.push_back(Order(static_cast<uint64_t>((i + 1) * 2), "STOCK", 100.0, 10, true));
    }

    int right = static_cast<int>(orders.size()) - 1;

    // Test even IDs (present)
    for (int i = 0; i < N; i += 50) {
        uint64_t target = (i + 1) * 2;
        int idx = binary_search_dc(orders, target, 0, right);
        assert(idx == i);
        assert(orders[idx].order_id == target);
    }

    // Test odd IDs (absent)
    for (int i = 0; i < N; i += 50) {
        uint64_t target = (i + 1) * 2 - 1;
        int idx = binary_search_dc(orders, target, 0, right);
        assert(idx == -1);
    }

    std::cout << "[PASS] Large binary search test passed." << std::endl;
}

int main() {
    try {
        test_empty_and_bounds();
        test_single_element();
        test_boundary_and_gaps();
        test_large_search();
        std::cout << "All private search divide-conquer tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Private search test failed: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Private search test failed with unknown error." << std::endl;
        return 1;
    }
}
