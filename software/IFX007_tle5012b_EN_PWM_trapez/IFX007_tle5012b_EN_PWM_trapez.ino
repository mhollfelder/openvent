#include <Tle5012b.h>

#include <Tle5012b_reg.h>

//Define Inputs & Outputs
#define DIR_U 11
#define DIR_V 10
#define DIR_W 9
#define EN_U 6
#define EN_V 5
#define EN_W 3

#define SS   38 // P0.3
#define MOSI  39 // P0.1 -----> 0.1 und 0.0 zusammenlöten! (3-Wire SPI)
#define MISO  65 // P0.0
#define SCK   40 // P0.10

#define MOTORPOLES 20.0 
#define OFFSETMAGNET 83.5
#define TIMING 5.4 //Switching timinig of the Motor. Has to be defined for every

#define anzahlMittelWerte 300
int werte[anzahlMittelWerte], zaehlerMittelWerte=0;

Tle5012b_SPI Spi1 = Tle5012b_SPI(1);
Tle5012b_reg Sensor1 = Tle5012b_reg();

int currentSense = A5;
int current;

double PI_Update_Timeout = 10;
double raw_angle = 0;
int16_t rev = 0;
double angle = 0;
double old_angle = 0;
int8_t stateCount = 0;
double rpm_soll = 150;
double rpm_old = 0.0;
double rpm = 0.0;
double sum_rpm = 0.0;

int DIR = -1;

double absolut_angle;
double absolut_angle_top;
double absolut_angle_bottom = -2400;
double Nullpunkt;

int i=0;

int state = 0;
int calculatedState = 0;
int DutyCycle = 20;

float offset = 0; //7.4

uint8_t calculateState(double angle);
uint8_t oldstate = 1;

float f;

float f_break;

bool fertig = 0;

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
}

void loop() {
while (Serial.available() != 0)
    {
        int input = 0;
        input = Serial.read();
        if(input == 43)
        {
             DutyCycle += 5;
            Serial.print("\t\t");
            //Serial.println(DutyCycle);
        }
        if(input == 45)
        {
            DutyCycle -= 5;
            Serial.print("\t\t");
           // Serial.println(DutyCycle);
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
 
//set direction 
  if(absolut_angle > absolut_angle_top){
    DIR = -1;
    if(fertig == 0){
      digitalWrite(DIR_U, LOW);
      digitalWrite(DIR_V, LOW);
      digitalWrite(DIR_W, LOW);
      delay(2000);
      fertig++;
    }
  }
  if(absolut_angle < absolut_angle_bottom){
    DIR = 1;
    fertig = 0;
    }

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
      }

     

////measure current
//  current = analogRead(currentSense);
//  f= mittelWert(current); //7,6mA per ADC
//  if(i>100) {Serial.println(f); i=0;}
//  i++; 
    
////Speed control
//  Sensor1.getAngleSpeed(rpm);
//  rpm = abs(rpm);
//  sum_rpm += rpm;
//    if ( i > 49) {
//      rpm = sum_rpm/50;
//      //DutyCycle = constrain(DutyCycle+0.08*(rpm_soll-rpm),0,150);
//      DutyCycle = constrain(0.1*(rpm_soll),0,150);
//      rpm_old = rpm;
//      i = 0;
//      sum_rpm = 0;
//      Serial.print(rpm); Serial.print("\t");
//      Serial.print(rpm_soll); Serial.print("\t");
//      Serial.println(DutyCycle);
//    }
  
 
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
      newState = (newState + (int)(counter/50))%6;
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

float mittelWert(int neuerWert) {
  float mittel, summe=0;
    werte[zaehlerMittelWerte] = neuerWert;
    for(int k=0; k < anzahlMittelWerte; k++) summe += werte[k];
    mittel=(float) summe / anzahlMittelWerte; 
    zaehlerMittelWerte++;
    if(zaehlerMittelWerte >= anzahlMittelWerte) zaehlerMittelWerte=0;
    return mittel;
}
