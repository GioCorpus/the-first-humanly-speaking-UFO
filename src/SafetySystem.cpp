/**
 * @file SafetySystem.cpp
 * @brief Implementación del sistema de seguridad
 */

#include "SafetySystem.h"

SafetySystem::SafetySystem() 
    : m_currentLevel(SafetyLevel::NOMINAL)
    , m_redundancyActive(true)
    , m_emergencyTriggered(false)
    , m_lastSafetyCheck(0) {
    // Umbrales por defecto segura para operación médica
    m_thresholds = {
        30.0f,    // maxRollAngle
        30.0f,    // maxPitchAngle
        5.0f,     // maxVerticalSpeed
        14.0f,    // minBatteryVoltage (4S LiPo)
        60.0f,    // maxMotorTemp
        70.0f,    // minSignalStrength (%)
        2.0f      // maxVibration (m/s²)
    };
}

bool SafetySystem::initialize() {
    m_currentLevel = SafetyLevel::NOMINAL;
    m_emergencyTriggered = false;
    return true;
}

SafetyLevel SafetySystem::evaluateSafetyStatus() {
    int warnings = 0;
    int critical = 0;
    
    if (!checkAttitudeLimits()) critical++;
    if (!checkBatteryLevel()) warnings++;
    if (!checkMotorStatus()) critical++;
    if (!checkSignalStrength()) critical++;
    if (!checkVibrationLevels()) warnings++;
    
    if (critical > 0) {
        m_currentLevel = SafetyLevel::EMERGENCY;
    } else if (warnings > 1) {
        m_currentLevel = SafetyLevel::WARNING;
    } else if (warnings == 1) {
        m_currentLevel = SafetyLevel::NOMINAL;
    } else {
        m_currentLevel = SafetyLevel::NOMINAL;
    }
    
    m_lastSafetyCheck = 0;
    return m_currentLevel;
}

void SafetySystem::executeFailSafe(SafetyLevel level) {
    switch (level) {
        case SafetyLevel::WARNING:
            logSafetyEvent(level);
            break;
            
        case SafetyLevel::CRITICAL:
            logSafetyEvent(level);
            // Estabilizar y preparar para landing
            break;
            
        case SafetyLevel::EMERGENCY:
            logSafetyEvent(level);
            triggerEmergencyLanding();
            break;
            
        case SafetyLevel::FAILSAFE:
            logSafetyEvent(level);
            emergencyStop();
            break;
            
        default:
            break;
    }
}

void SafetySystem::setThresholds(const SafetyThresholds& thresholds) {
    m_thresholds = thresholds;
}

const SafetyThresholds& SafetySystem::getThresholds() const {
    return m_thresholds;
}

bool SafetySystem::checkRedundancy() {
    // Verificar doble IMU, doble barómetro, múltiples GPS
    return m_redundancyActive && !m_emergencyTriggered;
}

SafetyLevel SafetySystem::getCurrentSafetyLevel() const {
    return m_currentLevel;
}

bool SafetySystem::checkAttitudeLimits() {
    // En hardware: verificar desde sensor manager
    return true;
}

bool SafetySystem::checkBatteryLevel() {
    // En hardware: leer voltaje de batería vía ADC
    return true;
}

bool SafetySystem::checkMotorStatus() {
    // Verificar temperatura y corriente de motores
    return true;
}

bool SafetySystem::checkSignalStrength() {
    // Verificar calidad de señal RC/Telemetría
    return true;
}

bool SafetySystem::checkVibrationLevels() {
    // Analizar datos del acelerómetro para detección de vibración excesiva
    return true;
}

void SafetySystem::logSafetyEvent(SafetyLevel level) {
    // Log a EEPROM/SD para auditoría médica
}

void SafetySystem::triggerEmergencyLanding() {
    m_emergencyTriggered = true;
    // Activar modo de aterrizaje automático seguro
}

void SafetySystem::emergencyStop() {
    m_currentLevel = SafetyLevel::FAILSAFE;
    m_emergencyTriggered = true;
}