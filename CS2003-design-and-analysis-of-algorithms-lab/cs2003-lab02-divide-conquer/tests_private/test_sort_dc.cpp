#include "divide_conquer.hpp"
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <random>

void test_empty_and_single() {
    std::cout << "[PRIVATE SORT] Testing empty & single-element vectors..." << std::endl;
    std::vector<Order> empty_qs;
    quick_sort_dc(empty_qs, 0, -1);
    assert(empty_qs.empty());

    std::vector<Order> empty_ms;
    merge_sort_dc(empty_ms, 0, -1);
    assert(empty_ms.empty());

    std::vector<Order> single_qs = { Order(42, "BTC", 50000.0, 1, true) };
    quick_sort_dc(single_qs, 0, 0);
    assert(single_qs.size() == 1 && single_qs[0].order_id == 42);

    std::vector<Order> single_ms = { Order(42, "BTC", 50000.0, 1, true) };
    merge_sort_dc(single_ms, 0, 0);
    assert(single_ms.size() == 1 && single_ms[0].order_id == 42);

    std::cout << "[PASS] Empty & single-element test passed." << std::endl;
}

void test_sorted_and_reverse() {
    std::cout << "[PRIVATE SORT] Testing already sorted & reverse sorted vectors..." << std::endl;
    std::vector<Order> sorted_qs, reverse_qs, sorted_ms, reverse_ms;
    for (uint64_t i = 1; i <= 20; ++i) {
        sorted_qs.push_back(Order(i, "SYM", 10.0 * i, 10, true));
        reverse_qs.push_back(Order(21 - i, "SYM", 10.0 * (21 - i), 10, true));
        sorted_ms.push_back(Order(i, "SYM", 10.0 * i, 10, true));
        reverse_ms.push_back(Order(21 - i, "SYM", 10.0 * (21 - i), 10, true));
    }

    quick_sort_dc(sorted_qs, 0, static_cast<int>(sorted_qs.size()) - 1);
    quick_sort_dc(reverse_qs, 0, static_cast<int>(reverse_qs.size()) - 1);
    merge_sort_dc(sorted_ms, 0, static_cast<int>(sorted_ms.size()) - 1);
    merge_sort_dc(reverse_ms, 0, static_cast<int>(reverse_ms.size()) - 1);

    for (size_t i = 0; i < 20; ++i) {
        assert(sorted_qs[i].order_id == i + 1);
        assert(reverse_qs[i].order_id == i + 1);
        assert(sorted_ms[i].order_id == i + 1);
        assert(reverse_ms[i].order_id == i + 1);
    }

    std::cout << "[PASS] Sorted & reverse sorted test passed." << std::endl;
}

void test_duplicate_keys() {
    std::cout << "[PRIVATE SORT] Testing vectors with duplicate keys..." << std::endl;
    std::vector<Order> orders_qs = {
        Order(10, "A", 100.0, 1, true),
        Order(5,  "B", 200.0, 2, false),
        Order(10, "C", 150.0, 3, true),
        Order(2,  "D", 300.0, 4, false),
        Order(5,  "E", 250.0, 5, true)
    };
    std::vector<Order> orders_ms = orders_qs;

    quick_sort_dc(orders_qs, 0, static_cast<int>(orders_qs.size()) - 1);
    merge_sort_dc(orders_ms, 0, static_cast<int>(orders_ms.size()) - 1);

    assert(orders_qs[0].order_id == 2);
    assert(orders_qs[1].order_id == 5 && orders_qs[2].order_id == 5);
    assert(orders_qs[3].order_id == 10 && orders_qs[4].order_id == 10);

    assert(orders_ms[0].order_id == 2);
    assert(orders_ms[1].order_id == 5 && orders_ms[2].order_id == 5);
    assert(orders_ms[3].order_id == 10 && orders_ms[4].order_id == 10);

    std::cout << "[PASS] Duplicate keys test passed." << std::endl;
}

void test_custom_bid_ask_comparators() {
    std::cout << "[PRIVATE SORT] Testing custom Bid/Ask comparators..." << std::endl;
    std::vector<Order> bids = {
        Order(101, "AAPL", 150.0, 100, true),
        Order(102, "AAPL", 155.0, 200, true),
        Order(103, "AAPL", 152.5, 150, true),
        Order(104, "AAPL", 155.0, 50,  true)
    };

    // Bid comparator: price descending; tie-breaker order_id ascending
    auto bid_comp = [](const Order& a, const Order& b) {
        if (a.price != b.price) return a.price > b.price;
        return a.order_id < b.order_id;
    };

    std::vector<Order> bids_qs = bids;
    std::vector<Order> bids_ms = bids;

    quick_sort_dc(bids_qs, 0, static_cast<int>(bids_qs.size()) - 1, bid_comp);
    merge_sort_dc(bids_ms, 0, static_cast<int>(bids_ms.size()) - 1, bid_comp);

    assert(bids_qs[0].price == 155.0 && bids_qs[0].order_id == 102);
    assert(bids_qs[1].price == 155.0 && bids_qs[1].order_id == 104);
    assert(bids_qs[2].price == 152.5 && bids_qs[2].order_id == 103);
    assert(bids_qs[3].price == 150.0 && bids_qs[3].order_id == 101);

    assert(bids_ms[0].price == 155.0 && bids_ms[0].order_id == 102);
    assert(bids_ms[1].price == 155.0 && bids_ms[1].order_id == 104);
    assert(bids_ms[2].price == 152.5 && bids_ms[2].order_id == 103);
    assert(bids_ms[3].price == 150.0 && bids_ms[3].order_id == 101);

    std::cout << "[PASS] Custom Bid/Ask comparators test passed." << std::endl;
}

void test_large_dataset() {
    std::cout << "[PRIVATE SORT] Testing large dataset sorting (2000 items)..." << std::endl;
    const int N = 2000;
    std::vector<Order> original;
    original.reserve(N);

    std::mt19937 rng(1337);
    std::uniform_int_distribution<uint64_t> dist_id(1, 1000000);
    std::uniform_real_distribution<double> dist_price(10.0, 1000.0);

    for (int i = 0; i < N; ++i) {
        original.push_back(Order(dist_id(rng), "STOCK", dist_price(rng), 100, i % 2 == 0));
    }

    std::vector<Order> qs_data = original;
    std::vector<Order> ms_data = original;
    std::vector<Order> std_data = original;

    quick_sort_dc(qs_data, 0, static_cast<int>(qs_data.size()) - 1);
    merge_sort_dc(ms_data, 0, static_cast<int>(ms_data.size()) - 1);
    std::sort(std_data.begin(), std_data.end(), default_order_comparator);

    for (int i = 0; i < N; ++i) {
        assert(qs_data[i].order_id == std_data[i].order_id);
        assert(ms_data[i].order_id == std_data[i].order_id);
    }

    std::cout << "[PASS] Large dataset sorting test passed." << std::endl;
}

int main() {
    try {
        test_empty_and_single();
        test_sorted_and_reverse();
        test_duplicate_keys();
        test_custom_bid_ask_comparators();
        test_large_dataset();
        std::cout << "All private sort divide-conquer tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Private sort test failed: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Private sort test failed with unknown error." << std::endl;
        return 1;
    }
}
