#include "dynamic_programming.hpp"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

void test_lcs_edge_cases() {
    // 1. Empty strings
    LCSResult r1 = longest_common_subsequence("", "");
    assert(r1.length == 0);
    assert(r1.lcs == "");
    assert(r1.diff.empty());

    // 2. Identical strings
    LCSResult r2 = longest_common_subsequence("HELLODP", "HELLODP");
    assert(r2.length == 7);
    assert(r2.lcs == "HELLODP");
    assert(r2.diff.size() == 7);
    for (const auto& token : r2.diff) {
        assert(token.size() == 2 && token[0] == ' ');
    }

    // 3. Completely disjoint strings
    LCSResult r3 = longest_common_subsequence("XYZ", "ABC");
    assert(r3.length == 0);
    assert(r3.lcs == "");
    assert(r3.diff.size() == 6); // 3 deletions, 3 insertions
}

void test_lcs_diff_application() {
    std::pair<std::string, std::string> test_pairs[] = {
        {"ABCBDAB", "BDCABA"},
        {"AGGTAB", "GXTXAYB"},
        {"DYNAMICPROGRAMMING", "PYTHONCODING"},
        {"INTENTION", "EXECUTION"},
        {"SHORT", "LONGSTRING"}
    };

    for (const auto& pair : test_pairs) {
        const std::string& X = pair.first;
        const std::string& Y = pair.second;

        LCSResult res = longest_common_subsequence(X, Y);
        assert(static_cast<int>(res.lcs.length()) == res.length);

        // Verify diff application to rebuild Y from X
        std::string reconstructed_Y = "";
        std::string consumed_X = "";

        for (const std::string& token : res.diff) {
            assert(token.length() == 2);
            char op = token[0];
            char c = token[1];

            if (op == ' ') {
                consumed_X.push_back(c);
                reconstructed_Y.push_back(c);
            } else if (op == '-') {
                consumed_X.push_back(c);
            } else if (op == '+') {
                reconstructed_Y.push_back(c);
            } else {
                assert(false && "Invalid diff operator!");
            }
        }

        assert(consumed_X == X);
        assert(reconstructed_Y == Y);
    }
}

int main() {
    std::cout << "[Private Test] Running test_lcs_diff..." << std::endl;
    try {
        test_lcs_edge_cases();
        test_lcs_diff_application();
        std::cout << "[Private Test] test_lcs_diff PASSED!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "[Private Test] test_lcs_diff FAILED: " << e.what() << std::endl;
        return 1;
    }
}
