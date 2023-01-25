#ifndef TEMPCONTROLLER_H
#define TEMPCONTROLLER_H

#include <QObject>


class TempController : public QObject
{
    Q_OBJECT
public:
    TempController();

    void    Init(double minTemp=16.0, double maxTemp=24.0);

    void    UpdateTemp(double Temp);

    void    SetMinTemp(double minTemp);
    void    SetMaxTemp(double maxTemp);

signals:
    void    SignalLog(QString Text);

    void    SignalUpdateMinTemp(double minTemp);
    void    SignalUpdateMaxTemp(double maxTemp);

    void    SignalHeating(bool bState);
    void    SignalCooling(bool bState);

private:
    void    Log(QString Text);

    double  m_minTemp=16.0;
    double  m_maxTemp=24.0;

    bool    m_bInit=false;
    bool    m_bHeating=false;
    bool    m_bCooling=false;
};

#endif // TEMPCONTROLLER_H
