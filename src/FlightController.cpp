/**
 * @file FlightController.cpp
 * @brief Implementación del controlador de vuelo
 */

#include "FlightController.h"

FlightController::FlightController() 
    : m_flightMode(FlightMode::STABILIZE)
    , m_lastUpdateTime(0) {
    m_pidRoll.setConfig({4.5f, 0.0f, 0.1f, 100.0f, -200.0f, 200.0f, 0.01f});
    m_pidPitch.setConfig({4.5f, 0.0f, 0.1f, 100.0f, -200.0f, 200.0f, 0.01f});
    m_pidYaw.setConfig({3.0f, 0.0f, 0.05f, 100.0f, -100.0f, 100.0f, 0.01f});
    m_pidAltitude.setConfig({2.0f, 0.5f, 0.2f, 100.0f, -150.0f, 150.0f, 0.01f});
    m_pidPosXY.setConfig({1.5f, 0.2f, 0.3f, 50.0f, -100.0f, 100.0f, 0.01f});
}

bool FlightController::initialize() {
    if (!m_sensorManager.initialize()) {
        return false;
    }
    if (!m_motorControl.initialize()) {
        return false;
    }
    if (!m_safetySystem.initialize()) {
        return false;
    }
    
    m_motorControl.setMotorCount(12);
    m_motorControl.emergencyStop();
    
    m_lastUpdateTime = 0;
    return true;
}

void FlightController::update() {
    readSensors();
    
    checkSafetyLimits();
    
    if (m_safetySystem.getCurrentSafetyLevel() <= SafetyLevel::WARNING) {
        updateAttitudeControl();
        updatePositionControl();
    }
    
    smoothMotorOutputs();
}

void FlightController::setFlightMode(FlightMode mode) {
    m_flightMode = mode;
}

const VehicleState& FlightController::getState() const {
    return m_vehicleState;
}

void FlightController::loopDelay(uint32_t ms) {
    // Simulación de retardo - en hardware real usar delay ms
}

void FlightController::readSensors() {
    IMUData imu = m_sensorManager.readIMU();
    Attitude attitude = m_sensorManager.getAttitude();
    
    m_vehicleState.roll = attitude.roll;
    m_vehicleState.pitch = attitude.pitch;
    m_vehicleState.yaw = attitude.yaw;
}

void FlightController::updateAttitudeControl() {
    float rollOutput = m_pidRoll.compute(0.0f, m_vehicleState.roll);
    float pitchOutput = m_pidPitch.compute(0.0f, m_vehicleState.pitch);
    float yawOutput = m_pidYaw.compute(0.0f, m_vehicleState.yaw);
    
    std::array<float, 12> motorRpms = {0.0f};
    
    for (int i = 0; i < 12; ++i) {
        motorRpms[i] = 4000.0f + rollOutput * 0.1f + pitchOutput * 0.1f + yawOutput * 0.05f;
    }
    
    m_motorControl.applyRPMRampa(motorRpms, 0.02f);
}

void FlightController::updatePositionControl() {
    float altOutput = m_pidAltitude.compute(0.0f, m_vehicleState.altitude);
    
    for (int i = 0; i < 12; ++i) {
        float& rpm = m_vehicleState.altitude; // Placeholder
    }
}

void FlightController::checkSafetyLimits() {
    m_safetySystem.evaluateSafetyStatus();
}

void FlightController::smoothMotorOutputs() {
    // Los motores ya aplican rampa suave en applyRPMRampa
    m_lastUpdateTime = 0;
}