
#include "MotorController.hpp"

#include <SPI.h>


static const MotorControllerPinConfig_t mcConfig = {
  6, // .enU
  5, // .enV
  3, // .enW
  11, // .pwmU
  10, // .pwmV
  9, // .pwmW
  A3, // .bemfU
  A2, // .bemfV
  A1, // .bemfW
  A0, // .adcVs
  4, // .polePairs
};

uint8_t DutyCycle;


void setup()
{
  Serial.begin(115200);

  SPI.begin();
}

void loop()
{
  MotorController mc(mcConfig);

  uint16_t i = 5000;
  // Startup procedure: start rotating the field slowly and increase the speed
  while (i > 1000)
  {
    delayMicroseconds(i);
    mc.outputVoltage();
    mc.m_commutationStep++;
    if (mc.m_commutationStep == 6)
      mc.m_commutationStep = 0;
    i = i - 20;
  }

  DutyCycle = mc.getDutyCycle();
  
  while(1)
  {  
    mc.runLoop();
  
    serialHandler(mc);
  }
}

void serialHandler(MotorController &mc)
{
  if (Serial.available() > 1)
  {
    char buf[2];
    buf[0] = Serial.read();
    buf[1] = Serial.read();

    switch (buf[0])
    {
      case 'd':
        switch (buf[1])
        {
          case '+':
            if (DutyCycle <= 250) DutyCycle += 5;
            break;
          case '-':
            if (DutyCycle >= 5) DutyCycle -= 5;
            break;
          default:
            break;
        }
        mc.setDutyCycle(DutyCycle);
        break;
      default:
        break;
    }

    Serial.print("DutyCycle: ");
    Serial.println(DutyCycle, DEC);
    Serial.print("Actual RPM: ");
    Serial.println(mc.m_actualRpm, 3);
  }
}
