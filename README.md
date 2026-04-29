# PELS_Plant_Monitor_Workshop

This Arduino project uses a soil moisture sensor and an OLED display to show the current moisture level of a plant. The display includes an animated flower face that changes mood depending on how dry or wet the soil is.

# Features
- Reads soil moisture using an analog soil sensor
- Displays moisture percentage on an OLED screen
- Shows raw sensor value for testing and calibration
- Animated blinking flower face
- Flower mood changes based on moisture level:
  - Sad: the soil is dry and needs water
  - Okay: soil moisture is in a normal range
  - Happy: soil is wet

# Hardware Used
- Arduino Nano
- Soil moisture sensor
- 128x64 OLED display
- Jumper wires
- Breadboard
- USB cable for programming and power

# Libraries Required
Install these libraries in the Arduino IDE:
- `Wire`
- `Adafruit_GFX`
- `Adafruit_SSD1306`

# Pin Connections
- Soil Moisture Sensor Signal:  A0
- OLED SDA: A4 
- OLED SCL: A5
- OLED VCC: 5V
- OLED GND: GND

# How It Works
The soil moisture sensor sends an analog value to the Arduino. The Arduino maps this raw value into a percentage from 0% to 100%.
