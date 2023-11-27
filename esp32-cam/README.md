# ESP32-CAM Internet-based System

## Overview

This project utilizes the ESP32-CAM module to create a simple internet-based system. The ESP32-CAM captures images or streams video and makes it accessible over the internet.

## Features

- Capture and store images remotely.
- Stream live video over the internet.
- Customizable settings for image quality, resolution, and more.
- Access the system from any device with an internet connection.

## Getting Started

### Prerequisites

- Arduino IDE installed.
- ESP32 board support installed in Arduino IDE.
- ESP32-CAM module.

### Installation

1. Clone this repository or download the ZIP file.

2. Open the Arduino IDE.

3. Install the required libraries:
   - [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
   - [ESPAsyncTCP](https://github.com/me-no-dev/ESPAsyncTCP)

4. Open the `ESP32CAM.ino` file in the Arduino IDE.

5. Set up your WiFi credentials in the code.

6. Create an API Key in your google account

7. Add key to the code

8. Add source and destination emails

9. Select the correct board and port in the Arduino IDE.

10. Upload the code to your ESP32-CAM.

## Usage

1. After uploading the code, open the Serial Monitor in the Arduino IDE to get the ESP32-CAM's IP address.

2. Enter the IP address in your web browser to access the web interface.

3. Configure settings such as image quality, resolution, etc.

4. Start capturing images or streaming video.
