#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    setlocale(LC_ALL,"en_US.UTF-8");
    w.show();

    return a.exec();
}
