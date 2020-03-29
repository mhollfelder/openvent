
//#define OpenLoopToClosedLoopCount 50
//uint8_t ClosedLoop = 0;
//uint8_t BEMF_phase = A1;


// the following should be moved to a library

#include <Platform.h>


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

  uint32_t polePairs;
} MotorControllerPinConfig_t;


class MotorController
{
public:
  MotorController(const MotorControllerPinConfig_t &config, IGpio* gpio = defaultIGpio, IDac* dac = defaultIDac, IAdc* adc = defaultIAdc);
  
  inline void updateVNeutral();

  void setDirection(bool direction)
  {
    m_direction = direction;
  }
  void setDutyCycle(uint8_t dutyCycle);
  inline uint8_t getDutyCycle()
  {
    return m_dutyCycle;
  }
  void runLoop();

//private:
  constexpr static unsigned int voltageSteps = 20;
  void outputVoltage();

  float m_actualRpm;

  int m_voltageSteps = voltageSteps;

  bool m_direction;
  uint8_t m_dutyCycle;
  uint8_t m_commutationStep;
  clock_ticks_t m_lastCommutation;  
  clock_ticks_t m_deltaT;

  const MotorControllerPinConfig_t &m_config;
  IGpio* m_gpio;
  IDac* m_dac;
  IAdc* m_adc;

  const uint32_t m_steps;

  uint32_t m_vNeutral;
};

MotorController::MotorController(const MotorControllerPinConfig_t &config, IGpio* gpio, IDac* dac, IAdc* adc) :
  m_config {config},
  m_gpio {gpio},
  m_dac {dac},
  m_adc {adc},
  m_direction {false},
  m_commutationStep {0},
  m_dutyCycle {150},
  m_steps {m_config.polePairs * 6}
{
  m_gpio->configureGpio(m_config.enU, GPIO_MODE_OUTPUT_PUSH_PULL);
  m_gpio->configureGpio(m_config.enV, GPIO_MODE_OUTPUT_PUSH_PULL);
  m_gpio->configureGpio(m_config.enW, GPIO_MODE_OUTPUT_PUSH_PULL);

  m_dac->configureOutput(m_config.pwmU, DAC_MODE_PWM);
  m_dac->configureOutput(m_config.pwmV, DAC_MODE_PWM);
  m_dac->configureOutput(m_config.pwmW, DAC_MODE_PWM);
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
  4, // .polePairs
};

MotorController mc(mcConfig);

uint8_t DutyCycle;

void setup()
{
  // Setup the serial connection
  Serial.begin(115200);

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

}

void loop()
{
  mc.runLoop();

  serialHandler();
}

void serialHandler()
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

void MotorController::runLoop()
{
  updateVNeutral();
  // m_vNeutral = m_adc->getValue(m_config.BEMF_phase);

  if (!m_direction)
  {
    switch (m_commutationStep)
    {
      case 0:
        if (m_adc->getValue(m_config.bemfW) < m_vNeutral)
        {
            m_voltageSteps--;
        }
        break;
      case 1:
        if (m_adc->getValue(m_config.bemfV) > m_vNeutral)
        {
            m_voltageSteps--;
        }
        break;
      case 2:
        if (m_adc->getValue(m_config.bemfU) < m_vNeutral)
        {
            m_voltageSteps--;
        }
        break;
      case 3:
        if (m_adc->getValue(m_config.bemfW) > m_vNeutral)
        {
            m_voltageSteps--;
        }
        break;
      case 4:
        if (m_adc->getValue(m_config.bemfV) < m_vNeutral)
        {
            m_voltageSteps--;
        }
        break;
      case 5:
        if (m_adc->getValue(m_config.bemfU) > m_vNeutral)
        {
            m_voltageSteps--;
        }
        break;
      default:
        break;
    }
  }
  else
  {
    switch (m_commutationStep)
    {
      case 0:
        if (m_adc->getValue(m_config.bemfW) > m_vNeutral)
        {
            m_voltageSteps--;
        }
        break;
      case 1:
        if (m_adc->getValue(m_config.bemfV) < m_vNeutral)
        {
            m_voltageSteps--;
        }
        break;
      case 2:
        if (m_adc->getValue(m_config.bemfU) > m_vNeutral)
        {
            m_voltageSteps--;
        }
        break;
      case 3:
        if (m_adc->getValue(m_config.bemfW) < m_vNeutral)
        {
            m_voltageSteps--;
        }
        break;
      case 4:
        if (m_adc->getValue(m_config.bemfV) > m_vNeutral)
        {
            m_voltageSteps--;
        }
        break;
      case 5:
        if (m_adc->getValue(m_config.bemfU) < m_vNeutral)
        {
            m_voltageSteps--;
        }
        break;
      default:
        break;
    }
  }

  if (m_voltageSteps == 0)
  {
    if (!m_direction)
    {
      if (m_commutationStep == 5)
      {
        m_commutationStep = 0;
      }
      else
      {
        m_commutationStep++;
      }
    }
    else
    {
      if (m_commutationStep == 0)
      {
        m_commutationStep = 5;
      }
      else
      {
        m_commutationStep--;
      }
    }

    m_deltaT = clock_elapsed_since(m_lastCommutation);

    outputVoltage();
    m_voltageSteps = voltageSteps;
    m_lastCommutation += m_deltaT;

    // use average or filter
    m_actualRpm = 60.0f * clock_ticks_per_sec / m_deltaT / m_steps;
  }
}

void MotorController::outputVoltage()
{
  // check for direction and only switch the ones necessary
  switch (m_commutationStep)
  {
    case 0:
      m_gpio->setGpio(m_config.enW, false);
      m_dac->setOutput(m_config.pwmV, 0);
      m_dac->setOutput(m_config.pwmW, 0);
      m_dac->setOutput(m_config.pwmU, m_dutyCycle);
      m_gpio->setGpio(m_config.enU, true);
      m_gpio->setGpio(m_config.enV, true);
      break;
    case 1:
      m_gpio->setGpio(m_config.enV, false);
      m_dac->setOutput(m_config.pwmV, 0);
      m_dac->setOutput(m_config.pwmW, 0);
      m_dac->setOutput(m_config.pwmU, m_dutyCycle);
      m_gpio->setGpio(m_config.enU, true);
      m_gpio->setGpio(m_config.enW, true);
      break;
    case 2:
      m_gpio->setGpio(m_config.enU, false);
      m_dac->setOutput(m_config.pwmU, 0);
      m_dac->setOutput(m_config.pwmW, 0);
      m_dac->setOutput(m_config.pwmV, m_dutyCycle);
      m_gpio->setGpio(m_config.enV, true);
      m_gpio->setGpio(m_config.enW, true);
      break;
    case 3:
      m_gpio->setGpio(m_config.enW, false);
      m_dac->setOutput(m_config.pwmU, 0);
      m_dac->setOutput(m_config.pwmW, 0);
      m_dac->setOutput(m_config.pwmV, m_dutyCycle);
      m_gpio->setGpio(m_config.enU, true);
      m_gpio->setGpio(m_config.enV, true);
      break;
    case 4:
      m_gpio->setGpio(m_config.enV, false);
      m_dac->setOutput(m_config.pwmU, 0);
      m_dac->setOutput(m_config.pwmV, 0);
      m_dac->setOutput(m_config.pwmW, m_dutyCycle);
      m_gpio->setGpio(m_config.enU, true);
      m_gpio->setGpio(m_config.enW, true);
      break;
    case 5:
      m_gpio->setGpio(m_config.enU, false);
      m_dac->setOutput(m_config.pwmU, 0);
      m_dac->setOutput(m_config.pwmV, 0);
      m_dac->setOutput(m_config.pwmW, m_dutyCycle);
      m_gpio->setGpio(m_config.enV, true);
      m_gpio->setGpio(m_config.enW, true);
      break;
    default:
      break;
  }
}
