#include <Wire.h>
#include <MPU6050.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <BlynkSimpleEsp32.h>
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* firebaseURL = "https://your-project-id.firebaseio.com/alerts.json";
const char* firebaseAuth = "YOUR_FIREBASE_WEB_API_KEY";
char auth[] = "YOUR_BLYNK_AUTH_TOKEN";
MPU6050 mpu;

float fallThreshold = 0.4;   // g-force drop (free fall)
float recoveryThreshold = 1.0; // g-force recovery (impact)
bool fallDetected = false;
unsigned long fallTime = 0;
void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA = 21, SCL = 22
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  Blynk.begin(auth, ssid, password);
}
void loop() {
  Blynk.run();

  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);
  // Convert to g-force
  float gX = ax / 16384.0;
  float gY = ay / 16384.0;
  float gZ = az / 16384.0;
  float totalG = sqrt(gX * gX + gY * gY + gZ * gZ);
  Serial.print("Total Acceleration: ");
  Serial.println(totalG);
  // Detect fall
  if (totalG < fallThreshold && !fallDetected) {
    fallDetected = true;
    fallTime = millis();
    Serial.println("Fall Detected!");
    sendBlynkAlert();
    sendFirebaseAlert();
  }
  // Reset detection after recovery
  if (fallDetected && (millis() - fallTime > 2000)) {
    if (totalG > recoveryThreshold) {
      fallDetected = false;
      Serial.println("Recovered from fall.");
    }
  delay(300);
}
void sendBlynkAlert() {
  Blynk.logEvent("fall_alert", "Fall Detected!");
  Serial.println("Blynk alert sent!");
}
void sendFirebaseAlert() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(firebaseURL);
    http.addHeader("Content-Type", "application/json");
    String json = "{\"fall\":\"Fall detected at " + String(millis() / 1000) + " seconds\"}";
    int httpResponseCode = http.PUT(json);
    if (httpResponseCode > 0) {
      Serial.print("Firebase Response: ");
      Serial.println(http.getString());
    } else {
      Serial.print("Firebase Error: ");
      Serial.println(httpResponseCode);
    }
    http.end();
