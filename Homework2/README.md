# Traffic Lights

## Hardware components

* 2 red leds
* 2 green leds
* 1 yellow led
* 1 push button
* 1 buzzer (active buzzer preferably)
* 5 resistors for leds
* 1 resistor for buzzer
* Arduino Uno Board
* breadboard
* connection cables

## Technical Task 

Building  the  traffic  lights  for  a  crosswalk.   
You will use 2 LEDs to represent the traffic lights for people (red and green) and 3 LEDs to represent the traffic lights for cars (red, yellow and green).

The system has the following states:
1. State 1(default, reinstated after state 4 ends): green light for cars,red  light  for  people,  no  sounds. Duration:  indefinite,  changed  by pressing the button.
2. State 2(initiated by counting down 10 seconds after a button press): the  light  should  be  yellow  for  cars,  red  for  people  and  no  sounds. Duration: 3 seconds.
3. State 3(initiated after state 2 ends): red for cars, green for people anda beeping sound from the buzzer at a constant interval. Duration: 10 seconds.
4. State 4(initiated after state 3 ends): red for cars, blinking green for people and a beeping sound from the buzzer, at a constant interval, faster than the beeping in state 3.  This state should last 5 seconds.

## Setup

![setup](https://github.com/alexandraburu23/IntroductionToRobotics/blob/main/Homework2/setup.jpg)

## Video Demo

Video demo can be viewed [here](https://drive.google.com/file/d/1Zg2o1vct7bX0Hb04yaZCIGJq_H1Rxsel/view?usp=drivesdk) .
