#include "db_connection.hpp"
#include <iostream>

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

void test_raii_scope_cleanup() {
    std::cout << "--- Private Test: RAII Scope Automatic Cleanup ---\n";
    DatabaseConnection::reset_counters();

    {
        DatabaseConnection conn("session_db", 88);
        ASSERT_EQ(DatabaseConnection::get_active_connections(), 1, "Active connections incremented to 1");
        conn.write_to_buffer("INSERT INTO users VALUES('alice');");
        ASSERT_EQ(DatabaseConnection::get_total_flushes(), 0, "No flushes before scope exit");
        ASSERT_EQ(DatabaseConnection::get_total_closes(), 0, "No closes before scope exit");
    }

    // After block exit, destructor should have executed
    ASSERT_EQ(DatabaseConnection::get_total_flushes(), 1, "Destructor automatically flushed buffer");
    ASSERT_EQ(DatabaseConnection::get_total_closes(), 1, "Destructor automatically closed socket");
    ASSERT_EQ(DatabaseConnection::get_active_connections(), 0, "Active connections decremented back to 0");
}

void test_raii_disconnected_cleanup() {
    std::cout << "--- Private Test: Disconnected Connection Cleanup ---\n";
    DatabaseConnection::reset_counters();

    {
        DatabaseConnection default_conn;
        ASSERT_EQ(DatabaseConnection::get_active_connections(), 0, "Default connection has 0 active connections");
    }

    ASSERT_EQ(DatabaseConnection::get_total_flushes(), 0, "Destructor did not flush disconnected object");
    ASSERT_EQ(DatabaseConnection::get_total_closes(), 0, "Destructor did not close disconnected object");
}

void test_raii_idempotent_manual_close() {
    std::cout << "--- Private Test: Manual Flush/Close Before Destructor ---\n";
    DatabaseConnection::reset_counters();

    {
        DatabaseConnection conn("manual_db", 99);
        conn.write_to_buffer("SOME PENDING WRITE");
        conn.flush_buffer();
        conn.close_connection();

        ASSERT_EQ(DatabaseConnection::get_total_flushes(), 1, "Manual flush recorded");
        ASSERT_EQ(DatabaseConnection::get_total_closes(), 1, "Manual close recorded");
        ASSERT_EQ(DatabaseConnection::get_active_connections(), 0, "Active connections is 0 after manual close");
    }

    // Destructor runs on already closed/flushed connection
    ASSERT_EQ(DatabaseConnection::get_total_flushes(), 1, "Destructor did not double-flush");
    ASSERT_EQ(DatabaseConnection::get_total_closes(), 1, "Destructor did not double-close");
}

void test_multiple_objects_raii() {
    std::cout << "--- Private Test: Multiple Objects RAII Lifecycle ---\n";
    DatabaseConnection::reset_counters();

    {
        DatabaseConnection conn1("db1", 101);
        DatabaseConnection conn2("db2", 102);
        DatabaseConnection conn3("db3", 103);

        conn1.write_to_buffer("QUERY 1");
        conn2.write_to_buffer("QUERY 2");

        ASSERT_EQ(DatabaseConnection::get_active_connections(), 3, "3 active connections created");
    }

    ASSERT_EQ(DatabaseConnection::get_total_flushes(), 2, "Destructors flushed 2 non-empty buffers");
    ASSERT_EQ(DatabaseConnection::get_total_closes(), 3, "Destructors closed all 3 sockets");
    ASSERT_EQ(DatabaseConnection::get_active_connections(), 0, "Active connections reset to 0");
}

int main() {
    test_raii_scope_cleanup();
    test_raii_disconnected_cleanup();
    test_raii_idempotent_manual_close();
    test_multiple_objects_raii();

    if (failed) {
        std::cerr << "\nRAII Destructor private tests failed!\n";
        return 1;
    }

    std::cout << "\nAll RAII Destructor Private Tests Passed!\n";
    return 0;
}
