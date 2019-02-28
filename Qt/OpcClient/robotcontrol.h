#ifndef AXISCONTROL_H
#define AXISCONTROL_H

#include <QGroupBox>
#include <vector>


class QPushButton;
class QLabel;
class QLineEdit;

class RobotControl : public QGroupBox
{
    Q_OBJECT

public:
    explicit RobotControl(QWidget *parent = nullptr);
    bool controllerStatus(void);

signals:
    void onBtnPower(void);
    void onBtnHome(void);
    void onBtnMoveProgram(void);
    void onBtnHalt(void);
    void onBtnAcknowledge(void);

public slots:
    void setRobotName(QString axisName);
    void setActualPosition( QString position );
    void setActualPositionX( QString position );
    void setActualPositionY( QString position );
    void setActualPositionZ( QString position );
    void setCurrentBlock( QString block );
    void setAxisStatus(bool status);
    void setHomingStatus(bool status);
    void setControllerStatus(bool status);
    void setMotionStatus(int status);
    void setStatusID(QString position);

private:
    bool m_controllerStatus;
    QLineEdit *m_txtActPosition;
    QLineEdit *m_txtActPositionX;
    QLineEdit *m_txtActPositionY;
    QLineEdit *m_txtActPositionZ;
    QLineEdit *m_txtCurrentBlock;
    QLineEdit *m_lineEditStatusID;
    QLabel *m_lblAxisStatus;
    QLabel *m_lblHomingStatus;
    QLabel *m_lblControllerStatus;
    QLabel *m_lblMotionStatus;
    QPushButton *m_btnPower;
    QPushButton *m_btnHome;
    QPushButton *m_btnMoveProgram;
    QPushButton *m_btnHalt;
    QPushButton *m_btnAcknowledge;
    std::vector<QPixmap*> m_icons;
};

#endif // AXISCONTROL_H
