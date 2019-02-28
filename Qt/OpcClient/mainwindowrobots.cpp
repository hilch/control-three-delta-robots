#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDebug>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include <QByteArray>
#include <string>
#include <exception>

#include "opcua_client.h"
#include "open62541.h"

int MainWindow::string2int(std::string x)
{
    try {
        return std::stoi(x);
    } catch (std::invalid_argument) {
        return 0;
    }

}


void MainWindow::addAxesSubscription()
{
    bool result;
    RobotControl * const robotWidgets[]={ ui->robotControlA, ui->robotControlB, ui->robotControlC};


    result = m_uaClient->addSubscription(m_subscriptionId, 200);
    if( result )
    {
        for( int i = 0; i<3; ++i )
        {
            std::string opcPrefix = "ns=6;s=::delta:robot[" + std::to_string(i) + "].delta";

            result =  m_uaClient->addMonitoredItem( opcPrefix + ".Info.Path.CurrentPathPosition" , m_subscriptionId, m_monitoredItemId[0],
                                                    [=]( std::string value, int64_t sourceTimeStamp) { Q_UNUSED(sourceTimeStamp) robotWidgets[i]->setActualPosition(QString::fromStdString(value));  } );

            result =  m_uaClient->addMonitoredItem( opcPrefix + ".X" , m_subscriptionId, m_monitoredItemId[0],
                                                    [=]( std::string value, int64_t sourceTimeStamp) { Q_UNUSED(sourceTimeStamp) robotWidgets[i]->setActualPositionX(QString::fromStdString(value));  } );

            result =  m_uaClient->addMonitoredItem( opcPrefix + ".Y" , m_subscriptionId, m_monitoredItemId[0],
                                                    [=]( std::string value, int64_t sourceTimeStamp) { Q_UNUSED(sourceTimeStamp) robotWidgets[i]->setActualPositionY(QString::fromStdString(value));  } );

            result =  m_uaClient->addMonitoredItem( opcPrefix + ".Z" , m_subscriptionId, m_monitoredItemId[0],
                                                    [=]( std::string value, int64_t sourceTimeStamp) { Q_UNUSED(sourceTimeStamp) robotWidgets[i]->setActualPositionZ(QString::fromStdString(value));  } );

            result =  m_uaClient->addMonitoredItem( opcPrefix + ".Info.Program.ProgramMonitor.BlockMonitor.Current" , m_subscriptionId, m_monitoredItemId[0],
                                                [=]( std::string value, int64_t sourceTimeStamp) { Q_UNUSED(sourceTimeStamp) robotWidgets[i]->setCurrentBlock(QString::fromStdString(value));  } );


            result =  m_uaClient->addMonitoredItem( opcPrefix + ".StatusID" , m_subscriptionId, m_monitoredItemId[3],
                                                    [=]( std::string value, int64_t sourceTimeStamp) { Q_UNUSED(sourceTimeStamp) robotWidgets[i]->setStatusID(QString::fromStdString(value));   } );

            result =  m_uaClient->addMonitoredItem( opcPrefix + ".Info.ReadyToPowerOn" , m_subscriptionId, m_monitoredItemId[4],
                                                     [=]( std::string value, int64_t sourceTimeStamp) { Q_UNUSED(sourceTimeStamp) robotWidgets[i]->setAxisStatus( string2int(value));   } );

            result =  m_uaClient->addMonitoredItem( opcPrefix + ".PowerOn" , m_subscriptionId, m_monitoredItemId[5],
                                                    [=]( std::string value, int64_t sourceTimeStamp) { Q_UNUSED(sourceTimeStamp) robotWidgets[i]->setControllerStatus( string2int(value));   } );

            result =  m_uaClient->addMonitoredItem( opcPrefix + ".IsHomed" , m_subscriptionId, m_monitoredItemId[6],
                                                    [=]( std::string value, int64_t sourceTimeStamp) { Q_UNUSED(sourceTimeStamp) robotWidgets[i]->setHomingStatus(string2int(value)); } );

            result =  m_uaClient->addMonitoredItem( opcPrefix + ".InMotion" , m_subscriptionId, m_monitoredItemId[7],
                                                    [=]( std::string value, int64_t sourceTimeStamp) { Q_UNUSED(sourceTimeStamp) robotWidgets[i]->setMotionStatus( value == "1"? 1: 0 ) ; } );

        }
    }

}



/* robot A --------------------------------------------------------------------------------- */

void MainWindow::on_robotControlA_onBtnPower()
{
    if( ui->robotControlA->controllerStatus() )
        m_uaClient->writeValueAttribute("ns=6;s=::delta:robot[0].delta.Power","0"); /* switch off */
    else
        m_uaClient->writeValueAttribute("ns=6;s=::delta:robot[0].delta.Power","1");
}

void MainWindow::on_robotControlA_onBtnHome()
{
    m_uaClient->writeValueAttribute("ns=6;s=::delta:robot[0].delta.Home","1");
}

void MainWindow::on_robotControlA_onBtnMoveProgram()
{
    m_uaClient->writeValueAttribute("ns=6;s=::delta:robot[0].delta.MoveProgram","1");
}

void MainWindow::on_robotControlA_onBtnHalt()
{
    m_uaClient->writeValueAttribute("ns=6;s=::delta:robot[0].delta.Stop","1");
}

void MainWindow::on_robotControlA_onBtnAcknowledge()
{
    m_uaClient->writeValueAttribute("ns=6;s=::delta:robot[0].delta.ErrorReset","1");
}


/* robot B --------------------------------------------------------------------------------- */

void MainWindow::on_robotControlB_onBtnPower()
{
    if( ui->robotControlB->controllerStatus() )
        m_uaClient->writeValueAttribute("ns=6;s=::delta:robot[1].delta.Power","0"); /* switch off */
    else
        m_uaClient->writeValueAttribute("ns=6;s=::delta:robot[1].delta.Power","1");
}

void MainWindow::on_robotControlB_onBtnHome()
{
    m_uaClient->writeValueAttribute("ns=6;s=::delta:robot[1].delta.Home","1");
}

void MainWindow::on_robotControlB_onBtnMoveProgram()
{
    m_uaClient->writeValueAttribute("ns=6;s=::delta:robot[1].delta.MoveProgram","1");
}

void MainWindow::on_robotControlB_onBtnHalt()
{
    m_uaClient->writeValueAttribute("ns=6;s=::delta:robot[1].delta.Stop","1");
}

void MainWindow::on_robotControlB_onBtnAcknowledge()
{
    m_uaClient->writeValueAttribute("ns=6;s=::delta:robot[1].delta.ErrorReset","1");
}



/* robot C --------------------------------------------------------------------------------- */

void MainWindow::on_robotControlC_onBtnPower()
{
    if( ui->robotControlC->controllerStatus() )
        m_uaClient->writeValueAttribute("ns=6;s=::delta:robot[2].delta.Power","0"); /* switch off */
    else
        m_uaClient->writeValueAttribute("ns=6;s=::delta:robot[2].delta.Power","1");
}

void MainWindow::on_robotControlC_onBtnHome()
{
    m_uaClient->writeValueAttribute("ns=6;s=::delta:robot[2].delta.Home","1");
}

void MainWindow::on_robotControlC_onBtnMoveProgram()
{
    m_uaClient->writeValueAttribute("ns=6;s=::delta:robot[2].delta.MoveProgram","1");
}

void MainWindow::on_robotControlC_onBtnHalt()
{
    m_uaClient->writeValueAttribute("ns=6;s=::delta:robot[2].delta.Stop","1");
}

void MainWindow::on_robotControlC_onBtnAcknowledge()
{
    m_uaClient->writeValueAttribute("ns=6;s=::delta:robot[2].delta.ErrorReset","1");
}

