#include "greedy_huffman.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

static int tests_passed = 0;
static int tests_failed = 0;

static void assert_double_eq(double val1, double val2, const std::string& test_name) {
    if (std::abs(val1 - val2) < 1e-4) {
        std::cout << "[PASS] " << test_name << "\n";
        tests_passed++;
    } else {
        std::cout << "[FAIL] " << test_name << " (Expected " << val2 << ", got " << val1 << ")\n";
        tests_failed++;
    }
}

static void assert_bool(bool condition, const std::string& test_name) {
    if (condition) {
        std::cout << "[PASS] " << test_name << "\n";
        tests_passed++;
    } else {
        std::cout << "[FAIL] " << test_name << "\n";
        tests_failed++;
    }
}

void test_fractional_knapsack_public() {
    std::cout << "--- Running Public Tests: Fractional Knapsack ---\n";
    std::vector<Item> items = {
        {1, 10.0, 60.0},  // ratio = 6.0
        {2, 20.0, 100.0}, // ratio = 5.0
        {3, 30.0, 120.0}  // ratio = 4.0
    };
    double capacity = 50.0;
    std::vector<double> fractions;

    double max_val = fractional_knapsack_greedy(capacity, items, fractions);
    assert_double_eq(max_val, 240.0, "Knapsack Standard Max Value");

    if (fractions.size() == 3) {
        assert_double_eq(fractions[0], 1.0, "Knapsack Item 1 Fraction");
        assert_double_eq(fractions[1], 1.0, "Knapsack Item 2 Fraction");
        assert_double_eq(fractions[2], 2.0 / 3.0, "Knapsack Item 3 Fraction");
    } else {
        std::cout << "[FAIL] Knapsack Fractions Output Size\n";
        tests_failed++;
    }
}

void test_huffman_encoding_public() {
    std::cout << "--- Running Public Tests: Huffman Coding ---\n";
    std::string text = "ABRACADABRA";
    HuffmanResult result = huffman_encode_text(text);

    assert_bool(!result.encoded_bitstring.empty(), "Huffman Encoded String Non-Empty");
    assert_bool(result.root != nullptr, "Huffman Tree Root Non-Null");
    assert_bool(result.huffman_codes.find('A') != result.huffman_codes.end(), "Huffman Code Exists for 'A'");

    // Check prefix code property: no code is prefix of another
    bool prefix_ok = true;
    for (auto it1 = result.huffman_codes.begin(); it1 != result.huffman_codes.end(); ++it1) {
        for (auto it2 = result.huffman_codes.begin(); it2 != result.huffman_codes.end(); ++it2) {
            if (it1 != it2) {
                if (it2->second.find(it1->second) == 0) {
                    prefix_ok = false;
                }
            }
        }
    }
    assert_bool(prefix_ok, "Huffman Codes Prefix-Free Property");

    free_huffman_tree(result.root);
}

int main() {
    test_fractional_knapsack_public();
    test_huffman_encoding_public();

    std::cout << "\nPublic Test Summary: " << tests_passed << " PASSED, " << tests_failed << " FAILED.\n";
    return (tests_failed == 0) ? 0 : 1;
}
