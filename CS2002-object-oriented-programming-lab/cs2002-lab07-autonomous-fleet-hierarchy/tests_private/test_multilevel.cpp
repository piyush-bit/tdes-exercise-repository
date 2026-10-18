#include "fleet_hierarchy.hpp"
#include <iostream>
#include <cassert>
#include <cmath>

int main() {
    std::cout << "=== Running Private Test: Multilevel Inheritance ===" << std::endl;

    // 1. Inheritance Hierarchy Checks
    AutonomousElectricVehicle aev("AEV-300", "CyberCruiser", 0.0, 100.0, 80.0, 0.25, "v12.1.0");

    // Dynamic cast checks to verify inheritance relationship
    ElectricVehicle* ev_ptr = dynamic_cast<ElectricVehicle*>(&aev);
    BaseVehicle* base_ptr = dynamic_cast<BaseVehicle*>(&aev);
    assert(ev_ptr != nullptr && "AEV must derive from ElectricVehicle");
    assert(base_ptr != nullptr && "AEV must derive from BaseVehicle");

    // Initial state
    assert(aev.get_software_version() == "v12.1.0");
    assert(!aev.is_autopilot_engaged());
    assert(std::abs(aev.get_autonomous_odometer() - 0.0) < 1e-6);
    assert(aev.get_disengagement_count() == 0);

    // 2. Drive without autopilot
    aev.drive(40.0); // consumes 10 kWh, remaining battery = 70 kWh, total odo = 40 km
    assert(std::abs(aev.get_odometer() - 40.0) < 1e-6);
    assert(std::abs(aev.get_autonomous_odometer() - 0.0) < 1e-6); // Auto odo should stay 0

    // 3. Engage Autopilot and Drive
    aev.engage_autopilot();
    assert(aev.is_autopilot_engaged());

    aev.drive(100.0); // consumes 25 kWh, remaining battery = 45 kWh, total odo = 140 km
    assert(std::abs(aev.get_odometer() - 140.0) < 1e-6);
    assert(std::abs(aev.get_autonomous_odometer() - 100.0) < 1e-6); // Auto odo increased by 100

    // Status check
    std::string status = aev.get_status();
    assert(status.find("ENGAGED") != std::string::npos);
    assert(status.find("100.0 km") != std::string::npos);

    // 4. Disengage Autopilot
    aev.disengage_autopilot("Driver Intervention");
    assert(!aev.is_autopilot_engaged());
    assert(aev.get_disengagement_count() == 1);

    // Disengaging when already disengaged should not increment count
    aev.disengage_autopilot();
    assert(aev.get_disengagement_count() == 1);

    // 5. Autopilot battery depletion tracking
    aev.engage_autopilot();
    // Remaining battery = 45 kWh, consumption = 0.25 kWh/km -> can drive 180 km max
    try {
        aev.drive(300.0); // requests 300 km, depletes at 180 km
        assert(false && "Should throw battery depletion runtime_error");
    } catch (const std::runtime_error&) {}

    // Driven 180 km while autopilot engaged -> total odo = 140 + 180 = 320, auto odo = 100 + 180 = 280
    assert(std::abs(aev.get_odometer() - 320.0) < 1e-6);
    assert(std::abs(aev.get_autonomous_odometer() - 280.0) < 1e-6);

    // 6. Validation exceptions
    try {
        AutonomousElectricVehicle bad_aev("AEV-BAD", "Model", 0.0, 50.0, 50.0, 0.2, "");
        assert(false && "Should throw invalid_argument for empty software version");
    } catch (const std::invalid_argument&) {}

    std::cout << "=== Multilevel Inheritance Private Tests Passed! ===" << std::endl;
    return 0;
}
