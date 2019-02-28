#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <string>
#include <vector>

namespace Ui {
    class MainWindow;
}

namespace SimpleOPCUA {
    class OPCUA_Client;
}


class QTime;
class QNetworkAccessManager;
class QFile;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButtonConnect_clicked();

    void on_pushButtonDisconnect_clicked();

    void refreshTimer_elapsed();

    void addAxesSubscription();

    void on_robotControlA_onBtnPower();

    void on_robotControlA_onBtnMoveProgram();

    void on_robotControlB_onBtnPower();

    void on_robotControlB_onBtnHome();

    void on_robotControlB_onBtnMoveProgram();

    void on_robotControlC_onBtnPower();

    void on_robotControlC_onBtnHome();

    void on_robotControlC_onBtnMoveProgram();

    void on_robotControlA_onBtnHalt();

    void on_robotControlB_onBtnHalt();

    void on_robotControlC_onBtnHalt();

    void on_robotControlA_onBtnHome();

    void on_robotControlA_onBtnAcknowledge();

    void on_robotControlB_onBtnAcknowledge();

    void on_robotControlC_onBtnAcknowledge();

    void on_btnSendProgram_clicked();

    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
    void uploadFinished(void);
private:
    Ui::MainWindow *ui;
    SimpleOPCUA::OPCUA_Client *m_uaClient;
    uint32_t m_subscriptionId;
    std::vector<uint32_t> m_monitoredItemId;
    QTimer *m_refreshTimer;
    QTime m_time;
    QNetworkAccessManager *m_networkAccessManager;
    QFile *m_robotProgram;
    static int string2int(std::string x);
};





#endif // MAINWINDOW_H
