#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "string_matching.hpp"

void assert_test(const std::string& name, const std::vector<size_t>& actual, const std::vector<size_t>& expected) {
    if (actual != expected) {
        std::cerr << "[FAIL] " << name << "\n  Expected size: " << expected.size() 
                  << ", Actual size: " << actual.size() << "\n";
        std::exit(1);
    }
    std::cout << "[PASS] " << name << "\n";
}

int main() {
    std::cout << "=== Private Test Suite: Rabin-Karp String Matcher ===\n";

    // 1. Edge Case: Empty pattern or pattern > text
    {
        assert_test("Empty Pattern", rabin_karp_string_match("hello world", ""), {});
        assert_test("Pattern Longer Than Text", rabin_karp_string_match("cat", "caterpillar"), {});
    }

    // 2. Exact Match (pattern == text)
    {
        assert_test("Exact Match", rabin_karp_string_match("FIREWALL_ALERT", "FIREWALL_ALERT"), {0});
    }

    // 3. Custom Prime and Base
    {
        std::string text = "192.168.1.1 - - [13/Aug/2026] 192.168.1.100 - - [13/Aug/2026]";
        std::string pattern = "192.168.1.";
        std::vector<size_t> expected = {0, 30};
        // Using prime 101, base 256
        assert_test("Default Params", rabin_karp_string_match(text, pattern), expected);
        // Using prime 1000000007, base 31
        assert_test("Custom Prime and Base", rabin_karp_string_match(text, pattern, 1000000007, 31), expected);
    }

    // 4. Multiple matches with repeating patterns
    {
        std::string text = "abracadabra";
        std::string pattern = "abra";
        assert_test("Abracadabra Search", rabin_karp_string_match(text, pattern), {0, 7});
    }

    // 5. Binary/special character string security token matching
    {
        std::string text = "auth_token=Bearer\x01\x02\x03&type=admin;auth_token=Bearer\x01\x02\x03&type=user";
        std::string pattern = "Bearer\x01\x02\x03";
        assert_test("Binary/Control Char Pattern", rabin_karp_string_match(text, pattern), {11, 49});
    }

    std::cout << "All Rabin-Karp String Matcher private tests passed!\n";
    return 0;
}
