#ifndef FLEET_HIERARCHY_HPP
#define FLEET_HIERARCHY_HPP

#include <string>
#include <stdexcept>
#include <sstream>
#include <iomanip>

// ============================================================================
// 1. Base Class: BaseVehicle
// ============================================================================
class BaseVehicle {
protected:
    std::string vehicle_id;
    std::string model;
    double odometer_km;

public:
    BaseVehicle(const std::string& id, const std::string& model_name, double initial_odometer = 0.0);
    virtual ~BaseVehicle() = default;

    std::string get_vehicle_id() const;
    std::string get_model() const;
    double get_odometer() const;

    virtual void drive(double distance_km);
    virtual std::string get_status() const;
};

// ============================================================================
// 2. Single Inheritance: ElectricVehicle
// ============================================================================
class ElectricVehicle : public BaseVehicle {
protected:
    double battery_capacity_kwh;
    double battery_level_kwh;
    double consumption_rate_kwh_per_km;

public:
    ElectricVehicle(const std::string& id, const std::string& model_name, double initial_odometer,
                    double capacity_kwh, double current_battery_kwh, double rate_kwh_per_km);
    virtual ~ElectricVehicle() = default;

    double get_battery_capacity() const;
    double get_battery_level() const;
    double get_consumption_rate() const;
    double get_battery_percentage() const;

    void charge(double amount_kwh);
    void drive(double distance_km) override;
    std::string get_status() const override;
};

// ============================================================================
// 3. Multilevel Inheritance: AutonomousElectricVehicle
//    BaseVehicle -> ElectricVehicle -> AutonomousElectricVehicle
// ============================================================================
class AutonomousElectricVehicle : public ElectricVehicle {
private:
    std::string software_version;
    bool autopilot_engaged;
    double autonomous_odometer_km;
    int disengagement_count;

public:
    AutonomousElectricVehicle(const std::string& id, const std::string& model_name, double initial_odometer,
                              double capacity_kwh, double current_battery_kwh, double rate_kwh_per_km,
                              const std::string& sw_version);
    virtual ~AutonomousElectricVehicle() = default;

    std::string get_software_version() const;
    bool is_autopilot_engaged() const;
    double get_autonomous_odometer() const;
    int get_disengagement_count() const;

    void engage_autopilot();
    void disengage_autopilot(const std::string& reason = "Manual Override");
    void drive(double distance_km) override;
    std::string get_status() const override;
};

// ============================================================================
// 4. Standalone Class: AutonomousSystem
// ============================================================================
class AutonomousSystem {
protected:
    std::string system_id;
    int sensor_count;
    std::string system_status;
    bool self_test_passed;

public:
    AutonomousSystem(const std::string& sys_id, int sensors, const std::string& status = "OK");
    virtual ~AutonomousSystem() = default;

    std::string get_system_id() const;
    int get_sensor_count() const;
    std::string get_system_status() const;
    bool is_self_test_passed() const;

    bool perform_self_test();
    void set_system_status(const std::string& status);
    std::string get_telemetry_report() const;
};

// ============================================================================
// 5. Multiple Inheritance: AutonomousRoboTaxi
//    Inherits from ElectricVehicle AND AutonomousSystem
// ============================================================================
class AutonomousRoboTaxi : public ElectricVehicle, public AutonomousSystem {
private:
    int passenger_capacity;
    double fare_rate_per_km;
    double total_fares_collected;
    int completed_trips;

public:
    AutonomousRoboTaxi(const std::string& vehicle_id, const std::string& model_name, double initial_odometer,
                       double capacity_kwh, double current_battery_kwh, double rate_kwh_per_km,
                       const std::string& sys_id, int sensors,
                       int passenger_cap, double fare_rate);
    virtual ~AutonomousRoboTaxi() = default;

    int get_passenger_capacity() const;
    double get_fare_rate() const;
    double get_total_fares() const;
    int get_completed_trips() const;

    double dispatch_trip(int passengers, double distance_km);
    std::string get_full_report() const;
};

#endif // FLEET_HIERARCHY_HPP
