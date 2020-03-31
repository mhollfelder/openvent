# First prototype

## Introduction

The first prototype was developed as part of a hackathon #WirvsVirus of the German government.\
It was mainly a proof of concept to show how a mechanical setup could look like.

A video summarizing the hackathon can be found on our official YouTube channel [here](https://www.youtube.com/watch?v=LgbF94eOf6w&t=19s
).

[<img src="https://img.youtube.com/vi/LgbF94eOf6w/0.jpg">](https://www.youtube.com/watch?v=LgbF94eOf6w)

## Idea

The basic idea of this prototype is to use a [bag valve mask](https://en.wikipedia.org/wiki/Bag_valve_mask) in combination with a mechanical setup to compress it.\
A belt is compressed by being wrapped around an axis which is driven by a stepper motor.\
The design and idea is inspired by the one developed by the [OSV/OpenLung](https://opensourceventilator.ie/) team and which is shown [here](https://www.hackster.io/news/open-source-ventilator-openlung-projects-aim-to-address-the-covid-19-ventilator-shortfall-c7a5ee2f8e58).

## Design files

The design files for the initial prototype can be found here:

We have uploaded the `.stl` files of the initial prototype to the repository.\
If you modify them or use them for additional testing, feel free to create a branch in our repository and work with those files.

## Mechanical and hardware setup

The mechanical design and setup is illustrated here:

<p>
  <img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/1stprototype/v1_stepper_axis.jpeg" height="200px">
  <img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/1stprototype/v1_motor_with_belt.jpeg" height="200px">
</p>

As you can see above, the motor is directly connected to the axis.\
Moreover, the axis holds the belt which is getting wrapped around it when the motor starts.\
Relaxation of the compressed object will un-wind the belt and relax the whole setup. The assembled device is illustrated here:

<p>
  <img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/1stprototype/v1_assembled.jpeg" height="200px">
  <img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/1stprototype/v1_assembled_test.jpeg" height="200px">
</p>

For a first test with a balloon, one NEMA-17 stepper motor with `0.5 Nm` was used with a voltage of `6 V`. Here, the device had problems with compressing the balloon as the power was too low.\
The second test with `12 V` and the same setup showed better results as the balloon got more squeezed.

Here, you can find the two videos:

## Software setup

## Bill of material

## Advantages and disadvantages

* When the device is running with full power over a long time, the head deforms the material
* Due to to no transmission, the torque from the motor is too low
* No continuous compression of the bag valve mask possible
* The design with the belt cannot compress the bag efficiently
  * Force is applied symmetrically 
  * The bag cannot be efficiently compressed as the material itself resists to compression
  * If a buckling occurs, the bag cannot be compressed anymore

## Related prototypes

As this is the first prototype, there are no predecessors and additional related ones existing. 

