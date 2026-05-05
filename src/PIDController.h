/**
 * @file PIDController.h
 * @brief Controlador PID avanzado para control de vuelo
 */

#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <cstdint>

/**
 * @struct PIDConfig
 * @brief Configuración del controlador PID
 */
struct PIDConfig {
    float kp;          ///< Ganancia proporcional
    float ki;          ///< Ganancia integral
    float kd;          ///< Ganancia derivativa
    float windupMax;   ///< Límite anti-windup
    float outputMin;   ///< Límite inferior de salida
    float outputMax;   ///< Límite superior de salida
    float dt;          ///< Período de muestreo en segundos
};

/**
 * @class PIDController
 * @brief Controlador PID con filtrado y límites de saturación
 */
class PIDController {
public:
    /**
     * @brief Constructor con configuración
     * @param config Configuración del PID
     */
    explicit PIDController(const PIDConfig& config);

    /**
     * @brief Constructor por defecto
     */
    PIDController();

    /**
     * @brief Reinicia el controlador
     */
    void reset();

    /**
     * @brief Calcula la salida del PID
     * @param setpoint Valor deseado
     * @param input Valor actual
     * @return Salida del controlador
     */
    float compute(float setpoint, float input);

    /**
     * @brief Establece la configuración del PID
     * @param config Nueva configuración
     */
    void setConfig(const PIDConfig& config);

    /**
     * @brief Establece el período de muestreo
     * @param dt Período en segundos
     */
    void setDt(float dt);

private:
    PIDConfig m_config;
    
    float m_integral;
    float m_previousError;
    float m_previousInput;
    float m_derivativeFilter;
    
    uint32_t m_lastComputeTime;
};

#endif // PID_CONTROLLER_H