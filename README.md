# CanSat

## Overview

CanSat, short for "Can Satellite," is a type of educational project that involves the design, construction, and launch of a small satellite contained within the size and shape of a typical soda can. This initiative aims to provide students with practical experience in various fields, including aerospace engineering, electronics, and data analysis.

## Components

A typical CanSat consists of several key components:

- **Canister:** The outer shell, usually resembling a standard soda can, contains the entire satellite.

- **Sensors:** CanSats are equipped with various sensors to measure environmental parameters such as temperature, pressure, humidity, and sometimes even atmospheric composition.

- **Communication System:** CanSats are designed to transmit data to a ground station, allowing students to analyze the collected information.

- **Parachute:** To ensure a safe descent, CanSats often include a parachute for a controlled landing.

## Objectives

The primary objectives of CanSat projects include:

1. **Educational Experience:** Provide students with a hands-on learning experience in satellite design, electronics, and programming.

2. **Data Collection:** Gather data from the sensors during the CanSat's flight to analyze and draw conclusions about the atmosphere or environment.

3. **Teamwork and Problem-Solving:** Encourage teamwork and problem-solving skills as students work together to overcome challenges in the design and launch process.

4. **Real-world Application:** Mimic real-world satellite launches in a smaller, more accessible scale for educational purposes.

## Launch and Recovery

CanSats are typically launched using rockets or balloons, simulating the launch and descent phases of a real satellite. The parachute aids in the safe recovery of the CanSat after it completes its mission.

## Applications

While CanSats are primarily educational tools, the skills and knowledge gained through these projects can be applied to various fields, including aerospace engineering, physics, and data science.

# CanSat Project

This repository contains the code and documentation for our CanSat project, designed for participation in CanSat competitions. The CanSat is equipped with an Arduino-based Onboard Computer (OBC) and an ESP32-Cam for vision capabilities. Data transmission of this project is internet based, making it an IoT project.

## Project Components

### 1. Arduino Mega

The Arduino Mega serves as the core of our Onboard Computer (OBC), managing and controlling various sensors and modules.

### 2. BMP180 (Weather Condition Measurements)

The BMP180 sensor is utilized for precise weather condition measurements during the CanSat's flight.

### 3. GY-271 (Magnetic Electronic Compass)

The GY-271 module provides accurate magnetic orientation data, contributing to the CanSat's navigation capabilities.

### 4. Neo M8 Series (GPS Module)

The Neo M8 series GPS module enables precise location tracking and contributes to the CanSat's overall navigation system.

### 5. GY-521 MPU6050 (Gyroscope)

The GY-521 MPU6050 gyroscope enhances the CanSat's stability and control by providing accurate orientation data.

### 6. MicroSD Card Module

The MicroSD card module facilitates the storage of data on an SD card.

### 7. ESP32-Cam

The ESP32-Cam module is responsible for the vision capabilities of the CanSat, leveraging internet connectivity for real-time image processing.

## Getting Started

### Prerequisites

- Arduino IDE installed
- [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32) installed
- Libraries included

### Installation

1. Clone this repository: `git clone https://github.com/PouyaNorouzi/CanSat.git`
2. Open the Arduino IDE.
3. Load the Arduino sketch from the `src` directory.
4. Connect the CanSat hardware components as per the provided schematic.

### Usage

1. Upload the code to the Arduino Mega.
2. Power up the CanSat.
3. Monitor the CanSat's performance through the serial monitor in the Arduino IDE.
4. For ESP32-Cam functionality, follow additional instructions in the `esp32-cam/README.md` file.

## Customize

Feel free to customize the code according to your requirements. You can add features, improve the user interface, or integrate additional sensors.

## Troubleshooting

If you encounter issues, check the serial monitor for error messages. Make sure your connections are correct and your WiFi credentials are accurate.

## Contributing

Contributions are welcome! If you have ideas for improvements or find bugs, please open an issue or submit a pull request.
