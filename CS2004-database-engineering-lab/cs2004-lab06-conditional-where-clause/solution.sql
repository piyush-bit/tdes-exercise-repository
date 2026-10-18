-- CS2004 Lab 06: Healthcare Patient Audit & Clinical Triage Filter
-- Target Database Engine: SQLite / ANSI SQL

-- ============================================================================
-- TASK 1: High Acuity Patients (Equal Operator '=')
-- Retrieve patient_id, first_name, last_name, triage_level, chief_complaint
-- for patients with triage_level equal to 1.
-- Order by patient_id ASC.
-- ============================================================================
-- TASK_1_START
-- TODO: Write SQL query for Task 1
SELECT NULL AS patient_id, NULL AS first_name, NULL AS last_name, NULL AS triage_level, NULL AS chief_complaint WHERE 0;
-- TASK_1_END


-- ============================================================================
-- TASK 2: Tachycardia Alert (Greater Than Operator '>')
-- Retrieve patient_id, heart_rate, systolic_bp for patients with heart_rate > 100.
-- Order by heart_rate DESC, patient_id ASC.
-- ============================================================================
-- TASK_2_START
-- TODO: Write SQL query for Task 2
SELECT NULL AS patient_id, NULL AS heart_rate, NULL AS systolic_bp WHERE 0;
-- TASK_2_END


-- ============================================================================
-- TASK 3: Hypoxia Risk Monitoring (Less Than Operator '<')
-- Retrieve patient_id, first_name, last_name, oxygen_stat for patients with oxygen_stat < 95.
-- Order by oxygen_stat ASC, patient_id ASC.
-- ============================================================================
-- TASK_3_START
-- TODO: Write SQL query for Task 3
SELECT NULL AS patient_id, NULL AS first_name, NULL AS last_name, NULL AS oxygen_stat WHERE 0;
-- TASK_3_END


-- ============================================================================
-- TASK 4: Senior Patient Audit (Greater Than or Equal To Operator '>=')
-- Retrieve patient_id, first_name, last_name, age for patients with age >= 65.
-- Order by age DESC, patient_id ASC.
-- ============================================================================
-- TASK_4_START
-- TODO: Write SQL query for Task 4
SELECT NULL AS patient_id, NULL AS first_name, NULL AS last_name, NULL AS age WHERE 0;
-- TASK_4_END


-- ============================================================================
-- TASK 5: Hypothermia Protocol (Less Than or Equal To Operator '<=')
-- Retrieve patient_id, body_temp, chief_complaint for patients with body_temp <= 35.5.
-- Order by body_temp ASC, patient_id ASC.
-- ============================================================================
-- TASK_5_START
-- TODO: Write SQL query for Task 5
SELECT NULL AS patient_id, NULL AS body_temp, NULL AS chief_complaint WHERE 0;
-- TASK_5_END


-- ============================================================================
-- TASK 6: Prehypertension Screening (Range Operator 'BETWEEN')
-- Retrieve patient_id, first_name, last_name, systolic_bp for patients with systolic_bp BETWEEN 120 AND 139.
-- Order by systolic_bp ASC, patient_id ASC.
-- ============================================================================
-- TASK_6_START
-- TODO: Write SQL query for Task 6
SELECT NULL AS patient_id, NULL AS first_name, NULL AS last_name, NULL AS systolic_bp WHERE 0;
-- TASK_6_END


-- ============================================================================
-- TASK 7: Emergency Transport Priority (Set Membership Operator 'IN')
-- Retrieve patient_id, first_name, last_name, arrival_code, triage_level for patients with arrival_code IN ('AMB', 'XFER').
-- Order by triage_level ASC, patient_id ASC.
-- ============================================================================
-- TASK_7_START
-- TODO: Write SQL query for Task 7
SELECT NULL AS patient_id, NULL AS first_name, NULL AS last_name, NULL AS arrival_code, NULL AS triage_level WHERE 0;
-- TASK_7_END


-- ============================================================================
-- TASK 8: Pediatric Vital Stability (Combined 'IN' and 'BETWEEN')
-- Retrieve patient_id, age, triage_level, heart_rate for patients with age IN (5, 12, 17) AND heart_rate BETWEEN 80 AND 110.
-- Order by patient_id ASC.
-- ============================================================================
-- TASK_8_START
-- TODO: Write SQL query for Task 8
SELECT NULL AS patient_id, NULL AS age, NULL AS triage_level, NULL AS heart_rate WHERE 0;
-- TASK_8_END
