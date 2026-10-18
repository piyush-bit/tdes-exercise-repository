#ifndef MICROSERVICE_POOL_HPP
#define MICROSERVICE_POOL_HPP

#include <string>
#include <cstddef>

class ServiceConnection {
private:
    int id_;
    std::string endpoint_;
    bool is_connected_;
    size_t bytes_transferred_;

    static int active_connections_;
    static int total_connections_created_;
    static int max_allowed_connections_;

public:
    ServiceConnection(int id, const std::string& endpoint);
    ~ServiceConnection();

    // Disable copy constructor and assignment operator to ensure proper pool counting
    ServiceConnection(const ServiceConnection&) = delete;
    ServiceConnection& operator=(const ServiceConnection&) = delete;

    // Instance member methods
    void disconnect();
    bool isConnected() const;
    int getId() const;
    const std::string& getEndpoint() const;
    void sendData(size_t bytes);
    size_t getBytesTransferred() const;

    // Static pool management functions
    static ServiceConnection* createConnection(int id, const std::string& endpoint);
    static void setMaxConnections(int max_conn);
    static int getActiveConnections();
    static int getTotalConnectionsCreated();
    static void resetCounters();
};

// Inline telemetry functions for zero-overhead performance calculations
inline double calculateLatencyMs(double requestTimeSec, double responseTimeSec) {
    if (responseTimeSec < requestTimeSec) {
        return 0.0;
    }
    return (responseTimeSec - requestTimeSec) * 1000.0;
}

inline double bytesToMegabytes(size_t bytes) {
    return static_cast<double>(bytes) / (1024.0 * 1024.0);
}

#endif // MICROSERVICE_POOL_HPP
