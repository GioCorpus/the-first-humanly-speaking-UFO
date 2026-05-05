/**
 * @file MotorControl.cpp
 * @brief Implementación del control de motores ducted fans
 */

#include "MotorControl.h"
#include <algorithm>

MotorControl::MotorControl() 
    : m_motorCount(12)
    , m_lastUpdate(0) {
    // Configuración por defecto para 12 motores en disposición simétrica
    for (size_t i = 0; i < MAX_MOTORS; ++i) {
        m_motors[i] = {
            static_cast<uint8_t>(2 + i),  // Pin PWM
            static_cast<uint8_t>(14 + i), // Pin DIR
            static_cast<uint8_t>(i),      // motorId
            8000.0f,                      // maxRPM
            1000.0f,                      // minRPM
            i % 2 == 0                    // clockwise par, counterclockwise impar
        };
        m_currentRpms[i] = 0.0f;
        m_targetRpms[i] = 0.0f;
    }
}

bool MotorControl::initialize() {
    // En hardware: inicializar pines PWM y dirección
    // analogWriteFrequency(25000); // 25kHz para reducir ruido audible
    return true;
}

void MotorControl::setMotorSpeed(uint8_t motorId, float rpm) {
    if (motorId >= m_motorCount) return;
    
    rpm = std::clamp(rpm, m_motors[motorId].minRPM, m_motors[motorId].maxRPM);
    m_targetRpms[motorId] = rpm;
}

void MotorControl::setAllMotorSpeeds(const std::array<float, MAX_MOTORS>& rpms) {
    for (size_t i = 0; i < MAX_MOTORS; ++i) {
        if (i < m_motorCount) {
            m_targetRpms[i] = std::clamp(rpms[i], 
                m_motors[i].minRPM, 
                m_motors[i].maxRPM);
        }
    }
}

void MotorControl::emergencyStop() {
    for (size_t i = 0; i < MAX_MOTORS; ++i) {
        m_currentRpms[i] = 0.0f;
        m_targetRpms[i] = 0.0f;
    }
}

float MotorControl::getMotorSpeed(uint8_t motorId) const {
    if (motorId >= m_motorCount) return 0.0f;
    return m_currentRpms[motorId];
}

void MotorControl::setMotorCount(uint8_t count) {
    if (count >= 6 && count <= 12) {
        m_motorCount = count;
    }
}

void MotorControl::applyRPMRampa(const std::array<float, MAX_MOTORS>& targetRpms, float rampRate) {
    for (size_t i = 0; i < m_motorCount; ++i) {
        float delta = targetRpms[i] - m_currentRpms[i];
        float maxDelta = std::abs(delta) * rampRate;
        
        if (delta > 0) {
            m_currentRpms[i] += maxDelta;
            if (m_currentRpms[i] > targetRpms[i]) {
                m_currentRpms[i] = targetRpms[i];
            }
        } else if (delta < 0) {
            m_currentRpms[i] -= maxDelta;
            if (m_currentRpms[i] < targetRpms[i]) {
                m_currentRpms[i] = targetRpms[i];
            }
        }
        
        // En hardware: escribir PWM al pin correspondiente
        // analogWrite(m_motors[i].pinPWM, rpmToPWM(m_currentRpms[i]));
    }
    m_lastUpdate = 0;
}

void MotorControl::calculateThrustDistribution(std::array<float, MAX_MOTORS>& thrustCmd) {
    // Distribución simétrica para control de actitud:
    // Cada motor contribuye proporcionalmente a roll, pitch y yaw
}

float MotorControl::rpmToPWM(float rpm) const {
    return (rpm / 8000.0f) * 255.0f;
}

float MotorControl::pwmToRPM(uint16_t pwm) const {
    return (pwm / 255.0f) * 8000.0f;
}