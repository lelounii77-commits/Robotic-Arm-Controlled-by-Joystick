# Arduino-Based Robotic Arm Controlled by Joystick

Assignment 1

## Overview

This project demonstrates the design and implementation of a simple robotic arm built with an Arduino microcontroller. The arm is controlled using a joystick module, allowing the user to move it in different directions. Servo motors simulate joint movements similar to a real robotic arm.

## Objective

- Build a basic robotic arm using servo motors
- Control the arm using a joystick
- Understand how Arduino interacts with input and output devices

## Components

| Component | Quantity |
|---|---|
| Arduino UNO | 1 |
| Breadboard | 1 |
| Servo Motors | 2-4 (depending on arm design) |
| Joystick Module | 1 |
| Jumper Wires | As needed |
| USB Cable (for programming) | 1 |
| External Power Supply (optional, recommended for servos) | 1 |

## Working Principle

The joystick acts as an input device and sends analog signals to the Arduino, representing movement along the X and Y axes.

When the joystick is moved:

1. The Arduino reads the analog values
2. Converts them into angle values
3. Sends signals to the servo motors
4. The servo motors rotate based on these signals
5. This movement controls different parts of the robotic arm (base, joint, grip, etc.)

## Circuit Description

- The joystick has 5 pins: VCC, GND, VRx, VRy, and SW
- VRx and VRy are connected to Arduino analog pins (A0 and A1)
- Servo motors are connected to digital PWM pins (D9, D10)
- Power (5V) and Ground (GND) are shared across components

| Joystick Pin | Arduino Pin |
|---|---|
| VCC | 5V |
| GND | GND |
| VRx | A0 |
| VRy | A1 |
| SW | D2 (optional) |

| Servo | Arduino Pin |
|---|---|
| Base | D9 |
| Grip / Joint | D10 |

## Software

The Arduino is programmed using the Arduino IDE. The sketch is available in [`robotic_arm_joystick.ino`](./robotic_arm_joystick.ino).

Basic steps:

1. Read joystick values using `analogRead()`
2. Map values to servo angles (0-180 degrees)
3. Use the `Servo` library to control the motors

### Required Library

- `Servo.h` (included with the Arduino IDE by default)

### How to Run

1. Open `robotic_arm_joystick.ino` in the Arduino IDE
2. Connect the components as described in the Circuit Description section
3. Select the correct board (Arduino UNO) and port under **Tools**
4. Upload the sketch
5. Open the Serial Monitor (9600 baud) to view live joystick and servo values
6. Move the joystick to control the arm

## Applications

- Robotics learning and education
- Industrial automation basics
- Remote-controlled systems
- Pick-and-place robotic systems

## Advantages

- Easy to build and low cost
- Simple control using a joystick
- Good introduction to robotics and automation

## Conclusion

This project successfully demonstrates how a robotic arm can be controlled using an Arduino and a joystick. It helps in understanding basic robotics concepts such as motor control, signal processing, and microcontroller programming.

## Team

| Name |
|---|
| Layan Alfares |
| Shmokh Aljomah |
| Dana Alsubaie |
| Maha Alhudaybi |
