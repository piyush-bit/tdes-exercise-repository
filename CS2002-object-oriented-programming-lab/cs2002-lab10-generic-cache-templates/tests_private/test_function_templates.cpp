#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <stdexcept>
#include "generic_cache.hpp"

struct ProcessData {
    int id;
    double score;

    bool operator<(const ProcessData& other) const {
        return score < other.score;
    }
    bool operator==(const ProcessData& other) const {
        return id == other.id && score == other.score;
    }
};

void test_function_template_basic_types() {
    // Single element
    std::vector<int> single = {42};
    assert(findMaxMetric(single) == 42);

    // Negative numbers
    std::vector<int> negatives = {-10, -50, -3, -20};
    assert(findMaxMetric(negatives) == -3);

    // Floating point precision
    std::vector<double> floats = {0.001, 0.0005, 0.1, 0.099};
    assert(findMaxMetric(floats) == 0.1);
}

void test_function_template_custom_struct() {
    std::vector<ProcessData> processes = {
        {1, 85.5},
        {2, 92.0},
        {3, 78.3},
        {4, 91.9}
    };

    ProcessData max_proc = findMaxMetric(processes);
    assert(max_proc.id == 2);
    assert(max_proc.score == 92.0);
}

void test_function_template_exceptions() {
    std::vector<std::string> empty_strings;
    bool caught = false;
    try {
        findMaxMetric(empty_strings);
    } catch (const std::invalid_argument&) {
        caught = true;
    }
    assert(caught);
}

int main() {
    std::cout << "[Private Test] Running Function Templates Test Suite..." << std::endl;
    test_function_template_basic_types();
    test_function_template_custom_struct();
    test_function_template_exceptions();
    std::cout << "[Private Test] Function Templates Test Suite PASSED" << std::endl;
    return 0;
}
