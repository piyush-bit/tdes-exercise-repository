#ifndef STRING_MATCHING_HPP
#define STRING_MATCHING_HPP

#include <string>
#include <vector>
#include <cstddef>

/**
 * Performs Naive String Matching to find all occurrences of pattern in text.
 * 
 * @param text The source text / security log string to search within.
 * @param pattern The pattern / signature string to search for.
 * @return std::vector<size_t> Vector of 0-based starting indices where pattern occurs in text.
 */
std::vector<size_t> naive_string_match(const std::string& text, const std::string& pattern);

/**
 * Performs Rabin-Karp String Matching using a rolling hash to find all occurrences of pattern in text.
 * 
 * @param text The source text / security log string to search within.
 * @param pattern The pattern / signature string to search for.
 * @param prime Prime number modulus used for rolling hash computation (default 101).
 * @param base Base / alphabet size for rolling hash computation (default 256).
 * @return std::vector<size_t> Vector of 0-based starting indices where pattern occurs in text.
 */
std::vector<size_t> rabin_karp_string_match(const std::string& text, 
                                           const std::string& pattern, 
                                           size_t prime = 101, 
                                           size_t base = 256);

#endif // STRING_MATCHING_HPP
