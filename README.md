# Wearable-Fall-Detection-System
IoT-based wearable fall detection system using ESP32 and MPU6050

An IoT-based wearable fall detection system designed to detect falls in elderly or mobility-impaired individuals using real-time motion sensing and wireless alerts.

### 📌 Project Overview
Falls are a major health risk for elderly individuals. This project uses an **ESP32 microcontroller** and **MPU6050 accelerometer/gyroscope** to continuously monitor motion and detect fall events based on acceleration thresholds.

When a fall is detected, alerts are generated via:
- Serial Monitor (development stage)
- Firebase Realtime Database
- Blynk IoT Platform (real-time notifications)

## 🎯 Objectives
- Detect falls accurately in real-time
- Minimize false alarms
- Provide immediate alerts to caregivers
- Enable future cloud & mobile app integration

## 🧠 Technologies Used
- ESP32 WROOM-32
- MPU6050 (Accelerometer + Gyroscope)
- Arduino IDE
- Firebase Realtime Database
- Blynk IoT Platform
- Wi-Fi Communication

## ⚙️ System Working
1. MPU6050 continuously measures acceleration (X, Y, Z)
2. Resultant acceleration is calculated
3. Fall detected when:
   - Acceleration < 0.4g (free fall)
   - Followed by recovery > 1.0g
4. Alert sent to Blynk and Firebase

## 🔌 Hardware Connections
| ESP32 | MPU6050 |
|------|--------|
| 3V3  | VCC    |
| GND  | GND    |
| GPIO21 | SDA |
| GPIO22 | SCL |

## 📊 Results
- Accuracy: **>90%**
- Successfully detects:
  - Free falls
  - Sudden drops
- Ignores:
  - Walking
  - Sitting
  - Normal movements

## 🔮 Future Enhancements
- Machine Learning based fall classification
- GPS & heart-rate sensor integration
- Low-power deep sleep modes
- SMS / Email alerts

## 👩‍💻 Authors
- **Raja Priya R**
- **Sherlin J**

Department of Electronics and Communication Engineering  
Mepco Schlenk Engineering College, Sivakasi

## 📚 References
Refer to `/report` and `/references` folders for detailed documentation and research papers.



