# Hungry Crab
Hungry Crab is an open source project which consists of a medium sized hexapod that can pick up small objects from the floor and transport them to a nearby location.

## CAD Files
* Pending upload.

<img src="cad-image.JPG" alt="cad-image" width="auto" style="display: block;margin-left: auto; margin-right:auto;" title="CAD image of current Hungry Crab"/>

## Companion App

This project includes an app to control the Hungry Crab with serial communication via Bluetooth.

<img src="hungry-crab-icon.jpeg" alt="app-icon" width="auto" style="display: block;margin-left: auto; margin-right:auto;" title="Icon of the Hungry Crab Companion App"/>

<img src="homescreen-app.jpeg" alt="home-screen-app" width="auto" style="display: block;margin-left: auto; margin-right:auto;" title="Home Screen of the Hungry Crab Companion App"/>



## Necessary Electronics
* 1  x NodeMCU-32S Microcontroller
* 2  x 18650 Batteries *(recommendation: INR18650-35E SAMSUNG)*
* 18 x MG90S servomotors
* 2  x 12 channel servomotor drivers PCA9685
* 1  x UBEC @ 5V/5A
* 2  x UBEC @ 6V/3A
* 1  x 28BYJ-48 Stepper motor

For now, the following rough electronic diagram lays out how the different components are connected:

<img src="electronic-diagram.JPG" alt="electronic-diagram" width="auto" style="display: block;margin-left: auto; margin-right:auto;" title="Electronic Diagram of Hungry Crab"/>

## Hungry Crab Capabilities

An example of each capability will be shown but bear in mind that the GIFs are speed up 2x.

* Walk in all directions

<img src="crab-moving.gif" alt="Crab Moving" height="300" style="display: block;margin-left: auto; margin-right:auto;" title="Crab Moving"/>

* Rotate Clockwise
* Rotate Counter Clockwise

<img src="crab-rotating.gif" alt="Crab Rotating" height="300" style="display: block;margin-left: auto; margin-right:auto;" title="Crab Rotating"/>


* Change height
* Open and close mouth to pick up objects

<img src="pick-up.gif" alt="Pick Up Gomboc" height="300" style="display: block;margin-left: auto; margin-right:auto;" title="Pick Up Gomboc"/>
