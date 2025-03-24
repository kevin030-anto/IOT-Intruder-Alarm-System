#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL3dC3XMg6b" //Enter template ID (that links your code to a specific project)
#define BLYNK_TEMPLATE_NAME "Intruder Alarm System" // Project Name (Editable)
#define BLYNK_AUTH_TOKEN "" //Enter your Blynk Auth Token (the authentication token that connects your physical device)

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
const char* ssid = ""; //Enter Wifi Name
const char* password = ""; //Enter Wifi Password

// Define pins for PIR sensor and buzzer
const int PIRPin = 2;  // GPIO2 (D4) for PIR sensor
const int buzzerPin = 4;  // GPIO4 (D2) for buzzer

int pirValue = 0;
bool sensorEnabled = true;  // Variable to store sensor on/off state
bool alarmTriggered = false; // Variable to track if the alarm has been triggered
unsigned long lastMillis = 0;
unsigned long lastEventMillis = 0;
unsigned long updateInterval = 1000;   // Interval for updating values on Blynk cloud, min = 1 sec
unsigned long eventInterval = 60000;   // Interval for logging event/sending notification, 1 minute

BLYNK_WRITE(V2) {
  sensorEnabled = param.asInt(); // Assign incoming value from pin V2 to sensorEnabled variable

  if (sensorEnabled) {
    Serial.println("Sensor ON."); // Print on Serial Monitor
  } else {
    digitalWrite(buzzerPin, LOW);  // Ensure buzzer is OFF
    alarmTriggered = false;        // Ensure alarm is reset
    Serial.println("Sensor OFF."); // Print on Serial Monitor
  }
}

BLYNK_WRITE(V3) {
  int alarmVal = param.asInt(); // Assign incoming value from pin V3 to a variable
  Serial.print("Alarm value received: "); // Debug print
  Serial.println(alarmVal); // Debug print

  if (alarmVal == 0) {
    digitalWrite(buzzerPin, LOW);  // Turn OFF buzzer
    Serial.println("Alarm OFF.");  // Print on Serial Monitor
  } else {  // If Alarm ON button pressed on app/web dashboard
    digitalWrite(buzzerPin, HIGH); // Turn ON buzzer
    Serial.println("Alarm ON.");   // Print on Serial Monitor
  }
}

BLYNK_WRITE(V4) {
  int resetVal = param.asInt(); // Assign incoming value from pin V4 to a variable
  if (resetVal == 1) { // If reset button pressed
    alarmTriggered = false; // Reset the alarm triggered state
    digitalWrite(buzzerPin, LOW);  // Turn OFF buzzer
    Blynk.virtualWrite(V3, 0);  // Push the alarm status as OFF
    Serial.println("Reset button pressed. Alarm OFF.");  // Print on Serial Monitor
  }
}

void setup() {
  Serial.begin(115200);  // Open Serial Monitor at 115200 Baud rate
  pinMode(PIRPin, INPUT);  // Set the PIR sensor pin as Input
  pinMode(LED_BUILTIN, OUTPUT);  // Set the built-in LED as Output
  pinMode(buzzerPin, OUTPUT);     // Set buzzer pin as output
  digitalWrite(buzzerPin, LOW);   // Turn OFF buzzer at start

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);  // Connect to Wi-Fi and Blynk
}

void loop() {
  Blynk.run();  // Update the values on Blynk

  if (millis() - lastMillis >= updateInterval) {  // If 1 second has passed, update the values on Blynk cloud
    lastMillis = millis();  // Save the update time

    if (sensorEnabled) {
      pirValue = digitalRead(PIRPin);  // Continuously read the PIR sensor value
      Blynk.virtualWrite(V0, pirValue);  // Push value on V0

      if (pirValue == HIGH && !alarmTriggered) {  // If intruder detected and alarm not already triggered
        alarmTriggered = true; // Set alarm triggered state
        Blynk.virtualWrite(V1, "Warning! Intruder detected."); // Send a warning status string on V1
        digitalWrite(buzzerPin, HIGH); // Turn ON buzzer
        Blynk.virtualWrite(V3, 1);  // Push the alarm status on V3
        if (millis() - lastEventMillis >= eventInterval) {  // If 1 minute has passed since the last intruder notification
          lastEventMillis = millis();
          Blynk.logEvent("intruderalarm");  // Log a new event and send notification
        }
      } else if (pirValue == LOW && !alarmTriggered) {  // If no intruder detected and alarm not triggered
        Blynk.virtualWrite(V1, "No intruder.");  // Set the status as normal
        digitalWrite(buzzerPin, LOW);  // Turn OFF buzzer
        Blynk.virtualWrite(V3, 0);  // Push the alarm status on V3
      }
    } else {
      Blynk.virtualWrite(V1, "Sensor is OFF.");  // Indicate that the sensor is OFF
      digitalWrite(buzzerPin, LOW);  // Turn OFF buzzer
      Blynk.virtualWrite(V3, 0);  // Push the alarm status as OFF
    }
  }

  digitalWrite(LED_BUILTIN, pirValue);  // Turn ON/OFF the built-in LED according to the pirValue
  Serial.println(pirValue);  // Print the pirValue on Serial monitor
}