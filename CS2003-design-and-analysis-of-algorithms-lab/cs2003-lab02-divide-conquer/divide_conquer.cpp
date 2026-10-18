#include "divide_conquer.hpp"
#include <algorithm>

bool default_order_comparator(const Order& a, const Order& b) {
    return a.order_id < b.order_id;
}

void quick_sort_dc(std::vector<Order>& orders, int left, int right, OrderComparator comp) {
    if (orders.empty() || left >= right || left < 0 || right >= static_cast<int>(orders.size())) {
        return;
    }

    // Pick pivot element (using middle element to reduce worst-case on sorted data)
    int mid = left + (right - left) / 2;
    std::swap(orders[mid], orders[right]);
    Order pivot = orders[right];

    // Lomuto partitioning scheme
    int i = left - 1;
    for (int j = left; j < right; ++j) {
        if (comp(orders[j], pivot)) {
            ++i;
            std::swap(orders[i], orders[j]);
        }
    }
    std::swap(orders[i + 1], orders[right]);
    int pivot_idx = i + 1;

    quick_sort_dc(orders, left, pivot_idx - 1, comp);
    quick_sort_dc(orders, pivot_idx + 1, right, comp);
}

void merge_sort_dc(std::vector<Order>& orders, int left, int right, OrderComparator comp) {
    if (orders.empty() || left >= right || left < 0 || right >= static_cast<int>(orders.size())) {
        return;
    }

    int mid = left + (right - left) / 2;
    merge_sort_dc(orders, left, mid, comp);
    merge_sort_dc(orders, mid + 1, right, comp);

    // Merge step
    std::vector<Order> temp;
    temp.reserve(right - left + 1);

    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right) {
        if (comp(orders[j], orders[i])) {
            temp.push_back(orders[j++]);
        } else {
            temp.push_back(orders[i++]);
        }
    }

    while (i <= mid) {
        temp.push_back(orders[i++]);
    }
    while (j <= right) {
        temp.push_back(orders[j++]);
    }

    for (size_t k = 0; k < temp.size(); ++k) {
        orders[left + k] = temp[k];
    }
}

int binary_search_dc(const std::vector<Order>& orders, uint64_t target_id, int left, int right) {
    if (orders.empty() || left > right || left < 0 || right >= static_cast<int>(orders.size())) {
        return -1;
    }

    int mid = left + (right - left) / 2;
    if (orders[mid].order_id == target_id) {
        return mid;
    } else if (orders[mid].order_id > target_id) {
        return binary_search_dc(orders, target_id, left, mid - 1);
    } else {
        return binary_search_dc(orders, target_id, mid + 1, right);
    }
}
