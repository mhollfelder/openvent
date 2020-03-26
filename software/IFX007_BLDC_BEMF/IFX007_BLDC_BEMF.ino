////This example code is for sensorless BLDC motor control
//Please be noticed it has to be modified for diffenrent motor

//Define Inputs & Outputs
#define PWM_U 11
#define PWM_V 10
#define PWM_W 9
#define EN_U 6
#define EN_V 5
#define EN_W 3

// Based on ADC phase voltage inputs
#define BEMF_U A3
#define BEMF_V A2
#define BEMF_W A1
#define ADC_VS A0

//Define Motor parameters
#define MotorPoles 8
#define HallPoleShift 0

//PrintInfo

//Start up - Commutation-Counts to switch over to closed-loop

#define OpenLoopToClosedLoopCount 50
uint8_t Commutation = 0;
uint8_t BEMF_phase = A1;
uint8_t ClosedLoop = 0;
uint8_t DutyCycle = 150;
uint8_t Dir = 0;
uint32_t V_neutral = 0;

void setup()
{

  // Setup the serial connection
  Serial.begin(115200);

  // Define the pin modes
  pinMode(EN_U, OUTPUT);
  pinMode(EN_V, OUTPUT);
  pinMode(EN_W, OUTPUT);
  pinMode(PWM_U, OUTPUT);
  pinMode(PWM_V, OUTPUT);
  pinMode(PWM_W, OUTPUT);

  V_neutral = (((uint32_t)analogRead(ADC_VS) * DutyCycle) >> 8);
}

void loop()
{

  uint16_t i = 5000;
  uint8_t CommStartup = 0;

  // Startup procedure: start rotating the field slowly and increase the speed
  while (i > 1000)
  {
    delayMicroseconds(i);
    Commutation = CommStartup;
    UpdateHardware(CommStartup, 0);
    CommStartup++;
    if (CommStartup == 6)
      CommStartup = 0;
    i = i - 20;
  }

  // main loop:
  while (1)
  {
    DoCommutation();

    while (Serial.available() > 0) {
      byte in = Serial.read();
      if (in == '+' && (DutyCycle <= 250) ) DutyCycle += 5; //DutyCycle + 5
      if (in == '-' && (DutyCycle >= 5)   ) DutyCycle -= 5; //DutyCycle - 5

      if (in == 'd') Serial.println(DutyCycle, DEC);      //Show DutyCycle
      if (in == 'm') Serial.println(millis(), DEC);       //TimeStamp
    }
  }
}

void DoCommutation()
{
  V_neutral = (((uint32_t)analogRead(ADC_VS) * DutyCycle) >> 8);
  // V_neutral = analogRead(BEMF_phase);

  if (Dir == 0)
  {
    switch (Commutation)
    {
      case 0:
        for (int i = 0; i < 20; i++)
        {
          if (analogRead(BEMF_W) > V_neutral)
            i -= 1;
        }
        if (analogRead(BEMF_W) < V_neutral)
        {
          Commutation = 1;
          UpdateHardware(Commutation, 0);
        }
        break;

      case 1:

        for (int i = 0; i < 20; i++)
        {
          if (analogRead(BEMF_V) < V_neutral)
            i -= 1;
        }
        if (analogRead(BEMF_V) > V_neutral)
        {
          Commutation = 2;
          UpdateHardware(Commutation, 0);
        }
        break;

      case 2:

        for (int i = 0; i < 20; i++)
        {
          if (analogRead(BEMF_U) > V_neutral)
            i -= 1;
        }
        if (analogRead(BEMF_U) < V_neutral)
        {
          Commutation = 3;
          UpdateHardware(Commutation, 0);
        }
        break;

      case 3:

        for (int i = 0; i < 20; i++)
        {
          if (analogRead(BEMF_W) < V_neutral)
            i -= 1;
        }
        if (analogRead(BEMF_W) > V_neutral)
        {
          Commutation = 4;
          UpdateHardware(Commutation, 0);
        }
        break;

      case 4:

        for (int i = 0; i < 20; i++)
        {
          if (analogRead(BEMF_V) > V_neutral)
            i -= 1;
        }
        if (analogRead(BEMF_V) < V_neutral)
        {
          Commutation = 5;
          UpdateHardware(Commutation, 0);
        }
        break;

      case 5:

        for (int i = 0; i < 20; i++)
        {
          if (analogRead(BEMF_U) < V_neutral)
            i -= 1;
        }
        if (analogRead(BEMF_U) > V_neutral)
        {
          Commutation = 0;
          UpdateHardware(Commutation, 0);
        }
        break;

      default:
        break;
    }
  }
}

//defining commutation steps according to HALL table
void UpdateHardware(uint8_t CommutationStep, uint8_t Dir)
{

  // update neutral voltage:
  V_neutral = (int)(((uint32_t)analogRead(ADC_VS) * DutyCycle) >> 8);

  //CW direction
  if (Dir == 0)
  {

    switch (CommutationStep)
    {
      case 0:
        digitalWrite(EN_U, HIGH);
        digitalWrite(EN_V, HIGH);
        digitalWrite(EN_W, LOW);
        analogWrite(PWM_U, DutyCycle);
        analogWrite(PWM_V, 0);
        analogWrite(PWM_W, 0);
        break;

      case 1:
        digitalWrite(EN_U, HIGH);
        digitalWrite(EN_V, LOW);
        digitalWrite(EN_W, HIGH);
        analogWrite(PWM_U, DutyCycle);
        analogWrite(PWM_V, 0);
        analogWrite(PWM_W, 0);
        break;

      case 2:
        digitalWrite(EN_U, LOW);
        digitalWrite(EN_V, HIGH);
        digitalWrite(EN_W, HIGH);
        analogWrite(PWM_U, 0);
        analogWrite(PWM_V, DutyCycle);
        analogWrite(PWM_W, 0);
        break;

      case 3:
        digitalWrite(EN_U, HIGH);
        digitalWrite(EN_V, HIGH);
        digitalWrite(EN_W, LOW);
        analogWrite(PWM_U, 0);
        analogWrite(PWM_V, DutyCycle);
        analogWrite(PWM_W, 0);
        break;

      case 4:
        digitalWrite(EN_U, HIGH);
        digitalWrite(EN_V, LOW);
        digitalWrite(EN_W, HIGH);
        analogWrite(PWM_U, 0);
        analogWrite(PWM_V, 0);
        analogWrite(PWM_W, DutyCycle);
        break;

      case 5:
        digitalWrite(EN_U, LOW);
        digitalWrite(EN_V, HIGH);
        digitalWrite(EN_W, HIGH);
        analogWrite(PWM_U, 0);
        analogWrite(PWM_V, 0);
        analogWrite(PWM_W, DutyCycle);
        break;

      default:
        break;
    }
  }
  else
  {
    //CCW direction
    switch (CommutationStep)
    {
      case 0:
        digitalWrite(EN_U, LOW);
        digitalWrite(EN_V, HIGH);
        digitalWrite(EN_W, HIGH);
        analogWrite(PWM_U, 0);
        analogWrite(PWM_V, DutyCycle);
        analogWrite(PWM_W, 0);
        break;

      case 1:
        digitalWrite(EN_U, HIGH);
        digitalWrite(EN_V, LOW);
        digitalWrite(EN_W, HIGH);
        analogWrite(PWM_U, DutyCycle);
        analogWrite(PWM_V, 0);
        analogWrite(PWM_W, 0);
        break;

      case 2:
        digitalWrite(EN_U, HIGH);
        digitalWrite(EN_V, HIGH);
        digitalWrite(EN_W, LOW);
        analogWrite(PWM_U, DutyCycle);
        analogWrite(PWM_V, 0);
        analogWrite(PWM_W, 0);
        break;

      case 3:
        digitalWrite(EN_U, LOW);
        digitalWrite(EN_V, HIGH);
        digitalWrite(EN_W, HIGH);
        analogWrite(PWM_U, 0);
        analogWrite(PWM_V, 0);
        analogWrite(PWM_W, DutyCycle);
        break;

      case 4:
        digitalWrite(EN_U, HIGH);
        digitalWrite(EN_V, LOW);
        digitalWrite(EN_W, HIGH);
        analogWrite(PWM_U, 0);
        analogWrite(PWM_V, 0);
        analogWrite(PWM_W, DutyCycle);
        break;

      case 5:
        digitalWrite(EN_U, HIGH);
        digitalWrite(EN_V, HIGH);
        digitalWrite(EN_W, LOW);
        analogWrite(PWM_U, 0);
        analogWrite(PWM_V, DutyCycle);
        analogWrite(PWM_W, 0);
        break;

      default:
        break;
    }
  }
}
