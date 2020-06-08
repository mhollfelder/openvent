# Latest prototype

Please check the status of the prototype [here](#status).

## Introduction

The third prototype is merging the condensed learnings of the first two [prototypes](./README.md).\
In a nutshell, it is overall an extension of the first prototype with one tilting lever that is pulled to squeeze the bag valve mask.

A video summarizing showing this prototype can be found on our YouTube channel OpenVent [here](https://www.youtube.com/watch?v=tE5zFFq62-0).

<a href="https://www.youtube.com/watch?v=tE5zFFq62-0"><img src="https://img.youtube.com/vi/tE5zFFq62-0/0.jpg" width="300px"></a>

## Idea

The basic idea of this prototype sticks to the [bag valve mask](https://en.wikipedia.org/wiki/Bag_valve_mask).
In combination with a mechanical setup to compress it efficiently, it is derived from the first prototype [here](./prototype1st.md).

A bag valve mask gets squeezed between the frame and one tilting lever (similar to a lift bridge) with one side attached to the frame.\
The other side is pulled down by a belt that is winded up by a motor.\ 
During compression, the belt get winded up by a motor to pull the lever bridge down and relaxation is driven by the bag valve mask itself.\
No further parameters are controlled or gathered, it's a free-wheeling system just trying to compress a bag of air and trying to generate an air-flow.

## Design files

The design files for the initial prototype can be found [here](https://github.com/mhollfelder/openvent/tree/mechanics/stable/mechanics/00_prototypes/02_thirdPrototype).

The basic folder structure is as follows:

```console
01_secondPrototype/
┣ 01_frame/         # The frame as an outline of the prototype
┣ 02_axis/          # Motor axis for connecting the motor
┗ 03_tilt/          # The tilt with the lever and cylinders
```

The motor axis is the same one as for the second prototype [here](https://github.com/mhollfelder/openvent/tree/mechanics/stable/mechanics/00_prototypes/01_secondPrototype/02_axis).\
Moreover, the axis of the first prototype can be used as well and they are stored [here](https://github.com/mhollfelder/openvent/tree/mechanics/stable/mechanics/00_prototypes/00_firstPrototype/02_axis).

We have uploaded the `.stl` files of the initial prototype to the repository in the respective `mechanics/stable` branch.\
If you modify them or use them for additional testing, feel free to create a branch in your repository and work with those files.\
Feedback would be very much appreciated and please feed back the changes to the community.

The design files are illustrated in the section [Mechanical and hardware setup](#mechanical-and-hardware-setup). 

## Mechanical and hardware setup

The mechanical design and setup is illustrated here:

<p>
  <img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/3rdprototype/v3_design_explosion.jpeg" height="200px">
  <img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/3rdprototype/v3_design_assembled.jpeg" height="200px">
</p>

As you can see above, the motor is directly connected to the axis without any transmission, `.stl` is stored [here](https://github.com/mhollfelder/openvent/tree/mechanics/stable/mechanics/00_prototypes/02_thirdPrototype/02_axis).\
Moreover, the axis holds the belt which is getting wrapped around it when the motor starts. The other side of the belt is mounted directly to the frame whose `.stl` files are stored in the `01_frame` folder [here](https://github.com/mhollfelder/openvent/tree/mechanics/stable/mechanics/00_prototypes/02_thirdPrototype/01_frame).\
The tilt lever is consisting of two identical side levers `v3_4_vertical_arm.stl` which can be found [here](https://github.com/mhollfelder/openvent/tree/mechanics/stable/mechanics/00_prototypes/02_thirdPrototype/03_tilt) and a top lever which can be found there as well.\
Additionally, one punch block `v3_1_punch_block.stl` can be found there as well which should be mounted to the top lever to enhance compression of the bag.\
Relaxation of the compressed object will un-wind the wire and relax the whole setup. 

The assembled real-life prototype is illustrated here:

<p>
  <img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/3rdprototype/v3_assembled_test_relaxed.jpeg" height="250px">
  <img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/3rdprototype/v3_assembled_test_compressed.jpeg" height="250px">
</p>

The core advantage compared to the first two prototypes [one](./prototype1st.md) and [two](./prototype2nd.md) is that the compression is mechanically well designed for the bag valve mask. This design solves various pitfalls of the first two prototypes.

First tests were carried out with different settings.

### First test

* Full load with closed pipe of bag (overpressure value `60 cmH2O`)
* `25 cycles/min` 
* Ratio 1:1 
* NEMA-17 
* 12 V 
* 2.5 A 
* Halfstep 
* Frequency of `750 1/min` 
* Travel of `900 k`

Here, you can find the video:

<a href="https://youtu.be/1XlCXz6gViw"><img src="https://youtu.be/1XlCXz6gViw/0.jpg" width="250px"></a>

### Second test

* No load with open pipe of bag
* `18 cycles/min` 
* Ratio 1:4 
* NEMA-17
* 8 V
* 2.8 A 
* Halfstep 
* Frequency of `750 1/min` 
* Travel of `900 k`

Here, you can find the video:

<a href="https://youtu.be/1XlCXz6gViw?t=83"><img src="https://youtu.be/1XlCXz6gViw/0.jpg" width="250px"></a>

### Third test

* Full load with narrow pipe of bag (overpressure value up to `60 cmH2O`)
* `49 cycles/min` 
* Ratio 1:1 
* NEMA-23
* 12 V
* 2.8 A 
* Halfstep 
* Frequency of `1400 1/min` 
* Travel of `900 k`

Here, you can find the video:

<a href="https://youtu.be/1XlCXz6gViw?t=163"><img src="https://youtu.be/1XlCXz6gViw/0.jpg" width="250px"></a>

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

* 2 piece printed frame (motor-side and backside) 
* 1 piece tilting bridge top
* 2 side levers
* Punch block
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
* Well printable
* Low friction losses in the mechanics itself 
* Pulley-looping of the belt easily possible
* Cylinder compress bag valve mask efficiently

### Disadvantages

* Friction of optional pulley 
  * Works against torque maximization
  * Works against the achievable max. ventilation frequency 

## Status

:start:

* [ ] INACTIVE
* [X] ACTIVE

Prototype was built and experimentally verified.\
It is a potential candidate for further evaluation and improvements.\

## Related prototypes

The predecessor is the first prototype which can be found here with [one](./prototype1st.md) and [two](./prototype2nd.md).