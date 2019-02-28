#ifndef DIALOGAXIS_H
#define DIALOGAXIS_H

#include <QDialog>

namespace Ui {
class DialogAxis;
}

class DialogAxis : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAxis(QWidget *parent = nullptr);
    ~DialogAxis();

private:
    Ui::DialogAxis *ui;
};

#endif // DIALOGAXIS_H
