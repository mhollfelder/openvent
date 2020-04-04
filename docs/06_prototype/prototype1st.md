# First prototype

Please check the status of the prototype [here](#status).

## Introduction

The very first prototype was developed as part of the hackathon #WirvsVirus of the German government.\
It was mainly a proof of concept to show how a mechanical setup could look like.\
The core idea is a belt wrapped around a bag valve mask (also know as Ambu bag) and winded up by a rotor to squeeze the bag.

A video summarizing the results from the hackathon can be found on our official YouTube channel OpenVent [here](https://www.youtube.com/watch?v=LgbF94eOf6w&t=19s
).

<a href="https://www.youtube.com/watch?v=LgbF94eOf6w"><img src="https://img.youtube.com/vi/LgbF94eOf6w/0.jpg" width="300px"></a>

## Idea

The basic idea of this prototype is to use a [bag valve mask](https://en.wikipedia.org/wiki/Bag_valve_mask) in combination with a mechanical setup to compress it.\
A belt is compressing the bag by being wrapped around an axis which is driven by a stepper motor.\
The design and idea is also inspired by the one shown by the [OSV/OpenLung](https://opensourceventilator.ie/) team and which is shown [here](https://www.hackster.io/news/open-source-ventilator-openlung-projects-aim-to-address-the-covid-19-ventilator-shortfall-c7a5ee2f8e58).

## Design files

The design files for the initial prototype can be found [here](https://github.com/mhollfelder/openvent/tree/mechanics/stable/mechanics/00_prototypes/00_firstPrototype).

The basic folder structure is as follows:

We have uploaded the `.stl` files of the initial prototype to the repository.\
If you modify them or use them for additional testing, feel free to create a branch in our repository and work with those files.

The design files are illustrated here in the section [Mechanical and hardware setup](#mechanical-and-hardware-setup). 

## Mechanical and hardware setup

The mechanical design and setup is illustrated here:

<p>
  <img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/1stprototype/v1_design_explosion.jpeg" height="200px">
  <img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/1stprototype/v1_design_assembled.jpeg" height="200px">
  <img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/1stprototype/v1_printer_preview.jpeg" height="200px">
</p>

As you can see above, the motor is directly connected to the axis.\
Moreover, the axis holds the belt which is getting wrapped around it when the motor starts.\
Relaxation of the compressed object will un-wind the belt and relax the whole setup. The assembled real-life prototype is illustrated here:

<p>
  <img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/1stprototype/v1_assembled.jpeg" height="200px">
  <img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/1stprototype/v1_assembled_test.jpeg" height="200px">
</p>

For a first test with a balloon, one NEMA-17 stepper motor with `0.5 Nm` was used with a voltage of `6 V`. Here, the device had problems with compressing the balloon as the power was too low.\
The second test with `12 V` and the same setup showed better results as the balloon got more squeezed.

Here, you can find the two videos:

<a href="https://www.youtube.com/watch?v=LgbF94eOf6w"><img src="https://img.youtube.com/vi/kt0_SyTIqIQ/0.jpg" width="250px"></a>
<a href="https://www.youtube.com/watch?v=LgbF94eOf6w"><img src="https://img.youtube.com/vi/SUNwU-FeAAc/0.jpg" width="250px"></a>

## Software and hardware setup

A simple software driver for Arduino controlling a stepper motor driver has been used.\
Such example sketches can be easily found on the Internet, e.g. here:

* [Easy Driver Examples](https://www.schmalzhaus.com/EasyDriver/Examples/EasyDriverExamples.html)
* [Adafruit stepper tutorial #1](https://learn.adafruit.com/adafruit-motor-shield/using-stepper-motors)
* [Adafruit stepper tutorial #2](https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/using-stepper-motors)
* [Adafruit Arduino lessons](https://learn.adafruit.com/adafruit-arduino-lesson-16-stepper-motors)

Any microcontroller supporting Arduino can be used.

We used an Infineon [XMC microcontroller](https://www.infineon.com/cms/en/product/microcontroller/32-bit-industrial-microcontroller-based-on-arm-cortex-m/) on a [XMC4700 Relax Kit](https://github.com/Infineon/XMC-for-Arduino/wiki/XMC4700-Relax-Kit) wih the [XMC-for-Arduino](https://github.com/Infineon/XMC-for-Arduino) integration.\
As a stepper motor control shield we used the [KIT_XMC1300_IFX9201](https://www.infineon.com/cms/en/product/evaluation-boards/kit_xmc1300_ifx9201/) from Infineon.\
The official software can be found [here](https://www.infineon.com/cms/en/product/evaluation-boards/kit_xmc1300_ifx9201/#!tools), an Arduino integration can be found [here](https://github.com/Infineon/Stepper-Motor-Shield-IFX9201-XMC1300).

## Bill of material

### Mechanics

* 2-piece printed frame (motor-side and backside) 
* 2-piece rotor for motor shaft
* Belt of fibre tape 
* NEMA-17 stepper motor

### Hardware

* [KIT_XMC1300_IFX9201](https://www.infineon.com/cms/en/product/evaluation-boards/kit_xmc1300_ifx9201/)
* [XMC4700 Relax Kit](https://github.com/Infineon/XMC-for-Arduino/wiki/XMC4700-Relax-Kit)
* External power supply

## Advantages and disadvantages

### Advantages

* Most simple design 
* Highly robust
* Perfectly printable
* Almost no friction in the mechanics itself 
* Single-sided or symmetrical pull possible

### Disadvantages

* High torque motor required: due to missing transmission, the torque of the motor is too low
* No continuous compression of the bag valve mask possible
* The design with the belt cannot compress the bag efficiently
  * Force is applied symmetrically 
  * The bag cannot be efficiently compressed as the material itself resists to compression
  * If a buckling occurs, the bag cannot be compressed anymore
* When the device is running with full power over a long time, the heat deforms the material
* Belt size/width determines the required force
* Not well suited for the self-inflating design of the bag valve mask
* Friction of belt on bag valve mask

## Status

:boom:

* [X] INACTIVE
* [ ] ACTIVE

Prototype was built and experimentally verified.\
Due to the disadvantages it is **NOT** further used.\
Current status not recommended to be rebuilt as it is.

## Related prototypes

As this is the first prototype, there are no predecessors and additional related ones existing. 