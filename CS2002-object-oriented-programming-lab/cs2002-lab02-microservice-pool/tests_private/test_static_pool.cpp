#include <iostream>
#include <cassert>
#include "microservice_pool.hpp"

int main() {
    std::cout << "--- Running Private Test: Static Connection Pool ---" << std::endl;

    ServiceConnection::resetCounters();

    // 1. Set Custom Pool Limit
    ServiceConnection::setMaxConnections(3);

    // 2. Create connections up to capacity limit
    ServiceConnection* c1 = ServiceConnection::createConnection(1, "srv-1");
    ServiceConnection* c2 = ServiceConnection::createConnection(2, "srv-2");
    ServiceConnection* c3 = ServiceConnection::createConnection(3, "srv-3");

    assert(c1 != nullptr && c2 != nullptr && c3 != nullptr);
    assert(ServiceConnection::getActiveConnections() == 3);
    assert(ServiceConnection::getTotalConnectionsCreated() == 3);

    // 3. Attempt creation beyond limit -> should fail & return nullptr
    ServiceConnection* c4 = ServiceConnection::createConnection(4, "srv-4");
    assert(c4 == nullptr);
    assert(ServiceConnection::getActiveConnections() == 3);
    assert(ServiceConnection::getTotalConnectionsCreated() == 3);

    // 4. Release one connection via disconnect() and allocate new one
    c1->disconnect();
    assert(ServiceConnection::getActiveConnections() == 2);

    c4 = ServiceConnection::createConnection(4, "srv-4");
    assert(c4 != nullptr);
    assert(ServiceConnection::getActiveConnections() == 3);
    assert(ServiceConnection::getTotalConnectionsCreated() == 4);

    // 5. Destructor releases active count automatically
    delete c2; // c2 destroyed, active count should drop to 2
    assert(ServiceConnection::getActiveConnections() == 2);

    // 6. Repeated disconnect calls should be idempotent
    c3->disconnect();
    assert(ServiceConnection::getActiveConnections() == 1);
    c3->disconnect(); // Second call should not double-decrement
    assert(ServiceConnection::getActiveConnections() == 1);

    // Clean up remaining allocations
    delete c1;
    delete c3;
    delete c4;

    assert(ServiceConnection::getActiveConnections() == 0);

    // 7. Test resetCounters()
    ServiceConnection::resetCounters();
    assert(ServiceConnection::getActiveConnections() == 0);
    assert(ServiceConnection::getTotalConnectionsCreated() == 0);

    std::cout << "test_static_pool passed successfully!" << std::endl;
    return 0;
}
