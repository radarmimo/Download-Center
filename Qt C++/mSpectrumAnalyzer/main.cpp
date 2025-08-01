#include "mainwindow.h"

#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QThread::currentThread()->setPriority(QThread::HighPriority);
    return a.exec();
}
