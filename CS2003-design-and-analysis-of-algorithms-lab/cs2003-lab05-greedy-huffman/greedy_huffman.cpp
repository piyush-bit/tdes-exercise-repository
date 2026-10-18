#include "greedy_huffman.hpp"
#include <algorithm>
#include <cmath>
#include <queue>
#include <iostream>

struct ItemIndexed {
    size_t original_index;
    int id;
    double weight;
    double value;
    double ratio;
};

double fractional_knapsack_greedy(double capacity, const std::vector<Item>& items, std::vector<double>& fractions_taken) {
    fractions_taken.assign(items.size(), 0.0);

    if (capacity <= 0.0 || items.empty()) {
        return 0.0;
    }

    std::vector<ItemIndexed> list;
    list.reserve(items.size());

    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i].weight > 0.0) {
            double r = items[i].value / items[i].weight;
            list.push_back({i, items[i].id, items[i].weight, items[i].value, r});
        }
    }

    std::sort(list.begin(), list.end(), [](const ItemIndexed& a, const ItemIndexed& b) {
        if (std::abs(a.ratio - b.ratio) > 1e-9) {
            return a.ratio > b.ratio; // Descending ratio
        }
        return a.id < b.id; // Tie-breaker: smaller id first
    });

    double remaining = capacity;
    double total_value = 0.0;

    for (const auto& item : list) {
        if (remaining <= 0.0) {
            break;
        }

        if (item.weight <= remaining) {
            fractions_taken[item.original_index] = 1.0;
            remaining -= item.weight;
            total_value += item.value;
        } else {
            double frac = remaining / item.weight;
            fractions_taken[item.original_index] = frac;
            total_value += frac * item.value;
            remaining = 0.0;
        }
    }

    return total_value;
}

static char get_min_char(const HuffmanNode* node) {
    if (!node) return '\177';
    if (!node->left && !node->right) {
        return node->ch;
    }
    char left_min = get_min_char(node->left);
    char right_min = get_min_char(node->right);
    return std::min(left_min, right_min);
}

struct NodeComparator {
    bool operator()(const HuffmanNode* a, const HuffmanNode* b) const {
        if (a->freq != b->freq) {
            return a->freq > b->freq; // Smaller frequency has higher priority
        }
        char min_a = get_min_char(a);
        char min_b = get_min_char(b);
        return min_a > min_b; // Smaller min_char has higher priority
    }
};

static void generate_codes(HuffmanNode* node, const std::string& current_code, std::map<char, std::string>& huffman_codes) {
    if (!node) return;
    if (!node->left && !node->right) {
        huffman_codes[node->ch] = current_code.empty() ? "0" : current_code;
        return;
    }
    if (node->left) {
        generate_codes(node->left, current_code + "0", huffman_codes);
    }
    if (node->right) {
        generate_codes(node->right, current_code + "1", huffman_codes);
    }
}

HuffmanResult huffman_encode_text(const std::string& text) {
    HuffmanResult result;
    result.encoded_bitstring = "";
    result.root = nullptr;

    if (text.empty()) {
        return result;
    }

    std::map<char, int> freq_map;
    for (char c : text) {
        freq_map[c]++;
    }

    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, NodeComparator> pq;
    for (const auto& pair : freq_map) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    if (pq.size() == 1) {
        result.root = pq.top();
        result.huffman_codes[result.root->ch] = "0";
        for (char c : text) {
            result.encoded_bitstring += "0";
        }
        return result;
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        HuffmanNode* parent = new HuffmanNode('\0', left->freq + right->freq, left, right);
        pq.push(parent);
    }

    result.root = pq.top();
    generate_codes(result.root, "", result.huffman_codes);

    for (char c : text) {
        result.encoded_bitstring += result.huffman_codes[c];
    }

    return result;
}

void free_huffman_tree(HuffmanNode* root) {
    if (!root) return;
    free_huffman_tree(root->left);
    free_huffman_tree(root->right);
    delete root;
}
