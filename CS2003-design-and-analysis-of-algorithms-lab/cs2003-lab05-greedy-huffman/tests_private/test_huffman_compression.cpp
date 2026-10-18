#include "greedy_huffman.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cassert>

static int tests_passed = 0;
static int tests_failed = 0;

static void assert_bool(bool condition, const std::string& test_name) {
    if (condition) {
        std::cout << "[PASS] " << test_name << "\n";
        tests_passed++;
    } else {
        std::cout << "[FAIL] " << test_name << "\n";
        tests_failed++;
    }
}

static void assert_string_eq(const std::string& val1, const std::string& val2, const std::string& test_name) {
    if (val1 == val2) {
        std::cout << "[PASS] " << test_name << "\n";
        tests_passed++;
    } else {
        std::cout << "[FAIL] " << test_name << " (Expected \"" << val2 << "\", got \"" << val1 << "\")\n";
        tests_failed++;
    }
}

void test_empty_string() {
    HuffmanResult res = huffman_encode_text("");
    assert_string_eq(res.encoded_bitstring, "", "Private Huffman: Empty String Encoded");
    assert_bool(res.huffman_codes.empty(), "Private Huffman: Empty String Code Map");
    assert_bool(res.root == nullptr, "Private Huffman: Empty String Root Null");
    free_huffman_tree(res.root);
}

void test_single_character() {
    std::string text = "CCCCCC";
    HuffmanResult res = huffman_encode_text(text);
    assert_string_eq(res.encoded_bitstring, "000000", "Private Huffman: Single Char Bitstring");
    assert_bool(res.huffman_codes.size() == 1, "Private Huffman: Single Char Map Size");
    assert_string_eq(res.huffman_codes['C'], "0", "Private Huffman: Single Char Code");
    assert_bool(res.root != nullptr, "Private Huffman: Single Char Root Non-Null");
    assert_bool(res.root->freq == 6, "Private Huffman: Single Char Root Frequency");
    free_huffman_tree(res.root);
}

void test_decodability_and_prefix() {
    std::string text = "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG";
    HuffmanResult res = huffman_encode_text(text);

    assert_bool(!res.encoded_bitstring.empty(), "Private Huffman: Bitstring Non-Empty");
    assert_bool(res.root != nullptr, "Private Huffman: Root Non-Null");
    assert_bool(res.root->freq == (int)text.length(), "Private Huffman: Root Frequency Total");

    // Verify prefix-free property
    bool is_prefix_free = true;
    for (const auto& kv1 : res.huffman_codes) {
        for (const auto& kv2 : res.huffman_codes) {
            if (kv1.first != kv2.first) {
                if (kv2.second.rfind(kv1.second, 0) == 0) { // kv2 starts with kv1
                    is_prefix_free = false;
                }
            }
        }
    }
    assert_bool(is_prefix_free, "Private Huffman: Prefix-Free Codes");

    // Decode bitstring using Huffman Tree
    std::string decoded = "";
    HuffmanNode* curr = res.root;
    for (char bit : res.encoded_bitstring) {
        if (bit == '0') {
            curr = curr->left;
        } else if (bit == '1') {
            curr = curr->right;
        }
        if (curr && !curr->left && !curr->right) {
            decoded += curr->ch;
            curr = res.root;
        }
    }

    assert_string_eq(decoded, text, "Private Huffman: Decoded Text Matches Original");

    // Check compression ratio: encoded length should be significantly less than 8 * length
    size_t original_bits = text.length() * 8;
    size_t compressed_bits = res.encoded_bitstring.length();
    assert_bool(compressed_bits < original_bits, "Private Huffman: Compression Ratio Efficiency");

    free_huffman_tree(res.root);
}

void test_deterministic_tie_breaking() {
    // String with equal character frequencies: 'a':1, 'b':1, 'c':1, 'd':1
    std::string text = "abcd";
    HuffmanResult res = huffman_encode_text(text);

    assert_bool(res.huffman_codes.size() == 4, "Private Huffman: Deterministic Tie Breaking Code Map Size");

    // With tie-breaking by min_char:
    // Leaves: 'a':1, 'b':1, 'c':1, 'd':1
    // Step 1: pop 'a' (min_char 'a'), pop 'b' (min_char 'b') -> parent N1 (freq 2, min_char 'a', left='a', right='b')
    // Step 2: pop 'c' (min_char 'c'), pop 'd' (min_char 'd') -> parent N2 (freq 2, min_char 'c', left='c', right='d')
    // Step 3: pop N1 (freq 2, min_char 'a'), pop N2 (freq 2, min_char 'c') -> root (freq 4, left=N1, right=N2)
    // Code for 'a' -> 00, 'b' -> 01, 'c' -> 10, 'd' -> 11
    assert_string_eq(res.huffman_codes['a'], "00", "Private Huffman: Deterministic Code 'a'");
    assert_string_eq(res.huffman_codes['b'], "01", "Private Huffman: Deterministic Code 'b'");
    assert_string_eq(res.huffman_codes['c'], "10", "Private Huffman: Deterministic Code 'c'");
    assert_string_eq(res.huffman_codes['d'], "11", "Private Huffman: Deterministic Code 'd'");

    assert_string_eq(res.encoded_bitstring, "00011011", "Private Huffman: Deterministic Bitstring");

    free_huffman_tree(res.root);
}

int main() {
    std::cout << "--- Private Test Suite: Huffman Compression ---\n";
    test_empty_string();
    test_single_character();
    test_decodability_and_prefix();
    test_deterministic_tie_breaking();

    std::cout << "\nPrivate Huffman Test Summary: " << tests_passed << " PASSED, " << tests_failed << " FAILED.\n";
    return (tests_failed == 0) ? 0 : 1;
}
