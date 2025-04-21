# SO2Predictor-TinyML
# TinyML SO2 Removal Prediction on ESP32

This project implements a TensorFlow Lite model on an ESP32 microcontroller to predict SO2 removal efficiency based on 4 input features.

---

## Project Overview
- Load a pre-trained TFLite model
- Input 4 float values
- Predict SO2 removal efficiency
- Output results via Serial Monitor

---

## Hardware Requirements
- ESP32 DevKit (WROOM-32 based)
- USB Cable
- Computer (Arduino IDE 1.8.19)

---

## Software Requirements
- Arduino IDE
- EloquentTinyML Library
- TensorFlowLite_ESP32 Library (tflm_esp32)

---

## How It Works
1. Flash the code to your ESP32 using Arduino IDE.
2. Open Serial Monitor at **115200 baud**.
3. Send 4 comma-separated floats like: value1,value2,value3,value4

---

## Acknowledgements
This project was modified and adapted based on code from [Gimhan-AI's ML-ESP32S3-ArduinoIDE repository](https://github.com/Gimhan-AI/ML-ESP32S3-ArduinoIDE)
Special thanks for providing an excellent starting point for TinyML deployment on ESP32 devices.
Modifications were made to adapt the model input structure, inference flow, and TensorFlow ops registration
