#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "TempProbe/TempProbeSimulator.h"
#include "TempController/TempController.h"
#include "Led/LED.h"

#include <QMainWindow>
#include <QTimer>
#include <QString>
#include <QLabel>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void    Log(QString Text);

public slots:
    void    OnHeating(bool bState);
    void    OnCooling(bool bState);

private slots:
    void    TempUpdate(void);

private:
    Ui::MainWindow *ui;

    double              m_LastRoomTemp=0.0;

    QTimer              m_TempTimer;
    TempProbeSimulator  m_TempProbe = TempProbeSimulator(20.0);

    TempController*     m_pTempController=NULL;

    QLabel*             m_pLabelHeating=NULL;
    LED*                m_pLedHeating=NULL;
    QLabel*             m_pLabelCooling=NULL;
    LED*                m_pLedCooling=NULL;
};
#endif // MAINWINDOW_H
