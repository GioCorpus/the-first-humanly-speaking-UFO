/**
 * @file main.cpp
 * @brief Sistema de control principal para OVNI Medevac UAV
 * @author Ingeniero Aeroespacial Senior
 * @date 2026
 */

#include "FlightController.h"
#include "MotorControl.h"
#include "SensorManager.h"
#include "SafetySystem.h"

/**
 * @brief Configuración principal del UAV OVNI Medevac
 */
int main() {
    // Inicializar sistema de vuelo
    FlightController controller;
    controller.initialize();
    
    // Bucle principal de control
    while (true) {
        controller.update();
        controller.loopDelay(10); // 10ms loop time
    }
    
    return 0;
}