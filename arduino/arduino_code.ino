#include <DHT.h>
/* OPTIONAL NATIVE MQTT & WIFI IMPLEMENTATION (NON-ACTIVE)
 * The following code demonstrates the architecture for direct WiFi/MQTT 
 * communication using the PubSubClient library. 
 * * Note: This implementation was bypassed due to hardware limitations
 * NATIVE MQTT & WIFI IMPLEMENTATION (PROTOTYPE)
#include <WiFi.h>
#include <PubSubClient.h>

// Network & Broker Credentials
const char* ssid = "KorniliosXoirinos";
const char* password = "+DyoXeria3Podia@7-q";
const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
}

// Requirement D: Handle incoming 'alert' and 'stopalert' signals from Node-RED
void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) message += (char)payload[i];

  if (String(topic) == "home/alert") {
    if (message == "alert") digitalWrite(LED_PIN, HIGH);     // Trigger LED ON
    else if (message == "stopalert") digitalWrite(LED_PIN, LOW); // Trigger LED OFF
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("SmartHomeClient")) {
      client.subscribe("home/alert"); // Subscribe to the alert topic
    } else {
      delay(5000);
    }
  }
}

// Requirement A & B: Publish raw data to dedicated MQTT topics
void publishData(float t, float h) {
  if (client.connected()) {
    client.publish("home/temp", String(t).c_str()); 
    client.publish("home/hum", String(h).c_str());  
  }
}
*/
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const int alertLedPin = 13;
unsigned long lastExecutionMillis = 0;
const unsigned long interval = 5000; 

void setup() {
  Serial.begin(9600); 
  dht.begin();
  pinMode(alertLedPin, OUTPUT);
}

void loop() {
  // RECEIVE COMMANDS FROM NODE-RED
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n'); 
    command.trim(); 

    if (command == "LED_ON") {
      digitalWrite(alertLedPin, HIGH); 
      Serial.println("ACK: ALERT_ACTIVE");
    } 
    else if (command == "LED_OFF") {
      digitalWrite(alertLedPin, LOW);
      Serial.println("ACK: ALERT_STOPPED");
    }
  }

  // SEND TELEMETRY
  unsigned long currentMillis = millis();
  if (currentMillis - lastExecutionMillis >= interval) {
    lastExecutionMillis = currentMillis;
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (!isnan(h) && !isnan(t)) {
      Serial.print("Temp: "); Serial.print(t); 
      Serial.print(" Hum: "); Serial.println(h); 
    }
  }
}