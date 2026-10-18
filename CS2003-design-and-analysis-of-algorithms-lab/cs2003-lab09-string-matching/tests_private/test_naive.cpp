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
    std::cout << "=== Private Test Suite: Naive String Matcher ===\n";

    // 1. Edge Case: Empty pattern or pattern > text
    {
        assert_test("Empty Pattern", naive_string_match("hello world", ""), {});
        assert_test("Pattern Longer Than Text", naive_string_match("cat", "caterpillar"), {});
    }

    // 2. Exact Match (pattern == text)
    {
        assert_test("Exact Match", naive_string_match("FIREWALL_ALERT", "FIREWALL_ALERT"), {0});
    }

    // 3. Repeated Single Character
    {
        std::string text = "AAAAAA";
        std::string pattern = "AA";
        // indices 0, 1, 2, 3, 4
        assert_test("Repeated Overlapping Char", naive_string_match(text, pattern), {0, 1, 2, 3, 4});
    }

    // 4. Security Log SQL Injection Signature Detection
    {
        std::string log = "GET /api/v1/users?id=1%27%20OR%201%3D1-- HTTP/1.1 200 OK\n"
                          "POST /login username=admin&pass=123 HTTP/1.1 401 Unauthorized\n"
                          "GET /api/v1/items?cat=select%20*%20from%20users-- HTTP/1.1 200 OK";
        std::string signature = "HTTP/1.1 200 OK";
        assert_test("Log Signature Search", naive_string_match(log, signature), {47, 187});
    }

    // 5. Pattern at start and end
    {
        std::string text = "START middle END";
        assert_test("Pattern at Start", naive_string_match(text, "START"), {0});
        assert_test("Pattern at End", naive_string_match(text, "END"), {13});
    }

    std::cout << "All Naive String Matcher private tests passed!\n";
    return 0;
}
