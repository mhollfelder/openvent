////This example code is for sensorless BLDC motor control
//Please be noticed it has to be modified for diffenrent motor


//Define Motor parameters
#define MotorPoles 8
#define HallPoleShift 0

//PrintInfo

//Start up - Commutation-Counts to switch over to closed-loop

//#define OpenLoopToClosedLoopCount 50
//uint8_t ClosedLoop = 0;
//uint8_t BEMF_phase = A1;


// the following should be moved to a library

#include <Platform.h>


#define DAC_MODE_PWM    (1u << 0)
#define DAC_MODE_ANALOG (1u << 1)
 
class IPwm
{
public:
  virtual void configureOutput(uint32_t channel, uint8_t flags) = 0;
  virtual void setOutput(uint32_t channel, uint32_t value) = 0;
};

class ArduinoPwm :
  public IPwm
{
  void configureOutput(uint32_t channel, uint8_t flags)
  {
    pinMode(channel, OUTPUT);
  }
  void setOutput(uint32_t channel, uint32_t value)
  {
    analogWrite(channel, value);
  }
};

ArduinoPwm Pwm;
IPwm *defaultIPwm = &Pwm;


typedef struct
{
  // digital output pins
  uint16_t enU;
  uint16_t enV;
  uint16_t enW;

  // analog output pins
  uint16_t pwmU;
  uint16_t pwmV;
  uint16_t pwmW;

  // analog input channels
  uint32_t bemfU;
  uint32_t bemfV;
  uint32_t bemfW;
  uint32_t adcVs;
} MotorControllerPinConfig_t;

class MotorController
{
public:
  MotorController(const MotorControllerPinConfig_t &config, IGpio* gpio = defaultIGpio, IPwm* pwm = defaultIPwm, IAdc* adc = defaultIAdc);
  
  inline void updateVNeutral();

  void setDirection(uint8_t direction)
  {
    m_direction = direction;
  }
  void setDutyCycle(uint8_t dutyCycle);
  inline uint8_t getDutyCycle()
  {
    return m_dutyCycle;
  }
  void UpdateHardware(uint8_t CommutationStep);
  void DoCommutation();
  
private:
  uint8_t m_direction;
  uint8_t m_commutationStep;
  uint8_t m_dutyCycle;

  const MotorControllerPinConfig_t &m_config;
  IGpio* m_gpio;
  IAdc* m_adc;
  IPwm* m_pwm;

  uint32_t m_vNeutral;
};

MotorController::MotorController(const MotorControllerPinConfig_t &config, IGpio* gpio, IPwm* pwm, IAdc* adc) :
  m_config {config},
  m_gpio {gpio},
  m_pwm {pwm},
  m_adc {adc},
  m_direction {0},
  m_commutationStep {0},
  m_dutyCycle {150}
{
  m_gpio->configureGpio(m_config.enU, GPIO_MODE_OUTPUT_PUSH_PULL);
  m_gpio->configureGpio(m_config.enV, GPIO_MODE_OUTPUT_PUSH_PULL);
  m_gpio->configureGpio(m_config.enW, GPIO_MODE_OUTPUT_PUSH_PULL);

  m_pwm->configureOutput(m_config.pwmU, DAC_MODE_PWM);
  m_pwm->configureOutput(m_config.pwmV, DAC_MODE_PWM);
  m_pwm->configureOutput(m_config.pwmW, DAC_MODE_PWM);
}

void MotorController::setDutyCycle(uint8_t dutyCycle)
{
  m_dutyCycle = dutyCycle;
}

void MotorController::updateVNeutral()
{
  m_vNeutral = (m_adc->getValue(m_config.adcVs) * m_dutyCycle) >> 8;
}

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
};

MotorController mc(mcConfig);


void setup()
{
  // Setup the serial connection
  Serial.begin(115200);
}

void loop()
{
  uint16_t i = 5000;
  uint8_t CommStartup = 0;

  // Startup procedure: start rotating the field slowly and increase the speed
  while (i > 1000)
  {
    delayMicroseconds(i);
    mc.UpdateHardware(CommStartup);
    CommStartup++;
    if (CommStartup == 6)
      CommStartup = 0;
    i = i - 20;
  }

  uint8_t DutyCycle = mc.getDutyCycle();
  
  // main loop:
  while (1)
  {
    mc.DoCommutation();

    while (Serial.available() > 0)
    {
      byte in = Serial.read();
      if (in == '+' && (DutyCycle <= 250) ) DutyCycle += 5; //DutyCycle + 5
      if (in == '-' && (DutyCycle >= 5)   ) DutyCycle -= 5; //DutyCycle - 5

      if (in == 'd') Serial.println(DutyCycle, DEC);      //Show DutyCycle
      if (in == 'm') Serial.println(millis(), DEC);       //TimeStamp

      mc.setDutyCycle(DutyCycle);
    }
  }
}

void MotorController::DoCommutation()
{
  updateVNeutral();
  // m_vNeutral = m_adc->getValue(m_config.BEMF_phase);

  if (m_direction == 0)
  {
    switch (m_commutationStep)
    {
      case 0:
        for (int i = 0; i < 20; i++)
        {
          if (m_adc->getValue(m_config.bemfW) > m_vNeutral)
            i -= 1;
        }
        if (m_adc->getValue(m_config.bemfW) < m_vNeutral)
        {
          UpdateHardware(1);
        }
        break;

      case 1:

        for (int i = 0; i < 20; i++)
        {
          if (m_adc->getValue(m_config.bemfV) < m_vNeutral)
            i -= 1;
        }
        if (m_adc->getValue(m_config.bemfV) > m_vNeutral)
        {
          UpdateHardware(2);
        }
        break;

      case 2:

        for (int i = 0; i < 20; i++)
        {
          if (m_adc->getValue(m_config.bemfU) > m_vNeutral)
            i -= 1;
        }
        if (m_adc->getValue(m_config.bemfU) < m_vNeutral)
        {
          UpdateHardware(3);
        }
        break;

      case 3:

        for (int i = 0; i < 20; i++)
        {
          if (m_adc->getValue(m_config.bemfW) < m_vNeutral)
            i -= 1;
        }
        if (m_adc->getValue(m_config.bemfW) > m_vNeutral)
        {
          UpdateHardware(4);
        }
        break;

      case 4:

        for (int i = 0; i < 20; i++)
        {
          if (m_adc->getValue(m_config.bemfV) > m_vNeutral)
            i -= 1;
        }
        if (m_adc->getValue(m_config.bemfV) < m_vNeutral)
        {
          UpdateHardware(5);
        }
        break;

      case 5:

        for (int i = 0; i < 20; i++)
        {
          if (m_adc->getValue(m_config.bemfU) < m_vNeutral)
            i -= 1;
        }
        if (m_adc->getValue(m_config.bemfU) > m_vNeutral)
        {
          UpdateHardware(0);
        }
        break;

      default:
        break;
    }
  }
  else
  {
    
  }
}

//defining commutation steps according to HALL table
void MotorController::UpdateHardware(uint8_t CommutationStep)
{
  m_commutationStep = CommutationStep;
  updateVNeutral(); // why is this done here? it is only used in the other function...

  //CW direction
  if (m_direction == 0)
  {

    switch (CommutationStep)
    {
      case 0:
        m_gpio->setGpio(m_config.enU, true);
        m_gpio->setGpio(m_config.enV, true);
        m_gpio->setGpio(m_config.enW, false);
        m_pwm->setOutput(m_config.pwmU, m_dutyCycle);
        m_pwm->setOutput(m_config.pwmV, 0);
        m_pwm->setOutput(m_config.pwmW, 0);
        break;

      case 1:
        m_gpio->setGpio(m_config.enU, true);
        m_gpio->setGpio(m_config.enV, false);
        m_gpio->setGpio(m_config.enW, true);
        m_pwm->setOutput(m_config.pwmU, m_dutyCycle);
        m_pwm->setOutput(m_config.pwmV, 0);
        m_pwm->setOutput(m_config.pwmW, 0);
        break;

      case 2:
        m_gpio->setGpio(m_config.enU, false);
        m_gpio->setGpio(m_config.enV, true);
        m_gpio->setGpio(m_config.enW, true);
        m_pwm->setOutput(m_config.pwmU, 0);
        m_pwm->setOutput(m_config.pwmV, m_dutyCycle);
        m_pwm->setOutput(m_config.pwmW, 0);
        break;

      case 3:
        m_gpio->setGpio(m_config.enU, true);
        m_gpio->setGpio(m_config.enV, true);
        m_gpio->setGpio(m_config.enW, false);
        m_pwm->setOutput(m_config.pwmU, 0);
        m_pwm->setOutput(m_config.pwmV, m_dutyCycle);
        m_pwm->setOutput(m_config.pwmW, 0);
        break;

      case 4:
        m_gpio->setGpio(m_config.enU, true);
        m_gpio->setGpio(m_config.enV, false);
        m_gpio->setGpio(m_config.enW, true);
        m_pwm->setOutput(m_config.pwmU, 0);
        m_pwm->setOutput(m_config.pwmV, 0);
        m_pwm->setOutput(m_config.pwmW, m_dutyCycle);
        break;

      case 5:
        m_gpio->setGpio(m_config.enU, false);
        m_gpio->setGpio(m_config.enV, true);
        m_gpio->setGpio(m_config.enW, true);
        m_pwm->setOutput(m_config.pwmU, 0);
        m_pwm->setOutput(m_config.pwmV, 0);
        m_pwm->setOutput(m_config.pwmW, m_dutyCycle);
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
        m_gpio->setGpio(m_config.enU, false);
        m_gpio->setGpio(m_config.enV, true);
        m_gpio->setGpio(m_config.enW, true);
        m_pwm->setOutput(m_config.pwmU, 0);
        m_pwm->setOutput(m_config.pwmV, m_dutyCycle);
        m_pwm->setOutput(m_config.pwmW, 0);
        break;

      case 1:
        m_gpio->setGpio(m_config.enU, true);
        m_gpio->setGpio(m_config.enV, false);
        m_gpio->setGpio(m_config.enW, true);
        m_pwm->setOutput(m_config.pwmU, m_dutyCycle);
        m_pwm->setOutput(m_config.pwmV, 0);
        m_pwm->setOutput(m_config.pwmW, 0);
        break;

      case 2:
        m_gpio->setGpio(m_config.enU, true);
        m_gpio->setGpio(m_config.enV, true);
        m_gpio->setGpio(m_config.enW, false);
        m_pwm->setOutput(m_config.pwmU, m_dutyCycle);
        m_pwm->setOutput(m_config.pwmV, 0);
        m_pwm->setOutput(m_config.pwmW, 0);
        break;

      case 3:
        m_gpio->setGpio(m_config.enU, false);
        m_gpio->setGpio(m_config.enV, true);
        m_gpio->setGpio(m_config.enW, true);
        m_pwm->setOutput(m_config.pwmU, 0);
        m_pwm->setOutput(m_config.pwmV, 0);
        m_pwm->setOutput(m_config.pwmW, m_dutyCycle);
        break;

      case 4:
        m_gpio->setGpio(m_config.enU, true);
        m_gpio->setGpio(m_config.enV, false);
        m_gpio->setGpio(m_config.enW, true);
        m_pwm->setOutput(m_config.pwmU, 0);
        m_pwm->setOutput(m_config.pwmV, 0);
        m_pwm->setOutput(m_config.pwmW, m_dutyCycle);
        break;

      case 5:
        m_gpio->setGpio(m_config.enU, true);
        m_gpio->setGpio(m_config.enV, true);
        m_gpio->setGpio(m_config.enW, false);
        m_pwm->setOutput(m_config.pwmU, 0);
        m_pwm->setOutput(m_config.pwmV, m_dutyCycle);
        m_pwm->setOutput(m_config.pwmW, 0);
        break;

      default:
        break;
    }
  }
}
