
// the following should be moved to a library

#include "MotorStepper.hpp"

#include <SPI.h>

static const MotorStepperPinConfig_t msConfig = {
  11, // .dis
  9, // .dir
  10, // .stp
  800, // .steps
};


int rotationsPerBreath = 5;
int breathsPerMinute = 10;
int rpm;
int upDown = -1;


void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  SPI.begin();
}

void loop()
{
  MotorStepper ms(msConfig);

  rpm = 60 * rotationsPerBreath * breathsPerMinute;
  ms.setSpeed(rpm);  

  while(1)
  {
    ms.runLoop();
  
    if (ms.getStepsToMake() == 0)
    {
      upDown *= -1;
      ms.step(upDown * rotationsPerBreath * msConfig.steps);
    }
    
    serialHandler(ms);
  }
}

void serialHandler(MotorStepper &ms)
{
  if (Serial.available() > 1)
  {
    char buf[2];
    buf[0] = Serial.read();
    buf[1] = Serial.read();

    switch (buf[0])
    {
      case 'r':
        switch (buf[1])
        {
          case '+':
            rotationsPerBreath++;
            break;
          case '-':
            rotationsPerBreath--;
            break;
          default:
            break;
        }
        break;
      case 'b':
        switch (buf[1])
        {
          case '+':
            breathsPerMinute++;
            break;
          case '-':
            breathsPerMinute--;
            break;
          default:
            break;
        }
        break;
      default:
        break;
    }

    rpm = 60 * rotationsPerBreath * breathsPerMinute;
    ms.setSpeed(rpm);  

    Serial.print("Actual RPM: ");
    Serial.println(rpm, DEC);
    Serial.print("RotationsPerBreath: ");
    Serial.println(rotationsPerBreath, DEC);
    Serial.print("BreathsPerMinute: ");
    Serial.println(breathsPerMinute, DEC);
  }
}
