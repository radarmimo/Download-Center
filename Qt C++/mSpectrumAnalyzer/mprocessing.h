#ifndef MPROCESSING_H
#define MPROCESSING_H

#include <QThread>
#include <QObject>
#include <iostream>
#include <QVector>
#include <math.h>

class mProcessing : public QThread
{
public:
    explicit mProcessing(QObject *parent = nullptr);

    QVector<double> windwoing(QString Type, int Length);
    QVector<double> filtering(QString Type, int Length, double fc);
    QVector<double> smoothing(QString Type, int windowLength, QVector<double> signal);




private:


};

#endif // MPROCESSING_H
