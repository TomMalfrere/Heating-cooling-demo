#include "TempProbeSimulator.h"

#include "math.h"

TempProbeSimulator::TempProbeSimulator(double startvalue)
{
    m_target = startvalue;
    m_CurrentValue = startvalue;
}


/**
 * @brief TempProbeSimulator::read
 * @return
 */
double TempProbeSimulator::read()
{
    double delta = m_CurrentValue - m_target;
    if( fabs(delta) > 0.01 )                                //fix rounding error with floats
    {
        if( delta > 0 )
        {
            m_CurrentValue -= 0.1;
        }
        else
        {
            m_CurrentValue += 0.1;
        }
    }

    return m_CurrentValue;
}


/**
 * @brief TempProbeSimulator::SetNewTarget
 * @param NewValue
 */
void TempProbeSimulator::SetNewTarget(double NewValue)
{
    if( NewValue < 50.0 and
        NewValue > -20.0 )
    {
        m_target = NewValue;
    }
}
