#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QVector>
#include <QMetaType>
#include "qcustomplot.h"
#include "usrprx.h"
#include <stdio.h>
#include <math.h>
#include <fftw3.h>
#include <QElapsedTimer>
#include "mprocessing.h"
#include <QMenu>
#include <QComboBox>
#include <QWidgetAction>
#include <QTabWidget>



#define REAL 0
#define IMAG 1
// #define sampleRateMHz 56

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    usrpRx* threadUSRPrx = new usrpRx();

protected:
    virtual void closeEvent(QCloseEvent* event) override;

public slots:


private slots:
    void onDataReady(QVector<double> dataI, QVector<double> dataQ);
    void onUSRPstatus(bool status, QString deviceAddress);
    void onDockInitialize();
    void onPlotInitialize();
    void onSettingInitialize();
    void onSignalSlotsConnection();

    void on_comboBox_AntennaSingle_currentIndexChanged(int index);

    void plotTimeDomain(QVector<double> &dataI, QVector<double> &dataQ);

    void calcSpectrum(QVector<double> &avgFFToverTimeFrame, QVector<double> &fftavgRMS,
                      QVector<double> &fftIndex, QVector<double> &fftVal, QVector<double> &fftIndexSweep,
                      QVector<double> &fftMaxHoldDB, QVector<double> &fftMinHoldDB,
                      double &currentFreqMHz, QVector<double> &sweepArray,
                      QVector<double> &avgRMS, QVector<double> &maxHold,
                      QVector<double> &minHold);


    void plotSpectrum(QVector<double> &fftIndex, QVector<double> &sweepIndex,
                      QVector<double> &fftVal, QVector<double> &fftavgRMS,
                      QVector<double> &fftMaxHoldDB, QVector<double> &fftMinHoldDB);

    void plotWaterfall(QVector<double> &fftavgRMS);

    void plotConstellation(QVector<double> &constI, QVector<double> &constQ);

    void calcFFT(QVector<double> &dataI, QVector<double> &dataQ, QVector<double> &avgFFToverTimeFrame, QVector<double> &constI, QVector<double> &constQ);
    void calcAvgMaxMin(QVector<double> &avgFFToverTimeFrame,
                       int &sCounter, QVector<double> &sweepArrayFreqMHz,
                       QVector<double> &avgRMS, QVector<QVector<double>>&avgMatrix,
                       QVector<double> &maxHold, QVector<double> &minHold, int &avgIndex);

    void on_comboBox_nFFT_currentIndexChanged(int index);

    void on_mouseDoubleClickPlot1();
    void on_mouseDoubleClickPlot2();
    void on_mouseDoubleClickPlot3();

    void on_doubleSpinBox_SampleRateMHz_editingFinished();
    void on_spinBox_mSamples_editingFinished();
    void on_doubleSpinBox_TimeFrameUS_editingFinished();

    void on_pushButton_Test_clicked();

    void on_comboBox_WindowType_currentTextChanged(const QString &arg1);

//    void on_spinBox_WaterfallSize_editingFinished();

    void on_comboBox_Gradient_currentTextChanged(const QString &arg1);
    void contextMenuRequest(QPoint pos);
    void showConstellationGraph();

    void on_actionFind_Devices_triggered();
    void on_actionStop_Device_triggered();


    void on_actionAverage_triggered();
    void on_actionSample_triggered();
    void on_actionMax_Hold_triggered();
    void on_actionMin_Hold_triggered();

    void on_verticalSlider_valueChanged(int value);

    void on_doubleSpinBox_FreqSingleMHz_valueChanged(double arg1);

    void on_pushButton_SweepFullSpan_clicked();


    void on_pushButton_SpanWiFiBand_clicked();


//    void on_doubleSpinBox_SweepCenterFreqMHz_editingFinished();

    void on_doubleSpinBox_SweepSpanMHz_editingFinished();

    void on_spinBox_GaindBsingle_valueChanged(int arg1);

    void on_spinBox_WaterfallSize_valueChanged(int arg1);

    void on_spinBox_AverageSize_valueChanged(int arg1);

    void on_doubleSpinBox_SampleRateMHz_valueChanged(double arg1);

    void on_actionReset_to_Default_triggered();

    void removeRectItem();
    void onMousePress(QMouseEvent *event);
    void on_doubleSpinBox_ConstellationCenterFreqMHz_valueChanged(double arg1);

    void on_doubleSpinBox_ConstellationBandwidthMHz_valueChanged(double arg1);
    void updateConstellationRect();

    void on_mouseDoubleClickPlot4();




    void on_doubleSpinBox_RBW_valueChanged(double arg1);



    void onPauseDispley();



    void on_spinBox_Index1_valueChanged(int arg1);

    void on_spinBox_Index2_valueChanged(int arg1);


    void on_checkBox_AGC_clicked(bool checked);

    void on_comboBox_Channel_currentIndexChanged(int index);


    void clearWaterfall();
    void calcSweepIndices();
    void updateSweepFrequencies(double arg1);
    void setUSRPsweepThread(double arg1);
    void resetCustomPlot(int id, int nGraphs);
    void resetFilters();


    void on_pushButton_SpanWiFiBand2_clicked();

    void on_pushButton__SpanBand3_clicked();

    void on_checkBox_DCatt_clicked(bool checked);


private:
    Ui::MainWindow *ui;
    bool usrpDeviceFound = false, autoScaleWaterfall=true;
    bool showMaxHold, showMinHold, showSample, showAverage;
    int avgSize, avgIndex, avgIndexRFB, nFFT, mSamples, nTimeFrame;

    int updateCounter, updateIndex, nyWaterfall = 64;

    double freqMHz, sampleRateMHz , freqMHzRFB;
//    double maxSpectrum, minSpectrum;
    double timeFrameUS;
    double startFreqMHz, stopFreqMHz, spanMHz;
//    double startFreqMHzRFB, stopFreqMHzRFB, spanMHzRFB;
    double limitFreqLow = 70, limitFreqHigh = 6000;

    double x1constRectItem, x2constRectItem, y1constRectItem, y2constRectItem;

    QVector<QVector<double>> avgMatrix, waterfallMatrix;
//    QVector<QVector<double>> avgMatrixRFB, waterfallMatrixRFB;

    QVector<double> avgRMS, maxHold, minHold;
//    QVector<double> avgRMSRFB, maxHoldRFB, minHoldRFB;

    mProcessing sigpro;
    QVector<double> weight;

    QTextBrowser* usrpInfo;

    QCustomPlot* customPlot1,* customPlot2, * customPlot3,* customPlot4;
//    QCustomPlot * customPlot3RFB,* customPlot2RFB;

    bool firstRun = true;

    QCPColorMap *colorMap;
    QCPColorScale *colorScale;
    QCPMarginGroup *marginGroup;

//    QCPColorMap *colorMap, *colorMapRFB;
//    QCPColorScale *colorScale, *colorScaleRFB;
//    QCPMarginGroup *marginGroup, *marginGroupRFB;

    QDockWidget *dockPlot1, *dockPlot2, *dockPlot3, *dockPlot4;
//    QDockWidget *dockPlot2RFB, *dockPlot3RFB, *dockFrameRFB;
    QDockWidget *dockUsrpInfo, *dockFrameRFA,  *dockSettings;
//    QDockWidget *dockSettings;

    QPoint constRectPos1;
    bool showConstFlag = false;
    QCPItemRect *constRectItem;

    QVector<double> filterCoef, filterSpec, filterSpecI, filterSpecQ;
    int filterLength = 100;

    QVector<double> sweepFFTval , sweepFFTindx;
//    QVector<double> sweepFFTvalRFB , sweepFFTindxRFB;
    double sweepStepSizeMHz;
//    double sweepStepSizeMHzRFB;

    bool pauseDisplay = false, updateWaterfallRange = false;
//    bool updateWaterfallRangeRFB = false;
    int index1, index2 ;
//    int index1RFB, index2RFB;

    QVector<double> sweepfftavgRMS, sweepArrayFreqMHz;
    QVector<double> sweepArrayFreqMHzA;
//    QVector<double>  sweepArrayFreqMHzB, sweepfftavgRMSRFB;
//    QVector<int> sweepArrayRF, sweepArrayAnt;

//    sweepArrayFreqMHzRFB;
//    QVector<double> sweepArrayGain;

//    QVector<bool> sweepArrayAGC, sweepArrayDCoffset;

//    QVector<std::string> sweepArrayAnt;

    bool testFlag = false, RFA = true;
//            bool RFB = false;
//    QVector<double> sweepFFTindxplt, sweepFFTvalplt;

    // size(dataI) = nTimeFrame * mSamples
//    fftw_complex *in, *out, *ifft_in ,*ifft_out;
//    fftw_plan my_fft, my_ifft;
};


#endif // MAINWINDOW_H
