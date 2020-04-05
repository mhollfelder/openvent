
// the following should be moved to a library

#include <Platform.h>


typedef struct
{
  // digital output pins
  uint16_t dis;
  uint16_t dir;
  uint16_t stp;

  uint32_t steps;
} MotorStepperPinConfig_t;

class MotorStepper
{
public:
  MotorStepper(const MotorStepperPinConfig_t &config, IGpio* gpio = defaultIGpio);
  
  inline void setSpeed(float rpm)
  {
    m_delay = microseconds_to_clock_ticks(1000000.f * 60 / rpm / m_config.steps /2); // rpm to (steps/ microseconds), /2 since we have a high and a low time per period
  }

  void stop()
  {
    // mutex
    m_stepsToMake = 0;
  }

  void step(int32_t steps)
  {
    // mutex
    m_stepsToMake += steps;
  }

  int32_t getStepsToMake()
  {
    return m_stepsToMake;
  }
  
  int32_t getTotalSteps()
  {
    return m_totalSteps;
  }

  void reset(bool modulo = false)
  {
    if (modulo)
    {
      const int32_t resetSteps = (-m_totalSteps + m_config.steps / 2) % m_config.steps - m_config.steps / 2;
      step(resetSteps);
    }
    else
    {
      step(-m_totalSteps);
    }
  }
  
  void runLoop();
  
private:
  void setDirection(bool direction);
  void outputStep();

  const MotorStepperPinConfig_t &m_config;
  IGpio* m_gpio;

  int32_t m_totalSteps;

  int32_t m_stepsToMake;
  bool m_direction;
  bool m_cycle;

  clock_ticks_t m_delay;
  clock_ticks_t m_nextTimepoint;
};

MotorStepper::MotorStepper(const MotorStepperPinConfig_t &config, IGpio* gpio) :
  m_config {config},
  m_gpio {gpio},
  m_totalSteps {0},
  m_direction {false},
  m_cycle {true}
{
  m_gpio->configureGpio(m_config.dis, GPIO_MODE_OUTPUT_PUSH_PULL | GPIO_FLAG_OUTPUT_INITIAL_HIGH);
  m_gpio->configureGpio(m_config.dir, GPIO_MODE_OUTPUT_PUSH_PULL);
  m_gpio->configureGpio(m_config.stp, GPIO_MODE_OUTPUT_PUSH_PULL);
}

void MotorStepper::setDirection(bool direction)
{
  if (m_direction != direction)
  {
    m_direction = direction;
    m_gpio->setGpio(m_config.dir, direction);
  }
}

void MotorStepper::outputStep()
{
  m_gpio->setGpio(m_config.stp, m_cycle);
  m_cycle = !m_cycle;
  m_nextTimepoint += m_delay; 
}

void MotorStepper::runLoop()
{
  if (m_cycle)
  {
    if (m_stepsToMake != 0)
    {
      if (clock_has_passed(m_nextTimepoint))
      {
        // mutex
        if (m_stepsToMake < 0)
        {
          setDirection(false);
          m_stepsToMake++;
          m_totalSteps--;
        }
        else
        {
          setDirection(true);
          m_stepsToMake--;
          m_totalSteps++;
        }
  
        outputStep();
      }
    }
  }
  else if (clock_has_passed(m_nextTimepoint))
  {
    outputStep();
  }
}


static const MotorStepperPinConfig_t msConfig = {
  11, // .dis
  9, // .dir
  10, // .stp
  800, // .steps
};

MotorStepper ms(msConfig);


int rotationsPerBreath = 5;
int breathsPerMinute = 10;
int rpm;
int upDown = -1;


void setup() {
  // put your setup code here, to run once:

  rpm = 60 * rotationsPerBreath * breathsPerMinute;
  ms.setSpeed(rpm);  

  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  ms.runLoop();

  if (ms.getStepsToMake() == 0)
  {
    upDown *= -1;
    ms.step(upDown * rotationsPerBreath * msConfig.steps);
  }
  
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
