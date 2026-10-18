#include "microservice_pool.hpp"

// Define static member variables
int ServiceConnection::active_connections_ = 0;
int ServiceConnection::total_connections_created_ = 0;
int ServiceConnection::max_allowed_connections_ = 10;

ServiceConnection::ServiceConnection(int id, const std::string& endpoint)
    : id_(id), endpoint_(endpoint), is_connected_(true), bytes_transferred_(0) {
    active_connections_++;
    total_connections_created_++;
}

ServiceConnection::~ServiceConnection() {
    disconnect();
}

void ServiceConnection::disconnect() {
    if (is_connected_) {
        is_connected_ = false;
        if (active_connections_ > 0) {
            active_connections_--;
        }
    }
}

bool ServiceConnection::isConnected() const {
    return is_connected_;
}

int ServiceConnection::getId() const {
    return id_;
}

const std::string& ServiceConnection::getEndpoint() const {
    return endpoint_;
}

void ServiceConnection::sendData(size_t bytes) {
    if (is_connected_) {
        bytes_transferred_ += bytes;
    }
}

size_t ServiceConnection::getBytesTransferred() const {
    return bytes_transferred_;
}

ServiceConnection* ServiceConnection::createConnection(int id, const std::string& endpoint) {
    if (active_connections_ >= max_allowed_connections_) {
        return nullptr;
    }
    return new ServiceConnection(id, endpoint);
}

void ServiceConnection::setMaxConnections(int max_conn) {
    max_allowed_connections_ = max_conn;
}

int ServiceConnection::getActiveConnections() {
    return active_connections_;
}

int ServiceConnection::getTotalConnectionsCreated() {
    return total_connections_created_;
}

void ServiceConnection::resetCounters() {
    active_connections_ = 0;
    total_connections_created_ = 0;
    max_allowed_connections_ = 10;
}
