#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDoubleSpinBox>

#include <math.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Heating Cooling control demo");

    //set a temperature starting point
    m_TempProbe.SetNewTarget(18.0);

    //set the room temperature GUI control
    ui->RoomTemp->setMinimum(0.0);
    ui->RoomTemp->setMaximum(30.0);
    ui->RoomTemp->setSingleStep(0.5);
    ui->RoomTemp->setSuffix("°C");
    ui->RoomTemp->setValue(18.0);
    connect(ui->RoomTemp,   QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            &m_TempProbe,   &TempProbeSimulator::SetNewTarget);
    ui->Log->append(QString("Room temperature initialized to: %1°C").arg(ui->RoomTemp->value(),4,'f',1));

    //set the minimum temperature GUI control
    ui->MinTemp->setMinimum(5.0);
    ui->MinTemp->setMaximum(21.0);
    ui->MinTemp->setSingleStep(0.5);
    ui->MinTemp->setSuffix("°C");
    ui->MinTemp->setValue(16.0);
    ui->Log->append(QString("minimum temperature initialized to: %1°C").arg(ui->MinTemp->value(),4,'f',1));

    //set the maximum temperature GUI control
    ui->MaxTemp->setMinimum(8.0);
    ui->MaxTemp->setMaximum(35.0);
    ui->MaxTemp->setSingleStep(0.5);
    ui->MaxTemp->setSuffix("°C");
    ui->MaxTemp->setValue(24.0);
    ui->Log->append(QString("maximum temperature initialized to: %1°C").arg(ui->MaxTemp->value(),4,'f',1));

    //heating LED
    m_pLedHeating = new LED(this);
    m_pLedHeating->setDiameter(4);
    m_pLedHeating->setColor(Qt::black);
    ui->LayoutValues->insertWidget(-1, m_pLedHeating);
    m_pLabelHeating = new QLabel("Heating:");
    ui->LayoutLabels->insertWidget(-1, m_pLabelHeating);

    //cooling LED
    m_pLedCooling = new LED(this);
    m_pLedCooling->setDiameter(4);
    m_pLedCooling->setColor(Qt::black);
    ui->LayoutValues->insertWidget(-1, m_pLedCooling);
    m_pLabelCooling = new QLabel("Cooling:");
    ui->LayoutLabels->insertWidget(-1, m_pLabelCooling);

    m_pTempController = new TempController();
    connect(m_pTempController,  &TempController::SignalLog,
            this,               &MainWindow::Log);
    connect(m_pTempController,  &TempController::SignalUpdateMinTemp,
            ui->MinTemp,        &QDoubleSpinBox::setValue);
    connect(m_pTempController,  &TempController::SignalUpdateMaxTemp,
            ui->MaxTemp,        &QDoubleSpinBox::setValue);
    connect(m_pTempController,  &TempController::SignalHeating,
            this,               &MainWindow::OnHeating);
    connect(m_pTempController,  &TempController::SignalCooling,
            this,               &MainWindow::OnCooling);

    connect(ui->MinTemp,        QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            m_pTempController,  &TempController::SetMinTemp);
    connect(ui->MaxTemp,        QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            m_pTempController,  &TempController::SetMaxTemp);

    m_pTempController->Init(18,25);


    connect( &m_TempTimer,  &QTimer::timeout,
             this,          &MainWindow::TempUpdate);

    m_TempTimer.start(500);

    ui->Log->append("started");
}

MainWindow::~MainWindow()
{
    delete m_pTempController;

    delete ui;
}


/**
 * @brief write something in to GUI log window
 * @param Text
 */
void MainWindow::Log(QString Text)
{
    ui->Log->append(Text);
}


/**
 * @brief MainWindow::OnHeating
 * @param bState
 */
void MainWindow::OnHeating(bool bState)
{
    if(bState==true)
    {
        m_pLedHeating->setColor(Qt::red);
    }
    else
    {
        m_pLedHeating->setColor(Qt::black);
    }
}


/**
 * @brief MainWindow::OnCooling
 * @param bState
 */
void MainWindow::OnCooling(bool bState)
{
    if(bState==true)
    {
        m_pLedCooling->setColor(Qt::blue);
    }
    else
    {
        m_pLedCooling->setColor(Qt::black);
    }
}


/**
 * @brief MainWindow::TempUpdate
 */
void MainWindow::TempUpdate()
{
    double NewTemp = m_TempProbe.read();

    if( fabs(NewTemp-m_LastRoomTemp)> 0.01)                                     //only print if the temp changed
    {
        Log( QString("%1°C").arg(NewTemp,4,'f',1) );
    }

    m_LastRoomTemp = NewTemp;                                                   //save the temperature to detect temperature changes

    m_pTempController->UpdateTemp(NewTemp);
}

