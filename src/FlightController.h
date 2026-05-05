/**
 * @file FlightController.h
 * @brief Sistema de control de vuelo para OVNI Medevac
 * @details Implementa control de 6 grados de libertad con PID avanzados
 */

#ifndef FLIGHT_CONTROLLER_H
#define FLIGHT_CONTROLLER_H

#include "PIDController.h"
#include "SensorManager.h"
#include "MotorControl.h"
#include "SafetySystem.h"

/**
 * @struct VehicleState
 * @brief Estado actual del vehículo
 */
struct VehicleState {
    float roll;          ///< Ángulo de roll en grados
    float pitch;         ///< Ángulo de pitch en grados  
    float yaw;           ///< Ángulo de yaw en grados
    float altitude;      ///< Altitud en metros
    float positionX;     ///< Posición X en metros
    float positionY;     ///< Posición Y en metros
    float velocityX;     ///< Velocidad X en m/s
    float velocityY;     ///< Velocidad Y en m/s
    float verticalSpeed; ///< Velocidad vertical en m/s
};

/**
 * @enum FlightMode
 * @brief Modos de operación del vehículo
 */
enum class FlightMode {
    MANUAL,        ///< Control manual
    STABILIZE,     ///< Estabilización activada
    ALT_HOLD,      ///< Mantenimiento de altura
    LOITER,        ///< Mantener posición
    AUTO_MISSION,  ///< Misión automática
    EMERGENCY_LAND ///< Aterrizaje de emergencia
};

/**
 * @class FlightController
 * @brief Controlador principal de vuelo para OVNI Medevac
 */
class FlightController {
public:
    /**
     * @brief Constructor por defecto
     */
    FlightController();

    /**
     * @brief Inicializa el controlador de vuelo
     * @return true si la inicialización fue exitosa
     */
    bool initialize();

    /**
     * @brief Bucle de actualización principal
     */
    void update();

    /**
     * @brief Establece el modo de vuelo
     * @param mode Nuevo modo de vuelo
     */
    void setFlightMode(FlightMode mode);

    /**
     * @brief Obtiene el estado actual del vehículo
     * @return Referencia constante al estado
     */
    const VehicleState& getState() const;

    /**
     * @brief Retardo para mantener frecuencia del loop
     * @param ms Milisegundos de retardo
     */
    void loopDelay(uint32_t ms);

private:
    void readSensors();
    void updateAttitudeControl();
    void updatePositionControl();
    void checkSafetyLimits();
    void smoothMotorOutputs();

    SensorManager m_sensorManager;
    MotorControl m_motorControl;
    SafetySystem m_safetySystem;
    
    VehicleState m_vehicleState;
    VehicleState m_targetState;
    
    PIDController m_pidRoll;
    PIDController m_pidPitch;
    PIDController m_pidYaw;
    PIDController m_pidAltitude;
    PIDController m_pidPosXY;
    
    FlightMode m_flightMode;
    uint32_t m_lastUpdateTime;
};

#endif // FLIGHT_CONTROLLER_H