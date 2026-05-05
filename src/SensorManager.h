/**
 * @file SensorManager.h
 * @brief Gestión de sensores IMU y sistemas de navegación
 */

#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <cstdint>
#include <cmath>

/**
 * @struct IMUData
 * @brief Datos del sensor IMU (acelerómetro, giroscopio, magnetómetro)
 */
struct IMUData {
    float accelX;  ///< Aceleración X (m/s²)
    float accelY;  ///< Aceleración Y (m/s²)
    float accelZ;  ///< Aceleración Z (m/s²)
    float gyroX;   ///< Velocidad angular X (rad/s)
    float gyroY;   ///< Velocidad angular Y (rad/s)
    float gyroZ;   ///< Velocidad angular Z (rad/s)
    float magX;    ///< Campo magnético X (μT)
    float magY;    ///< Campo magnético Y (μT)
    float magZ;    ///< Campo magnético Z (μT)
    uint32_t timestamp; ///< Timestamp en ms
};

/**
 * @struct Attitude
 * @brief Actitud del vehículo (ángulos de orientación)
 */
struct Attitude {
    float roll;    ///< Roll en grados
    float pitch;   ///< Pitch en grados
    float yaw;     ///< Yaw en grados
};

/**
 * @class SensorManager
 * @brief Gestor de sensores para el OVNI Medevac
 */
class SensorManager {
public:
    /**
     * @brief Constructor por defecto
     */
    SensorManager();

    /**
     * @brief Inicializa los sensores
     * @return true si la inicialización fue exitosa
     */
    bool initialize();

    /**
     * @brief Lee datos del IMU
     * @return Datos del IMU actualizados
     */
    IMUData readIMU();

    /**
     * @brief Obtiene la actitud calculada
     * @return Actitud actual (roll, pitch, yaw)
     */
    Attitude getAttitude();

    /**
     * @brief Actualiza el filtro de estimación de actitud
     * @param imuData Datos del IMU
     */
    void updateAttitudeFilter(const IMUData& imuData);

private:
    void calibrateSensors();
    void applyMadgwickFilter(const IMUData& data);
    void applyKalmanFilter(const IMUData& data);

    IMUData m_imuData;
    Attitude m_attitude;
    
    float m_madgwickBeta;    ///< Ganancia del filtro Madgwick
    float m_kalmanQAngle;    ///< Covarianza del ángulo
    float m_kalmanQBias;     ///< Covarianza del sesgo
    float m_kalmanRMeasure;  ///< Covarianza de la medida
    
    float m_kalmanAngle;     ///< Ángulo estimado (Kalman)
    float m_kalmanBias;      ///< Sesgo estimado (Kalman)
    float m_kalmanRate;      ///< Velocidad angular (Kalman)
    float m_kalmanP[2][2];   ///< Matriz de covarianza (Kalman)
};

#endif // SENSOR_MANAGER_H