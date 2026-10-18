# CS2004 Lab 06: Healthcare Patient Audit & Clinical Triage Filter

## Overview

In emergency medical services and hospital clinical audit systems, rapid triage data filtering is vital for identifying critical patients, flagging abnormal vital signs, and prioritizing urgent medical intervention.

In this lab, you will author ANSI SQL queries utilizing conditional `WHERE` clauses to query the emergency department's `patient_triage` database table. You will apply comparison operators (`=`, `>`, `<`, `>=`, `<=`), range filtering (`BETWEEN`), and set membership (`IN`) to filter clinical records based on acuity levels, vital signs, age demographics, and transportation codes.

---

## Database Schema: `patient_triage`

All queries run against a single database table named `patient_triage` with the following structure:

| Column Name | Data Type | Description |
| :--- | :--- | :--- |
| `patient_id` | `INTEGER` | Unique primary key identifier for the patient. |
| `first_name` | `TEXT` | Patient's first name. |
| `last_name` | `TEXT` | Patient's last name. |
| `age` | `INTEGER` | Patient's age in years. |
| `gender` | `TEXT` | Patient's recorded gender (`'M'`, `'F'`). |
| `triage_level` | `INTEGER` | Emergency acuity level (1 = Immediate/Resuscitation, 2 = Emergent, 3 = Urgent, 4 = Less Urgent, 5 = Non-Urgent). |
| `chief_complaint` | `TEXT` | Primary medical complaint reported at check-in. |
| `heart_rate` | `INTEGER` | Resting heart rate in beats per minute (bpm). |
| `systolic_bp` | `INTEGER` | Systolic blood pressure in mmHg. |
| `oxygen_stat` | `INTEGER` | Blood oxygen saturation percentage ($\text{SpO}_2$). |
| `body_temp` | `REAL` | Body temperature in degrees Celsius (°C). |
| `arrival_code` | `TEXT` | Arrival method code (`'AMB'` = Ambulance, `'WALK'` = Walk-in, `'XFER'` = Transfer). |

---

## Problem Statement & Task Specifications

All queries must be authored inside `solution.sql` between the corresponding `-- TASK_N_START` and `-- TASK_N_END` markers.

### Group 1: Comparison Operator Filtering (`=`, `>`, `<`, `>=`, `<=`)

#### Task 1: High Acuity Patients (`=`)
Retrieve records for all patients with a `triage_level` equal to `1` (Resuscitation / Immediate attention).
- **Columns to Select**: `patient_id`, `first_name`, `last_name`, `triage_level`, `chief_complaint`
- **Condition**: `triage_level = 1`
- **Ordering**: Order results by `patient_id ASC`.

#### Task 2: Tachycardia Alert (`>`)
Filter for patients presenting with tachycardia, defined as a `heart_rate` strictly greater than `100` bpm.
- **Columns to Select**: `patient_id`, `heart_rate`, `systolic_bp`
- **Condition**: `heart_rate > 100`
- **Ordering**: Order results by `heart_rate DESC`, then `patient_id ASC`.

#### Task 3: Hypoxia Risk Monitoring (`<`)
Identify patients at risk of hypoxia, defined as blood oxygen saturation (`oxygen_stat`) strictly less than `95`%.
- **Columns to Select**: `patient_id`, `first_name`, `last_name`, `oxygen_stat`
- **Condition**: `oxygen_stat < 95`
- **Ordering**: Order results by `oxygen_stat ASC`, then `patient_id ASC`.

#### Task 4: Senior Patient Audit (`>=`)
Audit clinical records for senior patients whose `age` is greater than or equal to `65` years.
- **Columns to Select**: `patient_id`, `first_name`, `last_name`, `age`
- **Condition**: `age >= 65`
- **Ordering**: Order results by `age DESC`, then `patient_id ASC`.

#### Task 5: Hypothermia Protocol (`<=`)
Identify patients exhibiting hypothermia symptoms, defined as a `body_temp` less than or equal to `35.5`°C.
- **Columns to Select**: `patient_id`, `body_temp`, `chief_complaint`
- **Condition**: `body_temp <= 35.5`
- **Ordering**: Order results by `body_temp ASC`, then `patient_id ASC`.

---

### Group 2: Range & Set Filtering (`BETWEEN`, `IN`)

#### Task 6: Prehypertension Screening (`BETWEEN`)
Screen patients whose `systolic_bp` falls within the prehypertension blood pressure range between `120` and `139` mmHg (inclusive).
- **Columns to Select**: `patient_id`, `first_name`, `last_name`, `systolic_bp`
- **Condition**: `systolic_bp BETWEEN 120 AND 139`
- **Ordering**: Order results by `systolic_bp ASC`, then `patient_id ASC`.

#### Task 7: Emergency Transport Priority (`IN`)
Filter for urgent patient arrivals brought in via high-priority transportation methods: Ambulance (`'AMB'`) or Hospital Transfer (`'XFER'`).
- **Columns to Select**: `patient_id`, `first_name`, `last_name`, `arrival_code`, `triage_level`
- **Condition**: `arrival_code IN ('AMB', 'XFER')`
- **Ordering**: Order results by `triage_level ASC`, then `patient_id ASC`.

#### Task 8: Pediatric Vital Stability (`IN` & `BETWEEN`)
Audit pediatric or adolescent patients whose `age` is in the discrete set `(5, 12, 17)` AND whose `heart_rate` falls within the normal resting range of `80` to `110` bpm (inclusive).
- **Columns to Select**: `patient_id`, `age`, `triage_level`, `heart_rate`
- **Condition**: `age IN (5, 12, 17) AND heart_rate BETWEEN 80 AND 110`
- **Ordering**: Order results by `patient_id ASC`.

---

## Execution & Testing

### Running Public Tests
To test your SQL solution locally, run:
```bash
make test-public
# or using the executable wrapper script:
./run
```

### Cleaning Artifacts
To clean up temporary execution artifacts:
```bash
make clean
# or:
./run clean
```
