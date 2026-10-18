#include "fleet_hierarchy.hpp"

// Helper function to format double with fixed precision
static std::string format_double(double val, int precision) {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(precision) << val;
    return ss.str();
}

// ============================================================================
// 1. BaseVehicle Implementation
// ============================================================================

BaseVehicle::BaseVehicle(const std::string& id, const std::string& model_name, double initial_odometer)
    : vehicle_id(id), model(model_name), odometer_km(initial_odometer) {
    if (vehicle_id.empty()) {
        throw std::invalid_argument("Vehicle ID cannot be empty");
    }
    if (model.empty()) {
        throw std::invalid_argument("Vehicle model cannot be empty");
    }
    if (odometer_km < 0.0) {
        throw std::invalid_argument("Initial odometer reading cannot be negative");
    }
}

std::string BaseVehicle::get_vehicle_id() const {
    return vehicle_id;
}

std::string BaseVehicle::get_model() const {
    return model;
}

double BaseVehicle::get_odometer() const {
    return odometer_km;
}

void BaseVehicle::drive(double distance_km) {
    if (distance_km <= 0.0) {
        throw std::invalid_argument("Drive distance must be strictly positive");
    }
    odometer_km += distance_km;
}

std::string BaseVehicle::get_status() const {
    return "ID: " + vehicle_id + " | Model: " + model + " | Odometer: " + format_double(odometer_km, 1) + " km";
}

// ============================================================================
// 2. ElectricVehicle Implementation
// ============================================================================

ElectricVehicle::ElectricVehicle(const std::string& id, const std::string& model_name, double initial_odometer,
                                 double capacity_kwh, double current_battery_kwh, double rate_kwh_per_km)
    : BaseVehicle(id, model_name, initial_odometer),
      battery_capacity_kwh(capacity_kwh), battery_level_kwh(current_battery_kwh), consumption_rate_kwh_per_km(rate_kwh_per_km) {
    if (battery_capacity_kwh <= 0.0) {
        throw std::invalid_argument("Battery capacity must be strictly positive");
    }
    if (consumption_rate_kwh_per_km <= 0.0) {
        throw std::invalid_argument("Consumption rate must be strictly positive");
    }
    if (battery_level_kwh < 0.0 || battery_level_kwh > battery_capacity_kwh) {
        throw std::invalid_argument("Current battery level must be between 0.0 and capacity");
    }
}

double ElectricVehicle::get_battery_capacity() const {
    return battery_capacity_kwh;
}

double ElectricVehicle::get_battery_level() const {
    return battery_level_kwh;
}

double ElectricVehicle::get_consumption_rate() const {
    return consumption_rate_kwh_per_km;
}

double ElectricVehicle::get_battery_percentage() const {
    return (battery_level_kwh / battery_capacity_kwh) * 100.0;
}

void ElectricVehicle::charge(double amount_kwh) {
    if (amount_kwh <= 0.0) {
        throw std::invalid_argument("Charge amount must be strictly positive");
    }
    battery_level_kwh += amount_kwh;
    if (battery_level_kwh > battery_capacity_kwh) {
        battery_level_kwh = battery_capacity_kwh;
    }
}

void ElectricVehicle::drive(double distance_km) {
    if (distance_km <= 0.0) {
        throw std::invalid_argument("Drive distance must be strictly positive");
    }
    double energy_needed = distance_km * consumption_rate_kwh_per_km;
    if (battery_level_kwh >= energy_needed) {
        battery_level_kwh -= energy_needed;
        BaseVehicle::drive(distance_km);
    } else {
        double max_dist = battery_level_kwh / consumption_rate_kwh_per_km;
        battery_level_kwh = 0.0;
        if (max_dist > 0.0) {
            BaseVehicle::drive(max_dist);
        }
        throw std::runtime_error("Battery depleted during drive");
    }
}

std::string ElectricVehicle::get_status() const {
    return BaseVehicle::get_status() + " | Battery: " + format_double(get_battery_percentage(), 1) +
           "% (" + format_double(battery_level_kwh, 1) + "/" + format_double(battery_capacity_kwh, 1) + " kWh)";
}

// ============================================================================
// 3. AutonomousElectricVehicle Implementation
// ============================================================================

AutonomousElectricVehicle::AutonomousElectricVehicle(const std::string& id, const std::string& model_name, double initial_odometer,
                                                     double capacity_kwh, double current_battery_kwh, double rate_kwh_per_km,
                                                     const std::string& sw_version)
    : ElectricVehicle(id, model_name, initial_odometer, capacity_kwh, current_battery_kwh, rate_kwh_per_km),
      software_version(sw_version), autopilot_engaged(false), autonomous_odometer_km(0.0), disengagement_count(0) {
    if (software_version.empty()) {
        throw std::invalid_argument("Software version cannot be empty");
    }
}

std::string AutonomousElectricVehicle::get_software_version() const {
    return software_version;
}

bool AutonomousElectricVehicle::is_autopilot_engaged() const {
    return autopilot_engaged;
}

double AutonomousElectricVehicle::get_autonomous_odometer() const {
    return autonomous_odometer_km;
}

int AutonomousElectricVehicle::get_disengagement_count() const {
    return disengagement_count;
}

void AutonomousElectricVehicle::engage_autopilot() {
    autopilot_engaged = true;
}

void AutonomousElectricVehicle::disengage_autopilot(const std::string& /* reason */) {
    if (autopilot_engaged) {
        autopilot_engaged = false;
        disengagement_count++;
    }
}

void AutonomousElectricVehicle::drive(double distance_km) {
    double initial_odo = get_odometer();
    bool threw_exception = false;
    std::exception_ptr eptr;

    try {
        ElectricVehicle::drive(distance_km);
    } catch (...) {
        threw_exception = true;
        eptr = std::current_exception();
    }

    double driven_distance = get_odometer() - initial_odo;
    if (autopilot_engaged && driven_distance > 0.0) {
        autonomous_odometer_km += driven_distance;
    }

    if (threw_exception) {
        std::rethrow_exception(eptr);
    }
}

std::string AutonomousElectricVehicle::get_status() const {
    return ElectricVehicle::get_status() + " | Autopilot: " + (autopilot_engaged ? "ENGAGED" : "DISENGAGED") +
           " | AutoOdo: " + format_double(autonomous_odometer_km, 1) + " km | Disengagements: " + std::to_string(disengagement_count);
}

// ============================================================================
// 4. AutonomousSystem Implementation
// ============================================================================

AutonomousSystem::AutonomousSystem(const std::string& sys_id, int sensors, const std::string& status)
    : system_id(sys_id), sensor_count(sensors), system_status(status), self_test_passed(false) {
    if (system_id.empty()) {
        throw std::invalid_argument("System ID cannot be empty");
    }
    if (sensor_count <= 0) {
        throw std::invalid_argument("Sensor count must be positive");
    }
}

std::string AutonomousSystem::get_system_id() const {
    return system_id;
}

int AutonomousSystem::get_sensor_count() const {
    return sensor_count;
}

std::string AutonomousSystem::get_system_status() const {
    return system_status;
}

bool AutonomousSystem::is_self_test_passed() const {
    return self_test_passed;
}

bool AutonomousSystem::perform_self_test() {
    if (sensor_count >= 4 && system_status != "OFFLINE") {
        self_test_passed = true;
        system_status = "OK";
        return true;
    } else {
        self_test_passed = false;
        system_status = "DEGRADED";
        return false;
    }
}

void AutonomousSystem::set_system_status(const std::string& status) {
    system_status = status;
}

std::string AutonomousSystem::get_telemetry_report() const {
    return "System ID: " + system_id + " | Sensors: " + std::to_string(sensor_count) +
           " | Status: " + system_status + " | SelfTest: " + (self_test_passed ? "PASS" : "FAIL");
}

// ============================================================================
// 5. AutonomousRoboTaxi Implementation
// ============================================================================

AutonomousRoboTaxi::AutonomousRoboTaxi(const std::string& vehicle_id, const std::string& model_name, double initial_odometer,
                                       double capacity_kwh, double current_battery_kwh, double rate_kwh_per_km,
                                       const std::string& sys_id, int sensors,
                                       int passenger_cap, double fare_rate)
    : ElectricVehicle(vehicle_id, model_name, initial_odometer, capacity_kwh, current_battery_kwh, rate_kwh_per_km),
      AutonomousSystem(sys_id, sensors, "OK"),
      passenger_capacity(passenger_cap), fare_rate_per_km(fare_rate), total_fares_collected(0.0), completed_trips(0) {
    if (passenger_capacity <= 0) {
        throw std::invalid_argument("Passenger capacity must be positive");
    }
    if (fare_rate_per_km <= 0.0) {
        throw std::invalid_argument("Fare rate must be positive");
    }
}

int AutonomousRoboTaxi::get_passenger_capacity() const {
    return passenger_capacity;
}

double AutonomousRoboTaxi::get_fare_rate() const {
    return fare_rate_per_km;
}

double AutonomousRoboTaxi::get_total_fares() const {
    return total_fares_collected;
}

int AutonomousRoboTaxi::get_completed_trips() const {
    return completed_trips;
}

double AutonomousRoboTaxi::dispatch_trip(int passengers, double distance_km) {
    if (passengers <= 0 || passengers > passenger_capacity) {
        throw std::invalid_argument("Invalid passenger count for trip dispatch");
    }
    if (distance_km <= 0.0) {
        throw std::invalid_argument("Distance must be positive for trip dispatch");
    }
    if (!is_self_test_passed()) {
        throw std::runtime_error("Cannot dispatch trip: AutonomousSystem self-test failed");
    }

    ElectricVehicle::drive(distance_km);

    double fare = distance_km * fare_rate_per_km;
    total_fares_collected += fare;
    completed_trips++;

    return fare;
}

std::string AutonomousRoboTaxi::get_full_report() const {
    return ElectricVehicle::get_status() + " || " + AutonomousSystem::get_telemetry_report() +
           " || Taxi: [Cap: " + std::to_string(passenger_capacity) + ", Fares: $" + format_double(total_fares_collected, 2) +
           ", Trips: " + std::to_string(completed_trips) + "]";
}
