#include "string_matching.hpp"

std::vector<size_t> naive_string_match(const std::string& text, const std::string& pattern) {
    std::vector<size_t> matches;
    (void)text;
    (void)pattern;

    // TODO: Implement the Naive String Matching algorithm.
    // Slide pattern across text 1 character at a time and compare character-by-character.
    // Record all 0-based starting indices where pattern matches text.
    // Return empty vector if pattern is empty or pattern length > text length.

    return matches;
}

std::vector<size_t> rabin_karp_string_match(const std::string& text, 
                                           const std::string& pattern, 
                                           size_t prime, 
                                           size_t base) {
    std::vector<size_t> matches;
    (void)text;
    (void)pattern;
    (void)prime;
    (void)base;

    // TODO: Implement the Rabin-Karp String Matching algorithm using a rolling hash.
    // 1. Calculate h = base^(M-1) % prime where M is pattern length.
    // 2. Compute initial hash values for pattern and the first text window.
    // 3. Slide window across text:
    //    a. If pattern hash == window hash, perform character-by-character comparison.
    //    b. If match is verified, record the 0-based starting index.
    //    c. Compute rolling hash for the next window:
    //       t_hash = (base * (t_hash - text[i] * h) + text[i + M]) % prime
    //       (handle negative modulo values appropriately).
    // Return empty vector if pattern is empty or pattern length > text length.

    return matches;
}
