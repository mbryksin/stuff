#include "toolbar.h"

#include <QMainWindow>
#include <QMenu>
#include <QPainter>
#include <QPainterPath>
#include <QSpinBox>
#include <QLabel>
#include <QToolTip>

#include <QToolBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <QGroupBox>

#include <stdlib.h>

ToolBar::ToolBar(const QString &title, QWidget *parent)
    : QToolBar(parent)
{
    setWindowTitle(title);
    setObjectName(title);
    setIconSize(QSize(32, 32));

    insertToolBox();

    setMovable(false);

    addAction(toggleViewAction());
    //toggleViewAction()->setShortcut(Qt::CTRL|Qt::Key_Q);
}

void ToolBar::insertToolBox()
{
    menuBox = new QToolBox();
    menuBox->setStyleSheet("QToolBox::tab { background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E1E1E1, stop: 0.4 #DDDDDD, stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3); border-radius: 3px; color: darkgray; }"
                       "QToolBox::tab:selected { font: italic; color: black;}");

    //----------------
    QGroupBox *connectToTRIK = new QGroupBox();
    QVBoxLayout *connectToTRIKLayout = new QVBoxLayout;
    QLabel* ipLabel = new QLabel("Connect to IP:");
    QLineEdit* ipTextEdit = new QLineEdit("192.168.0.0");
    ipTextEdit->setFixedSize(100,24);
    connectToTRIKLayout->addWidget(ipLabel);
    connectToTRIKLayout->addWidget(ipTextEdit);
    connectToTRIKLayout->addStretch(0);
    connectToTRIK->setLayout(connectToTRIKLayout);
    menuBox->addItem(connectToTRIK, "Connect");


    QGroupBox *settings = new QGroupBox();
    QVBoxLayout *settingsLayout = new QVBoxLayout;
    QCheckBox* logging = new QCheckBox("Logging", this);
    settingsLayout->addWidget(logging);
    settingsLayout->addStretch(0);
    settings->setLayout(settingsLayout);
    menuBox->addItem(settings, "Settings");
    //----------------

    QToolBox* telemetry = new QToolBox();
    telemetry->setStyleSheet("QToolBox::tab { background: gray; border-radius: 3px; color: darkgray; }"
                             "QToolBox::tab:selected { font: italic; color: black;}");
    menuBox->addItem(telemetry, "Telemetry");

    QGroupBox* sensors3D = new QGroupBox();
    QVBoxLayout* sensors3DLayout = new QVBoxLayout;
    QPushButton* accel=new QPushButton("Accelerometer",this);
    accel->setStyleSheet("QPushButton { background-color: rgb(170, 170, 170); border-style: outset; border-width: 0.5px; border-radius: 5px; border-color: beige; padding: 4px;}"
                         "QPushButton:pressed { background-color: rgb(200, 200, 200); border-style: inset; }");
    accelAction = new QAction(tr("Accelerometer"), this);
    connect(accel, SIGNAL(clicked()), accelAction, SIGNAL(triggered()));

    QPushButton* gyro=new QPushButton("Gyroscope",this);
    gyro->setStyleSheet("QPushButton { background-color: rgb(170, 170, 170); border-style: outset; border-width: 0.5px; border-radius: 5px; border-color: beige; padding: 4px;}"
                        "QPushButton:pressed { background-color: rgb(200, 200, 200); border-style: inset; }");
    gyroAction = new QAction(tr("Gyroscope"), this);
    gyroAction->setCheckable(true);
    connect(gyro, SIGNAL(clicked(bool)), gyroAction, SIGNAL(toggled(bool)));

    sensors3DLayout->addWidget(accel);
    sensors3DLayout->addWidget(gyro);
    sensors3DLayout->addStretch(0);
    sensors3D->setLayout(sensors3DLayout);
    telemetry->addItem(sensors3D,"3D sensors");

    QGroupBox* analogSensors = new QGroupBox();
    QVBoxLayout* analogSensorsLayout = new QVBoxLayout;
    QPushButton* analog=new QPushButton("Sensor 1",this);
    analogSensorsLayout->addWidget(analog);
    analogSensorsLayout->addStretch(0);
    analogSensors->setLayout(analogSensorsLayout);
    telemetry->addItem(analogSensors,"Analog sensors");

    QGroupBox* servoMotors = new QGroupBox();
    QVBoxLayout* servoMotorsLayout = new QVBoxLayout;
    QPushButton* smotor1=new QPushButton("Servomotor 1",this);
    servoMotorsLayout->addWidget(smotor1);
    servoMotorsLayout->addStretch(0);
    servoMotors->setLayout(servoMotorsLayout);
    telemetry->addItem(servoMotors,"Servomotors");

    QGroupBox* powerMotors = new QGroupBox();
    QVBoxLayout* powerMotorsLayout = new QVBoxLayout;
    QPushButton* pmotor1=new QPushButton("Motor 1",this);
    powerMotorsLayout->addWidget(pmotor1);
    powerMotorsLayout->addStretch(0);
    powerMotors->setLayout(powerMotorsLayout);
    telemetry->addItem(powerMotors,"Motors");

    QGroupBox* encoders = new QGroupBox();
    QVBoxLayout* encodersLayout = new QVBoxLayout;
    QPushButton* encoder=new QPushButton("Encoder 1",this);
    encodersLayout->addWidget(encoder);
    encodersLayout->addStretch(0);
    encoders->setLayout(encodersLayout);
    telemetry->addItem(encoders,"Encoders");

    QMenu* battery=new QMenu();
    telemetry->addItem(battery,"Battery");

    this->addWidget(menuBox);
}

void ToolBar::enterEvent(QEvent*)
{
}

void ToolBar::leaveEvent(QEvent*)
{
}
