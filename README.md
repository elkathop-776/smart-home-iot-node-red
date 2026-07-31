## IoT Smart Home Climate Monitoring & Automation Platform

An end-to-end IoT solution for real-time climate monitoring, automated data persistence, and threshold-driven alerts built with Arduino, Node-RED, SQLite, and MQTT.

## Project Overview
This project implements a modular, three-layer Smart Home IoT platform designed for real-time ambient climate monitoring and automated environmental control. The system captures high-precision temperature and humidity telemetry via an Arduino edge gateway, calculates real-time physiological Heat Index metrics in Node-RED, persists analytical data into an SQLite 3 database, and executes dual-protocol alerts (Serial + MQTT) during high-risk scenarios.

### Authors
* Anthopoulou Elpida-Kalliopi
* Argyriadou Anna

## Repository Structure

```text
IoT-Smart-Home-Platform/
├── arduino/
│   └── arduino_code.ino        # Arduino sketch for DHT22 sensor & LED actuation
├── node-red/
│   └── node_red_flow.json      # Exported Node-RED flow configuration
├── database/
│   └── iot_project.db          # Pre-configured SQLite database schema
├── docs/
│   ├── Report.pdf              # Comprehensive project report & architecture details
│   └── presentation.pdf        # Project presentation slides
└── README.md                   # Installation & operation instructions
```
## Installation and Operation Guide
1. **Hardware and Arduino Setup**
   * **Wiring:** Connect the *DHT22* sensor signal pin to *Pin 2* and the *alert LED* to *Pin 13*.
   * **Upload Code:** Open *arduino/arduino_code.ino* in the Arduino IDE and *upload* it to your board.
   * **Important:** *Close* the Arduino IDE *Serial Monitor* after uploading, as Node-RED requires exclusive serial access to the *COM port*.
     
2. **MQTT Broker Setup (Mosquitto)**
   Before launching Node-RED, the MQTT broker must be running locally to handle network alert signals:

    * **Download:** Install *Eclipse Mosquitto* from the official website.
    * **Execution:** *Run* the Mosquitto service (usually starts automatically) or open a *terminal* and type: *Bash mosquitto -v*
    * **Listener Configuration:** Ensure Mosquitto *allows* local connections on the default port *1883*.
      
3. **Node-RED Integration**
   * **Import Flow:** Open Node-RED, use the *Import function (Ctrl + I)*, and import *node-red/node_red_flow.json*.
   * **Palette Dependencies:** *Install* the following nodes via *Manage Palette*:
       * node-red-dashboard
       * node-red-node-sqlite
       * node-red-node-serialport
   * **Node Configurations:**
       * *Serial Node:* Select your Arduino's active COM port (e.g., COM3).
       * *MQTT Node:* Verify the server is set to 127.0.0.1:1883 (localhost).
       * *SQLite Node:* Update the file path to point to your local database file (database/iot_project.db).
   * **Deploy:** Click *Deploy* to activate the flow.
  
4. **System Operation & Usage**
   * **Database Initialization:** Upon first execution, click the *"Initialize DB"* inject node inside the Node-RED flow to create the required *sensor_data* and *hourly_stats tables.*
   * **Live Dashboard:** Open your browser and navigate to *http://localhost:1880/ui* to view live gauges, trend charts, and historical averages.
   * **Data Persistence:** Telemetry is *automatically* throttled and saved into SQLite every 1 minute.
   * **Hourly Aggregation:** Every 1 hour, the system *automatically* calculates average values over the preceding 60 minutes and updates the 24-hour historical log.
   * **Alert Mechanism:** If environmental parameters meet the alert condition *(Temperature > 30°C AND Humidity > 70%)*:
      * The local hardware LED *turns ON* instantly via direct Serial control.
      * An MQTT alert message ("alert") is *published* to the network topic home/alert.
      * The alert *automatically* deactivates once conditions fall below 30°C.
