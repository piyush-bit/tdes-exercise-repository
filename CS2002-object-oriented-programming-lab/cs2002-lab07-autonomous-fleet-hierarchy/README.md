# CS2002 Lab 07: Autonomous Electric Vehicle Fleet Hierarchy in C++

## 1. Overview & Objectives

In this lab, you will design and implement an Object-Oriented Autonomous Electric Vehicle Fleet management system in C++. This exercise focuses on mastering core C++ Object-Oriented Programming (OOP) concepts:

- **Single Inheritance**: Extending a base vehicle (`BaseVehicle`) into an electric vehicle (`ElectricVehicle`).
- **Multilevel Inheritance**: Building an autonomous vehicle (`AutonomousElectricVehicle`) on top of `ElectricVehicle`, forming the chain: `BaseVehicle` -> `ElectricVehicle` -> `AutonomousElectricVehicle`.
- **Multiple Inheritance**: Creating an autonomous robo-taxi (`AutonomousRoboTaxi`) that inherits concurrently from both `ElectricVehicle` and `AutonomousSystem`.
- **Virtual Functions & Method Overriding**: Dynamic polymorphism using `virtual` functions like `drive()` and `get_status()`.
- **Exception Handling**: Standard error handling using `std::invalid_argument` and `std::runtime_error`.

---

## 2. Class Specifications

### A. `BaseVehicle`
Base class representing any generic vehicle in the fleet.

- **Data Members**:
  - `std::string vehicle_id`: Unique identifier for the vehicle (e.g., `"EV-101"`).
  - `std::string model`: Model name (e.g., `"Model3"`).
  - `double odometer_km`: Total cumulative distance driven in kilometers.

- **Methods**:
  - `BaseVehicle(const std::string& id, const std::string& model_name, double initial_odometer = 0.0)`
    - Throws `std::invalid_argument` if `id` or `model_name` is empty, or if `initial_odometer < 0.0`.
  - `virtual ~BaseVehicle() = default;`
  - Getters: `get_vehicle_id()`, `get_model()`, `get_odometer()`.
  - `virtual void drive(double distance_km)`:
    - Throws `std::invalid_argument` if `distance_km <= 0.0`.
    - Increments `odometer_km` by `distance_km`.
  - `virtual std::string get_status() const`:
    - Returns string formatted as: `"ID: <id> | Model: <model> | Odometer: <odometer> km"` (odometer formatted to 1 decimal place).

---

### B. `ElectricVehicle` (Inherits from `BaseVehicle`)
Derived class representing an electric vehicle.

- **Data Members**:
  - `double battery_capacity_kwh`: Maximum battery capacity in kilowatt-hours.
  - `double battery_level_kwh`: Current charge remaining in kilowatt-hours.
  - `double consumption_rate_kwh_per_km`: Energy consumption rate in kWh per km.

- **Methods**:
  - `ElectricVehicle(const std::string& id, const std::string& model_name, double initial_odometer, double capacity_kwh, double current_battery_kwh, double rate_kwh_per_km)`
    - Throws `std::invalid_argument` if `capacity_kwh <= 0.0`, `rate_kwh_per_km <= 0.0`, `current_battery_kwh < 0.0`, or `current_battery_kwh > capacity_kwh`.
  - Getters: `get_battery_capacity()`, `get_battery_level()`, `get_consumption_rate()`.
  - `double get_battery_percentage() const`:
    - Returns `(battery_level_kwh / battery_capacity_kwh) * 100.0`.
  - `void charge(double amount_kwh)`:
    - Throws `std::invalid_argument` if `amount_kwh <= 0.0`.
    - Adds `amount_kwh` to `battery_level_kwh`, capped at `battery_capacity_kwh`.
  - `void drive(double distance_km) override`:
    - Throws `std::invalid_argument` if `distance_km <= 0.0`.
    - Calculates required energy: `needed = distance_km * consumption_rate_kwh_per_km`.
    - If `battery_level_kwh >= needed`: consumes energy and calls `BaseVehicle::drive(distance_km)`.
    - If `battery_level_kwh < needed`: drives as far as possible with remaining battery (`possible_km = battery_level_kwh / consumption_rate_kwh_per_km`), sets `battery_level_kwh = 0.0`, updates odometer via `BaseVehicle::drive(possible_km)`, and throws `std::runtime_error("Battery depleted during drive")`.
  - `std::string get_status() const override`:
    - Extends `BaseVehicle::get_status()` by appending: `" | Battery: <percentage>% (<level>/<capacity> kWh)"` (all floating-point values formatted to 1 decimal place).

---

### C. `AutonomousElectricVehicle` (Multilevel: `BaseVehicle` -> `ElectricVehicle` -> `AutonomousElectricVehicle`)
Derived class adding autonomous driving features to an electric vehicle.

- **Data Members**:
  - `std::string software_version`: Current autopilot software version (e.g., `"v11.4"`).
  - `bool autopilot_engaged`: Boolean indicating whether autopilot mode is active.
  - `double autonomous_odometer_km`: Distance driven specifically while autopilot was engaged.
  - `int disengagement_count`: Counter for manual overrides / disengagements.

- **Methods**:
  - `AutonomousElectricVehicle(const std::string& id, const std::string& model_name, double initial_odometer, double capacity_kwh, double current_battery_kwh, double rate_kwh_per_km, const std::string& sw_version)`
    - Throws `std::invalid_argument` if `sw_version` is empty. Initializes `autopilot_engaged = false`, `autonomous_odometer_km = 0.0`, `disengagement_count = 0`.
  - Getters: `get_software_version()`, `is_autopilot_engaged()`, `get_autonomous_odometer()`, `get_disengagement_count()`.
  - `void engage_autopilot()`: Sets `autopilot_engaged = true`.
  - `void disengage_autopilot(const std::string& reason = "Manual Override")`:
    - If `autopilot_engaged` was true, sets `autopilot_engaged = false` and increments `disengagement_count`.
  - `void drive(double distance_km) override`:
    - Drives the vehicle using `ElectricVehicle::drive(distance_km)`.
    - If autopilot is engaged, tracks the actual distance driven during this call and adds it to `autonomous_odometer_km` (even if battery depleted partway before an exception was rethrown).
  - `std::string get_status() const override`:
    - Extends `ElectricVehicle::get_status()` by appending: `" | Autopilot: <ENGAGED/DISENGAGED> | AutoOdo: <autonomous_odometer> km | Disengagements: <count>"`.

---

### D. `AutonomousSystem`
Standalone hardware/software monitoring class for autonomous systems.

- **Data Members**:
  - `std::string system_id`: Unique hardware unit ID (e.g., `"SYS-01"`).
  - `int sensor_count`: Number of onboard sensors (LiDAR, Radar, Cameras).
  - `std::string system_status`: System operational status (e.g., `"OK"`, `"DEGRADED"`, `"OFFLINE"`).
  - `bool self_test_passed`: Operational health check status.

- **Methods**:
  - `AutonomousSystem(const std::string& sys_id, int sensors, const std::string& status = "OK")`
    - Throws `std::invalid_argument` if `sys_id` is empty or `sensors <= 0`. Initializes `self_test_passed = false`.
  - Getters & Setters: `get_system_id()`, `get_sensor_count()`, `get_system_status()`, `is_self_test_passed()`, `set_system_status(const std::string& status)`.
  - `bool perform_self_test()`:
    - If `sensor_count >= 4` and `system_status != "OFFLINE"`, sets `self_test_passed = true`, `system_status = "OK"`, and returns `true`.
    - Otherwise, sets `self_test_passed = false`, `system_status = "DEGRADED"`, and returns `false`.
  - `std::string get_telemetry_report() const`:
    - Returns string formatted as: `"System ID: <sys_id> | Sensors: <sensor_count> | Status: <system_status> | SelfTest: <PASS/FAIL>"`.

---

### E. `AutonomousRoboTaxi` (Multiple Inheritance: `ElectricVehicle` and `AutonomousSystem`)
Combines EV operation and Autonomous System diagnostics for commercial ride-hailing services.

- **Data Members**:
  - `int passenger_capacity`: Maximum passenger capacity.
  - `double fare_rate_per_km`: Fare charged per kilometer in USD.
  - `double total_fares_collected`: Cumulative revenue earned in USD.
  - `int completed_trips`: Total successful trips dispatched.

- **Methods**:
  - `AutonomousRoboTaxi(const std::string& vehicle_id, const std::string& model_name, double initial_odometer, double capacity_kwh, double current_battery_kwh, double rate_kwh_per_km, const std::string& sys_id, int sensors, int passenger_cap, double fare_rate)`
    - Throws `std::invalid_argument` if `passenger_cap <= 0` or `fare_rate <= 0.0`.
  - Getters: `get_passenger_capacity()`, `get_fare_rate()`, `get_total_fares()`, `get_completed_trips()`.
  - `double dispatch_trip(int passengers, double distance_km)`:
    - Throws `std::invalid_argument` if `passengers <= 0`, `passengers > passenger_capacity`, or `distance_km <= 0.0`.
    - Throws `std::runtime_error("Cannot dispatch trip: AutonomousSystem self-test failed")` if `!is_self_test_passed()`.
    - Drives the vehicle via `ElectricVehicle::drive(distance_km)`.
    - Calculates fare: `fare = distance_km * fare_rate_per_km`.
    - Updates `total_fares_collected += fare` and `completed_trips++`.
    - Returns `fare`.
  - `std::string get_full_report() const`:
    - Formats combined telemetry: `"<ElectricVehicle::get_status()> || <AutonomousSystem::get_telemetry_report()> || Taxi: [Cap: <passenger_capacity>, Fares: $<total_fares_collected>, Trips: <completed_trips>]"` (Fares formatted to 2 decimal places).

---

## 3. File Structure

```
cs2002-lab07-autonomous-fleet-hierarchy/
├── Dockerfile
├── manifest.json
├── README.md
├── Makefile
├── run
├── fleet_hierarchy.hpp         # Class definitions & headers
├── fleet_hierarchy.cpp         # Student implementation file (EDIT THIS)
├── public_test.cpp             # Public test suite
├── tests_private/
│   ├── test_multilevel.cpp     # Private tests for Multilevel Inheritance
│   └── test_multiple.cpp       # Private tests for Multiple Inheritance
└── reference/
    └── fleet_hierarchy.cpp     # Problem setter reference solution
```

---

## 4. Building and Testing

Run public tests locally:
```bash
./run
# or
make test-public
```

Clean build artifacts:
```bash
make clean
```
