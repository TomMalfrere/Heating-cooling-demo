#ifndef TEMPPROBESIMULATOR_H
#define TEMPPROBESIMULATOR_H

#include <QObject>


class TempProbeSimulator : public QObject
{
    Q_OBJECT
public:
    TempProbeSimulator(double startvalue=20.0);

    double  read();
    void    SetNewTarget(double NewValue);

private:
    double  m_target;
    double  m_CurrentValue;
};

#endif // TEMPPROBESIMULATOR_H
