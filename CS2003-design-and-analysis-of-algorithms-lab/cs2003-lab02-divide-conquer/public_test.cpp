#include "divide_conquer.hpp"
#include <iostream>
#include <vector>
#include <cassert>

void test_public_quick_sort() {
    std::cout << "[RUN] Testing quick_sort_dc public test..." << std::endl;
    std::vector<Order> orders = {
        Order(105, "AAPL", 150.50, 100, true),
        Order(101, "GOOGL", 2800.00, 50, false),
        Order(103, "MSFT", 300.25, 200, true),
        Order(102, "AMZN", 3300.00, 15, false),
        Order(104, "NVDA", 220.75, 30, true)
    };

    quick_sort_dc(orders, 0, static_cast<int>(orders.size()) - 1);

    assert(orders.size() == 5);
    assert(orders[0].order_id == 101);
    assert(orders[1].order_id == 102);
    assert(orders[2].order_id == 103);
    assert(orders[3].order_id == 104);
    assert(orders[4].order_id == 105);

    std::cout << "[PASS] quick_sort_dc public test passed." << std::endl;
}

void test_public_merge_sort() {
    std::cout << "[RUN] Testing merge_sort_dc public test..." << std::endl;
    std::vector<Order> orders = {
        Order(500, "TSLA", 700.00, 10, true),
        Order(200, "META", 350.00, 45, false),
        Order(800, "NFLX", 500.00, 25, true),
        Order(100, "AMD", 110.00, 300, false)
    };

    merge_sort_dc(orders, 0, static_cast<int>(orders.size()) - 1);

    assert(orders.size() == 4);
    assert(orders[0].order_id == 100);
    assert(orders[1].order_id == 200);
    assert(orders[2].order_id == 500);
    assert(orders[3].order_id == 800);

    std::cout << "[PASS] merge_sort_dc public test passed." << std::endl;
}

void test_public_binary_search() {
    std::cout << "[RUN] Testing binary_search_dc public test..." << std::endl;
    std::vector<Order> sorted_orders = {
        Order(100, "AMD", 110.00, 300, false),
        Order(200, "META", 350.00, 45, false),
        Order(500, "TSLA", 700.00, 10, true),
        Order(800, "NFLX", 500.00, 25, true)
    };

    int idx_found = binary_search_dc(sorted_orders, 500, 0, static_cast<int>(sorted_orders.size()) - 1);
    assert(idx_found == 2);
    assert(sorted_orders[idx_found].symbol == "TSLA");

    int idx_not_found = binary_search_dc(sorted_orders, 999, 0, static_cast<int>(sorted_orders.size()) - 1);
    assert(idx_not_found == -1);

    std::cout << "[PASS] binary_search_dc public test passed." << std::endl;
}

void test_public_custom_comparator() {
    std::cout << "[RUN] Testing custom price comparator public test..." << std::endl;
    std::vector<Order> orders = {
        Order(1, "AAPL", 150.0, 100, true),
        Order(2, "AAPL", 155.5, 200, true),
        Order(3, "AAPL", 149.0, 150, true)
    };

    // Sort by price descending (highest bid first)
    auto price_desc_comp = [](const Order& a, const Order& b) {
        return a.price > b.price;
    };

    quick_sort_dc(orders, 0, static_cast<int>(orders.size()) - 1, price_desc_comp);

    assert(orders[0].price == 155.5);
    assert(orders[1].price == 150.0);
    assert(orders[2].price == 149.0);

    std::cout << "[PASS] custom price comparator public test passed." << std::endl;
}

int main() {
    try {
        test_public_quick_sort();
        test_public_merge_sort();
        test_public_binary_search();
        test_public_custom_comparator();
        std::cout << "All public tests passed successfully!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Public test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Public test failed with unknown error." << std::endl;
        return 1;
    }
}
