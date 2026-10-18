#include <iostream>
#include <cassert>
#include <cmath>
#include "microservice_pool.hpp"

int main() {
    std::cout << "--- Running Private Test: Inline Metrics & Telemetry ---" << std::endl;

    ServiceConnection::resetCounters();

    // 1. Test calculateLatencyMs
    double lat1 = calculateLatencyMs(1.0, 1.5);
    assert(std::abs(lat1 - 500.0) < 0.0001);

    double lat2 = calculateLatencyMs(100.5, 100.5);
    assert(std::abs(lat2 - 0.0) < 0.0001);

    // Response time before request time (edge case) -> return 0.0
    double lat3 = calculateLatencyMs(5.0, 4.0);
    assert(std::abs(lat3 - 0.0) < 0.0001);

    // 2. Test bytesToMegabytes
    assert(std::abs(bytesToMegabytes(0) - 0.0) < 0.0001);
    assert(std::abs(bytesToMegabytes(1048576) - 1.0) < 0.0001);       // 1 MB
    assert(std::abs(bytesToMegabytes(5242880) - 5.0) < 0.0001);       // 5 MB
    assert(std::abs(bytesToMegabytes(1572864) - 1.5) < 0.0001);       // 1.5 MB

    // 3. Telemetry on active vs disconnected ServiceConnection
    ServiceConnection* conn = ServiceConnection::createConnection(201, "telemetry-node");
    assert(conn != nullptr);
    assert(conn->getBytesTransferred() == 0);

    conn->sendData(1024);
    conn->sendData(2048);
    conn->sendData(4096);
    assert(conn->getBytesTransferred() == 7168);

    // Disconnect connection, sendData should now be ignored
    conn->disconnect();
    conn->sendData(8192);
    assert(conn->getBytesTransferred() == 7168);

    delete conn;

    std::cout << "test_inline_metrics passed successfully!" << std::endl;
    return 0;
}
