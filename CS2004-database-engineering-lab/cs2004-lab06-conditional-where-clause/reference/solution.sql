-- CS2004 Lab 06: Healthcare Patient Audit & Clinical Triage Filter - Reference Solution
-- Target Database Engine: SQLite / ANSI SQL

-- ============================================================================
-- TASK 1: High Acuity Patients (Equal Operator '=')
-- ============================================================================
-- TASK_1_START
SELECT patient_id, first_name, last_name, triage_level, chief_complaint
FROM patient_triage
WHERE triage_level = 1
ORDER BY patient_id ASC;
-- TASK_1_END


-- ============================================================================
-- TASK 2: Tachycardia Alert (Greater Than Operator '>')
-- ============================================================================
-- TASK_2_START
SELECT patient_id, heart_rate, systolic_bp
FROM patient_triage
WHERE heart_rate > 100
ORDER BY heart_rate DESC, patient_id ASC;
-- TASK_2_END


-- ============================================================================
-- TASK 3: Hypoxia Risk Monitoring (Less Than Operator '<')
-- ============================================================================
-- TASK_3_START
SELECT patient_id, first_name, last_name, oxygen_stat
FROM patient_triage
WHERE oxygen_stat < 95
ORDER BY oxygen_stat ASC, patient_id ASC;
-- TASK_3_END


-- ============================================================================
-- TASK 4: Senior Patient Audit (Greater Than or Equal To Operator '>=')
-- ============================================================================
-- TASK_4_START
SELECT patient_id, first_name, last_name, age
FROM patient_triage
WHERE age >= 65
ORDER BY age DESC, patient_id ASC;
-- TASK_4_END


-- ============================================================================
-- TASK 5: Hypothermia Protocol (Less Than or Equal To Operator '<=')
-- ============================================================================
-- TASK_5_START
SELECT patient_id, body_temp, chief_complaint
FROM patient_triage
WHERE body_temp <= 35.5
ORDER BY body_temp ASC, patient_id ASC;
-- TASK_5_END


-- ============================================================================
-- TASK 6: Prehypertension Screening (Range Operator 'BETWEEN')
-- ============================================================================
-- TASK_6_START
SELECT patient_id, first_name, last_name, systolic_bp
FROM patient_triage
WHERE systolic_bp BETWEEN 120 AND 139
ORDER BY systolic_bp ASC, patient_id ASC;
-- TASK_6_END


-- ============================================================================
-- TASK 7: Emergency Transport Priority (Set Membership Operator 'IN')
-- ============================================================================
-- TASK_7_START
SELECT patient_id, first_name, last_name, arrival_code, triage_level
FROM patient_triage
WHERE arrival_code IN ('AMB', 'XFER')
ORDER BY triage_level ASC, patient_id ASC;
-- TASK_7_END


-- ============================================================================
-- TASK 8: Pediatric Vital Stability (Combined 'IN' and 'BETWEEN')
-- ============================================================================
-- TASK_8_START
SELECT patient_id, age, triage_level, heart_rate
FROM patient_triage
WHERE age IN (5, 12, 17) AND heart_rate BETWEEN 80 AND 110
ORDER BY patient_id ASC;
-- TASK_8_END
