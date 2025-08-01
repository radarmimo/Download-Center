#ifndef USRPRX_H
#define USRPRX_H

#include <vector>
#include <QThread>
#include <QObject>
#include <iostream>
#include <QVector>
#include <uhd/utils/thread_priority.hpp>
#include <uhd/utils/safe_main.hpp>
#include <uhd/usrp/multi_usrp.hpp>
#include <uhd/exception.hpp>
#include <uhd/types/tune_request.hpp>
#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include <boost/thread.hpp>
#include <chrono>


class usrpRx : public QThread
{
    Q_OBJECT
public:
    explicit usrpRx(QObject *parent = nullptr);
    void run();
    uhd::usrp::multi_usrp::sptr usrp;
    double rate, gain;
    int mSamples, nTimeFrame;
//    , RFB;
    std::string ant;
//    std::string subdev;
//    QVector<std::string> sweepArrayAnt;

    bool agc;
    QVector<double> sweepArrayFreqMHz;
//    QVector<double> sweepArrayAnt;
//    QVector<bool> sweepArrayAGC, sweepArrayDCoffset;
//    QVector<int> sweepArrayRF;

public: signals:
    void dataReady(QVector<double> dataI, QVector<double> dataQ);
    void usrpStatus(bool status, QString deviceAddress);

private:

};

#endif // USRPRX_H
