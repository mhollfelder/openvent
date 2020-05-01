

//Define Inputs & Outputs
#define DIR_U 11
#define DIR_V 10
#define DIR_W 9
#define EN_U 6
#define EN_V 5
#define EN_W 3

#define MOTORPOLES 20.0 
#define OFFSETMAGNET 83.5
#define TIMING 5.4 //Switching timinig of the Motor. Has to be defined for every


class MotorController
{
public:
  MotorController();
  
	void stateMachine(uint8_t newState);
	void move();
  uint8_t calculateState(double angle);
  void setup();

//private:
	int DIR = -1;
  int state = 0;
int calculatedState = 0;
int DutyCycle = 20;

double angle = 0;

uint8_t oldstate = 1;

};

MotorController::MotorController()
{

}

void MotorController::setup()
{  
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
}

void MotorController::stateMachine(uint8_t newState)
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

uint8_t MotorController::calculateState(double angle)
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

void MotorController::move()
{
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
