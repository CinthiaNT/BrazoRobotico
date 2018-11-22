
# Brazo Robotico
## Software
- Arduino IDE
- Ubuntu 16.04
- NetBeans IDE
## Librerias
- PanamaHitek
- EEPROM
- Stepper
- Servo

## Proposito del proyecto
Desarrollar paso a paso una aplicacion para controlar y programar un Brazo Robot, simulando las funciones básicas de un robot industrial.

## Funciones del proyecto
 **Programar:** Registrar las posiciones de los brazos en tres dimensiones (cada registro es un "paso", un programa consiste en una serie de pasos).
 
 **Ejecutar:** Realice en secuencia las posiciones registradas en el "Programa". El robot ejecutará el programa hasta que se use el comando "ABORTAR".

## Descripcion del proyecto
Se controla un robot con 5 DOF(Grados de libertad).
El robot se controla desde una aplicacion en modo "remoto" por medio de una aplicacion en java a través del puerto serial.
El usuario conocera el estado del brazo por medio de LED'S de distintos colores:
  - LED ROJO 1: Pinza
  - LED AMARILLO: Codo
  - LED VERDE: Muñeca
  - LED ROJO 2: Cintura

En caso de existir un fallo de energia, al restablecerse la corriente el brazo robotico continua con la secuencia.(Esto sucede aun con
la aplicacion cerrada).

## Materiales

## Integrantes del equipo
González Alcaraz Hernán Arturo
Nava Torres Juana Cinthia Lizbeth
Padilla Guerrero Paul Adrian 
