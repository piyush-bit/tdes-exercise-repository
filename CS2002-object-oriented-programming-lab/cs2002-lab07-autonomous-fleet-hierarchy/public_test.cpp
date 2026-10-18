#include "fleet_hierarchy.hpp"
#include <iostream>
#include <cassert>
#include <cmath>

static void test_base_vehicle() {
    std::cout << "[TEST] BaseVehicle operations..." << std::endl;
    BaseVehicle v1("V-100", "Generic Truck", 50.0);
    assert(v1.get_vehicle_id() == "V-100");
    assert(v1.get_model() == "Generic Truck");
    assert(std::abs(v1.get_odometer() - 50.0) < 1e-6);

    v1.drive(25.5);
    assert(std::abs(v1.get_odometer() - 75.5) < 1e-6);

    std::string status = v1.get_status();
    assert(status.find("V-100") != std::string::npos);
    assert(status.find("75.5") != std::string::npos);

    // Exception tests
    try {
        BaseVehicle bad_v("", "ModelX", 0.0);
        assert(false && "Should have thrown invalid_argument");
    } catch (const std::invalid_argument&) {}

    try {
        v1.drive(-10.0);
        assert(false && "Should have thrown invalid_argument");
    } catch (const std::invalid_argument&) {}

    std::cout << " -> BaseVehicle PASS" << std::endl;
}

static void test_electric_vehicle() {
    std::cout << "[TEST] ElectricVehicle operations..." << std::endl;
    ElectricVehicle ev("EV-200", "Sedan-E", 100.0, 60.0, 50.0, 0.2); // 60kWh capacity, 50kWh current, 0.2kWh/km
    assert(ev.get_vehicle_id() == "EV-200");
    assert(std::abs(ev.get_battery_percentage() - (50.0 / 60.0 * 100.0)) < 1e-4);

    // Drive 100 km -> requires 20 kWh
    ev.drive(100.0);
    assert(std::abs(ev.get_odometer() - 200.0) < 1e-6);
    assert(std::abs(ev.get_battery_level() - 30.0) < 1e-6);

    // Charge 40 kWh -> caps at 60 kWh
    ev.charge(40.0);
    assert(std::abs(ev.get_battery_level() - 60.0) < 1e-6);

    // Depletion test: try driving 400 km -> requires 80 kWh, only 60 available
    try {
        ev.drive(400.0);
        assert(false && "Should have thrown runtime_error for battery depletion");
    } catch (const std::runtime_error& e) {
        std::string msg = e.what();
        assert(msg.find("depleted") != std::string::npos);
    }
    // Driven maximum possible distance: 60 kWh / 0.2 kWh/km = 300 km. Total odo = 200 + 300 = 500
    assert(std::abs(ev.get_battery_level() - 0.0) < 1e-6);
    assert(std::abs(ev.get_odometer() - 500.0) < 1e-6);

    std::cout << " -> ElectricVehicle PASS" << std::endl;
}

static void test_autonomous_system() {
    std::cout << "[TEST] AutonomousSystem operations..." << std::endl;
    AutonomousSystem sys("SYS-ALPHA", 6, "OK");
    assert(sys.get_system_id() == "SYS-ALPHA");
    assert(sys.get_sensor_count() == 6);
    assert(!sys.is_self_test_passed());

    bool passed = sys.perform_self_test();
    assert(passed);
    assert(sys.is_self_test_passed());
    assert(sys.get_telemetry_report().find("PASS") != std::string::npos);

    std::cout << " -> AutonomousSystem PASS" << std::endl;
}

int main() {
    std::cout << "=== Running Public Test Suite ===" << std::endl;
    test_base_vehicle();
    test_electric_vehicle();
    test_autonomous_system();
    std::cout << "=== Public Test Suite Passed! ===" << std::endl;
    return 0;
}
