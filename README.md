# OVNI Medevac

## Descripción del Proyecto
UAV/Platillo Volador (configuración discoidal) como Helicóptero Ambulancia Silencioso.

**Objetivo:** Desarrollar un dron tipo OVNI silencioso capaz de transportar 1 paciente + equipo médico, con operaciones en entornos urbanos, zonas de desastre y helipuertos existentes.

### Especificaciones Técnicas
- **Diseño:** Forma lenticular / discoidal (platillo volador)
- **Reducción de ruido:** Ducted fans + hélices toroidales + control de vibraciones
- **Plataforma:** ESP32 / STM32
- **Lenguaje:** C++ (C++17/20)
- **Sensores:** IMU (MPU9250 o superior)
- **Control:** Fly-by-wire con PID avanzados + Filtro Madgwick/Kalman
- **Grados de libertad:** 6DOF (Roll, Pitch, Yaw, Altitud, X, Y)
- **Actuadores:** 6-12 ducted fans distribuidos simétricamente

### Características de Seguridad
- Cumplimiento estándares médicos y aeronáuticos
- Alta redundancia y fail-safes
- Modo autónomo y manual

### Integración Futura
- LiDAR
- GPS RTK
- Telemetría médica (oxígeno, ECG, etc.)