---
useMath: true
---
# Physical concept

## Motor Requirements and Analysis
In this analysis we will estimate how much energy and power it takes to ventilate a lung. This information will us understand what type of motor power rate the ventilator requires.
For simplicity we will consider the following assumptions:
  - The lung is being ventilated withing the linear mechanical parameters windows. In other words, the lung compliance is constant.
  - The most extreme conditions for the motor is when the motor needs to generate pressure of 60 cmH2O (This assumption is valid, since the safety pressure release valves in Ambu Bags usually are triggered at 60cmH2O)
  - The maximum volume of air with which the lung is being ventilated is 800mL
  - The 800mL are pumped into the lung within 1 second

As such we can estimate the lung compliance as:
<!--$$C = \frac{Delta V }{ \Delta P}$$-->
<div class="math">
\begin{equation}
  C = \frac{\Delta V}{\Delta P}  
\end{equation}
</div>


The energy stored in the capacitor is:
$$E_C = \frac{1}{2} C \Delta P^2$$

The power required to pump air into the lung is:
$$P_C = \frac{E_C}{\Delta T_i}$$

where $\Delta T_i$ is the inhalation period. Following the assumptions the equations above:
$$C = \frac{800mL}{60cmH2O} = 1.3\cross 10^{-7} m^3/Pa $$
$$E_C = \frac{1}{2} \cross 1.3\cross 10^{-7} 6000^2 = 2.3 J$$
$$P_C = \frac{E_C}{\Delta T_i} = \frac{2.3J}{1 s} = 2.3 W$$

For simplicity, we assume that half of the motor power will be lost in the mechanics and another half of the remaining power in the tubing and the Ambu Bag. As such, a motor with around 10W power rating should be able to ventilate a lung.

## Flow Resistance Analysis
In this section, we are going to estimate the allowable flow resistance while inhaling and exhaling. The importance of this analysis lies in the fact, that it will allow us to estimate the impact of the sensors and pipings on the ventilation

To start, we need to look into the ventilation and take some assumptions. The following pictures shows, how the lung ventilation mechanism could be modeled as an electric circuit. 
During inhalation, the ventilator acts like a current generator (this is almost true for flowrate/volume control ventilation mode)   
<p><img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/physicalConcept/Lung_Ventilator_Inhale.svg?sanitize=true" alt="Mechanical ventilation during inhalation" width="300px"/>
<img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/physicalConcept/Lung_Ventilator_Inhale-circuit.svg?sanitize=true" alt="Electrical model of mechanical ventilation during inhalation" width="300px"/></p>
During exhalation, the ventilator acts acts as constant voltage node. If the PEEP is equal to zero, we can simply model the ventilator as a ground
<p><img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/physicalConcept/Lung_Ventilator_Exhale.svg?sanitize=true" alt="Mechanical ventilation during inhalation" width="300px"/>
<img src="https://raw.githubusercontent.com/mhollfelder/openvent/assets/docs/assets/physicalConcept/Lung_Ventilator_Exhale-circuit.svg?sanitize=true" alt="Electrical model of mechanical ventilation during exhalation" width="300px"/></p>
In both of the images above, one can notice that the current in the model circuit represents the flowrate, where as the voltage in the circuit represents the pressure. Furthermore, one observes that the during inhalation, the path resistance hinders the pump/motor. Whereas during the exhalation, the path resistance hinders the lung from getting all the air out of it. 


