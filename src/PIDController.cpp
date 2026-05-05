/**
 * @file PIDController.cpp
 * @brief Implementación del controlador PID avanzado
 */

#include "PIDController.h"

PIDController::PIDController(const PIDConfig& config) 
    : m_config(config)
    , m_integral(0.0f)
    , m_previousError(0.0f)
    , m_previousInput(0.0f)
    , m_derivativeFilter(0.0f)
    , m_lastComputeTime(0) {
}

PIDController::PIDController() 
    : m_integral(0.0f)
    , m_previousError(0.0f)
    , m_previousInput(0.0f)
    , m_derivativeFilter(0.0f)
    , m_lastComputeTime(0) {
    m_config = {1.0f, 0.0f, 0.0f, 100.0f, -100.0f, 100.0f, 0.01f};
}

void PIDController::reset() {
    m_integral = 0.0f;
    m_previousError = 0.0f;
    m_previousInput = 0.0f;
    m_derivativeFilter = 0.0f;
}

float PIDController::compute(float setpoint, float input) {
    float error = setpoint - input;
    
    m_integral += m_config.ki * error * m_config.dt;
    
    // Anti-windup
    if (m_integral > m_config.windupMax) {
        m_integral = m_config.windupMax;
    } else if (m_integral < -m_config.windupMax) {
        m_integral = -m_config.windupMax;
    }
    
    float derivative = (error - m_previousError) / m_config.dt;
    
    // Filtro derivativo (low-pass)
    m_derivativeFilter = 0.7f * derivative + 0.3f * m_derivativeFilter;
    
    float output = m_config.kp * error + m_integral + m_config.kd * m_derivativeFilter;
    
    // Limitar salida
    if (output > m_config.outputMax) {
        output = m_config.outputMax;
    } else if (output < m_config.outputMin) {
        output = m_config.outputMin;
    }
    
    m_previousError = error;
    m_previousInput = input;
    
    return output;
}

void PIDController::setConfig(const PIDConfig& config) {
    m_config = config;
}

void PIDController::setDt(float dt) {
    m_config.dt = dt;
}