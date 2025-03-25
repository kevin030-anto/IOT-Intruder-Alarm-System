# 🚨 IOT-BASED ALARM SYSTEM 🚨

## 📖 Description
This project is an **IoT-Based Alarm System** designed to detect intruders using an **ESP32 microcontroller**, a **PIR Motion Sensor**, and a **Buzzer**. When the PIR sensor detects motion, the ESP32 triggers the buzzer and also sends a real-time alert to your smartphone via the **Blynk.io** platform.

---

## 🧰 Components Used

### 1. ESP32
- A powerful Wi-Fi and Bluetooth-enabled microcontroller ideal for IoT applications.
- Acts as the core controller to receive input from the PIR sensor and activate the buzzer.
- It also communicates with the Blynk cloud to send notifications.

### 2. PIR Sensor (Passive Infrared Sensor)
- Detects motion based on changes in infrared radiation.
- Outputs a HIGH signal to the ESP32 when motion is detected.
- Commonly used in security and automation systems.

### 3. Buzzer
- A simple electronic component that produces a sound when triggered.
- In this project, it sounds the alarm when an intruder is detected by the PIR sensor.

---

## 🖼️ Sample Project Screenshot
![Project Screenshot](https://github.com/kevin030-anto/IOT-Intruder-Alarm-System/blob/main/Images/Project%20Image.jpg)

---

## 🌐 What is Blynk.io?
[Blynk.io](https://blynk.io/) is a popular IoT platform that allows you to:
- Control and monitor IoT devices via mobile apps and web dashboards.
- Receive notifications, view sensor data, and trigger actions in real-time.
- Blynk offers cloud services, device management, and customizable UI for your IoT projects.

You can connect your project to the **Blynk app** available for both **Android** and **iOS** to monitor the system remotely.

---

### Features:
- Easily monitor and control your ESP32 device.
- Get real-time push notifications when an intruder is detected.
- Customize your mobile dashboard with widgets such as **Notification**, **LED Indicator**, **Button**, etc.
- Works seamlessly on both Android and iOS.

---

## 🛠️ How to Run the Project

### 🔌 Hardware Connections

| Component       | ESP32 Pin (GPIO) | ESP32 Pin (Board Label) |
|-----------------|------------------|-------------------------|
| PIR Sensor OUT  | GPIO 2           | D4                      |
| PIR Sensor VCC  | 3.3V             | 3V3                     |
| PIR Sensor GND  | GND              | GND                     |
| Buzzer (+)      | GPIO 4           | D2                      |
| Buzzer (-)      | GND              | GND                     |

**Notes:**
- Connect the PIR sensor output to **GPIO 2 (D4)**.
- Connect the Buzzer positive terminal to **GPIO 4 (D2)**.
- Make sure all GNDs are connected to ESP32's GND.

---

### Connecting to Blynk.io
- Open [Blynk.io](https://blynk.io/) in Browser
- Create a new account **(Free)**
- In side menu click **Developer Zone**
- In right Top Conter Click **New Template**
- Give the name of the porject
- Select Hardware to **ESP32**
- Select Connecting Type **Wifi**
- Description (Optional)
- In Firmware configuration you will get **Template ID** (Ex: #define BLYNK_TEMPLATE_ID "TMPL3S77NZMdJ")
- In side menu go to **Devices**
- In right Top Conter Click **New Devices**
- Choose **From Template**
- In Template choose select your project
- Give the name of the Devices (Editable)
- Now you will get Example: 
  |---------------------------------------------------------------------|
  |#define BLYNK_TEMPLATE_ID "TMPL3S77NZMdJ"                   |
  |#define BLYNK_TEMPLATE_NAME "IOT Intruder Alarm System"     |
  |#define BLYNK_AUTH_TOKEN "ZA2zuJX_Qn18kP0U0rNjxmOE3Yb_k6nm" |
  - (Replace the code in **IOT-Based Alarm System.ino** in line 4-6)
- Now click Edit Dashboard
  
 
---

### 💻 Software Steps

#### 1. Install Arduino IDE
Download and install the [Arduino IDE](https://www.arduino.cc/en/software) to program the ESP32.

#### 2. Install ESP32 Board Support
- In Arduino IDE, go to **File > Preferences**, and paste this URL in **Additional Board Manager URLs**:

---

#### Apps
|App | App Link |
|-----------------------|--------------------------------------|
|Blynk Android App Link: |[Download from Google Play Store](https://play.google.com/store/apps/details?id=cloud.blynk)| 
|Blynk IOS App Link: |[Download from Apple App Store](https://apps.apple.com/us/app/blynk-iot/id1551718627)|
