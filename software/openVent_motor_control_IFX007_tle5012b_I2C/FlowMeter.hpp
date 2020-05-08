 
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
  }

  void getOffsets()
  {
    m_offset[0] = 0;
    m_offset[1] = 0;

    // caluclate an average of each offset
    const int count = 8;
    int i;
    for (i = count; i > 0; i--)
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

  float m_offset[2];  
  float m_lastPressure[2];

  PressureSensorDPS310 m_sensor0, m_sensor1;

};
