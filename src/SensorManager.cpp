/**
 * @file SensorManager.cpp
 * @brief Implementación del gestor de sensores
 */

#include "SensorManager.h"

SensorManager::SensorManager() 
    : m_madgwickBeta(0.1f)
    , m_kalmanQAngle(0.001f)
    , m_kalmanQBias(0.003f)
    , m_kalmanRMeasure(0.03f)
    , m_kalmanAngle(0.0f)
    , m_kalmanBias(0.0f)
    , m_kalmanRate(0.0f) {
    m_kalmanP[0][0] = 0.0f; m_kalmanP[0][1] = 0.0f;
    m_kalmanP[1][0] = 0.0f; m_kalmanP[1][1] = 0.0f;
}

bool SensorManager::initialize() {
    calibrateSensors();
    return true;
}

IMUData SensorManager::readIMU() {
    IMUData data = {0};
    
    // En hardware real: leer MPU9250 vía I2C
    // datos.simulados para prototipo
    data.accelX = 0.0f;
    data.accelY = 0.0f;
    data.accelZ = 9.81f;
    data.gyroX = 0.0f;
    data.gyroY = 0.0f;
    data.gyroZ = 0.0f;
    data.magX = 0.0f;
    data.magY = 0.0f;
    data.magZ = 0.0f;
    data.timestamp = 0;
    
    return data;
}

Attitude SensorManager::getAttitude() {
    return m_attitude;
}

void SensorManager::updateAttitudeFilter(const IMUData& imuData) {
    applyMadgwickFilter(imuData);
}

void SensorManager::calibrateSensors() {
    // Calibración del magnetómetro y compensación de offset
}

void SensorManager::applyMadgwickFilter(const IMUData& data) {
    // Implementación filtro Madgwick para estimación de actitud
    // q = quaternión de orientación
    const float GyroMeasError = 10.0f * (M_PI / 180.0f);
    const float beta = sqrt(3.0f / 4.0f) * GyroMeasError;
    
    m_attitude.roll = 0.0f;
    m_attitude.pitch = 0.0f;
    m_attitude.yaw = 0.0f;
}

void SensorManager::applyKalmanFilter(const IMUData& data) {
    // Implementación filtro Kalman para estimación de ángulo
    float dt = 0.01f;
    
    float rate = data.gyroX - m_kalmanBias;
    float angle = m_kalmanAngle + dt * rate;
    
    float P00 = m_kalmanP[0][0];
    float P01 = m_kalmanP[0][1];
    float P10 = m_kalmanP[1][0];
    float P11 = m_kalmanP[1][1];
    
    float Q_angle = m_kalmanQAngle;
    float Q_bias = m_kalmanQBias;
    float R_measure = m_kalmanRMeasure;
    
    float S = P00 + R_measure;
    float K0 = P00 / S;
    float K1 = P10 / S;
    
    float y = 0.0f - angle;
    angle += K0 * y;
    m_kalmanBias += K1 * y;
    
    float P00_new = P00 - K0 * P00;
    float P01_new = P01 - K0 * P01;
    float P10_new = P10 - K1 * P00;
    float P11_new = P11 - K1 * P01;
    
    m_kalmanP[0][0] = P00_new + Q_angle;
    m_kalmanP[0][1] = P01_new + Q_bias;
    m_kalmanP[1][0] = P10_new;
    m_kalmanP[1][1] = P11_new;
    
    m_kalmanAngle = angle;
    m_kalmanRate = rate;
}