#include <Wire.h>


#include "FlowMeter.hpp"
#include "MovingAverage.hpp"

FlowMeter fm;
MovingAverage<float> pressure[2] = {2, 2}; // constructor parameter is the number of values to average

float volume;
float offset[2];

unsigned long last = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  Wire.begin();
  //SPI.begin();

  fm.initialize();

  // caluclate an average of each offset
  int i;
  for (i = 0; i < 8; i++)
  {
    fm.doReadings();
    offset[0] += fm.m_lastPressure[0];
    offset[1] += fm.m_lastPressure[1];
  }
  offset[0] /= i;
  offset[1] /= i;

  volume = (offset[0] + offset[1]) / 2; // offset volume in between pressure values for plotting
}

void loop() {
  // put your main code here, to run repeatedly:

  auto now = millis();
  fm.doReadings();
  pressure[0].update(fm.m_lastPressure[0]);
  pressure[1].update(fm.m_lastPressure[1]);

  float delta = pressure[1] - pressure[0] - offset[1] + offset[0];

  // round in 5 Pa steps to remove noise (this should just be factored into the final calculation)
  const float rounding = 5;
  delta = round(delta / rounding) * rounding;
  volume += delta;
  
//    Serial.print("dt: ");
//    Serial.print(now - last, DEC);
//    Serial.print("\t");
  
  Serial.print("p0:");
  Serial.print(fm.m_lastPressure[0], 6);
  Serial.print("\t");
  Serial.print("p1:");
  Serial.print(fm.m_lastPressure[1], 6);
  Serial.print("\t");

  Serial.print("vol:");
  Serial.print(volume, 6);
  Serial.print("\t");

  Serial.print("p0_avg:");
  Serial.print(pressure[0], 6);
  Serial.print("\t");
  Serial.print("p1_avg:");
  Serial.print("\t");
  Serial.println(pressure[1], 6);

  last = now;
  
  serialHandler();

  delay(17);
}

void serialHandler()
{

}
