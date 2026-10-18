#include "db_connection.hpp"
#include <cstring>
#include <algorithm>

// Initialize static counters
int DatabaseConnection::total_flushes_ = 0;
int DatabaseConnection::total_closes_ = 0;
int DatabaseConnection::active_connections_ = 0;

// Default Constructor
DatabaseConnection::DatabaseConnection()
    : db_name_("default_db"),
      socket_fd_(-1),
      buffer_(new char[1024]),
      buffer_size_(0),
      buffer_capacity_(1024),
      is_connected_(false) {
    buffer_[0] = '\0';
}

// Parameterized Constructor
DatabaseConnection::DatabaseConnection(const std::string& db_name, int socket_fd)
    : db_name_(db_name),
      socket_fd_(socket_fd),
      buffer_(new char[1024]),
      buffer_size_(0),
      buffer_capacity_(1024),
      is_connected_(socket_fd >= 0) {
    buffer_[0] = '\0';
    if (is_connected_) {
        active_connections_++;
    }
}

// Copy Constructor (Deep Copy)
DatabaseConnection::DatabaseConnection(const DatabaseConnection& other)
    : db_name_(other.db_name_),
      socket_fd_(other.socket_fd_),
      buffer_size_(other.buffer_size_),
      buffer_capacity_(other.buffer_capacity_),
      is_connected_(other.is_connected_) {
    buffer_ = new char[buffer_capacity_];
    if (other.buffer_ && buffer_size_ > 0) {
        std::memcpy(buffer_, other.buffer_, buffer_size_);
    }
    buffer_[buffer_size_] = '\0';
    if (is_connected_) {
        active_connections_++;
    }
}

// RAII Destructor
DatabaseConnection::~DatabaseConnection() {
    if (is_connected_) {
        flush_buffer();
        close_connection();
    }
    delete[] buffer_;
    buffer_ = nullptr;
}

// Copy Assignment Operator
DatabaseConnection& DatabaseConnection::operator=(const DatabaseConnection& other) {
    if (this == &other) {
        return *this;
    }

    if (is_connected_) {
        flush_buffer();
        close_connection();
    }
    delete[] buffer_;

    db_name_ = other.db_name_;
    socket_fd_ = other.socket_fd_;
    buffer_capacity_ = other.buffer_capacity_;
    buffer_size_ = other.buffer_size_;
    is_connected_ = other.is_connected_;

    buffer_ = new char[buffer_capacity_];
    if (other.buffer_ && buffer_size_ > 0) {
        std::memcpy(buffer_, other.buffer_, buffer_size_);
    }
    buffer_[buffer_size_] = '\0';
    if (is_connected_) {
        active_connections_++;
    }

    return *this;
}

// Write data into the dynamic buffer
void DatabaseConnection::write_to_buffer(const std::string& data) {
    if (!is_connected_) {
        return;
    }
    std::size_t required_capacity = buffer_size_ + data.length() + 1;
    if (required_capacity > buffer_capacity_) {
        std::size_t new_capacity = buffer_capacity_;
        while (new_capacity < required_capacity) {
            new_capacity *= 2;
        }
        char* new_buffer = new char[new_capacity];
        if (buffer_) {
            std::memcpy(new_buffer, buffer_, buffer_size_);
            delete[] buffer_;
        }
        buffer_ = new_buffer;
        buffer_capacity_ = new_capacity;
    }
    std::memcpy(buffer_ + buffer_size_, data.c_str(), data.length());
    buffer_size_ += data.length();
    buffer_[buffer_size_] = '\0';
}

// Flush write buffer
void DatabaseConnection::flush_buffer() {
    if (buffer_size_ > 0) {
        total_flushes_++;
        buffer_size_ = 0;
        if (buffer_) {
            buffer_[0] = '\0';
        }
    }
}

// Close connection socket
void DatabaseConnection::close_connection() {
    if (is_connected_) {
        is_connected_ = false;
        socket_fd_ = -1;
        total_closes_++;
        if (active_connections_ > 0) {
            active_connections_--;
        }
    }
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
