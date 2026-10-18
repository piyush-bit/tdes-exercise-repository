#ifndef GREEDY_HUFFMAN_HPP
#define GREEDY_HUFFMAN_HPP

#include <string>
#include <vector>
#include <map>

// Item representation for Fractional Knapsack Problem
struct Item {
    int id;          // Unique item identifier
    double weight;   // Item weight (> 0)
    double value;    // Item value (>= 0)
};

// Node structure for Huffman Coding Tree
struct HuffmanNode {
    char ch;             // Character represented (or '\0' for internal nodes)
    int freq;            // Frequency count of character or combined subtree
    HuffmanNode* left;   // Pointer to left child ('0' bit branch)
    HuffmanNode* right;  // Pointer to right child ('1' bit branch)

    HuffmanNode(char c, int f, HuffmanNode* l = nullptr, HuffmanNode* r = nullptr)
        : ch(c), freq(f), left(l), right(r) {}
};

// Return type for Huffman Text Encoding
struct HuffmanResult {
    std::string encoded_bitstring;             // Binary string of '0's and '1's representing encoded text
    std::map<char, std::string> huffman_codes; // Prefix codes table for each character
    HuffmanNode* root;                         // Pointer to root of generated Huffman Tree
};

// Function Prototypes

/**
 * Solves the Fractional Knapsack Problem using a greedy approach.
 * Items are sorted by value-to-weight ratio in descending order.
 * If ratios are equal, items are tie-broken by smaller item `id`.
 *
 * @param capacity Maximum total weight the knapsack can hold.
 * @param items Vector of available items.
 * @param fractions_taken Output vector matching `items.size()` where fractions_taken[i]
 *                        indicates the fraction (0.0 to 1.0) of items[i] selected.
 * @return Maximum achievable total value as double.
 */
double fractional_knapsack_greedy(double capacity, const std::vector<Item>& items, std::vector<double>& fractions_taken);

/**
 * Encodes input text string using Huffman Coding.
 * Builds character frequency table, constructs min-heap priority queue Huffman tree,
 * generates prefix binary codes, and encodes the text.
 *
 * Deterministic Tie-Breaking for Priority Queue:
 * - Primary key: Node with smaller frequency has higher priority (pops first).
 * - Secondary key: Node whose subtree contains the minimum ASCII character has higher priority.
 *
 * @param text Input text string to compress.
 * @return HuffmanResult containing encoded_bitstring, huffman_codes map, and root pointer.
 */
HuffmanResult huffman_encode_text(const std::string& text);

/**
 * Helper function to recursively free memory allocated for a Huffman tree.
 *
 * @param root Pointer to root of Huffman tree to delete.
 */
void free_huffman_tree(HuffmanNode* root);

#endif // GREEDY_HUFFMAN_HPP
