#include <Wire.h>

// the following should be moved to a library


#include "FlowMeter.hpp"
#include "MovingAverage.hpp"

MovingAverage<float> pressure[2] = {4, 4}; // constructor parameter is the number of values to average


unsigned long last = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  Wire.begin();
  //SPI.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  FlowMeter fm; // must be local, Arduino does not support static objects
 
  fm.initialize();
  
  while(1) // this is necessary since we want to use stack-allocated object above
  {
  
    auto now = millis();
    fm.doReadings();
    pressure[0].update(fm.m_lastPressure[0]);
    pressure[1].update(fm.m_lastPressure[1]);
  
    Serial.print(now - last, DEC);
    Serial.print(" :   ");
    Serial.print(fm.m_lastPressure[0], 6);
    Serial.print(" - ");
    Serial.print(fm.m_lastPressure[1], 6);

    Serial.print("      Avg: ");
    Serial.print(pressure[0], 6);
    Serial.print(" - ");
    Serial.println(pressure[1], 6);

    last = now;
    
    serialHandler();

    delay(84);
  }
}

void serialHandler()
{

}
