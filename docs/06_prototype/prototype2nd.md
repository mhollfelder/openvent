# Second prototype

Please check the status of the prototype [here](#status).

## Introduction

The second prototype is the logical development of the first [prototype](./prototype1st.md).\
It is an extension of the first prototype with two pushing levers.

A video summarizing the testing of this prototype can be found on our YouTube channel OpenVent [here]().

<a href="https://www.youtube.com/watch?v=TBD"><img src="https://img.youtube.com/vi/TBD/0.jpg" width="300px"></a>

## Idea

The basic idea of this prototype continues with the [bag valve mask](https://en.wikipedia.org/wiki/Bag_valve_mask) in combination with a mechanical setup to compress it, similar as the first prototype [here](./prototype1st.md).\
A bag valve mask gets squeezed between two tilting levers (similar to a lift bridge).\ 
Two belts attached to the top of each lever end on one lever and are looped around the opposite side lever.\ 
During compression, these belts get winded up by a motor to pull the levers together and relaxation is driven by the bag valve mask itself.\
No further parameters are controlled or gathered, it's a free-wheeling system just trying to compress a bag of air and trying to generate an air-flow.

## Design files

The design files for the initial prototype can be found [here](https://github.com/mhollfelder/openvent/tree/mechanics/stable/mechanics/00_prototypes/00%20secondPrototype).

The basic folder structure is as follows:

```console
00 firstPrototype/
┣ 00_completeSet/   # A complete set for further processing
┣ 01_frame/         # The frame as an outline of the prototype
┗ 02_axis/          # Different motor axis for connecting the motor
```

We have uploaded the `.stl` files of the initial prototype to the repository in the respective `mechanics/stable` branch.\
If you modify them or use them for additional testing, feel free to create a branch in your repository and work with those files.\
Feedback would be very much appreciated and please feed back the changes to the community.

The design files are illustrated in the section [Mechanical and hardware setup](#mechanical-and-hardware-setup). 

## Mechanical and hardware setup

The mechanical design and setup is illustrated here:

<p>
  <img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/1stprototype/v2_design_explosion.jpeg" height="200px">
  <img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/1stprototype/v2_design_assembled.jpeg" height="200px">
</p>

As you can see above, the motor is directly connected to the axis without any transmission.\
Moreover, the axis holds the wires which is getting wrapped around it when the motor starts.\
Relaxation of the compressed object will un-wind the wire and relax the whole setup. The assembled real-life prototype is illustrated here:

<p>
  <img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/1stprototype/v2_assembled_relaxed.jpeg" height="200px">
  <img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/1stprototype/v2_assembled_compressed.jpeg" height="200px">
</p>

The core advantage compared to the first [prototype](./prototype1st.md) is that the compression is done with two cylinders from the side.\
This solves the problem that the belt of the first prototype was symmetrically wrapped around the bag valve mask.\
This introduced additional friction and forces as the bag was symmetrically compressed. Here, the cylinders push from the side with small surfaces only.

For a first test with, one NEMA-17 stepper motor was used again and it was able to compress the bag efficiently.

Here, you can find the two videos:

<a href="https://www.youtube.com/watch?v=TBD"><img src="https://img.youtube.com/vi/TBD/0.jpg" width="250px"></a>
<a href="https://www.youtube.com/watch?v=TBD"><img src="https://img.youtube.com/vi/TBD/0.jpg" width="250px"></a>

## Software and hardware setup

A simple software driver for Arduino controlling a stepper motor driver has been used similar as for the first [prototype](./prototype1st.md).\
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
* 2 levers
* Belt/smooth rope 
* NEMA-17 or NEMA-23 stepper motor

### Hardware

* [KIT_XMC1300_IFX9201](https://www.infineon.com/cms/en/product/evaluation-boards/kit_xmc1300_ifx9201/)
* [XMC4700 Relax Kit](https://github.com/Infineon/XMC-for-Arduino/wiki/XMC4700-Relax-Kit)
* External power supply

## Advantages and disadvantages

### Advantages

* Quite simple design 
* Highly effective and robust
* well printable
* Low friction losses in the mechanics itself 
* Pulley-looping of the belt easily possible
* Cylinder compress bag valve mask efficiently

### Disadvantages

* Friction of optional pulley 
  * works against torque maximization
  * against the achievable max. ventilation frequency 

## Status

:start:

* [ ] INACTIVE
* [X] ACTIVE

Prototype was built and experimentally verified.\
It is a potential candidate for further evaluation and improvements.\

## Related prototypes

The predecessor is the first prototype which can be found [here](./prototype1st.md).