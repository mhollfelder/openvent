
// the following should be moved to a library

#include <PressureSensorDPS310.h>



class FlowMeter
{
  public:

  FlowMeter() :
    m_sensor0(0x77),
    m_sensor1(0x76)
  {
  }
  
  void initialize()
  {  
    m_sensor0.initialize();
    m_sensor1.initialize();
  }

  void doReadings()
  {
    // at least trigger the measurements as close in time as possible
    // (todo: use SPI or variable I2C address to make both sensors receive the same start command)
    m_sensor0.startPressureMeasurements(false);
    m_sensor1.startPressureMeasurements(false);
    
    m_lastPressure[0] = m_sensor0.getPressure();
    m_lastPressure[1] = m_sensor1.getPressure();


    // average/filter sensor reading

    // feed into calculation algorithm
    
  }

  float m_lastPressure[2];
  
  PressureSensorDPS310 m_sensor0, m_sensor1;

};
