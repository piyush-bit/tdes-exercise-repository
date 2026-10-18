#include "db_connection.hpp"
#include <iostream>
#include <cstring>

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

void test_default_constructor() {
    std::cout << "--- Running Public Test: Default Constructor ---\n";
    DatabaseConnection conn;
    ASSERT_EQ(conn.get_db_name(), std::string("default_db"), "Default constructor sets db_name to default_db");
    ASSERT_EQ(conn.get_socket_fd(), -1, "Default constructor sets socket_fd to -1");
    ASSERT_TRUE(!conn.is_connected(), "Default constructor is_connected is false");
    ASSERT_TRUE(conn.get_buffer_capacity() >= 1024, "Default constructor buffer capacity is at least 1024");
    ASSERT_EQ(conn.get_buffer_size(), static_cast<std::size_t>(0), "Default constructor buffer size is 0");
}

void test_parameterized_constructor() {
    std::cout << "--- Running Public Test: Parameterized Constructor ---\n";
    DatabaseConnection conn("auth_service", 42);
    ASSERT_EQ(conn.get_db_name(), std::string("auth_service"), "Parameterized constructor sets db_name correctly");
    ASSERT_EQ(conn.get_socket_fd(), 42, "Parameterized constructor sets socket_fd correctly");
    ASSERT_TRUE(conn.is_connected(), "Parameterized constructor is_connected is true for fd >= 0");
}

void test_write_and_buffer() {
    std::cout << "--- Running Public Test: Write to Buffer ---\n";
    DatabaseConnection conn("analytics_db", 10);
    conn.write_to_buffer("INSERT INTO logs VALUES(1);");
    ASSERT_EQ(std::string(conn.get_buffer()), std::string("INSERT INTO logs VALUES(1);"), "Buffer holds written string");
    ASSERT_EQ(conn.get_buffer_size(), std::string("INSERT INTO logs VALUES(1);").length(), "Buffer size updated after write");
}

void test_copy_constructor_deep_copy() {
    std::cout << "--- Running Public Test: Copy Constructor Deep Copy ---\n";
    DatabaseConnection original("orders_db", 55);
    original.write_to_buffer("BEGIN TRANSACTION;");

    DatabaseConnection copy_conn(original);
    ASSERT_EQ(copy_conn.get_db_name(), std::string("orders_db"), "Copy constructor copies db_name");
    ASSERT_EQ(copy_conn.get_socket_fd(), 55, "Copy constructor copies socket_fd");
    ASSERT_EQ(std::string(copy_conn.get_buffer()), std::string("BEGIN TRANSACTION;"), "Copy constructor copies buffer contents");

    // Verify buffer pointers are distinct (Deep Copy)
    ASSERT_TRUE(original.get_buffer() != copy_conn.get_buffer(), "Copy constructor performs deep copy (pointers differ)");

    // Modify original and ensure copy is unchanged
    original.write_to_buffer(" UPDATE orders SET status='PAID';");
    ASSERT_TRUE(std::string(original.get_buffer()) != std::string(copy_conn.get_buffer()), "Modifying original does not alter copy");
}

int main() {
    DatabaseConnection::reset_counters();
    test_default_constructor();
    test_parameterized_constructor();
    test_write_and_buffer();
    test_copy_constructor_deep_copy();

    if (failed) {
        std::cerr << "\nPublic tests failed!\n";
        return 1;
    }

    std::cout << "\nAll Public Tests Passed Successfully!\n";
    return 0;
}
