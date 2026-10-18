#include <iostream>
#include <cassert>
#include <cmath>
#include "microservice_pool.hpp"

int main() {
    std::cout << "--- Running Public Tests for Microservice Connection Pool ---" << std::endl;

    // Reset counters before test execution
    ServiceConnection::resetCounters();
    assert(ServiceConnection::getActiveConnections() == 0);
    assert(ServiceConnection::getTotalConnectionsCreated() == 0);

    // Test 1: Factory Creation & Attribute Check
    ServiceConnection* conn = ServiceConnection::createConnection(101, "https://api.auth.internal/v1");
    assert(conn != nullptr);
    assert(conn->isConnected() == true);
    assert(conn->getId() == 101);
    assert(conn->getEndpoint() == "https://api.auth.internal/v1");

    // Test 2: Active & Total Counters
    assert(ServiceConnection::getActiveConnections() == 1);
    assert(ServiceConnection::getTotalConnectionsCreated() == 1);

    // Test 3: Data Transmission & Inline Telemetry (bytesToMegabytes)
    conn->sendData(2097152); // 2 MB (2 * 1024 * 1024)
    assert(conn->getBytesTransferred() == 2097152);
    double mb = bytesToMegabytes(conn->getBytesTransferred());
    assert(std::abs(mb - 2.0) < 0.0001);

    // Test 4: Inline Latency Metric Calculation
    double latency = calculateLatencyMs(10.0, 10.125); // 0.125s = 125ms
    assert(std::abs(latency - 125.0) < 0.0001);

    // Test 5: Disconnecting & Cleanup
    conn->disconnect();
    assert(conn->isConnected() == false);
    assert(ServiceConnection::getActiveConnections() == 0);

    delete conn;
    assert(ServiceConnection::getActiveConnections() == 0);

    std::cout << "All public tests passed successfully!" << std::endl;
    return 0;
}
