#include "db_connection.hpp"
#include <iostream>
#include <cstring>
#include <string>

static int failed = 0;

#define ASSERT_TRUE(condition, msg) \
    do { \
        if (!(condition)) { \
            std::cerr << "[FAIL] " << msg << std::endl; \
            failed = 1; \
        } else { \
            std::cout << "[PASS] " << msg << std::endl; \
        } \
    } while (0)

#define ASSERT_EQ(actual, expected, msg) \
    do { \
        if ((actual) != (expected)) { \
            std::cerr << "[FAIL] " << msg << ": Expected " << (expected) << ", got " << (actual) << std::endl; \
            failed = 1; \
        } else { \
            std::cout << "[PASS] " << msg << std::endl; \
        } \
    } while (0)

void test_default_constructor_details() {
    std::cout << "--- Private Test: Default Constructor Details ---\n";
    DatabaseConnection conn;
    ASSERT_EQ(conn.get_db_name(), std::string("default_db"), "Default constructor name is default_db");
    ASSERT_EQ(conn.get_socket_fd(), -1, "Default constructor socket_fd is -1");
    ASSERT_TRUE(!conn.is_connected(), "Default constructor is_connected is false");
    ASSERT_TRUE(conn.get_buffer() != nullptr, "Default constructor buffer pointer is non-null");
    ASSERT_EQ(conn.get_buffer_size(), static_cast<std::size_t>(0), "Default constructor buffer size is 0");
    ASSERT_TRUE(conn.get_buffer_capacity() >= 1024, "Default constructor buffer capacity >= 1024");
}

void test_parameterized_constructor_scenarios() {
    std::cout << "--- Private Test: Parameterized Constructor Scenarios ---\n";
    DatabaseConnection conn1("prod_db", 100);
    ASSERT_EQ(conn1.get_db_name(), std::string("prod_db"), "Name set correctly");
    ASSERT_EQ(conn1.get_socket_fd(), 100, "Socket FD set correctly");
    ASSERT_TRUE(conn1.is_connected(), "is_connected true for fd 100");

    DatabaseConnection conn2("invalid_db", -5);
    ASSERT_EQ(conn2.get_db_name(), std::string("invalid_db"), "Invalid connection name set");
    ASSERT_EQ(conn2.get_socket_fd(), -5, "Invalid connection socket_fd set");
    ASSERT_TRUE(!conn2.is_connected(), "is_connected false for negative socket FD");
}

void test_copy_constructor_and_deep_copy() {
    std::cout << "--- Private Test: Copy Constructor & Deep Copy ---\n";
    DatabaseConnection src("master_db", 12);
    src.write_to_buffer("SELECT 1;");

    DatabaseConnection copy_conn(src);
    ASSERT_EQ(copy_conn.get_db_name(), src.get_db_name(), "Copy has matching db_name");
    ASSERT_EQ(copy_conn.get_socket_fd(), src.get_socket_fd(), "Copy has matching socket_fd");
    ASSERT_EQ(copy_conn.get_buffer_size(), src.get_buffer_size(), "Copy has matching buffer_size");
    ASSERT_EQ(std::string(copy_conn.get_buffer()), std::string(src.get_buffer()), "Copy has matching buffer string");

    ASSERT_TRUE(src.get_buffer() != copy_conn.get_buffer(), "Buffer memory addresses must be distinct (Deep Copy)");

    copy_conn.write_to_buffer("SELECT 2;");
    ASSERT_EQ(std::string(src.get_buffer()), std::string("SELECT 1;"), "Original buffer unaffected by copy write");
    ASSERT_EQ(std::string(copy_conn.get_buffer()), std::string("SELECT 1;SELECT 2;"), "Copy buffer successfully appended");
}

void test_assignment_operator() {
    std::cout << "--- Private Test: Copy Assignment Operator ---\n";
    DatabaseConnection c1("db_one", 20);
    c1.write_to_buffer("DATA_ONE");

    DatabaseConnection c2("db_two", 30);
    c2.write_to_buffer("DATA_TWO");

    c2 = c1;
    ASSERT_EQ(c2.get_db_name(), std::string("db_one"), "Assignment copies db_name");
    ASSERT_EQ(c2.get_socket_fd(), 20, "Assignment copies socket_fd");
    ASSERT_EQ(std::string(c2.get_buffer()), std::string("DATA_ONE"), "Assignment copies buffer content");
    ASSERT_TRUE(c1.get_buffer() != c2.get_buffer(), "Assignment performs deep copy (distinct buffer pointers)");

    // Self-assignment test
    DatabaseConnection& self_ref = c2;
    c2 = self_ref;
    ASSERT_EQ(c2.get_db_name(), std::string("db_one"), "Self-assignment preserves db_name");
    ASSERT_EQ(std::string(c2.get_buffer()), std::string("DATA_ONE"), "Self-assignment preserves buffer content");
}

int main() {
    DatabaseConnection::reset_counters();
    test_default_constructor_details();
    test_parameterized_constructor_scenarios();
    test_copy_constructor_and_deep_copy();
    test_assignment_operator();

    if (failed) {
        std::cerr << "\nConstructor private tests failed!\n";
        return 1;
    }

    std::cout << "\nAll Constructor Private Tests Passed!\n";
    return 0;
}
