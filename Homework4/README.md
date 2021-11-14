# 4-digit 7-segments display control with shift register and joystick

## Hardware components

* 4-digit 7-segments display
* 74hc595 shift register
* joystick
* 3 330 ohms resistors
* connection cables
* Arduino Uno Board
* 1 big breadboard

## Technical Task 

First state: you can use a joystick axis to cycle through the 4 digits; using the other axis does nothing. A blinking decimal point shows the current digit position. When pressing the button, you lock in on the selected digit and enter the second state.  

Second state: the decimal point stays always on, no longer blinking and you can no longer use the axis to cycle through the 4 digits. Instead, using the other axis, you can increment or decrement the number on the current digit.  Pressing the button again returns you to the previous state.  

Observation : you must increment the number for each joystick movement - it should not work continuosly if you keep the joystick in one position.

## Setup

![setup](https://github.com/alexandraburu23/IntroductionToRobotics/blob/main/Homework4/setup.jpg)

## Video Demo

Video demo can be viewed [here](https://drive.google.com/file/d/1lNn6UG6Nsp7gszJBQVkoHtf0miJ4X_1B/view?usp=sharing) .
