# CS2003 Lab 05: Greedy Algorithms (Fractional Knapsack & Huffman Coding)

## Overview

In this lab, you will design and implement two classic **Greedy Algorithms** in C++:

1. **Fractional Knapsack Engine**: Optimize resource allocation by selecting items (or fractions of items) to maximize value within a weight capacity limit.
2. **Huffman Text Compression Engine**: Construct optimal prefix-free binary codes based on character frequencies to compress text.

---

## Technical Specifications

### 1. Fractional Knapsack (`fractional_knapsack_greedy`)

Given a maximum weight `capacity` and a list of items (`Item`), select items or item fractions to maximize total value.

#### Algorithm Requirements:
- Calculate value-to-weight ratio for each item: $r_i = \text{value}_i / \text{weight}_i$.
- Sort items by ratio in **descending** order.
- **Tie-Breaking Rule**: If two items have equal ratios ($|r_a - r_b| < 10^{-9}$), break ties by comparing item `id` in ascending order (`itemA.id < itemB.id`).
- Process items in sorted order:
  - If item weight $\le \text{remaining capacity}$, take fraction `1.0` of the item.
  - If item weight $> \text{remaining capacity}$ and $\text{remaining capacity} > 0$, take fraction $\text{remaining capacity} / \text{item.weight}$.
  - Otherwise, take fraction `0.0`.
- Populate `fractions_taken` vector such that `fractions_taken[i]` corresponds to the fraction taken for `items[i]` (the original index in the input `items` vector).
- Return total accumulated value as `double`.
- **Edge Cases**:
  - If `capacity <= 0` or `items` is empty, set all fractions to `0.0` and return `0.0`.
  - Items with non-positive weight (`weight <= 0`) must receive fraction `0.0`.

---

### 2. Huffman Coding (`huffman_encode_text`)

Given an input string `text`, compress it by generating a prefix-free Huffman tree and encoding table.

#### Algorithm Requirements:
1. **Frequency Table**: Calculate frequency of each distinct character in `text`.
2. **Priority Queue (Min-Heap)**: Create a leaf `HuffmanNode` for each distinct character and insert into a min-priority queue.
   - **Tie-Breaking Rule**:
     - Primary Key: Node with **smaller frequency** has higher priority (pops first).
     - Secondary Key: Node whose subtree contains the **smaller minimum ASCII character** (`min_char`) has higher priority.
3. **Tree Construction**:
   - While priority queue contains more than 1 node:
     - Pop `left` node (highest priority / smallest frequency).
     - Pop `right` node (second highest priority).
     - Create internal node with character `'\0'`, frequency `left->freq + right->freq`, left child = `left`, right child = `right`.
     - Push internal node back into priority queue.
   - Remaining node is `root`.
4. **Code Generation**:
   - Left branch corresponds to bit `'0'`.
   - Right branch corresponds to bit `'1'`.
   - Traversal from `root` to leaf yields character's prefix code string.
   - Special Case: If `text` has only 1 distinct character (e.g. `"AAAA"`), assign prefix code `"0"` to that character.
5. **Text Encoding**:
   - Concatenate prefix codes for each character in `text` to build `encoded_bitstring`.
6. **Edge Cases**:
   - If `text` is empty `""`: return empty `encoded_bitstring`, empty `huffman_codes` map, and `root = nullptr`.

---

## Function Prototypes & Structs

Defined in `greedy_huffman.hpp`:

```cpp
struct Item {
    int id;
    double weight;
    double value;
};

struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char c, int f, HuffmanNode* l = nullptr, HuffmanNode* r = nullptr);
};

struct HuffmanResult {
    std::string encoded_bitstring;
    std::map<char, std::string> huffman_codes;
    HuffmanNode* root;
};

double fractional_knapsack_greedy(double capacity, const std::vector<Item>& items, std::vector<double>& fractions_taken);

HuffmanResult huffman_encode_text(const std::string& text);

void free_huffman_tree(HuffmanNode* root);
```

---

## Building and Testing

Run public unit tests locally:

```bash
make test-public
# or
./run
```

Clean build artifacts:

```bash
make clean
# or
./run clean
```
