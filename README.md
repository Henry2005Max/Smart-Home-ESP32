# ESP32 Smart Home Voice-Controlled Automation System

![Project Status](https://img.shields.io/badge/Status-Complete-success)
![Platform](https://img.shields.io/badge/Platform-ESP32-blue)
![Voice Assistant](https://img.shields.io/badge/Voice-Siri-purple)
![IoT Platform](https://img.shields.io/badge/IoT-Blynk-green)

> A comprehensive smart home automation system featuring voice control, environmental monitoring, and intelligent automation using ESP32 microcontroller, Blynk IoT Cloud, and Apple Siri integration.

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [System Architecture](#system-architecture)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Pin Configuration](#pin-configuration)
- [Installation & Setup](#installation--setup)
- [Phase-wise Development](#phase-wise-development)
- [Voice Commands](#voice-commands)
- [API Integration](#api-integration)
- [Usage Guide](#usage-guide)
- [Troubleshooting](#troubleshooting)
- [Future Enhancements](#future-enhancements)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## 🎯 Overview

This final year project implements a fully automated smart home system that combines environmental sensing, automated responses, mobile app control, and voice command capabilities through Apple Siri. The system controls room lighting, door mechanisms, and window operations while monitoring temperature, humidity, and rain conditions in real-time.

**Key Highlights:**

-  Real-time environmental monitoring (Temperature, Humidity, Rain)
-  Intelligent automatic lighting based on ambient conditions
-  Automated door and window control with manual override
-  Remote control via Blynk mobile app
-  Voice control integration with Apple Siri
-  Cloud connectivity for anywhere access
-  Hybrid automation with manual override capabilities

##  Features

### Phase 1: Core Automation & Sensing

- ✅ **Environmental Monitoring**: DHT11 sensor for temperature and humidity tracking
- ✅ **Secure Access Control**: RFID RC522 module for contactless door authentication
- ✅ **Visual Display**: OLED screen for real-time data visualization
- ✅ **Weather Station**: Fully functional mini weather station with rain detection
- ✅ **Automated Cooling**: Relay Channel 1 controls a fan based on system logic
- ✅ **Rain Response**: Automatic window closing when rain is detected
- ✅ **Smart Security**: SG90 Servo motor (0°-90°) for automated door/gate mechanism
- ✅ **Intelligent Lighting**: LDR-based automatic room light control (Relay Channel 2)

### Phase 2: Cloud Integration & Remote Control

- ✅ **IoT Connectivity**: Real-time communication with Blynk IoT Cloud via WiFi
- ✅ **Remote Lighting**: Mobile app switch for room lights with LDR parallel operation
- ✅ **Hybrid Window System**: Automatic rain closure with manual sunny-day override
- ✅ **Manual Door Access**: 360° continuous servo with timed pulse control
- ✅ **Live Monitoring**: Real-time temperature streaming to mobile dashboard gauge
- ✅ **Remote Fan Control**: Digital switch for fan operation from anywhere

### Phase 3: Voice Command Integration

- ✅ **Siri Integration**: Apple Siri Shortcuts with HTTP webhook implementation
- ✅ **Voice-Activated Controls**: Fan and lights controllable via voice commands
- ✅ **Voice Door Control**: Precise 1.5-second pulse for door unlock/lock
- ✅ **Audible Feedback**: Confirmation responses (e.g., “Okay Master, I have turned on the fan”)
- ✅ **Live Data Retrieval**: Voice query for current temperature via GET API
- ✅ **Bidirectional Communication**: Full voice command and response interaction

##  System Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                     User Interface Layer                     │
├─────────────────────────────────────────────────────────────┤
│  Apple Siri          │  Blynk Mobile App  │  Physical Sensors│
│  (Voice Commands)    │  (Remote Control)  │  (Auto Triggers) │
└──────────┬───────────┴──────────┬─────────┴─────────┬────────┘
           │                      │                    │
           │ HTTP GET/UPDATE      │ Blynk Protocol     │
           ▼                      ▼                    ▼
┌─────────────────────────────────────────────────────────────┐
│                    Blynk IoT Cloud                           │
│                  (Central Hub & API)                         │
└──────────────────────────┬──────────────────────────────────┘
                           │ WiFi Communication
                           ▼
┌─────────────────────────────────────────────────────────────┐
│                      ESP32 Controller                        │
├─────────────────────────────────────────────────────────────┤
│  • WiFi Module          • Logic Processing                  │
│  • API Handler          • Automation Engine                 │
└──────────┬──────────────────────────────────────────────────┘
           │
           ├──────────────┬──────────────┬──────────────┐
           ▼              ▼              ▼              ▼
    ┌──────────┐   ┌──────────┐  ┌──────────┐  ┌──────────┐
    │ Sensors  │   │Actuators │  │  Servo   │  │ Display  │
    ├──────────┤   ├──────────┤  ├──────────┤  ├──────────┤
    │ DHT11    │   │ Relay 1  │  │ SG90     │  │   OLED   │
    │ Rain     │   │ (Fan)    │  │ (Window) │  │  Screen  │
    │ LDR      │   │ Relay 2  │  │ 360° CS  │  │          │
    │          │   │ (Light)  │  │ (Door)   │  │          │
    └──────────┘   └──────────┘  └──────────┘  └──────────┘
```

## 🔧 Hardware Requirements

|Component                         |Specification               |Quantity|Purpose                 |
|----------------------------------|----------------------------|--------|------------------------|
|**ESP32 Development Board**       |WiFi & Bluetooth enabled    |1       |Main controller         |
|**DHT11 Sensor**                  |Temperature & Humidity      |1       |Environmental monitoring|
|**Rain Sensor Module**            |Digital output              |1       |Rain detection          |
|**LDR (Light Dependent Resistor)**|Photoresistor               |1       |Ambient light sensing   |
|**OLED Display**                  |0.96” I2C (128x64)          |1       |Data visualization      |
|**SG90 Servo Motor**              |0°-90° rotation             |1       |Window control          |
|**360° Continuous Servo**         |Full rotation               |1       |Door lock mechanism     |
|**4-Channel Relay Module**        |5V trigger                  |1       |Fan & light control     |
|**Cooling Fan**                   |5V/12V DC                   |1       |Climate control         |
|**LED Bulb/Strip**                |Compatible voltage          |1       |Room lighting           |
|**Breadboard**                    |Standard size               |1       |Prototyping             |
|**Jumper Wires**                  |Male-to-Male, Male-to-Female|40+     |Connections             |
|**Power Supply**                  |5V 2A minimum               |1       |System power            |
|**Resistors**                     |10kΩ (for LDR divider)      |2       |Voltage division        |
|**RFID RC522 Module**             | 13.56MHz                   | 1      | Door access control    |
|**RFID Cards/Tags**               | 13.56MHz compatible        | 2-5    | Access authentication  |

## 💻 Software Requirements

### Development Environment

- **Visual Studio Code** with **PlatformIO IDE Extension**
- **ESP32 Board Support Package**
- **USB to Serial drivers** (CP2102/CH340)

### Required Libraries

```cpp
#include <MFRC522.h>              // RFID RC522 library
// Core ESP32 Libraries
#include <WiFi.h>
#include <HTTPClient.h>

// Sensor & Display Libraries
#include <DHT.h>                    // DHT sensor library
#include <Adafruit_SSD1306.h>       // OLED display
#include <Wire.h>                   // I2C communication

// Servo Control
#include <ESP32Servo.h>             // Servo motor library

// Blynk IoT Platform
#include <BlynkSimpleEsp32.h>
```

### Installation Commands

**Install PlatformIO in VSCode:**

```bash
# 1. Open Visual Studio Code
# 2. Go to Extensions (Ctrl+Shift+X or Cmd+Shift+X)
# 3. Search for "PlatformIO IDE"
# 4. Click Install and wait for installation to complete
# 5. Restart VSCode
```

**Create New PlatformIO Project:**

```bash
# 1. Click PlatformIO icon in VSCode sidebar
# 2. Click "New Project"
# 3. Project Name: ESP32_Smart_Home
# 4. Board: Espressif ESP32 Dev Module
# 5. Framework: Arduino
# 6. Click Finish
```

**platformio.ini Configuration:**

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200

lib_deps = 
    adafruit/DHT sensor library@^1.4.4
    adafruit/Adafruit SSD1306@^2.5.7
    adafruit/Adafruit GFX Library@^1.11.3
    madhephaestus/ESP32Servo@^0.13.0
    blynkkk/Blynk@^1.3.2
```

**Install libraries:**

```bash
# Libraries are automatically installed based on platformio.ini
# Or manually via PlatformIO Library Manager:
# Click PlatformIO icon > Libraries > Search and install the above libraries
```

### Cloud & Mobile Setup

- **Blynk IoT Account**: [blynk.cloud](https://blynk.cloud)
- **Blynk Mobile App**: iOS App Store or Google Play Store
- **Apple Shortcuts App**: Pre-installed on iOS devices

##  Pin Configuration

```cpp
// Sensor Pins
#define DHT_PIN          4      // DHT11 Data Pin
#define RAIN_SENSOR_PIN  5      // Rain Sensor Digital Output
#define LDR_PIN         34      // Light Dependent Resistor (Analog)

// Display Pins (I2C)
#define OLED_SDA        21      // I2C Data
#define OLED_SCL        22      // I2C Clock

// Servo Motor Pins
#define WINDOW_SERVO_PIN 18     // SG90 Servo (0°-90°)
#define DOOR_SERVO_PIN   19     // 360° Continuous Servo

// Relay Control Pins
#define RELAY_FAN_PIN    25     // Relay Channel 1 (Fan)
#define RELAY_LIGHT_PIN  26     // Relay Channel 2 (Room Light)

// DHT Sensor Type
#define DHT_TYPE DHT11
// RFID RC522 Pins (SPI)
#define RFID_SS_PIN    5       // SPI Chip Select
#define RFID_RST_PIN   27      // Reset Pin
#define RFID_MOSI_PIN  23      // SPI MOSI
#define RFID_MISO_PIN  19      // SPI MISO  
#define RFID_SCK_PIN   18      // SPI Clock
```

##  Installation & Setup

### 1. Hardware Assembly

1. **Connect DHT11 Sensor:**
- VCC → 3.3V
- GND → GND
- DATA → GPIO 4
1. **Connect Rain Sensor:**
- VCC → 5V
- GND → GND
- DO → GPIO 5
1. **Connect LDR Circuit:**
- LDR → 3.3V
- LDR → GPIO 34 (via 10kΩ pull-down resistor to GND)
1. **Connect OLED Display (I2C):**
- VCC → 3.3V
- GND → GND
- SDA → GPIO 21
- SCL → GPIO 22
1. **Connect Servo Motors:**
- Window Servo (SG90):
  - Red → 5V
  - Brown → GND
  - Orange → GPIO 18
- Door Servo (360°):
  - Red → 5V
  - Brown → GND
  - Orange → GPIO 19
1. **Connect 4-Channel Relay:**
- VCC → 5V
- GND → GND
- IN1 (Fan) → GPIO 25
- IN2 (Light) → GPIO 26
- IN3 (Reserved for future use)
- IN4 (Reserved for future use)
- Connect fan to Relay 1 NO/COM
- Connect light to Relay 2 NO/COM
- Channels 3 & 4 available for expansion

### 2. Software Configuration

#### A. PlatformIO Setup

```cpp
// 1. Open project in VSCode with PlatformIO
// 2. Board auto-configured via platformio.ini (esp32dev)
// 3. Connect ESP32 via USB (auto-detected)
// 4. Libraries installed automatically from platformio.ini
```

#### B. WiFi Configuration

```cpp
// Update these credentials in your code
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```

#### C. Blynk Configuration

```cpp
// Get these from Blynk Console (blynk.cloud)
#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Smart Home System"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"
```

**Blynk Virtual Pin Mapping:**

|Virtual Pin|Widget Type   |Function           |
|-----------|--------------|-------------------|
|V0         |Gauge         |Temperature Display|
|V1         |Switch        |Room Light Control |
|V2         |Switch        |Fan Control        |
|V3         |Button (Timed)|Door Lock/Unlock   |
|V4         |Switch        |Window Override    |

#### D. Upload Code

1. Connect ESP32 via USB
1. Click “Upload” button in PlatformIO toolbar (→ arrow icon)
- Or use: `PlatformIO: Upload` from command palette (Ctrl+Shift+P)
- Or click checkmark to build, then arrow to upload
1. Wait for “SUCCESS” message in terminal
1. Open Serial Monitor (plug icon) to verify connection (115200 baud)

### 3. Blynk Mobile App Setup

1. **Download Blynk App**
- iOS: App Store
- Android: Google Play Store
1. **Create New Template**
- Login to [blynk.cloud](https://blynk.cloud)
- Create new template: “Smart Home System”
- Select Device: ESP32
- Connection: WiFi
1. **Configure Datastreams**
   
   ```
   V0 - Temperature (Virtual Pin, Double, 0-50°C)
   V1 - Room Light (Virtual Pin, Integer, 0-1)
   V2 - Fan (Virtual Pin, Integer, 0-1)
   V3 - Door Control (Virtual Pin, Integer, 0-1)
   V4 - Window Control (Virtual Pin, Integer, 0-1)
   ```
1. **Design Dashboard**
- Add Gauge widget → Link to V0 (Temperature)
- Add Switch widget → Link to V1 (Room Light)
- Add Switch widget → Link to V2 (Fan)
- Add Button widget (Push mode) → Link to V3 (Door)
- Add Switch widget → Link to V4 (Window)
1. **Get Auth Token**
- Copy auth token from device info
- Paste into Arduino code

### 4. Siri Shortcuts Configuration

#### A. Get Blynk API Token

```
Login to Blynk Console → My Profile → Copy API Token
```

#### B. Create Shortcuts (Examples)

**Turn On Light:**

```
1. Open Shortcuts app on iPhone
2. Tap "+" to create new shortcut
3. Add action: "Get Contents of URL"
4. URL: https://blynk.cloud/external/api/update?token=YOUR_API_TOKEN&V1=1
5. Method: GET
6. Add action: "Speak Text"
7. Text: "Okay Master, I have turned on the light"
8. Name shortcut: "Turn on light"
9. Add to Siri: "Hey Siri, turn on light"
```

**Turn Off Light:**

```
URL: https://blynk.cloud/external/api/update?token=YOUR_API_TOKEN&V1=0
Speech: "Okay Master, I have turned off the light"
```

**Turn On Fan:**

```
URL: https://blynk.cloud/external/api/update?token=YOUR_API_TOKEN&V2=1
Speech: "Okay Master, I have turned on the fan"
```

**Turn Off Fan:**

```
URL: https://blynk.cloud/external/api/update?token=YOUR_API_TOKEN&V2=0
Speech: "Okay Master, I have turned off the fan"
```

**Open/Lock Door:**

```
URL: https://blynk.cloud/external/api/update?token=YOUR_API_TOKEN&V3=1
Speech: "Okay Master, the door is unlocked"
Note: ESP32 code should auto-reset V3 to 0 after 1.5 seconds
```

**Get Temperature:**

```
1. Get Contents of URL: https://blynk.cloud/external/api/get?token=YOUR_API_TOKEN&V0
2. Get Dictionary Value for key: "value"
3. Speak Text: "The room temperature is [Dictionary Value] degrees"
```

## Phase-wise Development

### Phase 1: Core Automation & Sensing ✅

**Objective:** Build foundational monitoring and automated response system

**Achievements:**

- Integrated DHT11 for temperature/humidity monitoring
- Implemented OLED display for real-time data visualization
- Created mini weather station with rain sensor
- Automated fan control (Relay 1) based on environmental logic
- Rain-triggered automatic window closing (SG90 servo)
- Smart door/gate mechanism with 0°-90° servo control
- LDR-based automatic lighting system (Relay 2)

**Key Learning:** Sensor integration, servo calibration, relay control logic

-----

### Phase 2: Cloud Integration & Remote Control ✅

**Objective:** Enable remote monitoring and control via mobile app

**Achievements:**

- Successfully connected ESP32 to Blynk IoT Cloud
- Implemented WiFi communication protocols
- Created hybrid lighting system (automatic LDR + manual app control)
- Developed smart window system with rain auto-close and manual override
- Integrated 360° continuous servo for door lock with timed pulse control
- Real-time temperature streaming to mobile gauge widget
- Remote fan control via mobile app switch

**Key Learning:** IoT cloud integration, bidirectional communication, hybrid automation

-----

### Phase 3: Voice Command Integration ✅

**Objective:** Implement voice control using Apple Siri

**Achievements:**

- Bridged Blynk Cloud with Apple Siri Shortcuts
- Implemented HTTP GET/UPDATE webhook architecture
- Voice-activated fan and lighting controls
- Precise voice-controlled door mechanism (1.5s pulse)
- Audible confirmation feedback system
- Live temperature data retrieval via voice query
- Full bidirectional voice interaction

**Key Learning:** API integration, webhook configuration, voice assistant protocols

##  Voice Commands

|Command                            |Action                                    |Feedback                                  |
|-----------------------------------|------------------------------------------|------------------------------------------|
|“Hey Siri, turn on the light”      |Sets V1=1, activates Relay 2              |“Okay Master, I have turned on the light” |
|“Hey Siri, turn off the light”     |Sets V1=0, deactivates Relay 2            |“Okay Master, I have turned off the light”|
|“Hey Siri, turn on the fan”        |Sets V2=1, activates Relay 1              |“Okay Master, I have turned on the fan”   |
|“Hey Siri, turn off the fan”       |Sets V2=0, deactivates Relay 1            |“Okay Master, I have turned off the fan”  |
|“Hey Siri, unlock the door”        |Sets V3=1 (1.5s pulse), rotates 360° servo|“Okay Master, the door is unlocked”       |
|“Hey Siri, lock the door”          |Sets V3=1 (1.5s pulse), rotates 360° servo|“Okay Master, the door is locked”         |
|“Hey Siri, what’s the temperature?”|GET request to V0, retrieves DHT11 data   |“The room temperature is 28.4 degrees”    |

## 🔌 API Integration

### Blynk HTTP API Endpoints

#### Update Virtual Pin (Control Devices)

```http
GET https://blynk.cloud/external/api/update?token=YOUR_API_TOKEN&V{PIN}={VALUE}

Examples:
- Turn ON light:  V1=1
- Turn OFF light: V1=0
- Turn ON fan:    V2=1
- Door pulse:     V3=1
```

#### Read Virtual Pin (Get Sensor Data)

```http
GET https://blynk.cloud/external/api/get?token=YOUR_API_TOKEN&V{PIN}

Example Response:
{
  "value": "28.4"
}
```

#### Batch Update (Multiple Pins)

```http
GET https://blynk.cloud/external/api/batch/update?token=YOUR_API_TOKEN&V1=1&V2=0
```

### Security Considerations

- Keep API token private and never commit to public repositories
- Use environment variables or separate config files
- Regenerate token if compromised
- Monitor API usage in Blynk console


```

> **Note:** For detailed wiring diagrams with color-coded connections, refer to the `/docs/wiring-diagrams/` folder in this repository.

## 📱 Usage Guide

### Automatic Operations

1. **Intelligent Lighting**
- System monitors ambient light via LDR
- When darkness detected → Room light (Relay 2) turns ON automatically
- When sufficient light → Room light turns OFF automatically
- Manual override available via app or voice
1. **Rain Protection**
- Rain sensor continuously monitors weather
- When rain detected → Window (SG90 servo) closes immediately to 0°
- System prevents water damage automatically
- Manual control available during dry weather
1. **Climate Control**
- DHT11 monitors temperature and humidity
- Logic-based fan activation via Relay 1
- Real-time display on OLED screen

### Manual Control via Blynk App

1. **Room Light**
- Toggle switch V1 for instant ON/OFF
- Works alongside automatic LDR control
1. **Cooling Fan**
- Toggle switch V2 for manual operation
- Override automatic temperature logic
1. **Door Lock**
- Press V3 button to unlock/lock
- 1.5-second servo pulse activates mechanism
- Auto-resets for next use
1. **Window Position**
- Switch V4 for manual window control
- Override rain-based automatic closing
1. **Temperature Monitoring**
- View live temperature on V0 gauge
- Updates in real-time from DHT11

### Voice Control via Siri

1. **Ensure Prerequisites:**
- iPhone connected to internet
- Siri shortcuts configured
- ESP32 online and connected to Blynk
1. **Issue Voice Commands:**
- Speak naturally: “Hey Siri, turn on the fan”
- Wait for audible confirmation
- Check device status on app or physically
1. **Query Information:**
- “Hey Siri, what’s the temperature?”
- Siri speaks current reading from sensor

## 🔍 Troubleshooting

### PlatformIO Build Errors

```
Error: Cannot find library 'X'
```

**Solution:**

- Check `platformio.ini` lib_deps section
- Run `PlatformIO: Clean` from command palette
- Delete `.pio` folder and rebuild
- Manually install library: PlatformIO Home → Libraries
- Update platform: `pio platform update espressif32`

### PlatformIO Upload Failed

```
Error: Failed to connect to ESP32
```

**Solution:**

- Check USB cable (data cable, not just charging)
- Press and hold BOOT button during upload
- Check COM port in Device Manager (Windows) or `ls /dev/tty*` (Mac/Linux)
- Install/update USB drivers (CP210x or CH340)
- Try different USB port
- Add to platformio.ini:
  
  ```ini
  upload_speed = 115200
  upload_port = /dev/ttyUSB0  ; or COM3 on Windows
  ```

### ESP32 Won’t Connect to WiFi

```cpp
// Check Serial Monitor output
// Verify WiFi credentials
// Ensure 2.4GHz network (ESP32 doesn't support 5GHz)
// Check router MAC filtering
```

**Solution:**

- Double-check SSID and password (case-sensitive)
- Move ESP32 closer to router
- Restart router and ESP32
- Use static IP if DHCP fails

### Blynk Connection Failed

```
Error: [5949] Login timeout
```

**Solution:**

- Verify Auth Token is correct
- Check internet connectivity
- Ensure Blynk servers are online (status.blynk.cc)
- Verify datastream configuration matches code

### Servo Not Moving

**Symptoms:** Servo jitters or doesn’t respond

**Solution:**

- Check power supply (servos need adequate current)
- Use external 5V power for servos, common GND with ESP32
- Verify GPIO pin assignment
- Test servo with example code
- Check PWM frequency settings

### DHT11 Reading Errors

```
Error: Failed to read from DHT sensor!
```

**Solution:**

- Check wiring (VCC, GND, DATA)
- Add 10kΩ pull-up resistor on DATA line
- Increase read delay (DHT11 needs 2s between reads)
- Replace sensor if physically damaged

### Relay Not Switching

**Symptoms:** Relay clicks but device doesn’t turn on/off

**Solution:**

- Check if relay is active LOW or HIGH
- Verify relay wiring (NO, NC, COM)
- Test with multimeter
- Ensure adequate power supply
- Check load compatibility

### Siri Shortcut Not Working

**Symptoms:** Siri doesn’t respond or gives error

**Solution:**

- Verify internet connection on iPhone
- Check Blynk API token in URL
- Test URL directly in browser
- Ensure Virtual Pin numbers match
- Check Blynk device is online
- Review Shortcuts app logs

### OLED Display Blank

**Solution:**

- Verify I2C address (usually 0x3C or 0x3D)
- Check SDA/SCL connections
- Run I2C scanner sketch
- Adjust contrast in code
- Check power supply voltage

### Rain Sensor Always Triggered

**Solution:**

- Clean sensor plate
- Adjust sensitivity potentiometer
- Check wiring
- Test in dry environment
- Replace if corroded

##  Future Enhancements

### Planned Features

- [ ] **Multi-Room Expansion**: Extend system to control multiple rooms
- [ ] **Energy Monitoring**: Add current sensors to track power consumption
- [ ] **Advanced Security**: Integrate fingerprint or RFID access control
- [ ] **Machine Learning**: Predictive automation based on usage patterns
- [ ] **Google Assistant**: Add support for Google Home ecosystem
- [ ] **Amazon Alexa**: Integrate with Alexa voice control
- [ ] **Mobile Notifications**: Push alerts for security events
- [ ] **Data Logging**: Historical data storage and visualization
- [ ] **Scheduled Automation**: Time-based task scheduling
- [ ] **Geofencing**: Location-based automation triggers

### Hardware Upgrades

- [ ] **Utilize Relay Channels 3 & 4**: Add additional appliances (e.g., exhaust fan, garden lights)
- [ ] Add motion sensors (PIR) for occupancy detection
- [ ] Integrate door/window magnetic sensors
- [ ] Add gas/smoke detectors for safety
- [ ] Include power backup (UPS/Battery)
- [ ] Upgrade to ESP32-CAM for video monitoring
- [ ] Add IR blaster for TV/AC control

### Software Improvements

- [ ] Implement OTA (Over-The-Air) firmware updates
- [ ] Create web-based configuration portal
- [ ] Add data encryption for enhanced security
- [ ] Develop custom mobile app (Flutter/React Native)
- [ ] Implement MQTT protocol for faster response
- [ ] Add offline mode with local control fallback

## 🤝 Contributing

Contributions are welcome! If you’d like to improve this project:

1. Fork the repository
1. Create your feature branch (`git checkout -b feature/AmazingFeature`)
1. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
1. Push to the branch (`git push origin feature/AmazingFeature`)
1. Open a Pull Request

Please ensure your code follows the existing style and includes 

- **Arduino Community**: For extensive documentation and examples
- **Blynk Documentation**: Comprehensive IoT platform guides
- **ESP32 Forums**: Hardware troubleshooting and optimization tips
- **Adafruit Learning System**: Sensor integration tutorials

### Libraries & Tools

- [Blynk IoT Platform](https://blynk.io/) - Cloud infrastructure
- [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32)
- [DHT Sensor Library](https://github.com/adafruit/DHT-sensor-library)
- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
- [ESP32Servo Library](https://github.com/madhephaestus/ESP32Servo)

### Special Thanks
- **Department of Faculty of Computing**: Resources and support
- **Fellow Students**: Temitope https://github.com/Jcolereincarnate 

### Inspiration

This project was inspired by the growing need for affordable, customizable smart home solutions and the desire to make home automation accessible to everyone.

-----

## 📞 Contact & Support

**Project Author**: Ehindero Henry 
**Email**: ehinderohenry7@gmail.com
**University**: Ajayi Crowther University
**Department**: Computer Science 
**Academic Year**: Final Year Project (2025-2026)

### Repository

- **GitHub**: [github.com/Henry2005Max/Smart-Home-ESP32](https://github.com/Henry2005Max/Smart-Home-ESP32)
- **Issues**: Report bugs or request features via GitHub Issues

### Project Demo
📸 **Gallery**: See `/images` folder for project photos

-----

<div align="center">

**⭐ If you found this project helpful, please consider giving it a star! ⭐**

Made with ❤️ for Smart Home Automation

![ESP32](https://img.shields.io/badge/ESP32-000000?style=for-the-badge&logo=espressif&logoColor=white)
![PlatformIO](https://img.shields.io/badge/PlatformIO-FF7F00?style=for-the-badge&logo=data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMjUwMCIgaGVpZ2h0PSIyNTAwIiB2aWV3Qm94PSIwIDAgMjU2IDI1NiIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiBwcmVzZXJ2ZUFzcGVjdFJhdGlvPSJ4TWlkWU1pZCI+PHBhdGggZD0iTTEyOCAwQzU3LjMwNyAwIDAgNTcuMzA3IDAgMTI4czU3LjMwNyAxMjggMTI4IDEyOCAxMjgtNTcuMzA3IDEyOC0xMjhTMTk4LjY5MyAwIDEyOCAwem0wIDI1MS43MzNjLTY4LjI2NyAwLTEyMy43MzMtNTUuNDY3LTEyMy43MzMtMTIzLjczM1M1OS43MzMgNC4yNjcgMTI4IDQuMjY3IDE1MS43MzMgNTkuNzMzIDE1MS43MzMgMTI4IDE5Ni4yNjcgMjUxLjczMyAxMjggMjUxLjczM3oiIGZpbGw9IiNGRjdGMDAiLz48L3N2Zz4=&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![VSCode](https://img.shields.io/badge/VSCode-007ACC?style=for-the-badge&logo=visualstudiocode&logoColor=white)
![IoT](https://img.shields.io/badge/IoT-Enabled-green?style=for-the-badge)

</div>
