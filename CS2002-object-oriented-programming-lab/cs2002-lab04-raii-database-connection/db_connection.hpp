#ifndef DB_CONNECTION_HPP
#define DB_CONNECTION_HPP

#include <string>
#include <cstddef>

class DatabaseConnection {
private:
    std::string db_name_;
    int socket_fd_;
    char* buffer_;
    std::size_t buffer_size_;
    std::size_t buffer_capacity_;
    bool is_connected_;

    // Static metric counters for testing RAII lifecycle events
    static int total_flushes_;
    static int total_closes_;
    static int active_connections_;

public:
    // Constructors & Destructor
    DatabaseConnection();
    DatabaseConnection(const std::string& db_name, int socket_fd);
    DatabaseConnection(const DatabaseConnection& other);
    ~DatabaseConnection();

    // Assignment Operator
    DatabaseConnection& operator=(const DatabaseConnection& other);

    // Core Member Functions
    void write_to_buffer(const std::string& data);
    void flush_buffer();
    void close_connection();

    // Getters
    std::string get_db_name() const;
    int get_socket_fd() const;
    const char* get_buffer() const;
    std::size_t get_buffer_size() const;
    std::size_t get_buffer_capacity() const;
    bool is_connected() const;

    // Static helper functions for testing
    static int get_total_flushes();
    static int get_total_closes();
    static int get_active_connections();
    static void reset_counters();
};

#endif // DB_CONNECTION_HPP
