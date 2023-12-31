# 🏠 Home Automation IoT Project

The Smart Home IoT Project is designed to manage various home devices remotely using Blynk and Arduino, allowing control of temperature, water management, and status updates through a Discord channel.

## 🔧 Setup

### 🔑 Requirements

- Arduino board (ESP32/ESP8266)
- Blynk Template ID: `**********`
- Blynk Device Name: `*************`
- Blynk Auth Token: `***************`

### ⚙️ Configuration

1. Connect the Arduino board and upload the provided `.ino` file.
2. Replace placeholders in the code with your specific details:
   - Blynk Template ID
   - Blynk Device Name
   - Blynk Auth Token

## 🚀 Usage

1. Power on the Arduino board after setup.
2. The system controls various home devices and sends status updates to a Discord channel.
3. Use the Blynk app to control devices remotely.
4. Check the Discord channel for real-time updates on temperature and water volume.

## 📚 Code Overview

The code consists of modules for temperature control, water tank management, and Blynk communication.

### Modules
- `main.h`: Defines pin mappings and Blynk virtual pins.
- `serial_tank.h/cpp`: Manages water tank valves and volume readings.
- `temperature_system.h/cpp`: Controls temperature sensors, cooler, and heater.

## 🛠️ Features

- Temperature control using a cooler and heater (`COOLER_V_PIN` and `HEATER_V_PIN`).
- Water management with inlet and outlet valve control (`INLET_V_PIN` and `OUTLET_V_PIN`).
- Real-time updates on Blynk app gauges for temperature and water volume.

## 🔌 Circuit

- Connect sensors and devices based on the pin configurations mentioned in `main.h`.
- Ensure proper grounding and power connections for each device.

## 👥 Contributing

Contributions to enhance or extend the functionality of this project are welcomed! Fork this repository, make changes, and create pull requests.

## 📄 License

This project is licensed under the [MIT License](LICENSE.md).
