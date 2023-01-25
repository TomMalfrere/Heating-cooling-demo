#include "TempController/TempController.h"

#include "Text.h"

#define MIN_MAX_DELTA 2.0

/**
 * @brief TempController::TempController
 * @param minTemp
 * @param maxTemp
 */
TempController::TempController()
{
}


/**
 * @brief TempController::Init
 * @param minTemp
 * @param maxTemp
 */
void TempController::Init(double minTemp, double maxTemp)
{
    m_minTemp = minTemp;
    m_maxTemp = maxTemp;

    if( m_minTemp > m_maxTemp - MIN_MAX_DELTA)
    {
        m_maxTemp = m_minTemp + MIN_MAX_DELTA;
    }

    m_bInit=true;

    emit SignalUpdateMinTemp(m_minTemp);
    emit SignalUpdateMaxTemp(m_maxTemp);
}


/**
 * @brief TempController::UpdateTemp
 * @param Temp
 */
void TempController::UpdateTemp(double Temp)
{
    //Log(QString("Controller received new temp: %1%2").arg(Temp).arg(UNIT));

    if( m_bHeating==true )
    {
        if(Temp > m_minTemp+MIN_MAX_DELTA/2)
        {
            m_bHeating = false;
            Log("Heating => OFF");
        }
    }
    else
    {
        if(Temp < m_minTemp-0.01)
        {
            m_bHeating = true;
            Log("Heating => ON");
        }
    }

    if( m_bCooling==true )
    {
        if(Temp < m_maxTemp-MIN_MAX_DELTA/2)
        {
            m_bCooling = false;
            Log("Cooling => OFF");
        }
    }
    else
    {
        if(Temp > m_maxTemp+0.01)
        {
            m_bCooling = true;
            Log("Cooling => ON");
        }
    }

    emit SignalCooling(m_bCooling);
    emit SignalHeating(m_bHeating);
}


/**
 * @brief TempController::SetMinTemp
 * @param minTemp
 */
void TempController::SetMinTemp(double minTemp)
{
    if( minTemp < m_maxTemp-MIN_MAX_DELTA)
    {
        m_minTemp = minTemp;

        //Log(QString("controller min temp:%1%2").arg(m_minTemp).arg(UNIT));
    }
    else
    {
        Log("Invalid min temp");
    }

    emit SignalUpdateMinTemp(m_minTemp);
}


/**
 * @brief TempController::SetMaxTemp
 * @param maxTemp
 */
void TempController::SetMaxTemp(double maxTemp)
{
    if( maxTemp > m_minTemp+MIN_MAX_DELTA)
    {
        m_maxTemp = maxTemp;

        //Log(QString("controller max temp:%1%2").arg(m_maxTemp).arg(UNIT));
    }
    else
    {
        Log("Invalid max temp");
    }

    emit SignalUpdateMaxTemp(m_maxTemp);
}


/**
 * @brief TempController::Log
 * @param Text
 */
void TempController::Log(QString Text)
{
    emit SignalLog(Text);
}
