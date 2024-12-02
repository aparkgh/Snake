# Snake

## Overview

This project recreates the classic Snake Game using an Arduino Uno R3, a 2x4 button array, and an 8x24 LED matrix. The game displays on the LED matrix, and the user can control the snake's direction using the button array.

## Setup and Installation
1. Wire the components according to the wiring guide.
2. Install the required libraries:
   - Adafruit GFX Library
   - Max72xxPanel
3. Upload the provided code to the Arduino Uno.

## How to Play
The **snake** is controlled using the button array:

1. Use the arrow buttons to control the snake's movement.
2. The goal is to eat as much food as possible without crashing into walls or the snake's body.
3. When the game ends, press the reset button to restart the game.

## Components
### Hardware
Component | Quantity
:-:|:-:
Arduino Uno R3|1
2x4 Button Array|1
8x24 MAX7219 LED Matrix|1

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

## License
This project is open-source and licensed under the MIT License.
