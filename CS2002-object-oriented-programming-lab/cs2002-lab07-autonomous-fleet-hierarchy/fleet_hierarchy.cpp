#include "fleet_hierarchy.hpp"

// ============================================================================
// 1. BaseVehicle Implementation (Student Boilerplate)
// ============================================================================

BaseVehicle::BaseVehicle(const std::string& id, const std::string& model_name, double initial_odometer)
    : vehicle_id(id), model(model_name), odometer_km(initial_odometer) {
    // TODO: Validate inputs: throw std::invalid_argument if id or model_name is empty or initial_odometer < 0.0
}

std::string BaseVehicle::get_vehicle_id() const {
    // TODO: Return vehicle_id
    return "";
}

std::string BaseVehicle::get_model() const {
    // TODO: Return model
    return "";
}

double BaseVehicle::get_odometer() const {
    // TODO: Return odometer_km
    return 0.0;
}

void BaseVehicle::drive(double distance_km) {
    // TODO: Validate distance_km > 0.0, then increment odometer_km
    (void)distance_km;
}

std::string BaseVehicle::get_status() const {
    // TODO: Return string format "ID: <id> | Model: <model> | Odometer: <odometer> km"
    return "";
}

// ============================================================================
// 2. ElectricVehicle Implementation (Student Boilerplate)
// ============================================================================

ElectricVehicle::ElectricVehicle(const std::string& id, const std::string& model_name, double initial_odometer,
                                 double capacity_kwh, double current_battery_kwh, double rate_kwh_per_km)
    : BaseVehicle(id, model_name, initial_odometer),
      battery_capacity_kwh(capacity_kwh), battery_level_kwh(current_battery_kwh), consumption_rate_kwh_per_km(rate_kwh_per_km) {
    // TODO: Validate inputs (capacity_kwh > 0, rate_kwh_per_km > 0, current_battery_kwh within [0, capacity_kwh])
}

double ElectricVehicle::get_battery_capacity() const {
    // TODO: Return battery_capacity_kwh
    return 0.0;
}

double ElectricVehicle::get_battery_level() const {
    // TODO: Return battery_level_kwh
    return 0.0;
}

double ElectricVehicle::get_consumption_rate() const {
    // TODO: Return consumption_rate_kwh_per_km
    return 0.0;
}

double ElectricVehicle::get_battery_percentage() const {
    // TODO: Return (battery_level_kwh / battery_capacity_kwh) * 100.0
    return 0.0;
}

void ElectricVehicle::charge(double amount_kwh) {
    // TODO: Validate amount_kwh > 0.0, add to battery_level_kwh capped at capacity
    (void)amount_kwh;
}

void ElectricVehicle::drive(double distance_km) {
    // TODO: Implement drive with battery consumption. If battery is insufficient,
    // drive as far as possible, set battery to 0.0, and throw std::runtime_error.
    (void)distance_km;
}

std::string ElectricVehicle::get_status() const {
    // TODO: Return BaseVehicle status extended with battery metrics
    return "";
}

// ============================================================================
// 3. AutonomousElectricVehicle Implementation (Student Boilerplate)
// ============================================================================

AutonomousElectricVehicle::AutonomousElectricVehicle(const std::string& id, const std::string& model_name, double initial_odometer,
                                                     double capacity_kwh, double current_battery_kwh, double rate_kwh_per_km,
                                                     const std::string& sw_version)
    : ElectricVehicle(id, model_name, initial_odometer, capacity_kwh, current_battery_kwh, rate_kwh_per_km),
      software_version(sw_version), autopilot_engaged(false), autonomous_odometer_km(0.0), disengagement_count(0) {
    // TODO: Validate sw_version non-empty
}

std::string AutonomousElectricVehicle::get_software_version() const {
    // TODO: Return software_version
    return "";
}

bool AutonomousElectricVehicle::is_autopilot_engaged() const {
    // TODO: Return autopilot_engaged
    return false;
}

double AutonomousElectricVehicle::get_autonomous_odometer() const {
    // TODO: Return autonomous_odometer_km
    return 0.0;
}

int AutonomousElectricVehicle::get_disengagement_count() const {
    // TODO: Return disengagement_count
    return 0;
}

void AutonomousElectricVehicle::engage_autopilot() {
    // TODO: Engage autopilot
}

void AutonomousElectricVehicle::disengage_autopilot(const std::string& reason) {
    // TODO: Disengage autopilot if active and increment disengagement_count
    (void)reason;
}

void AutonomousElectricVehicle::drive(double distance_km) {
    // TODO: Drive using ElectricVehicle::drive. Track distance driven under autopilot.
    (void)distance_km;
}

std::string AutonomousElectricVehicle::get_status() const {
    // TODO: Return ElectricVehicle status extended with autopilot telemetry
    return "";
}

// ============================================================================
// 4. AutonomousSystem Implementation (Student Boilerplate)
// ============================================================================

AutonomousSystem::AutonomousSystem(const std::string& sys_id, int sensors, const std::string& status)
    : system_id(sys_id), sensor_count(sensors), system_status(status), self_test_passed(false) {
    // TODO: Validate sys_id non-empty and sensor_count > 0
}

std::string AutonomousSystem::get_system_id() const {
    // TODO: Return system_id
    return "";
}

int AutonomousSystem::get_sensor_count() const {
    // TODO: Return sensor_count
    return 0;
}

std::string AutonomousSystem::get_system_status() const {
    // TODO: Return system_status
    return "";
}

bool AutonomousSystem::is_self_test_passed() const {
    // TODO: Return self_test_passed
    return false;
}

bool AutonomousSystem::perform_self_test() {
    // TODO: If sensor_count >= 4 and status != "OFFLINE", set self_test_passed = true & status = "OK", return true. Else return false.
    return false;
}

void AutonomousSystem::set_system_status(const std::string& status) {
    // TODO: Update system_status
    (void)status;
}

std::string AutonomousSystem::get_telemetry_report() const {
    // TODO: Return telemetry report string
    return "";
}

// ============================================================================
// 5. AutonomousRoboTaxi Implementation (Student Boilerplate)
// ============================================================================

AutonomousRoboTaxi::AutonomousRoboTaxi(const std::string& vehicle_id, const std::string& model_name, double initial_odometer,
                                       double capacity_kwh, double current_battery_kwh, double rate_kwh_per_km,
                                       const std::string& sys_id, int sensors,
                                       int passenger_cap, double fare_rate)
    : ElectricVehicle(vehicle_id, model_name, initial_odometer, capacity_kwh, current_battery_kwh, rate_kwh_per_km),
      AutonomousSystem(sys_id, sensors, "OK"),
      passenger_capacity(passenger_cap), fare_rate_per_km(fare_rate), total_fares_collected(0.0), completed_trips(0) {
    // TODO: Validate passenger_cap > 0 and fare_rate > 0.0
}

int AutonomousRoboTaxi::get_passenger_capacity() const {
    // TODO: Return passenger_capacity
    return 0;
}

double AutonomousRoboTaxi::get_fare_rate() const {
    // TODO: Return fare_rate_per_km
    return 0.0;
}

double AutonomousRoboTaxi::get_total_fares() const {
    // TODO: Return total_fares_collected
    return 0.0;
}

int AutonomousRoboTaxi::get_completed_trips() const {
    // TODO: Return completed_trips
    return 0;
}

double AutonomousRoboTaxi::dispatch_trip(int passengers, double distance_km) {
    // TODO: Validate inputs, check self-test, call drive, update fares & trips, return fare.
    (void)passengers;
    (void)distance_km;
    return 0.0;
}

std::string AutonomousRoboTaxi::get_full_report() const {
    // TODO: Return full report combining EV status, AutonomousSystem report, and Taxi metrics
    return "";
}
