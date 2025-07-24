# Touch_Air_Mouse
The Touch Air Mouse (TAM) is an innovative, lightweight device that lets users control the cursor with hand or finger movements in the air. Using motion sensors and touch input, it offers a simple, dynamic experience—ideal for gaming, presentations, and more.

# Main Component Assembly:
1. MPU6050 Sensor: Used to measure acceleration and angular rotation.
2. Pro Micro Controller (ATmega32U4): Processes data from the sensor and controls the mouse
movement.
3. TTP Touch Sensor: Allows the user to perform clicks or long presses (Tap = Left Click, Long
Press = Click and Hold).
4. Connectors and Breadboard: Organizes wiring and facilitates component connection.

# Wiring Connections:
MPU6050 Sensor:
- VCC: Power supply (usually 5V)
- GND: Ground
- SDA: Data line (connected to D2 on Pro Micro)
- SCL: Clock line (connected to D3 on Pro Micro)
TTP Touch Sensor:
- VCC: Connected to VCC on Pro Micro
- GND: Connected to GND on Pro Micro
- OUT: Data line (connected to D4 on Pro Micro)
Pro Micro (ATmega32U4) Pin Assignments:
1. VCC: Power supply
2. GND: Ground
3. D2: SDA line for MPU6050
4. D3: SCL line for MPU6050
5. D4: OUT line for TTP sensor
