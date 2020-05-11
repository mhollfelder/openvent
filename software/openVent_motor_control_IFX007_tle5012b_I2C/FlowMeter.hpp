 
#include <PressureSensorDPS310.h>


class FlowMeter
{
  public:

  FlowMeter(II2c* i2c = defaultII2c) :
    m_sensor0(0x77, i2c),
    m_sensor1(0x76, i2c)
  {
  }
  
  void initialize()
  {  
    m_sensor0.initialize();
    m_sensor1.initialize();

    getOffsets();
    resetFlow();
  }

  void getOffsets()
  {
    m_offset[0] = 0;
    m_offset[1] = 0;

    // caluclate an average of each offset
    const int count = 8;
    for (int i = count; i > 0; i--)
    {
      triggerMeasurements();
      readMeasurements();
      m_offset[0] += m_lastPressure[0];
      m_offset[1] += m_lastPressure[1];
    }
    m_offset[0] /= count;
    m_offset[1] /= count;
  }

  bool measurementsReady()
  {
    return m_sensor0.pressureReady() && m_sensor1.pressureReady();
  }
  
  void triggerMeasurements()
  {
    // at least trigger the measurements as close in time as possible
    // (todo: use SPI or variable I2C address to make both sensors receive the same start command)
    m_sensor0.startPressureMeasurements(false);
    m_sensor1.startPressureMeasurements(false);

    getTimeDelta();
  }

//    m_sensor0.startTemperatureMeasurements(false);
//    m_sensor1.startTemperatureMeasurements(false);
//
//    m_sensor0.getTemperature();
//    m_sensor1.getTemperature();    
      
  void readMeasurements()
  {
    m_lastPressure[0] = m_sensor0.getPressure();
    m_lastPressure[1] = m_sensor1.getPressure();
  }

  void getTimeDelta()
  {
    const auto t = millis();
    if (m_lastTime > 0)
    {
      m_deltaTime = t - m_lastTime; // switch to use of standard functions
    }
    m_lastTime = t;
  }

  void resetFlow()
  {
    m_lastTime = 0;
    m_deltaTime = 0;
  }

  float calculateVolumeDelta()
  {
    const float rho = 1.2041 * 1e-6; // for kg / ml
    const float r1 = 8e-3;
    const float r2 = 4e-3;
    const float cd = r1 / r2;
    const float area1 = PI * r1 * r1;

    const float factor = area1 * sqrt(2 / rho / (cd * cd - 1)) * 1e-3; // scale by 1e3 for milliseconds, check if microseconds would yield better
    const float deltaP = (m_lastPressure[0] - m_offset[0]) - (m_lastPressure[1] - m_offset[1]);
    float q;
    if (deltaP < 0)
    {
      q = -factor * sqrt(-deltaP);
    }
    else
    {
      q = factor * sqrt(deltaP);
    }
    return q * m_deltaTime;
  }

  float m_offset[2];  
  float m_lastPressure[2];
  uint32_t m_lastTime;
  float m_deltaTime;

  PressureSensorDPS310 m_sensor0, m_sensor1;

};
