#pragma once


template <typename T>
class Pid
{
public:
    Pid(T Kp, T Ki, T Kd, T minOutput, T maxOutput, T setPoint = 0, T dt = 1)
    {
      setParameters(Kp, Ki, Kd, dt);
      changeSetPoint(setPoint);
      setLimits(minOutput, maxOutput);
      reset();
    }
    
    void reset()
    {
       m_error = 0;
       m_int = 0;
       m_output = 0;
    }
    
    void setParameters(T Kp, T Ki, T Kd, T dt = 1)
    {
        m_Kp = Kp;
        m_Ki = Ki * dt;
        m_Kd = Kd / dt;
    }
    
    void changeSetPoint(T setPoint)
    {
       m_setPoint = setPoint;
    }
          
    void setLimits(T maxOutput, T minOutput = 0)
    {
       m_maxOutput = maxOutput;
       m_minOutput = minOutput;
    }
    
    inline void clip()
    {
       if (m_output > m_maxOutput)
	   {
		   m_output = m_maxOutput;
	   }
       else if (m_output < m_minOutput)
	   {
		   m_output = m_minOutput;
	   }
    }
    
    void update(T input) noexcept
    {
        const T error = m_setPoint - input;

        const T p = m_Kp * error;
        m_int += m_Ki * error;
        const T d = m_Kd * (error - m_error);

        m_output = p + m_int + d;
        clip();

        m_error = error;
    }

    inline operator const T&()
    {
        return m_output;
    }

private:
    T m_error;
    T m_int;
    T m_output;

    T m_Kp;
    T m_Ki;
    T m_Kd;
    T m_setPoint;
    T m_minOutput;
    T m_maxOutput;
};
