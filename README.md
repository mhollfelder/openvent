# OpenVent project

## Folder structure

```console
OpenVent/
┣ design/           # Overall design files like pictures, etc.
┣ documentation/    # Documentation of the whole project
┣ mechanic/         # All files related to the mechanical design
┣ software/         # All files related to the software
┣ LICENSE.md        # The license file here
┗ README.md         # This README document
```

## Project description

This repository contains generic information about an open-source ventilator project.

## Current status

Right now, a prototype is in development with a bag valve mask, a 3D printed fixture and a motor.

## Development flow

We have a Slack channel for exchange on the overall development and exchange on the project itself.
Moreover, we use GitHub [projects](https://github.com/mhollfelder/openvent/projects?query=sort%3Aname-asc+) to track the process, requirements, etc.

If you want to contribute, please open an issue, create a pull request or ping us at contact.openvent@gmail.com.

## Contributors

### Core team

The core team which started this project:

* [Mahmoud Ismail](https://github.com/mahmoudgo)
* [Nico Kelling](https://github.com/nicokelling)
* [Daniel Gernert](https://github.com/DanielGernert)
* [Alexander Maier](https://github.com/alex-km)
* [Manuel Hollfelder](https://github.com/mhollfelder)

## Similar projects

Here, we will add a list of similar projects which are worth being checked out.


## Introduction
### The Human Lung 

A human lung is a complex organ responsible for gas exchange between the body and the environment. The lung is mainly composed of two types of airways (conductive and respiratory airways), alveoli, and blood vessels.

- Conductive airways: The main role of the conductive airways is to transport the bulk of air from and into the lung. No gas exchange (perfusion) takes place in the conductive airways. This is why conductive airways are also called dead space.
  > Why is this information important? because mechanically, conductive airways are responsible for the resistance to the flow. Thus protecting the lung from high flowrates while inflation and from collapsing during deflation.

- Respiratory airways: These airways differ from the conductive airways by containing alveoli on their walls. Perfusion starts taking place at the respiratory airways. The air at this level is trasported via diffussion rather than conduction.
  > Why is this important? during respiration, the air needs to sit long enough in the lung for oxygen to diffuse from the tips of the conductive airways into respiratory airways. Same for carbon dioxide to diffuse from the repiratory airways into the conductive airways. This set the criteria for picking the ventilation periods for inhaling and exhaling.

- Alveoli: At the tip and the walls of the respiratory airways, alveoli are located. The group of alveoli form an acinus, which in return form the sponge like consistency of the lung. Each alveoli is surrounded by blood vessels. The common wall between the alvoelus and the blood capillaries offers the medium for oxygen and carbon dioxide be exchanged.
  > Why is this important? Diseases such Covid-19 lead SARS (Severe Acute Respiratory Syndrome) or ARDS (Acute Respiratory Distress Syndrome) via the inflamation in the lung. Which means water starts building up in the alveoli. Thus reducing or preventing the perfusion of the lung. This is a critical stage, where patients will need to be put on assistant/mechanical ventilation. Physicians will use different methods to keep the alveoli open, recruit the collapesed ones and bring the inflation down, all while not damaging further the alveolar wall.

### Mechanical Ventilators
Mechanical ventilator is a medical device used to assist or replace spontaneous breathing. 

#### Mechanical Ventilator Functionalities
In the following section we list the main functionalities of a mechanical ventilator. We also aim to translate these functionalities into design requirement.
As we aim in this work to address crutial need for supporting the high demand for mechanical ventilators during crisis times. The following functionalities aim to support the physians with the right tools to treat patients suffering form SARS & ARDS:

 - Tidal Volume: Is the volume of ventilated air at each reporatory cycle. An average adult at rest would need any where between 500 to 800mL of tidal volume each respiratory cycle to properly ventilate the lung. 
   > From **requirements** point of view, this means the ventilator need to:
   > * pump up to 800mL of air
   > * control the pumped volume
   > * monitor and report if the pumped volume exceeded to dropped below the critical tidal volume

 - Pressure: The pressure produced by the lung ventilators is responsibe for driving the air into the lung and controlling the rate of exhaling of the lung. 
   > From requirements point of viwe, this means ventilators need to:
   > * control the pumping pressure
   > * monitor and report if the pressure exceeds critical levels, to protect the lung from VALI (Ventilator-Associated Lung Injury)
   > * control the PEEP (Peak End Expiratory Pressure), which protects alveoli from collapsing

 - Fraction of inspired Oxygen (FIO2): To protect the lung from VALI, the physicians could choose to ventilate the lung with lower tidal volume but higher oxygen content. For that the ventilator is connected to an oxygen intake.
   > From requirements point of view:
   > * The ventilator needs to control the mixure fracture of oxygen and air, which will be ventilated into the lung
   > * Monitor the concentration of oxygen in the pumped gas. This value is used to adjust the FIO2 and to compare it with the oxygen level in the blood. Which in return is an important indicator of oxyen transfusion.

 - Expired Carbon-Dioxide: Carbon dioxide is toxic for humans. The concentration of the expired CO2 is an indicator if the patients lung is being well perfused and ventilated. Physicians track CO2, for example, to know if the patient is still alive. 
   > From the requirements point of view this means:
   > * Monitor and report the CO2 concentration of exhaled air.