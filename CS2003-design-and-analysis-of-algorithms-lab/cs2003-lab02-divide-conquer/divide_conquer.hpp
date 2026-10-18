#ifndef DIVIDE_CONQUER_HPP
#define DIVIDE_CONQUER_HPP

#include <vector>
#include <string>
#include <cstdint>
#include <functional>

// Represents a financial order in the trading engine order book
struct Order {
    uint64_t order_id;
    std::string symbol;
    double price;
    uint32_t quantity;
    bool is_buy; // true for BUY, false for SELL

    Order() : order_id(0), symbol(""), price(0.0), quantity(0), is_buy(true) {}
    Order(uint64_t id, const std::string& sym, double p, uint32_t q, bool buy)
        : order_id(id), symbol(sym), price(p), quantity(q), is_buy(buy) {}

    bool operator==(const Order& other) const {
        return order_id == other.order_id &&
               symbol == other.symbol &&
               price == other.price &&
               quantity == other.quantity &&
               is_buy == other.is_buy;
    }
};

// Type definition for custom order comparison strategy
using OrderComparator = std::function<bool(const Order&, const Order&)>;

// Default comparator: sorts orders strictly by order_id in ascending order
bool default_order_comparator(const Order& a, const Order& b);

/**
 * @brief Performs Quick Sort on a range of orders using Divide & Conquer.
 * 
 * @param orders Vector of Order objects to sort in-place.
 * @param left Starting 0-based index of range (inclusive).
 * @param right Ending 0-based index of range (inclusive).
 * @param comp Comparison function (defaults to default_order_comparator).
 */
void quick_sort_dc(std::vector<Order>& orders, int left, int right, OrderComparator comp = default_order_comparator);

/**
 * @brief Performs Merge Sort on a range of orders using Divide & Conquer.
 * 
 * @param orders Vector of Order objects to sort in-place.
 * @param left Starting 0-based index of range (inclusive).
 * @param right Ending 0-based index of range (inclusive).
 * @param comp Comparison function (defaults to default_order_comparator).
 */
void merge_sort_dc(std::vector<Order>& orders, int left, int right, OrderComparator comp = default_order_comparator);

/**
 * @brief Performs Binary Search for a target order_id using Divide & Conquer.
 * 
 * Assumes the orders vector is sorted in ascending order by order_id.
 * 
 * @param orders Const reference to vector of sorted Order objects.
 * @param target_id Target order_id to search for.
 * @param left Starting 0-based index of range (inclusive).
 * @param right Ending 0-based index of range (inclusive).
 * @return int 0-based index of target order if found, -1 if not found.
 */
int binary_search_dc(const std::vector<Order>& orders, uint64_t target_id, int left, int right);

#endif // DIVIDE_CONQUER_HPP
