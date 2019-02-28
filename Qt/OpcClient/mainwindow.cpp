#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDebug>
#include <QTime>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QByteArray>
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>



#include "opcua_client.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_uaClient(new SimpleOPCUA::OPCUA_Client)
{
    ui->setupUi(this);
    m_refreshTimer = new QTimer(parent);
    m_time.start();
    connect(m_refreshTimer, SIGNAL(timeout()), this, SLOT(refreshTimer_elapsed()) );
    m_refreshTimer->start(250);
    ui->lblConnected->setText("client not yet connected");
    setWindowTitle("Anonmous OPC-UA connection");
    ui->robotControlA->setRobotName("A");
    ui->robotControlB->setRobotName("B");
    ui->robotControlC->setRobotName("C");

    m_monitoredItemId.resize(50);

    m_networkAccessManager = new QNetworkAccessManager();
    ui->progressBar->setValue(0);
    }

MainWindow::~MainWindow()
{
    delete m_uaClient;
    delete ui;
}


void MainWindow::on_pushButtonConnect_clicked()
{
    QString host = ui->lineEditHostname->text();
    QString port = ui->lineEditPort->text();

    bool result = m_uaClient->connectTo( QString("opc.tcp://%1:%2").arg(host).arg(port).toStdString() );
    if( !result )
    {
        QMessageBox::critical(this, "connection error", QString("Cannot connect to ").arg(host));
        return;
    }
    ui->pushButtonConnect->setEnabled(false);
    ui->pushButtonDisconnect->setEnabled(true);
}


void MainWindow::on_pushButtonDisconnect_clicked()
{
    m_uaClient->disconnect();
    ui->pushButtonConnect->setEnabled(true);
    ui->pushButtonDisconnect->setEnabled(false);
}


void MainWindow::refreshTimer_elapsed()
{
    static bool connectedOld = false;

    m_uaClient->runAsync();
    ui->lblConnected->setText( m_uaClient->connected() ? "client connected" : "client not connected");

    if( m_uaClient->connected() && !connectedOld )
    {
        addAxesSubscription();

    }
    connectedOld = m_uaClient->connected();
}



void MainWindow::on_btnSendProgram_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
          tr("Open Robot Program"), QDir::homePath(), tr("B&R Robot programs (*.st *.cnc)"));
    if( fileName.length() )
    {
        m_robotProgram = new QFile(fileName);
        QUrl url("ftp://" + ui->lineEditHostname->text() + "/Robotic.st" );
         url.setPort(21);
         url.setUserName("br");
         url.setPassword("brautomation");


         QNetworkRequest request(url);

         if (m_robotProgram->open(QIODevice::ReadOnly))
         {
            QNetworkReply *reply = m_networkAccessManager->put(request, m_robotProgram);
            connect(reply, &QNetworkReply::uploadProgress, this, &MainWindow::uploadProgress);
            connect( reply, &QNetworkReply::finished, this, &MainWindow::uploadFinished );
         }
    }
}

void MainWindow::uploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    if( bytesTotal )
    {
        double p = bytesSent / bytesTotal;
        ui->progressBar->setValue(100 * static_cast<int>(p) );
    }
}

void MainWindow::uploadFinished()
{
}
