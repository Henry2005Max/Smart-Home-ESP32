#define BLYNK_PRINT Serial

// --- 1. BLYNK CONFIG ---
#define BLYNK_TEMPLATE_ID "TMPL2sDP-Ppku"
#define BLYNK_TEMPLATE_NAME "New Template"
#define BLYNK_AUTH_TOKEN "SMNTlYdKFwTOa3XS6NtTYDpgFlV7wYYR"

// --- 2. WIFI DETAILS ---
// (Change these to "Henry iPhone" if you are using your hotspot!)
char ssid[] = "MTN_4G_56DDF7";
char pass[] = "756C345D";

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// --- PINS ---
#define FAN_PIN 4        // Relay 1
#define LIGHT_PIN 16     // Relay 2 (LED Lights connect here)
#define WINDOW_PIN 13    // Servo 1 (Window)
#define DOOR_PIN 2       // Servo 2 (Door)
#define BUZZER_PIN 18    // <--- NEW! Connect Buzzer Positive here
#define DHT_PIN 14       // Temp
#define RAIN_PIN 27      // Rain
#define LDR_PIN 32       // Light
#define DHT_TYPE DHT11

Servo windowServo;
Servo doorServo;
Adafruit_SSD1306 display(128, 64, &Wire, -1);
DHT dht(DHT_PIN, DHT_TYPE);
BlynkTimer timer;

// Variables for App Control
int appFanState = 0;
int appLightState = 0;

// --- NEW: HELPER FUNCTION FOR BUZZER ---
// --- NEW BEEP FUNCTION (FOR PASSIVE BUZZERS) ---
void beep(int duration) {
  long startTime = millis();
  while (millis() - startTime < duration) {
    digitalWrite(BUZZER_PIN, HIGH);
    delayMicroseconds(200); // Wait 0.2ms (Vibrates pin)
    digitalWrite(BUZZER_PIN, LOW);
    delayMicroseconds(200); // Wait 0.2ms
  }
}

// --- BLYNK FUNCTIONS ---

BLYNK_WRITE(V1) { // Fan Control
  appFanState = param.asInt();
  if (appFanState == 1) {
    beep(200); // Short beep when Fan turns ON
  }
}

BLYNK_WRITE(V2) { // Lights Control
  appLightState = param.asInt();
  // No beep for lights usually, but you can add one if you want!
}

// --- DOOR CONTROL (V4) WITH SOUND ---
BLYNK_WRITE(V4) {
  int doorAction = param.asInt(); // 1 = Open, 0 = Close

  if (doorAction == 1) {
    // OPEN SEQUENCE
    Serial.println("Door Opening...");
    beep(100); delay(50); beep(100); // Double Beep-Beep
    doorServo.write(180); // Spin Forward
    delay(1500);          
    doorServo.write(90);  // STOP
  } 
  else {
    // CLOSE SEQUENCE
    Serial.println("Door Closing...");
    beep(500);            // Long Beep
    doorServo.write(0);   // Spin Backward
    delay(1500);          
    doorServo.write(90);  // STOP
  }
}

void sendSensorData() {
  float t = dht.readTemperature();
  if (!isnan(t)) Blynk.virtualWrite(V0, t);
}

void setup() {
  Serial.begin(115200);

  // Init Pins
  pinMode(FAN_PIN, OUTPUT);
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT); // <--- Set Buzzer as Output
  pinMode(RAIN_PIN, INPUT_PULLUP); 
  pinMode(LDR_PIN, INPUT);
  
  // Init Servos
  windowServo.attach(WINDOW_PIN);
  windowServo.write(90); 

  doorServo.attach(DOOR_PIN); 
  doorServo.write(90);   

  // Init Sensors/Display
  dht.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { for(;;); }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Connecting...");
  display.display();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(2000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();

  float t = dht.readTemperature();
  int isRaining = digitalRead(RAIN_PIN); 
  int isDark = digitalRead(LDR_PIN);     

  // --- 1. AUTOMATIC WINDOW LOGIC (Rain) ---
  // If Rain (HIGH) -> Close Window
  if (isRaining == HIGH) {
    windowServo.write(0);        // Auto-Close Window
    digitalWrite(FAN_PIN, LOW);  // Safety Fan OFF
    
    // RAIN ALARM SOUND
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW); // Rapid ticking sound
    
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("STATUS: RAINING!");
    display.setCursor(0, 15);
    display.println("Window: CLOSED");
  } 
  else {
    windowServo.write(90);       // Auto-Open Window
    
    // Fan Manual Control
    if (appFanState == 1) digitalWrite(FAN_PIN, HIGH);
    else digitalWrite(FAN_PIN, LOW);

    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("STATUS: SUNNY");
    display.setCursor(0, 15);
    display.println("Window: OPEN");
  }

  // --- 2. LIGHT LOGIC ---
  // (Connect your LED Lights to Relay 2 / Pin 16)
  if (isDark == LOW || appLightState == 1) {
    digitalWrite(LIGHT_PIN, HIGH);
    display.setCursor(0, 30);
    display.print("Light: ON");
  } else {
    digitalWrite(LIGHT_PIN, LOW);
    display.setCursor(0, 30);
    display.print("Light: OFF");
  }

  // Temp
  display.setCursor(0, 45);
  display.print("Temp: ");
  if(isnan(t)) display.print("--");
  else display.print(t, 1);
  display.print(" C");

  display.display();
}