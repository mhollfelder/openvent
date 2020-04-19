
#pragma once


template <typename T>
class MovingAverage
{
public:
    MovingAverage(unsigned int count)
    {
        reset(count);
    }

    void reset(unsigned int count = 0) noexcept
    {
        if (count)
        {
            m_count = count;
        }
        m_currentCount = 0;
        m_average = 0;
    }

    void update(T value) noexcept
    {
        if (m_currentCount < m_count)
        {
            m_currentCount++;
        }
        m_average += (value - m_average) / m_currentCount;
    }

    inline operator const T&() noexcept
    {
        return m_average;
    }

private:
    unsigned int m_count;
    unsigned int m_currentCount;
    T m_average;
};
