#include <Tle5012b.h>
#include <Tle5012b_reg.h>

//Define Inputs & Outputs
#define DIR_U 11
#define DIR_V 10
#define DIR_W 9
#define EN_U 6
#define EN_V 5
#define EN_W 3

#define SS    96 // P0.12
#define MOSI  71 // P3.11 -----> 3.11 und 3.12 zusammenlöten! (3-Wire SPI)
#define MISO  97 // P3.12
#define SCK   70 // P3.13

#define MOTORPOLES 20.0 
#define OFFSETMAGNET 83.5
#define TIMING 5.4 //Switching timinig of the Motor. Has to be defined for every


Tle5012b_SPI Spi1 = Tle5012b_SPI(2);
Tle5012b_reg Sensor1 = Tle5012b_reg();

double raw_angle = 0;
int16_t rev = 0;
double angle = 0;

int DIR = -1;

double absolut_angle;
double absolut_angle_top;
double absolut_angle_bottom = -2400;
double Nullpunkt;

int i=0;

int state = 0;
int calculatedState = 0;
int DutyCycle = 20;

uint8_t calculateState(double angle);
uint8_t oldstate = 1;

bool fertig = 0;

int resp_per_minute = 10;
double inhale = 1 ;
double exhale = 1;
uint32_t start_millis = 0;
uint32_t inhale_millis;
uint32_t exhale_millis;


bool safety;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Sensor1.begin(Spi1, MISO, MOSI, SCK, SS, Tle5012b::TLE5012B_S0);



   // Define the pin modes
  pinMode(EN_U, OUTPUT);
  pinMode(EN_V, OUTPUT);
  pinMode(EN_W, OUTPUT);
  pinMode(DIR_U, OUTPUT);
  pinMode(DIR_V, OUTPUT);
  pinMode(DIR_W, OUTPUT);
  setAnalogWriteFrequency(EN_U,10000);
  setAnalogWriteFrequency(EN_V,10000);
  setAnalogWriteFrequency(EN_W,10000);

  Sensor1.getAngleValue(raw_angle);
  Nullpunkt = raw_angle+180;
  absolut_angle_top = Nullpunkt;
  absolut_angle_bottom += absolut_angle_top;

  inhale_millis = 60000/resp_per_minute*(inhale/(inhale+exhale));
  exhale_millis = 60000/resp_per_minute*(exhale/(inhale+exhale));
  
}

void loop() {
   
//Inhale phase
if((millis()-start_millis) < inhale_millis && safety == 0){
  DIR = -1;

    DutyCycle = 20;
  
  //safety stop
  if(absolut_angle < absolut_angle_bottom){
    safety = 1;
        DIR = 0;
  }
}
//Exhale phase
if((millis()-start_millis) > inhale_millis && (millis()-start_millis) < (inhale_millis+exhale_millis)){
  safety = 0;
  DIR = 1;
  DutyCycle = 20;
  //safety stop
  if(absolut_angle > absolut_angle_top){
      digitalWrite(DIR_U, LOW);
      digitalWrite(DIR_V, LOW);
      digitalWrite(DIR_W, LOW);
        DIR = 2;
  }
}
if(millis()-start_millis > (inhale_millis+exhale_millis)) {start_millis = millis();}





while (Serial.available() != 0)
    {
        int input = 0;
        input = Serial.read();
        if(input == 43)
        {
             DutyCycle += 5;
            Serial.print("\t");
            Serial.println(DutyCycle);
        }
        if(input == 45)
        {
            DutyCycle -= 5;
            Serial.print("\t");
            Serial.println(DutyCycle);
        }
    }

Sensor1.getAngleValue(raw_angle);
//count rotations
  if(angle-(raw_angle+180) > 200){
    rev++;
  }
  if(angle-(raw_angle+180) < -200){
    rev--;
  }
//get actual and absolute angle  
  angle = raw_angle+180;
  absolut_angle = angle-Nullpunkt+360*rev;
//Serial.println(absolut_angle);


//move  
  switch (DIR)
        { case -1:
            calculatedState = calculateState(angle-OFFSETMAGNET-TIMING+360);
            stateMachine(calculatedState);
            break;
    
          case 0:
            calculatedState = calculateState(angle-OFFSETMAGNET+360);
            stateMachine(calculatedState);
            break;
    
          case 1:
            calculatedState = calculateState(angle-OFFSETMAGNET+TIMING+360);
            stateMachine(calculatedState);
            break;
          case 2:
            analogWrite(EN_U, 0);
            analogWrite(EN_V, 0);
            analogWrite(EN_W, 0);
            digitalWrite(DIR_U, LOW);
            digitalWrite(DIR_V, LOW);
            digitalWrite(DIR_W, LOW);
            break;
      }

}

void stateMachine(uint8_t newState)
{
  static int counter = 0;
   if(newState != oldstate){
        analogWrite(EN_U, 0);
        analogWrite(EN_V, 0);
        analogWrite(EN_W, 0);
        delayMicroseconds(15);
        oldstate = newState;
        counter = 0;
   } 
  if(newState == oldstate && DIR != 0){
    counter++;
    if(counter >= 50){
      if(DIR > 0){
        newState = (newState + (int)(counter/50))%6;
        }
      else{
        newState = (newState - (int)(counter/50))%6;
        }
     }
   }
  
   switch (newState)
      {
        case 0:
          analogWrite(EN_U, DutyCycle);
          analogWrite(EN_V, 255);
          analogWrite(EN_W, 0);
          digitalWrite(DIR_U, HIGH);
          digitalWrite(DIR_V, LOW);
          digitalWrite(DIR_W, LOW);
          break;

        case 1:
          analogWrite(EN_U, DutyCycle);
          analogWrite(EN_V, 255);
          analogWrite(EN_W, 255);
          digitalWrite(DIR_U, HIGH);
          digitalWrite(DIR_V, LOW);
          digitalWrite(DIR_W, LOW);
          break;  
          
        case 2:
          analogWrite(EN_U, DutyCycle);
          analogWrite(EN_V, 0);
          analogWrite(EN_W, 255);
          digitalWrite(DIR_U, HIGH);
          digitalWrite(DIR_V, LOW);
          digitalWrite(DIR_W, LOW);
          break;

        case 3:
          analogWrite(EN_U, DutyCycle/2);
          analogWrite(EN_V, DutyCycle/2);
          analogWrite(EN_W, 255);
          digitalWrite(DIR_U, HIGH);
          digitalWrite(DIR_V, HIGH);
          digitalWrite(DIR_W, LOW);
          break;
  
        case 4:
          analogWrite(EN_U, 0);
          analogWrite(EN_V, DutyCycle);
          analogWrite(EN_W, 255);
          digitalWrite(DIR_U, LOW);
          digitalWrite(DIR_V, HIGH);
          digitalWrite(DIR_W, LOW);
          break;
            
        case 5:
          analogWrite(EN_U, 255);
          analogWrite(EN_V, DutyCycle);
          analogWrite(EN_W, 255);
          digitalWrite(DIR_U, LOW);
          digitalWrite(DIR_V, HIGH);
          digitalWrite(DIR_W, LOW);
          break;
  
        case 6:
          analogWrite(EN_U, 255);
          analogWrite(EN_V, DutyCycle);
          analogWrite(EN_W, 0);
          digitalWrite(DIR_U, LOW);
          digitalWrite(DIR_V, HIGH);
          digitalWrite(DIR_W, LOW);
          break;

        case 7:
          analogWrite(EN_U, 255);
          analogWrite(EN_V, DutyCycle/2);
          analogWrite(EN_W, DutyCycle/2);
          digitalWrite(DIR_U, LOW);
          digitalWrite(DIR_V, HIGH);
          digitalWrite(DIR_W, HIGH);
          break;
  
        case 8:
          analogWrite(EN_U, 255);
          analogWrite(EN_V, 0);
          analogWrite(EN_W, DutyCycle);
          digitalWrite(DIR_U, LOW);
          digitalWrite(DIR_V, LOW);
          digitalWrite(DIR_W, HIGH);
          break;

        case 9:
          analogWrite(EN_U, 255);
          analogWrite(EN_V, 255);
          analogWrite(EN_W, DutyCycle);
          digitalWrite(DIR_U, LOW);
          digitalWrite(DIR_V, LOW);
          digitalWrite(DIR_W, HIGH);
          break;
            
      case 10:
        analogWrite(EN_U, 0);
        analogWrite(EN_V, 255);
        analogWrite(EN_W, DutyCycle);
        digitalWrite(DIR_U, LOW);
        digitalWrite(DIR_V, LOW);
        digitalWrite(DIR_W, HIGH);
        break;
              
       case 11:
        analogWrite(EN_U, DutyCycle/2);
        analogWrite(EN_V, 255);
        analogWrite(EN_W, DutyCycle/2);
        digitalWrite(DIR_U, HIGH);
        digitalWrite(DIR_V, LOW);
        digitalWrite(DIR_W, HIGH);
        break;
  
        default:
          break;
      }
}

uint8_t calculateState(double angle)
{
    double result = 0;
    uint8_t state = 0;

    result = angle / ((float)360/(float)MOTORPOLES);
    result = result - (int)result;
    result = result * 12;
    result = round(result);
    state = (int) result;
    if (state == 12 ){
      state = 0;
    }
    return state;
}
