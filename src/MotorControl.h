/**
 * @file MotorControl.h
 * @brief Control de motores ducted fans para OVNI Medevac
 * @details Gestión de 6-12 motores con control de RPM y distribución simétrica
 */

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <cstdint>
#include <array>

/**
 * @struct MotorConfig
 * @brief Configuración de un motor individual
 */
struct MotorConfig {
    uint8_t pinPWM;        ///< Pin de control PWM
    uint8_t pinDir;        ///< Pin de dirección
    uint8_t motorId;       ///< ID del motor (0-11)
    float maxRPM;          ///< RPM máximas operativas
    float minRPM;          ///< RPM mínimas operativas
    bool clockwise;        ///< TRUE si gira en sentido horario
};

/**
 * @class MotorControl
 * @brief Control de motores para OVNI Medevac
 */
class MotorControl {
public:
    /**
     * @brief Número máximo de motores soportados
     */
    static constexpr size_t MAX_MOTORS = 12;

    /**
     * @brief Constructor por defecto
     */
    MotorControl();

    /**
     * @brief Inicializa los motores
     * @return true si la inicialización fue exitosa
     */
    bool initialize();

    /**
     * @brief Establece la velocidad de un motor específico
     * @param motorId ID del motor (0-11)
     * @param rpm Velocidad deseada en RPM
     */
    void setMotorSpeed(uint8_t motorId, float rpm);

    /**
     * @brief Establece las velocidades de todos los motores
     * @param rpms Array con las RPM para cada motor
     */
    void setAllMotorSpeeds(const std::array<float, MAX_MOTORS>& rpms);

    /**
     * @brief Detiene todos los motores de forma segura
     */
    void emergencyStop();

    /**
     * @brief Obtiene la RPM actual de un motor
     * @param motorId ID del motor
     * @return RPM actual
     */
    float getMotorSpeed(uint8_t motorId) const;

    /**
     * @brief Configura el número de motores activos
     * @param count Número de motores (6-12)
     */
    void setMotorCount(uint8_t count);

    /**
     * @brief Aplica rampa suave de aceleración/desaceleración
     * @param targetRpms RPM objetivo
     * @param rampRate Tasa de cambio máxima (% por ciclo)
     */
    void applyRPMRampa(const std::array<float, MAX_MOTORS>& targetRpms, float rampRate = 0.05f);

private:
    void calculateThrustDistribution(std::array<float, MAX_MOTORS>& thrustCmd);
    float rpmToPWM(float rpm) const;
    float pwmToRPM(uint16_t pwm) const;

    std::array<MotorConfig, MAX_MOTORS> m_motors;
    std::array<float, MAX_MOTORS> m_currentRpms;
    std::array<float, MAX_MOTORS> m_targetRpms;
    
    uint8_t m_motorCount;
    uint32_t m_lastUpdate;
};

#endif // MOTOR_CONTROL_H