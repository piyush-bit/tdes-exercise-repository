#include "fleet_hierarchy.hpp"
#include <iostream>
#include <cassert>
#include <cmath>

int main() {
    std::cout << "=== Running Private Test: Multiple Inheritance ===" << std::endl;

    // 1. Instantiation and Multiple Inheritance Casts
    AutonomousRoboTaxi taxi("TAXI-900", "CyberCab", 10.0, 80.0, 80.0, 0.2, "SYS-TAXI-01", 8, 4, 1.50);

    // Verify multiple inheritance casts
    ElectricVehicle* ev_ptr = dynamic_cast<ElectricVehicle*>(&taxi);
    BaseVehicle* base_ptr = dynamic_cast<BaseVehicle*>(&taxi);
    AutonomousSystem* sys_ptr = dynamic_cast<AutonomousSystem*>(&taxi);

    assert(ev_ptr != nullptr && "RoboTaxi must derive from ElectricVehicle");
    assert(base_ptr != nullptr && "RoboTaxi must derive from BaseVehicle");
    assert(sys_ptr != nullptr && "RoboTaxi must derive from AutonomousSystem");

    // 2. Pre-trip check requirement (Self-test must pass before dispatch)
    try {
        taxi.dispatch_trip(2, 20.0);
        assert(false && "Dispatching before self-test should throw runtime_error");
    } catch (const std::runtime_error& e) {
        std::string msg = e.what();
        assert(msg.find("self-test failed") != std::string::npos);
    }

    // Perform self-test
    bool self_test_ok = taxi.perform_self_test();
    assert(self_test_ok);
    assert(taxi.is_self_test_passed());

    // 3. Passenger Capacity Validation
    try {
        taxi.dispatch_trip(5, 10.0); // Capacity is 4
        assert(false && "Dispatching exceeding passengers should throw invalid_argument");
    } catch (const std::invalid_argument&) {}

    try {
        taxi.dispatch_trip(0, 10.0); // Passengers <= 0
        assert(false && "Dispatching 0 passengers should throw invalid_argument");
    } catch (const std::invalid_argument&) {}

    // 4. Dispatch Valid Trips
    double fare1 = taxi.dispatch_trip(3, 50.0); // 50 km @ $1.50/km = $75.00
    assert(std::abs(fare1 - 75.0) < 1e-6);
    assert(std::abs(taxi.get_total_fares() - 75.0) < 1e-6);
    assert(taxi.get_completed_trips() == 1);
    // Battery consumed: 50 * 0.2 = 10 kWh -> remaining battery = 70 kWh, odo = 60 km
    assert(std::abs(taxi.get_battery_level() - 70.0) < 1e-6);
    assert(std::abs(taxi.get_odometer() - 60.0) < 1e-6);

    double fare2 = taxi.dispatch_trip(1, 100.0); // 100 km @ $1.50/km = $150.00
    assert(std::abs(fare2 - 150.0) < 1e-6);
    assert(std::abs(taxi.get_total_fares() - 225.0) < 1e-6);
    assert(taxi.get_completed_trips() == 2);
    // Battery consumed: 100 * 0.2 = 20 kWh -> remaining battery = 50 kWh, odo = 160 km
    assert(std::abs(taxi.get_battery_level() - 50.0) < 1e-6);

    // 5. System Status Degradation
    taxi.set_system_status("OFFLINE");
    taxi.perform_self_test();
    assert(!taxi.is_self_test_passed());

    try {
        taxi.dispatch_trip(2, 10.0);
        assert(false && "Dispatching when status is offline should fail self-test check");
    } catch (const std::runtime_error&) {}

    // Restore system
    taxi.set_system_status("OK");
    taxi.perform_self_test();
    assert(taxi.is_self_test_passed());

    // 6. Full Telemetry Report Inspection
    std::string report = taxi.get_full_report();
    assert(report.find("TAXI-900") != std::string::npos);
    assert(report.find("SYS-TAXI-01") != std::string::npos);
    assert(report.find("$225.00") != std::string::npos);
    assert(report.find("Trips: 2") != std::string::npos);

    std::cout << "=== Multiple Inheritance Private Tests Passed! ===" << std::endl;
    return 0;
}
