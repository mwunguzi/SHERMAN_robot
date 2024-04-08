# Remote Controlled Sherman tank robot
This repository contains the code and documentation for a remote-controlled sherman tank robot project. The project utilizes an Arduino Nano, a joystick, radio frequency modules, and a motor controller to enable remote control of a tank robot chassis.

## components Used
* Arduino Nano
* Arduino MEga 2560
* Joystick
* nRF 24L01 Radio Frequency (RF) Module (x2)
* XY160D motor controller

## Description
The project aims to create a remote-controlled robot capable of movement in various directions with adjustable speed. The joystick serves as the input device for controlling the movement of the robot. The Arduino Nano interprets the joystick's position and transmits corresponding signals to the robot via RF modules. These signals control both the speed and direction of the robot's movement.

## Features 
* Control the tank robot remotely using a joystick.
* Precise robot control over speed and direction.
* RF modules provide a communication range of up to 1km.

## Setup 
1. Upload the Arduino sketch (Sherman_transmitter.ino) to the Arduino Nano.
2. Upload the Arduino sketch (SHERMAN_robot.ino) to the Arduino Mega.
3. Power on the tank robot and the remote controller.
4. Use the joystick to control the movement of the tank robot.

## Usage
* Move the joystick forward/backward to control the forward/backward movement of the robot.
* Move the joystick left/right to control the rotation of the robot.
* Adjust the joystick's position to control the speed of the robot.
