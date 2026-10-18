#include "db_connection.hpp"
#include <cstring>

// Initialize static counters
int DatabaseConnection::total_flushes_ = 0;
int DatabaseConnection::total_closes_ = 0;
int DatabaseConnection::active_connections_ = 0;

// Default Constructor
DatabaseConnection::DatabaseConnection()
    : db_name_(""), socket_fd_(-1), buffer_(nullptr), buffer_size_(0), buffer_capacity_(0), is_connected_(false) {
    // TODO: Initialize db_name_ to "default_db", socket_fd_ to -1, is_connected_ to false.
    // TODO: Allocate buffer_ with initial capacity 1024, set buffer_size_ to 0, and null-terminate.
    buffer_capacity_ = 1024;
    buffer_ = new char[buffer_capacity_];
    buffer_[0] = '\0';
    db_name_ = "default_db";
}

// Parameterized Constructor
DatabaseConnection::DatabaseConnection(const std::string& db_name, int socket_fd)
    : db_name_(""), socket_fd_(-1), buffer_(nullptr), buffer_size_(0), buffer_capacity_(0), is_connected_(false) {
    // TODO: Initialize db_name_ and socket_fd_ from arguments.
    // TODO: Set is_connected_ to true if socket_fd >= 0, and increment active_connections_.
    // TODO: Allocate buffer_ with capacity 1024, set buffer_size_ to 0, and null-terminate.
    (void)db_name;
    (void)socket_fd;
}

// Copy Constructor (Deep Copy)
DatabaseConnection::DatabaseConnection(const DatabaseConnection& other)
    : db_name_(""), socket_fd_(-1), buffer_(nullptr), buffer_size_(0), buffer_capacity_(0), is_connected_(false) {
    // TODO: Deep copy all attributes from 'other'.
    // TODO: Allocate a new dynamic char array for buffer_ and copy contents from other.buffer_.
    // TODO: Increment active_connections_ if is_connected_ is true.
    (void)other;
}

// RAII Destructor
DatabaseConnection::~DatabaseConnection() {
    // TODO: If is_connected_ is true, flush the buffer and close the connection socket.
    // TODO: Deallocate dynamic memory buffer_ and set pointer to nullptr.
    delete[] buffer_;
    buffer_ = nullptr;
}

// Copy Assignment Operator
DatabaseConnection& DatabaseConnection::operator=(const DatabaseConnection& other) {
    // TODO: Check for self-assignment.
    // TODO: Clean up existing resources (flush buffer, close connection, delete[] buffer_).
    // TODO: Deep copy from 'other' and return *this.
    (void)other;
    return *this;
}

// Write data into the dynamic buffer
void DatabaseConnection::write_to_buffer(const std::string& data) {
    // TODO: Append data to buffer_ if connected. Resize buffer_ capacity if data exceeds capacity.
    (void)data;
}

// Flush write buffer
void DatabaseConnection::flush_buffer() {
    // TODO: If buffer_size_ > 0, increment total_flushes_, reset buffer_size_ to 0, and null-terminate.
}

// Close connection socket
void DatabaseConnection::close_connection() {
    // TODO: If connected, set is_connected_ to false, socket_fd_ to -1, increment total_closes_, and decrement active_connections_.
}

// Getters
std::string DatabaseConnection::get_db_name() const {
    return db_name_;
}

int DatabaseConnection::get_socket_fd() const {
    return socket_fd_;
}

const char* DatabaseConnection::get_buffer() const {
    return buffer_;
}

std::size_t DatabaseConnection::get_buffer_size() const {
    return buffer_size_;
}

std::size_t DatabaseConnection::get_buffer_capacity() const {
    return buffer_capacity_;
}

bool DatabaseConnection::is_connected() const {
    return is_connected_;
}

// Static Metrics Getters
int DatabaseConnection::get_total_flushes() {
    return total_flushes_;
}

int DatabaseConnection::get_total_closes() {
    return total_closes_;
}

int DatabaseConnection::get_active_connections() {
    return active_connections_;
}

void DatabaseConnection::reset_counters() {
    total_flushes_ = 0;
    total_closes_ = 0;
    active_connections_ = 0;
}
