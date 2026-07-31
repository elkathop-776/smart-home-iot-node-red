## IoT Smart Home Climate Monitoring & Automation Platform

This project implements an end-to-end Smart Home IoT project for real-time climate monitoring, automated data persistence, and threshold-driven alerts. Built on a modular three-layer architecture, the system combines hardware sensing via Arduino with a Node-RED orchestration server, SQLite local storage, and a dual-protocol feedback system (Serial & MQTT).

## Key Features
* **Edge Telemetry:** Captures ambient temperature and humidity using an Arduino edge node with a DHT22 sensor.
* **Real-Time Visualization:** Interactive Node-RED Dashboard featuring radial gauges, historical trend charts, and real-time Heat Index (apparent temperature) calculations.
* **Data Persistence & Analytics:** Logs granular telemetry into an SQLite 3 database at 1-minute intervals and automatically computes 24-hour historical hourly averages (`AVG()`).
* **Hybrid Alert Automation:** Dual-protocol control loop triggering instant local hardware responses (Serial LED) and asynchronous network notifications (`home/alert` via Mosquitto MQTT) when environmental parameters exceed safety thresholds (`Temp > 30°C` & `Humidity > 70%`).

## Tech Stack
* **Hardware / Perception:** Arduino Uno, DHT22 Sensor, LED Actuator
* **Middleware & Logic:** Node-RED (JavaScript Function Nodes), Serial (UART)
* **Messaging:** MQTT (Mosquitto Broker)
* **Storage & Visuals:** SQLite 3, Node-RED Dashboard
