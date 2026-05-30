# 🚗 Driver Drowsiness Detection System

![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)
![OpenCV](https://img.shields.io/badge/OpenCV-5C3EE8?style=for-the-badge&logo=opencv&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![ESP32](https://img.shields.io/badge/ESP32-000000?style=for-the-badge&logo=espressif&logoColor=white)

An intelligent, real-time drowsiness detection system that uses computer vision to monitor a driver's Eye Aspect Ratio (EAR). If sleep is detected, a Python script sends a serial signal to an ESP32 microcontroller, which triggers a rapid 2-second blinking/beeping alarm and activates an L298N-controlled DC motor to physically wake or alert the user.

---

## 📸 Project Demo
> *(Add a GIF or screenshot of your Python camera feed and hardware working here. You can place the image in your `assets/` folder and link it like this: `![Demo](assets/demo.gif)`)*

---
## 📖 About the Project

Driver fatigue is a leading cause of severe road accidents. This project aims to prevent micro-sleeps at the wheel by combining real-time computer vision with an active IoT hardware response. Unlike standard software-only alerts that just play a sound on a computer, this system bridges the gap into the physical world using an ESP32 microcontroller to trigger tangible environmental changes (spinning a motor, flashing lights, and sounding an active alarm).

### 🧠 How It Works (System Architecture)

The system operates on a continuous software-to-hardware loop:

**1. Facial Landmark Detection (The Software)**
The system captures live video via a webcam and processes it using **MediaPipe Face Mesh**. This lightweight machine learning model maps 468 3D landmarks across the driver's face in real time. We extract 12 specific coordinates—6 for the left eye and 6 for the right eye.

**2. The Eye Aspect Ratio (EAR) Math**
Using the extracted coordinates, the Python script calculates the Euclidean distance between the vertical eye landmarks and horizontal eye landmarks to compute the Eye Aspect Ratio (EAR).
* When a person's eyes are open, the EAR remains relatively constant.
* When a person blinks or closes their eyes, the EAR drops rapidly toward zero.

**3. State Machine & Sleep Logic**
Human blinks are incredibly fast (usually 3–5 frames). To prevent false alarms from normal blinking, the system uses a frame counter. 
* If the EAR drops below the threshold of `0.21`, the counter starts. 
* If the eyes remain closed for `20` consecutive frames, the driver is classified as **"SLEEPING"**.

**4. Serial Communication & Hardware Actuation (The Hardware)**
Once sleep is detected, the Python script instantly opens a serial communication line to the ESP32 and sends a `1` byte. 
* **The Alarm Cycle:** The ESP32 receives the signal and activates an L298N motor driver, spinning a DC motor (which could be attached to a steering wheel vibrator or seat mechanism). Simultaneously, it triggers a 2-second rapid-fire sequence of high-pitch buzzer beeps and LED flashes. 
* **The Wake State:** Once the driver opens their eyes, the software resets, sending a `0` byte. The ESP32 immediately cuts power to the buzzer and applies an electronic "hard brake" to the motor to stop it from spinning instantly.
## 🛠️ Hardware Requirements

*   **Microcontroller:** ESP32 Development Board
*   **Motor Controller:** L298N Motor Driver Module
*   **Actuator:** DC Motor (connected to L298N)
*   **Alerts:** Active Buzzer & LED (or use ESP32's built-in LED)
*   **Power:** External battery pack for the motor (e.g., 9V or 4x AA)
*   **Camera:** Standard Webcam (for facial landmark detection)

---

## 🔌 Circuit & Wiring

| Component | Pin / Terminal | Connected To |
| :--- | :--- | :--- |
| **L298N Driver** | `IN1` | ESP32 `GPIO 18` |
| **L298N Driver** | `IN2` | ESP32 `GPIO 19` |
| **L298N Driver** | `GND` | ESP32 `GND` **(Crucial)** & Battery `(-)` |
| **L298N Driver** | `12V/VCC`| External Battery `(+)` |
| **Buzzer** | `Positive (+)` | ESP32 `GPIO 4` |
| **LED** | `Anode (+)` | ESP32 `GPIO 2` (via 220Ω resistor) |

*(Note: The motor is connected to `OUT1` and `OUT2` on the L298N. Leave the `ENA` jumper cap ON for full speed).*

---

## 💻 Software & Libraries

**Python Dependencies:**
*   `opencv-python` (Image processing)
*   `mediapipe` (Face mesh and landmark detection)
*   `scipy` (Calculating Euclidean distance for EAR)
*   `pyserial` (Serial communication with ESP32)
*   `numpy` (Array operations)

**Arduino/ESP32:**
*   Standard Arduino IDE with ESP32 board manager installed.

---

## 🚀 Installation & Setup

### 1. Hardware Setup
1. Wire the components according to the wiring table above.
2. Connect your ESP32 to your computer via USB.
3. Open `esp32_controller/esp32_controller.ino` in the Arduino IDE.
4. Select your ESP32 board and COM port, then upload the code.

### 2. Python Setup
1. Clone this repository to your local machine:
```bash
   git clone [https://github.com/pruthvi-cs/Drowsiness-Detection-System.git](https://github.com/pruthvi-cs/Drowsiness-Detection-System.git)
   cd Drowsiness-Detection-System
Install the required Python libraries:
```
```bash
pip install -r requirements.txt
Open python_code/drowsiness_detector.py and update the SERIAL_PORT variable to match your ESP32's COM port (e.g., COM5 or /dev/ttyUSB0):
```
Python
SERIAL_PORT = 'COM5' 
🕹️ Usage
Ensure the ESP32 is plugged in and the battery pack is connected to the L298N.

Run the Python script:

Bash
python python_code/drowsiness_detector.py
Position yourself in front of the webcam. The system will track your eyes.

Close your eyes for more than 20 consecutive frames. The system will display a "SLEEPING!" alert on the screen and trigger the ESP32 hardware alarm (Motor spins, Buzzer beeps, LED flashes for 2 seconds).

📁 Repository Structure
Plaintext
```bash
Drowsiness-Detection-System/
├── esp32_controller/
│   └── esp32_controller.ino    # Arduino code for hardware control
├── python_code/
│   └── drowsiness_detector.py  # Computer Vision & Serial script
├── assets/                     # Images, diagrams, and demos
├── requirements.txt            # Python dependencies
└── README.md                   # Project documentation
```
