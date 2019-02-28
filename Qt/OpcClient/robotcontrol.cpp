#include "robotcontrol.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QStyle>
#include <QDebug>

using std::vector;

RobotControl::RobotControl(QWidget *parent) : QGroupBox (parent)
{
    setTitle("???");
    QGridLayout *layout = new QGridLayout();

    m_icons.push_back(new QPixmap(":/images/AxisError.PNG"));
    m_icons.push_back(new QPixmap(":/images/AxisOK.PNG"));
    m_icons.push_back(new QPixmap(":/images/ControllerOff_32x32.png"));
    m_icons.push_back(new QPixmap(":/images/ControllerOn_32x32.png"));
    m_icons.push_back(new QPixmap(":/images/HomingNotOK.PNG"));
    m_icons.push_back(new QPixmap(":/images/HomingOK.PNG"));
    m_icons.push_back(new QPixmap(":/images/stop.png"));
    m_icons.push_back(new QPixmap(":/images/motion.png"));

    m_lblAxisStatus = new QLabel();
    m_lblControllerStatus = new QLabel();
    m_lblHomingStatus = new QLabel();
    m_lblHomingStatus = new QLabel();
    m_lblMotionStatus = new QLabel();

    m_txtActPosition = new QLineEdit();
    m_txtActPosition->setReadOnly(true);
    m_txtActPosition->setAlignment(Qt::AlignRight);
    setActualPosition("3.14");

    m_txtActPositionX = new QLineEdit();
    m_txtActPositionX->setReadOnly(true);
    m_txtActPositionX->setAlignment(Qt::AlignRight);
    setActualPositionX("0.0");

    m_txtActPositionY = new QLineEdit();
    m_txtActPositionY->setReadOnly(true);
    m_txtActPositionY->setAlignment(Qt::AlignRight);
    setActualPositionY("0.0");

    m_txtActPositionZ = new QLineEdit();
    m_txtActPositionZ->setReadOnly(true);
    m_txtActPositionZ->setAlignment(Qt::AlignRight);
    setActualPositionZ("0.0");

    m_txtCurrentBlock = new QLineEdit();
    m_txtCurrentBlock->setReadOnly(true);
    m_txtCurrentBlock->setAlignment(Qt::AlignLeft);
    setCurrentBlock("<emtpy>");

    m_lineEditStatusID = new QLineEdit();
    m_lineEditStatusID->setReadOnly(true);
    m_lineEditStatusID->setAlignment(Qt::AlignRight);
    setStatusID("-1");

    m_btnPower = new QPushButton("Power");
    connect( m_btnPower, &QPushButton::clicked, this, &RobotControl::onBtnPower);

    m_btnHome = new QPushButton("Home");
    connect( m_btnHome, &QPushButton::clicked, this, &RobotControl::onBtnHome);

    m_btnMoveProgram = new QPushButton("Move");
    connect( m_btnMoveProgram, &QPushButton::clicked, this, &RobotControl::onBtnMoveProgram);
    m_btnMoveProgram->setEnabled(false);

    m_btnHalt = new QPushButton("Halt");
    connect( m_btnHalt, &QPushButton::clicked, this, &RobotControl::onBtnHalt );

    m_btnHalt = new QPushButton("Halt");
    connect( m_btnHalt, &QPushButton::clicked, this, &RobotControl::onBtnHalt );

    m_btnAcknowledge = new QPushButton("Ack");
    connect( m_btnAcknowledge, &QPushButton::clicked, this, &RobotControl::onBtnAcknowledge );


    int row = 0;

    layout->addWidget( m_lblAxisStatus, row,0 );

    ++row;
    layout->addWidget( new QLabel("Actual Path Position"), row, 0, 1, 2 );
    layout->addWidget(m_txtActPosition, row, 2 );

    ++row;
    layout->addWidget( new QLabel("Actual Position X"), row, 0, 1, 2 );
    layout->addWidget(m_txtActPositionX, row, 2 );

    ++row;
    layout->addWidget( new QLabel("Actual Position Y"), row, 0, 1, 2 );
    layout->addWidget(m_txtActPositionY, row, 2 );

    ++row;
    layout->addWidget( new QLabel("Actual Position Z"), row, 0, 1, 2 );
    layout->addWidget(m_txtActPositionZ, row, 2 );

    ++row;
    layout->addWidget( new QLabel("Current Block"), row, 0 );

    ++row;
    layout->addWidget(m_txtCurrentBlock, row, 0, 1, 3);

    ++row;
    layout->addWidget( new QLabel("StatusID"), row, 0, 1, 2 );
    layout->addWidget(m_lineEditStatusID, row, 2 );

    ++row;
    layout->addWidget( m_lblControllerStatus, row,0 );
    layout->addWidget( m_lblHomingStatus, row,1 );
    layout->addWidget( m_lblMotionStatus, row,2 );

    ++row;
    layout->addWidget( m_btnPower, row,0 );
    layout->addWidget( m_btnHome, row,1 );
    layout->addWidget( m_btnAcknowledge, row,2 );

    ++row;
    layout->addWidget( m_btnMoveProgram, row,0 );
    layout->addWidget( m_btnHalt, row, 1 );


    setLayout(layout);

    setAxisStatus(false);
    setHomingStatus(false);
    setMotionStatus(0);
    setControllerStatus(false);
    show();
}

bool RobotControl::controllerStatus()
{
   return( m_controllerStatus );
}

void RobotControl::setRobotName(QString axisName)
{
    setTitle( axisName );
}

void RobotControl::setActualPosition(QString position)
{
    double x = position.toDouble();
    m_txtActPosition->setText(QString::number(x, 'f',2));
}

void RobotControl::setActualPositionX(QString position)
{
    double x = position.toDouble();
    m_txtActPositionX->setText(QString::number(x, 'f',2));
}

void RobotControl::setActualPositionY(QString position)
{
    double x = position.toDouble();
    m_txtActPositionY->setText(QString::number(x, 'f',2));
}

void RobotControl::setActualPositionZ(QString position)
{
    double x = position.toDouble();
    m_txtActPositionZ->setText(QString::number(x, 'f',2));
}

void RobotControl::setCurrentBlock(QString block)
{
  m_txtCurrentBlock->setText(block);
}


void RobotControl::setStatusID(QString id)
{
    m_lineEditStatusID->setText(id);

    if( id.toInt() )
        m_lineEditStatusID->setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(0, 0, 0);");
    else
        m_lineEditStatusID->setStyleSheet("background-color: rgb(0, 170, 0);color: rgb(255, 255, 255);");
}

void RobotControl::setAxisStatus(bool status)
{
    m_lblAxisStatus->setPixmap( status ? *m_icons.at(1) : *m_icons.at(0));
}

void RobotControl::setHomingStatus(bool status)
{
    m_lblHomingStatus->setPixmap(status ? *m_icons.at(5) : *m_icons.at(4));
}

void RobotControl::setControllerStatus(bool status)
{
    m_lblControllerStatus->setPixmap( status ? *m_icons.at(3) : *m_icons.at(2));
    m_controllerStatus = status;
    m_btnMoveProgram->setEnabled(status);
}

void RobotControl::setMotionStatus(int status)
{
    switch( status )
    {
    case 0:  /* stop */
        m_lblMotionStatus->setPixmap( *m_icons.at(6));
        break;

    case 1:  /* continuous motion */
        m_lblMotionStatus->setPixmap( *m_icons.at(7));
        break;

    case 2:
        break;
    }

}


