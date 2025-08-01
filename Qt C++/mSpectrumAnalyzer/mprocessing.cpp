#include "mprocessing.h"

mProcessing::mProcessing(QObject *parent)
    : QThread{parent}
{

}

QVector<double> mProcessing::windwoing(QString Type, int Length)
{
    QVector<double> weight;

    double multiplier;
    for (int i = 0; i < Length; ++i) {
        if (Type == "Hann") {
            multiplier = 0.5 * (1 - cos(2*M_PI*i/(Length-1)));
        }else if (Type == "Hamming"){
            multiplier = 0.54 - 0.46 * cos(2 * M_PI / (Length-1));
        }
        else if (Type == "Blackman"){
            multiplier = 0.42 - 0.5 * cos(2 * M_PI * i / (Length - 1)) + 0.08 * cos(4 * M_PI * i /(Length - 1));
        }else if(Type == "Blackman-Harris"){
            multiplier = 0.359 - 0.488 * cos(2 * M_PI * i /(Length-1)) + 0.141 * cos(4* M_PI * i/(Length-1)) - 0.011 * cos(6*M_PI * i /(Length-1));
        }else if(Type == "FlatTop"){
            multiplier = 0.216  - 0.417 * cos(2 * M_PI * i/(Length-1)) + 0.277 * cos(4 * M_PI * i /(Length-1)) - 0.084 * cos(6 * M_PI * i /(Length - 1)) + 0.007 * cos(8 * M_PI * i/(Length - 1));
        }
        else{
            multiplier = 1;
        }
        weight.push_back(multiplier);
    }

//    if (Type == "Hamming") {
//        for (int i = 0; i < Length; i++) {
//            double multiplier = 0.5 * (1 - cos(2*M_PI*i/(Length-1)));
//            weight[i] = multiplier;
//        }
//    }

//    if (Type == "Blackman") {
//        for (int i = 0; i < Length; i++) {
//            double multiplier = 0.42 - 0.5 * cos(2 * M_PI * i / (Length - 1)) + 0.08 * cos(4 * M_PI * i /(Length - 1));
//            weight[i] = multiplier;
//        }
//    }

    return weight;

}

QVector<double> mProcessing::filtering(QString Type, int Length, double fc)
{
    double wc = Length * fc;

    QVector<double> weight;
    for (int i = 0; i < Length; ++i) {
        double n = -M_PI + (i *2* M_PI)/Length;
        if (n == 0) {
            weight.push_back(weight.back());
            continue;
        }
        double multiplier =  20*sin(wc * n)/(M_PI * n * Length);

//        maxFilter = std::max(multiplier,maxFilter);
        weight.push_back(multiplier);
    }
    return weight;

}

QVector<double> mProcessing::smoothing(QString Type, int windowLength, QVector<double> signal)
{
    QVector<double> smoothedSignal;
    if (Type == "mean") {
        for (int i = 0; i < signal.size() - windowLength; ++i) {
            double val = 0;
            for (int j = 0; j < windowLength; ++j) {
                val += signal[i+j];

            }
            val = val / windowLength;
            smoothedSignal.push_back(val);


        }
        return smoothedSignal;

    }
    if (Type == "max") {
        for (int i = 0; i < signal.size() - windowLength; ++i) {
            double val = -1000;
            for (int j = 0; j < windowLength; ++j) {
                val = std::max(val,signal[i+j]);
            }

            smoothedSignal.push_back(val);


        }
        return smoothedSignal;

    }

    if (Type == "envelop") {
        for (int i = 0; i < signal.size() - windowLength; ++i) {
            double val = 0;
            for (int j = 0; j < windowLength; ++j) {
                val += signal[i+j];

            }
            val = val / windowLength;
            val = std::max(signal[i] , val);


            smoothedSignal.push_back(val);


        }
        return smoothedSignal;

    }

}



