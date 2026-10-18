#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "string_matching.hpp"

void assert_equal(const std::string& test_name, 
                  const std::vector<size_t>& actual, 
                  const std::vector<size_t>& expected) {
    if (actual != expected) {
        std::cerr << "[FAIL] " << test_name << "\n  Expected: { ";
        for (size_t idx : expected) std::cerr << idx << " ";
        std::cerr << "}\n  Actual:   { ";
        for (size_t idx : actual) std::cerr << idx << " ";
        std::cerr << "}\n";
        std::exit(1);
    }
    std::cout << "[PASS] " << test_name << "\n";
}

int main() {
    std::cout << "--- Public Test Suite: Security Log Pattern & String Matcher ---\n";

    // Test 1: Log file error tag search (Naive)
    {
        std::string log = "2026-08-13 [WARN] Timeout. [ERROR] Auth fail. [ERROR] Reset.";
        std::string pattern = "[ERROR]";
        std::vector<size_t> expected = {27, 46};
        std::vector<size_t> actual = naive_string_match(log, pattern);
        assert_equal("Naive Matcher - Log Error Pattern", actual, expected);
    }

    // Test 2: Log file error tag search (Rabin-Karp)
    {
        std::string log = "2026-08-13 [WARN] Timeout. [ERROR] Auth fail. [ERROR] Reset.";
        std::string pattern = "[ERROR]";
        std::vector<size_t> expected = {27, 46};
        std::vector<size_t> actual = rabin_karp_string_match(log, pattern);
        assert_equal("Rabin-Karp Matcher - Log Error Pattern", actual, expected);
    }

    // Test 3: Overlapping matches
    {
        std::string text = "AABAACAADAABAABA";
        std::string pattern = "AABA";
        std::vector<size_t> expected = {0, 9, 12};
        
        std::vector<size_t> naive_actual = naive_string_match(text, pattern);
        assert_equal("Naive Matcher - Overlapping Patterns", naive_actual, expected);

        std::vector<size_t> rk_actual = rabin_karp_string_match(text, pattern);
        assert_equal("Rabin-Karp Matcher - Overlapping Patterns", rk_actual, expected);
    }

    // Test 4: Pattern not found
    {
        std::string text = "SYSTEM_STATUS_OK_NO_THREATS_DETECTED";
        std::string pattern = "MALWARE";
        std::vector<size_t> expected = {};

        assert_equal("Naive Matcher - No Match", naive_string_match(text, pattern), expected);
        assert_equal("Rabin-Karp Matcher - No Match", rabin_karp_string_match(text, pattern), expected);
    }

    std::cout << "\nAll public tests passed successfully!\n";
    return 0;
}
