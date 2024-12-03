# Snake in Arduino

## Overview

This project recreates the classic game we all know and love: 🐍**Snake**! Using an Arduino Uno R3, a 2x4 button array, and an 8x24 LED matrix, the game displays on the LED matrix, and the user can control the snake's direction using the button array.

## Setup and Installation
1. Wire the components according to the wiring guide.
2. Install the **Arduino IDE** and the required libraries:
   - [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
   - [Max72xxPanel](https://github.com/markruys/arduino-Max72xxPanel?tab=readme-ov-file)
4. Upload the provided file to the **Arduino Uno**.

## How to Play
1. Use the **directional buttons** to control the snake's movement.
2. The goal is to eat **as much** food as possible **without** crashing into walls or the snake's body.
3. Press the **reset** button to restart the game at any point.

## Components

### Hardware
Component | Quantity
:-:|:-:
Arduino Uno R3|1
2x4 Button Array|1
8x24 MAX7219 LED Matrix|1

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

## License
This project is open-source and licensed under the MIT License.
