# Week 2

The homework for this week was to create a switch where a button press trigger a state change for an LED lamp.

Here is my setup:

![img](assets/setup.JPG)

## Materials Used
- 1x Arduino Uno
- 1x Breadboard
- 1x LED
- 1x Push Button
- 1x Resistor 220
- 1x Resistor 10k

## Circuit

![Schematic](assets/schematic.png)

## Code

I started with the Arduino [Button example](http://www.arduino.cc/en/Tutorial/Button) and modified it with concepts taken from the [Debounce Tutorial](https://www.arduino.cc/en/Tutorial/Debounce).  

After getting the basic switch right, I added a Modulo condition to apply a blinking effect to the LED.

[See Arduino.ino for the code.](Arduino/Arduino.ino)

## Demos

The following videos show the setup in action:

[![Preview](assets/Switch.png)](https://vimeo.com/232496341/9052fb2db1)

[![Preview](assets/Switch-blink.png)](https://vimeo.com/232496407/cd38ba85a0)
