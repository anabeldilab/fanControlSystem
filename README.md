# IoT-Enabled Fan Control System

## Overview
This repository contains the code for an innovative fan control system designed for energy efficiency in various environments. Utilizing IoT technology, it integrates a reversible motor with a speed regulator (ATV320), sensors for environmental monitoring, and cloud connectivity for data analysis and monitoring.

## Features
- **Real-Time Environmental Monitoring**: Utilizes temperature and humidity sensors.
- **Dynamic Fan Speed Control**: Adjusts fan speed based on ambient temperature and light price data.
- **Energy Efficiency**: Focuses on reducing energy consumption while maintaining comfort.
- **IoT Integration**: Leverages WiFi for data communication and supports cloud-based data handling.

## Hardware Requirements
- Reversible motor
- Speed regulator (ATV320)
- Wemos D1 (ESP32)
- Temperature and humidity sensors
- WiFi module

## Software Dependencies
To utilize this fan control system, you'll need the following libraries in your development environment:

- ESP8266WiFi: For WiFi connectivity with the ESP8266 module.
- ESP8266HTTPClient: To make HTTP requests using the ESP8266 module.
- WiFiClientSecure: For establishing secure WiFi client connections, necessary if making HTTPS requests.
- ArduinoJson: Used for parsing JSON responses, such as light price data.
- time.h: Standard C library for time and date-related functions.

These libraries are essential for the project's functionality and should be present in your development environment before uploading the code to the ESP32 device.

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/fan-control-system.git
   ``` 
2. Install the necessary libraries using Arduino IDE or manually place them in your project directory.
3. Configure WiFi settings in networkHandler.h.
4. Upload the code to your ESP32 device.

## Configuration
* Set the `ssid` and `password` in networkHandler.h to match your WiFi network.
* Adjust sensor reading intervals and thresholds as needed in the configuration files.

## Usage
After installation, the system will automatically start monitoring the environment and adjust the fan speed accordingly. Real-time data can be monitored through the cloud platform.


