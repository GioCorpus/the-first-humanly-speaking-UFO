# Proyecto [OVNI Mexicali]

## Acerca del Proyecto

Este proyecto nació en **Mexicali, Baja California**, una región reconocida por su intensa y recurrente actividad OVNI y fenómenos aéreos no identificados. Inspirado en los múltiples avistamientos reportados en Mexicali y en la cercana **La Rumorosa** —considerada por muchos como la “capital mundial del fenómeno OVNI” en México—, el objetivo es diseñar y construir el **próximo platillo volador humano**.

Más allá de la especulación, este esfuerzo representa la unión entre la fascinación por lo desconocido y el rigor de la ingeniería moderna. Buscamos replicar, desde la ciencia y la tecnología actual, las características que durante décadas han sido atribuidas a estos objetos: despegue y aterrizaje vertical, maniobrabilidad omnidireccional, estabilidad en estacionario y formas discoidales.

## Visión

Desarrollar un vehículo discoidal (platillo volador) funcional, comenzando con prototipos a escala y avanzando hacia sistemas más complejos, utilizando tecnologías como:

- Propulsión eléctrica distribuida (ducted fans)
- Control avanzado por PID y algoritmos de estabilización
- Simulaciones CFD y dinámicas de vuelo
- Posible integración futura de sistemas electroaerodinámicos

## Origen de la Idea

La semilla de este proyecto surgió de la observación directa y los testimonios de la comunidad de Mexicali sobre luces extrañas, objetos luminosos y movimientos inusuales en el cielo del Valle de Mexicali y la sierra de La Rumorosa. Estos eventos, reportados durante años, despertaron una pregunta profunda:

**¿Qué pasaría si los humanos pudiéramos construir algo similar?**

Este repositorio documenta el camino desde esa inspiración paranormal hasta la ingeniería concreta.

## Estado Actual del Proyecto

- [ ] Diseño conceptual y modelado 3D
- [ ] Simulaciones de dinámica de vuelo
- [ ] Desarrollo del sistema de control (PID)
- [ ] Prototipo a escala inicial
- [ ] Pruebas de vuelo

## Tecnologías Utilizadas

- **Lenguajes**: Python, C++ (Arduino/ESP32)
- **Simulación**: NumPy, SciPy, Matplotlib (posiblemente Gazebo/ROS en etapas avanzadas)
- **Hardware**: Sensores IMU (MPU6050/MPU9250), controladoras de motores, baterías LiPo
- **Diseño**: Fusion 360 / SolidWorks
- **Control**: Controladores PID multieje + mixer para configuración discoidal

- **✅ README.md - Versión Profesional**

```markdown
# UAV OVNI Medevac - Platillo Volador Ambulancia Sigilosa

## Nombre del Proyecto
**OVNI Medevac**  
**UAV Tipo Platillo Volador como Helicóptero Ambulancia Silencioso**

---

## Descripción

**OVNI Medevac** es un proyecto de ingeniería aeroespacial que busca desarrollar un **UAV (Vehículo Aéreo No Tripulado) de configuración discoidal** (forma de platillo volador) destinado a operaciones de **evacuación médica (Medevac)**.

El objetivo principal es crear una plataforma mucho más silenciosa que los helicópteros tradicionales, capaz de realizar despegues y aterrizajes verticales (VTOL) en espacios reducidos, incluyendo helipuertos existentes, y operar de forma sigilosa en entornos urbanos, zonas de desastre y áreas de difícil acceso.

### Aplicaciones principales
- Atención prehospitalaria y traslado de pacientes críticos en México
- Operaciones en ciudades densamente pobladas y zonas montañosas
- Compatibilidad con helipuertos hospitalarios existentes, incluyendo el **Hospital para Niños de Seattle (Seattle Children's Hospital)** en Estados Unidos

---

## Origen del Proyecto

Inspirado en la alta actividad OVNI reportada históricamente en **Mexicali, Baja California** (especialmente en La Rumorosa), este proyecto transforma la observación de fenómenos aéreos no identificados en una propuesta tecnológica concreta: replicar las ventajas aparentes de los objetos discoidales (estabilidad, maniobrabilidad omnidireccional y bajo perfil acústico) mediante ingeniería moderna.

---

## Objetivos

### Objetivo General
Desarrollar un UAV discoidal de mediano porte capaz de transportar **1 paciente + equipo médico** de forma rápida, segura y significativamente más silenciosa que un helicóptero convencional.

### Objetivos Específicos
- Reducir el nivel de ruido por debajo de los 65-70 dB a 50 metros (meta ambiciosa)
- Operar en helipuertos existentes sin modificaciones mayores
- Cumplir con estándares de aviación civil en México (AFAC) y Estados Unidos (FAA) en categoría experimental
- Lograr autonomía suficiente para traslados urbanos y semi-urbanos
- Garantizar alta estabilidad en hover y vuelo estacionario

---

## Características Clave

- **Configuración aerodinámica**: Diseño lenticular / discoidal
- **Propulsión**: Sistema distribuido de **ducted fans** (ventiladores en conducto) con hélices de baja velocidad y diseño toroidal
- **Control de vuelo**: Sistema fly-by-wire con múltiples controladores PID y filtros avanzados
- **Sigilo acústico**: Reducción activa y pasiva de ruido + control preciso de vibraciones
- **Carga útil**: Mínimo 150-250 kg (paciente + camilla + equipo médico + paramédico)
- **Autonomía**: En desarrollo (meta inicial: 30-60 minutos)
- **Operación**: Tripulado remotamente y modo autónomo progresivo

---

## Tecnologías Principales

- **Hardware**: ESP32 / STM32, MPU9250 / ICM-20948, sensores LiDAR y ultrasonido
- **Software**: C++, Python, controladores PID avanzados, filtro Madgwick/Kalman
- **Diseño**: Fusion 360 / SolidWorks + simulaciones CFD
- **Propulsión**: Ducted fans eléctricos de alta eficiencia
- **Comunicaciones**: Telemetría de largo alcance + video en tiempo real

---

## Estado Actual del Proyecto

- [x] Conceptualización y justificación
- [x] Diseño inicial del controlador de vuelo
- [ ] Modelado 3D completo del aireframe
- [ ] Simulaciones aerodinámicas (CFD)
- [ ] Prototipo a escala reducida (pruebas de hover)
- [ ] Prototipo de tamaño funcional (150+ kg)

---

## Estructura del Repositorio

```
/OVNI-Medevac
├── /src                # Código del controlador de vuelo (C++)
├── /hardware           # Esquemas electrónicos y lista de materiales
├── /models             # Archivos CAD y diseños 3D
├── /simulation         # Simulaciones físicas y CFD
├── /docs               # Documentación técnica y regulatoria
├── /tests              # Resultados de pruebas
└── README.md
```

---

## Desafíos Técnicos Principales

1. **Reducción extrema de ruido** (principal reto)
2. **Estabilidad de plataforma discoidal**
3. **Eficiencia energética y autonomía**
4. **Certificación regulatoria** (AFAC México y FAA)
5. **Seguridad crítica** para transporte de pacientes

---

## Próximos Pasos

1. Completar prototipo a escala 1:4 con 8 ducted fans
2. Realizar pruebas acústicas comparativas
3. Desarrollar sistema de camilla médica y monitoreo vital
4. Contacto con instituciones médicas (México y Seattle Children's)
5. Solicitud de permisos experimentales ante AFAC

---

## Inspiración y Visión

Este proyecto representa la convergencia entre la fascinación por los fenómenos aéreos no identificados y la necesidad real de mejorar los servicios de emergencia médica. Buscamos crear la **próxima generación de ambulancias aéreas**: más silenciosas, accesibles y eficientes.

**"Inspirados en lo que se observa en el cielo de Mexicali, construimos lo que la medicina necesita."**

---

**Proyecto en desarrollo activo**  
**Ubicación principal**: México  
**Contacto**: [Agregar tu información]

## Estructura del Repositorio
