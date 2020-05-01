#include <Tle5012b.h>
#include <Tle5012b_reg.h>

#include "MotorController.hpp"


#define SS    96 // P0.12
#define MOSI  71 // P3.11 -----> 3.11 und 3.12 zusammenlöten! (3-Wire SPI)
#define MISO  97 // P3.12
#define SCK   70 // P3.13



Tle5012b_SPI Spi1 = Tle5012b_SPI(2);
Tle5012b_reg Sensor1 = Tle5012b_reg();

double raw_angle = 0;
int16_t rev = 0;


double absolut_angle;
double absolut_angle_top;
double absolut_angle_bottom = -2400;
double Nullpunkt;

int i=0;


bool fertig = 0;

int resp_per_minute = 10;
double inhale = 1 ;
double exhale = 1;
uint32_t start_millis = 0;
uint32_t inhale_millis;
uint32_t exhale_millis;


bool safety;


MotorController mc;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Sensor1.begin(Spi1, MISO, MOSI, SCK, SS, Tle5012b::TLE5012B_S0);

  mc.setup();

  Sensor1.getAngleValue(raw_angle);
  Nullpunkt = raw_angle+180;
  absolut_angle_top = Nullpunkt;
  absolut_angle_bottom += absolut_angle_top;

  inhale_millis = 60000/resp_per_minute*(inhale/(inhale+exhale));
  exhale_millis = 60000/resp_per_minute*(exhale/(inhale+exhale));
}

void loop()
{
   
  //Inhale phase
  if((millis()-start_millis) < inhale_millis && safety == 0)
  {
    mc.DIR = -1;
    mc.DutyCycle = 20;
  
    //safety stop
    if(absolut_angle < absolut_angle_bottom)
    {
      safety = 1;
      mc.DIR = 0;
    }
  }
  
  //Exhale phase
  if((millis()-start_millis) > inhale_millis && (millis()-start_millis) < (inhale_millis+exhale_millis))
  {
    safety = 0;
    mc.DIR = 1;
    mc.DutyCycle = 20;
    //safety stop
    if(absolut_angle > absolut_angle_top)
    {
        digitalWrite(DIR_U, LOW);
        digitalWrite(DIR_V, LOW);
        digitalWrite(DIR_W, LOW);
        mc.DIR = 2;
    }
  }
  
  if(millis()-start_millis > (inhale_millis+exhale_millis))
  {
    start_millis = millis();
  }

  calculateAngle();
  
  serialHandler();
  
  mc.move();
}

void serialHandler()
{
    while (Serial.available() != 0)
    {
        int input = 0;
        input = Serial.read();
        if(input == 43)
        {
             mc.DutyCycle += 5;
            Serial.print("\t");
            Serial.println(mc.DutyCycle);
        }
        if(input == 45)
        {
            mc.DutyCycle -= 5;
            Serial.print("\t");
            Serial.println(mc.DutyCycle);
        }
    }
}

void calculateAngle()
{
  Sensor1.getAngleValue(raw_angle);
  //count rotations
    if(mc.angle-(raw_angle+180) > 200){
      rev++;
    }
    if(mc.angle-(raw_angle+180) < -200){
      rev--;
    }
  //get actual and absolute angle  
    mc.angle = raw_angle+180;
    absolut_angle = mc.angle-Nullpunkt+360*rev;
  //Serial.println(absolut_angle);
}
