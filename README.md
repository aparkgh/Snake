# Snake Game on Arduino

## Overview

This project recreates the classic Snake Game using an Arduino Uno R3, a 2x4 button array, and an 8x24 LED matrix. The game displays on the LED matrix, and the user can control the snake's direction using the button array.

## Components
### Hardware
Component | Quantity
:-:|:-:
Arduino Uno R3|1
2x4 Button Array|1
8x24 LED Matrix|1

### Libraries Used
1. [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
2. [Max72xxPanel](https://github.com/markruys/arduino-Max72xxPanel?tab=readme-ov-file)

## Wiring Guide
### LED Matrix
Pin | Connection
:-:|:-:
VCC|5V
GND|GND
DIN|Pin 11
CS|Pin 10
CLK|Pin 13
### Button Array
Button | Connection
:-:|:-:
Up|5V
Down|Pin 3
Left|Pin 4
Right|Pin 5
Reset|Pin 6
