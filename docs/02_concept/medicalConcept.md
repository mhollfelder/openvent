# Medical concept

## Introduction
### The Human Lung 

<p><img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/upper_tract.svg?sanitize=true" alt="System overview" height="300px"/>
<img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/ventilatory_system_weibel.svg?sanitize=true" alt="System overview" height="300px"/></p>

A human lung is a complex organ responsible for gas exchange between the body and the environment. The lung is mainly composed of two types of airways (conductive and respiratory airways), alveoli, and blood vessels.

- Conductive airways: The main role of the conductive airways is to transport the bulk of air from and into the lung. No gas exchange (perfusion) takes place in the conductive airways. This is why conductive airways are also called dead space.
  > Why is this information important? because mechanically, conductive airways are responsible for the resistance to the flow. Thus protecting the lung from high flowrates while inflation and from collapsing during deflation.

- Respiratory airways: These airways differ from the conductive airways by containing alveoli on their walls. Perfusion starts taking place at the respiratory airways. The air at this level is transported via diffusion rather than conduction.
  > Why is this important? during respiration, the air needs to sit long enough in the lung for oxygen to diffuse from the tips of the conductive airways into respiratory airways. Same for carbon dioxide to diffuse from the respiratory airways into the conductive airways. This set the criteria for picking the ventilation periods for inhaling and exhaling.

- Alveoli: At the tip and the walls of the respiratory airways, alveoli are located. The group of alveoli form an acinus, which in return form the sponge like consistency of the lung. Each alveoli is surrounded by blood vessels. The common wall between the alveolus and the blood capillaries offers the medium for oxygen and carbon dioxide be exchanged.
  > Why is this important? Diseases such Covid-19 lead SARS (Severe Acute Respiratory Syndrome) or ARDS (Acute Respiratory Distress Syndrome) via the inflammation in the lung. Which means water starts building up in the alveoli. Thus reducing or preventing the perfusion of the lung. This is a critical stage, where patients will need to be put on assistant/mechanical ventilation. Physicians will use different methods to keep the alveoli open, recruit the collapsed ones and bring the inflation down, all while not damaging further the alveolar wall.

### Mechanical Ventilators
Mechanical ventilator is a medical device used to assist or replace spontaneous breathing. 

#### Mechanical Ventilator Functionalities
In the following section we list the main functionalities of a mechanical ventilator. We also aim to translate these functionalities into design requirement.
As we aim in this work to address crucial need for supporting the high demand for mechanical ventilators during crisis times. The following functionalities aim to support the physicians with the right tools to treat patients suffering form SARS & ARDS:

 - Tidal Volume: Is the volume of ventilated air at each respiratory cycle. An average adult at rest would need any where between 500 to 800mL of tidal volume each respiratory cycle to properly ventilate the lung. 
   > From **requirements** point of view, this means the ventilator need to:
   > * pump up to 800mL of air
   > * control the pumped volume
   > * monitor and report if the pumped volume exceeded to dropped below the critical tidal volume

 - Pressure: The pressure produced by the lung ventilators is responsible for driving the air into the lung and controlling the rate of exhaling of the lung. 
   > From requirements point of view, this means ventilators need to:
   > * control the pumping pressure
   > * monitor and report if the pressure exceeds critical levels, to protect the lung from VALI (Ventilator-Associated Lung Injury)
   > * control the PEEP (Peak End Expiratory Pressure), which protects alveoli from collapsing

 - Fraction of inspired Oxygen (FIO2): To protect the lung from VALI, the physicians could choose to ventilate the lung with lower tidal volume but higher oxygen content. For that the ventilator is connected to an oxygen intake.
   > From requirements point of view:
   > * The ventilator needs to control the mixture fracture of oxygen and air, which will be ventilated into the lung
   > * Monitor the concentration of oxygen in the pumped gas. This value is used to adjust the FIO2 and to compare it with the oxygen level in the blood. Which in return is an important indicator of oxygen transfusion.

 - Expired Carbon-Dioxide: Carbon dioxide is toxic for humans. The concentration of the expired CO2 is an indicator if the patients lung is being well perfused and ventilated. Physicians track CO2, for example, to know if the patient is still alive. 
   > From the requirements point of view this means:
   > * Monitor and report the CO2 concentration of exhaled air.

## Medical Requirements
### Parameters to be Recorded
These parameters are to be shown on a monitor:
| Parameters    | Value or Range (Tolerance)                           | Comment                                      |
|---------------|------------------------------------------------------|----------------------------------------------|
| PEEP          | 5 - 20 cmH2O (xx)                                    | Peak End Expiratory Pressure, is measured at the end of the respiration cycle|
| V_T            | xx (xx)      | Tidal volume. Is the total volume pumped/inspired during the inhalation period  |
| Respiratory rate <br> (RR) | 8 - 40/ min                             | |
| P_peak          | up to 60 cmH2O (xx) | peak pressure (usually capped by the safety valve of the Ambu Bag) |
| Inspiration to expiration rate | 1:2 - 1:4   | Must be adjustable |
| P_plat       | up to 60cmH2O                                        | Plateau pressure (usually capped by the safety valve of the Ambu Bag) |
| Exhaled volume | record the expired volume   | Patients during assist control get part of the tidal volume from other channels such as the exhalation port |
| Exhaled CO2 | measure expired CO2       | The exhaled CO2 is indicator: <br>  Tissular production of CO2 <br> CO2 transport in the venous system to the pulmonary arteries <br> CO2 elimination by the lungs |
| P_0.1           |                                                      | During assist control, the pressure generated 100ms after onset of inspiratory effort|
| PTP/min           |                                                      | During assist control, Pressure Time Product per minute |


### Parameters to be Controlled

| Parameters    | Value or Range                                       | Comment                                      |
|---------------|------------------------------------------------------|----------------------------------------------|
| Modes         | Volume control <br> Pressure control <br> Assist control|                               |
| Alarms        | Fails <br> pressure peaks <br> Lower tidal volume              | if the devices stops working <br> If the plateau pressure exceeds maximum allowed pressure (during volume control mode) <br> if the tidal volume is lower than minimum allowed tidal volume (during pressure control mode)|
| Rate          | 8 - 40 <br> 10 - 40 breaths per minute      | Must be adjustable <br> in assist control, only if the patient cannot breath less than assigned rate  |
| Tidal Volume  | 200 - 800 mL per ventilation | Must be adjustable |
| PEEP          | 5 - 20 cmH2O per ventilation | Must be adjustable |
| Inspiration to expiration rate | 1:2 - 1:4   | Must be adjustable |
| FiO2  | 30-100%       | Ventilator needs to be connectable to Oxygen intake|


Modes:
- Assist control/ a.k.a continuous mandatory ventilation (AMV))
 <p><img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/Assist_control_mode.svg?sanitize=true" alt="System overview" height="600px"/><p>

- Volume control
 <p><img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/volume_control_mode.svg?sanitize=true" alt="System overview" height="600px"/><p>
- Pressure control
 <p><img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/Pressure_control_mode.svg?sanitize=true" alt="System overview" height="600px"/><p>

# References
- The Basics of respiratory mechanics: ventilator-derived parameters https://www.ncbi.nlm.nih.gov/pmc/articles/PMC6212352/pdf/atm-06-19-376.pdf 
- Introduction to mechanical ventilation & ventilation modes https://www.youtube.com/watch?v=gk_Qf-JAL84
- CO2 measurement at the mouth level https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3182669/
- Reduced Dimensional Modeling of the Entire Human Lung https://mediatum.ub.tum.de/doc/1197313/1197313.pdf
