/**
 * @file SafetySystem.h
 * @brief Sistema de seguridad y gestión de fallos para OVNI Medevac
 * @details Implementa redundancia, fail-safes y protocolos médicos/aeronáuticos
 */

#ifndef SAFETY_SYSTEM_H
#define SAFETY_SYSTEM_H

#include <cstdint>

/**
 * @enum SafetyLevel
 * @brief Niveles de alerta de seguridad
 */
enum class SafetyLevel {
    NOMINAL,       ///< Operación normal
    WARNING,       ///< Advertencia - monitorear
    CRITICAL,      ///< Crítico - acciones correctivas
    EMERGENCY,     ///< Emergencia - aterrizaje inmediato
    FAILSAFE       ///< Falla total - aterrizaje de emergencia
};

/**
 * @struct SafetyThresholds
 * @brief Umbrales de seguridad configurables
 */
struct SafetyThresholds {
    float maxRollAngle;        ///< Máximo ángulo roll permitido (grados)
    float maxPitchAngle;       ///< Máximo ángulo pitch permitido (grados)
    float maxVerticalSpeed;    ///< Máxima velocidad vertical (m/s)
    float minBatteryVoltage;   ///< Voltaje mínimo batería (V)
    float maxMotorTemp;        ///< Temperatura máxima motor (°C)
    float minSignalStrength;   ///< Señal mínima de control (%)
    float maxVibration;        ///< Vibración máxima permitida (m/s²)
};

/**
 * @class SafetySystem
 * @brief Sistema de seguridad para OVNI Medevac UAV
 */
class SafetySystem {
public:
    /**
     * @brief Constructor por defecto
     */
    SafetySystem();

    /**
     * @brief Inicializa el sistema de seguridad
     * @return true si la inicialización fue exitosa
     */
    bool initialize();

    /**
     * @brief Evalúa el estado de seguridad actual
     * @return Nivel de seguridad detectado
     */
    SafetyLevel evaluateSafetyStatus();

    /**
     * @brief Ejecuta acciones de fail-safe según el nivel de emergencia
     * @param level Nivel de seguridad detectado
     */
    void executeFailSafe(SafetyLevel level);

    /**
     * @brief Configura los umbrales de seguridad
     * @param thresholds Umbrales personalizados
     */
    void setThresholds(const SafetyThresholds& thresholds);

    /**
     * @brief Obtiene los umbrales actuales
     * @return Referencia constante a los umbrales
     */
    const SafetyThresholds& getThresholds() const;

    /**
     * @brief Verifica redundancia de sistemas críticos
     * @return true si hay redundancia adecuada
     */
    bool checkRedundancy();

    /**
     * @brief Obtiene el estado actual del sistema de seguridad
     * @return Nivel de seguridad actual
     */
    SafetyLevel getCurrentSafetyLevel() const;

private:
    bool checkAttitudeLimits();
    bool checkBatteryLevel();
    bool checkMotorStatus();
    bool checkSignalStrength();
    bool checkVibrationLevels();
    void logSafetyEvent(SafetyLevel level);
    void triggerEmergencyLanding();

    SafetyThresholds m_thresholds;
    SafetyLevel m_currentLevel;
    
    bool m_redundancyActive;
    bool m_emergencyTriggered;
    uint32_t m_lastSafetyCheck;
};

#endif // SAFETY_SYSTEM_H