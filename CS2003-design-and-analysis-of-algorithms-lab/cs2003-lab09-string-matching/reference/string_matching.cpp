#include "string_matching.hpp"

std::vector<size_t> naive_string_match(const std::string& text, const std::string& pattern) {
    std::vector<size_t> matches;
    if (pattern.empty() || text.length() < pattern.length()) {
        return matches;
    }

    size_t N = text.length();
    size_t M = pattern.length();

    for (size_t i = 0; i <= N - M; ++i) {
        bool match = true;
        for (size_t j = 0; j < M; ++j) {
            if (text[i + j] != pattern[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            matches.push_back(i);
        }
    }

    return matches;
}

std::vector<size_t> rabin_karp_string_match(const std::string& text, 
                                           const std::string& pattern, 
                                           size_t prime, 
                                           size_t base) {
    std::vector<size_t> matches;
    if (pattern.empty() || text.length() < pattern.length()) {
        return matches;
    }

    size_t N = text.length();
    size_t M = pattern.length();

    // Compute base^(M-1) % prime
    size_t h = 1;
    for (size_t i = 0; i < M - 1; ++i) {
        h = (h * base) % prime;
    }

    // Compute initial hash values for pattern and first window of text
    size_t p_hash = 0;
    size_t t_hash = 0;
    for (size_t i = 0; i < M; ++i) {
        p_hash = (p_hash * base + static_cast<unsigned char>(pattern[i])) % prime;
        t_hash = (t_hash * base + static_cast<unsigned char>(text[i])) % prime;
    }

    // Slide window across text
    for (size_t i = 0; i <= N - M; ++i) {
        // If hash values match, check characters individually to handle collisions
        if (p_hash == t_hash) {
            bool match = true;
            for (size_t j = 0; j < M; ++j) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                matches.push_back(i);
            }
        }

        // Calculate hash for next window
        if (i < N - M) {
            long long leading = (static_cast<unsigned char>(text[i]) * h) % prime;
            long long next_hash = (static_cast<long long>(t_hash) - leading) % static_cast<long long>(prime);
            if (next_hash < 0) {
                next_hash += prime;
            }
            next_hash = (next_hash * base + static_cast<unsigned char>(text[i + M])) % prime;
            t_hash = static_cast<size_t>(next_hash);
        }
    }

    return matches;
}
