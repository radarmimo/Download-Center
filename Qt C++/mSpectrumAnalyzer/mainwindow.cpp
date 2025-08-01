#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    setCentralWidget(0);
    setDockNestingEnabled(true);

    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    onDockInitialize();
    onSettingInitialize();
    onPlotInitialize();
    onSignalSlotsConnection();
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // Delete dock manager here to delete all floating widgets. This ensures
    // that all top level windows of the dock manager are properly closed
//    fftw_destroy_plan(my_fft);
//    fftw_destroy_plan(my_ifft);
//    fftw_free(in);
//    fftw_free(out);
//    fftw_free(ifft_out);
    dockPlot1->deleteLater();
    dockPlot2->deleteLater();
    dockPlot3->deleteLater();
    dockPlot4->deleteLater();
//    dockPlot2RFB->deleteLater();
//    dockPlot3RFB->deleteLater();

    dockFrameRFA->deleteLater();
//    dockFrameRFB->deleteLater();

    dockUsrpInfo->deleteLater();
    dockSettings->deleteLater();
    threadUSRPrx->terminate();
    threadUSRPrx->deleteLater();
    QMainWindow::closeEvent(event);
}



void MainWindow::onDataReady(QVector<double> dataI, QVector<double> dataQ)
{
//    return;

    if (pauseDisplay) {
        return;
    }

    if (sweepArrayFreqMHz.size() == 0) {
        return;
    }


    double currentFreqMHz = dataI.last();
    int sCounter = dataQ.last();

    dataI.removeLast();
    dataQ.removeLast();

    QVector<double> sweepArray, sweepArrayA, sweepArrayB;

    sweepArray = sweepArrayFreqMHz;
    sweepArrayA = sweepArrayFreqMHzA;
//    sweepArrayB = sweepArrayFreqMHzB;


    if (sCounter >= sweepArray.size()) {
        return;
    }

    bool showSweep = ui->actionSweep->isChecked();

    if (testFlag) {
        qDebug() << "---- 1 -----" ;
    }


    updateIndex++;
    if (updateIndex >= updateCounter) {
        updateIndex = -1;
    }
    QVector<double> avgFFToverTimeFrame(nFFT), constI, constQ;

//    for (int i = 0; i < nFFT; ++i) {
//        avgFFToverTimeFrame.push_back(0);
//    }

    if (testFlag) {
        qDebug() << "---- 2 -----" ;
    }
    calcFFT(dataI, dataQ, avgFFToverTimeFrame, constI, constQ);

    if (testFlag) {
        qDebug() << "---- 3 -----" ;
    }

    if (updateIndex == 1) {
        if (!dockPlot1->isHidden()) {
            plotTimeDomain(dataI, dataQ);
        }
        if (!dockPlot2->isHidden()) {
            if (showSweep) {
                customPlot2->graph(5)->addData(sweepFFTindx, sweepFFTval);
            }
            customPlot2->replot();
        }
        if (!dockPlot3->isHidden()) {
            customPlot3->replot();
        }
    }


//    if (updateIndex == 1 && RFB) {
////        qDebug() << "---- updateIndex = 10 && RFB -----" ;
////        qDebug() << "---- sweepFFTvalRFB.size =  " << sweepFFTvalRFB.size() ;
//        if (!dockPlot2RFB->isHidden()) {
//            if (showSweep) {
//                customPlot2RFB->graph(5)->addData(sweepFFTindxRFB, sweepFFTvalRFB);
//            }
//            customPlot2RFB->replot();
//        }
////        if (!dockPlot3RFB->isHidden()) {
////            customPlot3RFB->replot();
////        }
//    }

//    if (sCounter < sweepArrayA.size()) {
    calcAvgMaxMin(avgFFToverTimeFrame,sCounter,sweepArrayA,
                  avgRMS, avgMatrix, maxHold, minHold,avgIndex);

    QVector<double> fftavgRMS(nFFT), fftIndex(nFFT), fftVal(nFFT), fftIndexSweep(nFFT);
    QVector<double> fftMaxHoldDB(nFFT), fftMinHoldDB(nFFT);

    calcSpectrum(avgFFToverTimeFrame,fftavgRMS,fftIndex,
                 fftVal,fftIndexSweep,fftMaxHoldDB,
                 fftMinHoldDB,currentFreqMHz,sweepArrayA,
                 avgRMS, maxHold, minHold);


    for (int k = nFFT/index1; k < nFFT/2-nFFT/index2; ++k) {
        sweepFFTval.push_back(fftVal[k]);
        sweepFFTindx.push_back(fftIndex[k]);
    }
    for (int k = nFFT/2+nFFT/index2; k < nFFT-nFFT/index1; ++k) {
        sweepFFTval.push_back(fftVal[k]);
        sweepFFTindx.push_back(fftIndex[k]);
    }

    if (sCounter == sweepArrayA.size()-1){

        customPlot2->graph(5)->setData(QVector<double>(), QVector<double>());
        plotSpectrum(fftIndexSweep,sweepFFTindx,sweepFFTval,fftavgRMS,fftMaxHoldDB,fftMinHoldDB);

        if (!dockPlot3->isHidden()) {
            if (updateWaterfallRange) {
                double r1 = fftIndexSweep.first() ;
                double r2 = fftIndexSweep.last() ;
                colorMap->data()->setRange(QCPRange(r1, r2), QCPRange(0, nyWaterfall-1));

                customPlot3->rescaleAxes();
                customPlot3->replot();

                updateWaterfallRange = false;

            }
            plotWaterfall(fftavgRMS);
        }
        sweepFFTindx.clear();
        sweepFFTval.clear();

        }
//    }
//    else
//    {

//        int dCounter = sCounter - sweepArrayA.size();
////        qDebug() << "dCounter = " << dCounter;


//        calcAvgMaxMin(avgFFToverTimeFrame,dCounter,sweepArrayB,
//                      avgRMSRFB, avgMatrixRFB, maxHoldRFB, minHoldRFB,avgIndexRFB);

//        QVector<double> fftavgRMSRFB(nFFT), fftIndexRFB(nFFT), fftValRFB(nFFT), fftIndexSweepRFB(nFFT);
//        QVector<double> fftMaxHoldDBRFB(nFFT), fftMinHoldDBRFB(nFFT);

//        calcSpectrum(avgFFToverTimeFrame,fftavgRMSRFB,fftIndexRFB,
//                     fftValRFB,fftIndexSweepRFB,fftMaxHoldDBRFB,
//                     fftMinHoldDBRFB,currentFreqMHz,sweepArrayB,
//                     avgRMSRFB, maxHoldRFB, minHoldRFB);


//        for (int k = nFFT/index1RFB; k < nFFT/2-nFFT/index2RFB; ++k) {
//            sweepFFTvalRFB.push_back(fftValRFB[k]);
//            sweepFFTindxRFB.push_back(fftIndexRFB[k]);
//        }
//        for (int k = nFFT/2+nFFT/index2RFB; k < nFFT-nFFT/index1RFB; ++k) {
//            sweepFFTvalRFB.push_back(fftValRFB[k]);
//            sweepFFTindxRFB.push_back(fftIndexRFB[k]);
//        }

//        if (dCounter == sweepArrayB.size()-1){

//            customPlot2RFB->graph(5)->setData(QVector<double>(), QVector<double>());
//            plotSpectrum(fftIndexSweepRFB,sweepFFTindxRFB,sweepFFTvalRFB,fftavgRMSRFB,fftMaxHoldDBRFB,fftMinHoldDBRFB);

////            if (!dockPlot3RFB->isHidden()) {
////                if (updateWaterfallRangeRFB) {
////                    double r1 = fftIndexSweep.first() ;
////                    double r2 = fftIndexSweep.last() ;
////                    colorMap->data()->setRange(QCPRange(r1, r2), QCPRange(0, nyWaterfall-1));

////                    customPlot3RFB->rescaleAxes();
////                    customPlot3RFB->replot();

////                    updateWaterfallRangeRFB = false;

////                }
////                plotWaterfall(fftavgRMS);
////            }
//            sweepFFTindxRFB.clear();
//            sweepFFTvalRFB.clear();

//        }
//    }




    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Sweep mode





    if (testFlag) {
        qDebug() << "---- 10 -----" ;
        testFlag = false;
    }

//    freqMHz = currentFreqMHz;





}

void MainWindow::onUSRPstatus(bool status, QString deviceAddress)
{
    usrpDeviceFound = status;
    if (!status) {
        usrpInfo->append("Device not found!");
    }
    else{
        usrpInfo->append("Connected to");
        QStringList pieces = deviceAddress.split( "," );
        foreach (QString var, pieces) {
            usrpInfo->append("    USRP " + var);
        }

    }

}

void MainWindow::onDockInitialize()
{

    dockPlot1 = new QDockWidget(tr("Oscilloscope"), this);
    dockPlot1->setAllowedAreas(Qt::AllDockWidgetAreas |Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    customPlot1 = new QCustomPlot();
    dockPlot1->setWidget(customPlot1);
    addDockWidget(Qt::RightDockWidgetArea, dockPlot1);
    ui->menuWindow->addAction(dockPlot1->toggleViewAction());
    dockPlot1->hide();
//    qDebug() <<" dockPlot1 status = " << dockPlot1->isHidden();





    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    dockPlot2 = new QDockWidget(tr("Spectrum"), this);
    dockPlot2->setAllowedAreas(Qt::AllDockWidgetAreas |Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    customPlot2 = new QCustomPlot();
    dockPlot2->setWidget(customPlot2);
    addDockWidget(Qt::RightDockWidgetArea, dockPlot2);
    //    tabifiedDockWidgetActivated(dock2);
    ui->menuWindow->addAction(dockPlot2->toggleViewAction());


    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    dockPlot2RFB = new QDockWidget(tr("Frequency - RF (B)"), this);
//    dockPlot2RFB->setAllowedAreas(Qt::AllDockWidgetAreas |Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
//    customPlot2RFB = new QCustomPlot();
//    dockPlot2RFB->setWidget(customPlot2RFB);
//    addDockWidget(Qt::RightDockWidgetArea, dockPlot2RFB);
//    //    tabifiedDockWidgetActivated(dock2);
//    ui->menuWindow->addAction(dockPlot2RFB->toggleViewAction());
//    dockPlot2RFB->hide();

    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    dockPlot3 = new QDockWidget(tr("Waterfall"), this);
    dockPlot3->setAllowedAreas(Qt::AllDockWidgetAreas |Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    customPlot3 = new QCustomPlot();
    dockPlot3->setWidget(customPlot3);
    addDockWidget(Qt::RightDockWidgetArea, dockPlot3);
    //    tabifiedDockWidgetActivated(dock3);
    ui->menuWindow->addAction(dockPlot3->toggleViewAction());
    dockPlot3->hide();

    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    dockPlot3RFB = new QDockWidget(tr("Waterfall - RF (B)"), this);
//    dockPlot3RFB->setAllowedAreas(Qt::AllDockWidgetAreas |Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
//    customPlot3RFB = new QCustomPlot();
//    dockPlot3->setWidget(customPlot3RFB);
//    addDockWidget(Qt::RightDockWidgetArea, dockPlot3RFB);
//    //    tabifiedDockWidgetActivated(dock3);
//    ui->menuWindow->addAction(dockPlot3RFB->toggleViewAction());
//    dockPlot3RFB->hide();

    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    dockPlot4 = new QDockWidget(tr("Constellation"), this);
    dockPlot4->setAllowedAreas(Qt::AllDockWidgetAreas |Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    customPlot4 = new QCustomPlot();
    dockPlot4->setWidget(customPlot4);
    addDockWidget(Qt::RightDockWidgetArea, dockPlot4);
    //    tabifiedDockWidgetActivated(dock3);
    ui->menuWindow->addAction(dockPlot4->toggleViewAction());
    dockPlot4->hide();



//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    tabifyDockWidget(dockPlot2,dockPlot3);
    tabifyDockWidget(dockPlot3,dockPlot4);
    tabifyDockWidget(dockPlot1,dockPlot2);

    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    dockUsrpInfo = new QDockWidget(tr("Connection"), this);
    dockUsrpInfo->setAllowedAreas(Qt::AllDockWidgetAreas |Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    usrpInfo = new QTextBrowser();

    dockUsrpInfo->setWidget(usrpInfo);
    addDockWidget(Qt::LeftDockWidgetArea, dockUsrpInfo);
    //    tabifiedDockWidgetActivated(dockUsrpInfo);
    ui->menuWindow->addSeparator();
    ui->menuWindow->addAction(dockUsrpInfo->toggleViewAction());

    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    dockFrameRFA = new QDockWidget(tr("Frequency"),this);
    dockFrameRFA->setAllowedAreas(Qt::AllDockWidgetAreas |Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    dockFrameRFA->setWidget(ui->frame_RFA);
    addDockWidget(Qt::LeftDockWidgetArea, dockFrameRFA);
    //    tabifiedDockWidgetActivated(dockUsrpInfo);
    ui->menuWindow->addSeparator();
    ui->menuWindow->addAction(dockFrameRFA->toggleViewAction());
    tabifyDockWidget(dockUsrpInfo,dockFrameRFA);
    //    tabifyDockWidget(dock2,dock3);

    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//    dockFrameRFB = new QDockWidget(tr("RF (B)"),this);
//    dockFrameRFB->setAllowedAreas(Qt::AllDockWidgetAreas |Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

//    dockFrameRFB->setWidget(ui->frame_RFB);
//    addDockWidget(Qt::LeftDockWidgetArea, dockFrameRFB);
//    //    tabifiedDockWidgetActivated(dockUsrpInfo);
////    ui->menuWindow->addSeparator();
//    ui->menuWindow->addAction(dockFrameRFB->toggleViewAction());
//    tabifyDockWidget(dockFrameRFA,dockFrameRFB);
//    dockFrameRFB->hide();


    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    dockSettings = new QDockWidget(tr("Settings"),this);
    dockSettings->setAllowedAreas(Qt::AllDockWidgetAreas |Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    dockSettings->setWidget(ui->frame_Settings);
    addDockWidget(Qt::LeftDockWidgetArea, dockSettings);
    //    tabifiedDockWidgetActivated(dockUsrpInfo);
    ui->menuWindow->addSeparator();
    ui->menuWindow->addAction(dockSettings->toggleViewAction());
    tabifyDockWidget(dockFrameRFA,dockSettings);
    //    tabifyDockWidget(dock2,dock3);

    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

}

void MainWindow::onPlotInitialize()
{


    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(21, 67, 96));
    plotGradient.setColorAt(1, QColor(21, 67, 96));
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(0, 0, 0));
    axisRectGradient.setColorAt(1, QColor(0, 0, 0));

    customPlot1->addGraph();
    customPlot1->graph(0)->setPen(QPen(Qt::cyan)); // line color blue for first graph
    customPlot1->addGraph();
    customPlot1->graph(1)->setPen(QPen(Qt::green)); // line color red for second graph
    customPlot1->xAxis->setRange(0,ui->doubleSpinBox_TimeFrameUS->value());
    customPlot1->yAxis->setRange(-0.5,0.5);

    customPlot1->xAxis2->setVisible(true);
    customPlot1->xAxis2->setTickLabels(true);
    customPlot1->yAxis2->setVisible(true);
    customPlot1->yAxis2->setTickLabels(true);

    customPlot1->xAxis->setLabel("Time [us]");
    customPlot1->yAxis->setLabel("Amplitude [v]");

    customPlot1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes  );

    // set some pens, brushes and backgrounds:
    customPlot1->xAxis->setLabelColor(Qt::white);
    customPlot1->yAxis->setLabelColor(Qt::white);
    customPlot1->xAxis2->setLabelColor(Qt::white);
    customPlot1->yAxis2->setLabelColor(Qt::white);
    customPlot1->xAxis->setBasePen(QPen(Qt::white, 1));
    customPlot1->yAxis->setBasePen(QPen(Qt::white, 1));
    customPlot1->xAxis->setTickPen(QPen(Qt::white, 1));
    customPlot1->yAxis->setTickPen(QPen(Qt::white, 1));
    customPlot1->xAxis2->setBasePen(QPen(Qt::white, 1));
    customPlot1->yAxis2->setBasePen(QPen(Qt::white, 1));
    customPlot1->xAxis2->setTickPen(QPen(Qt::white, 1));
    customPlot1->yAxis2->setTickPen(QPen(Qt::white, 1));

    customPlot1->xAxis->setSubTickPen(QPen(Qt::white, 1));
    customPlot1->yAxis->setSubTickPen(QPen(Qt::white, 1));
    customPlot1->xAxis->setTickLabelColor(Qt::white);
    customPlot1->yAxis->setTickLabelColor(Qt::white);

    customPlot1->xAxis2->setSubTickPen(QPen(Qt::white, 1));
    customPlot1->yAxis2->setSubTickPen(QPen(Qt::white, 1));
    customPlot1->xAxis2->setTickLabelColor(Qt::white);
    customPlot1->yAxis2->setTickLabelColor(Qt::white);

    customPlot1->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    customPlot1->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    customPlot1->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    customPlot1->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    customPlot1->xAxis->grid()->setSubGridVisible(true);
    customPlot1->yAxis->grid()->setSubGridVisible(true);
    customPlot1->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    customPlot1->yAxis->grid()->setZeroLinePen(Qt::NoPen);


    customPlot1->setBackground(plotGradient);
    customPlot1->axisRect()->setBackground(axisRectGradient);

    //        customPlot1->rescaleAxes();
    //    _______________________________________

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    customPlot2->addGraph();
    customPlot2->graph(0)->setPen(QPen(Qt::cyan)); // line color blue for first graph
    //    customPlot1->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
    customPlot2->addGraph();
    customPlot2->graph(1)->setPen(QPen(Qt::yellow)); // line color red for second graph

    customPlot2->addGraph();
    customPlot2->graph(2)->setPen(QPen(Qt::green));

    customPlot2->addGraph();
    customPlot2->graph(3)->setPen(QPen(Qt::magenta));

    customPlot2->addGraph();
    customPlot2->graph(4)->setPen(QPen(Qt::red));

    customPlot2->addGraph();
    customPlot2->graph(5)->setPen(QPen(Qt::gray));

    customPlot2->xAxis->setRange(-0.5*sampleRateMHz+freqMHz,0.5*sampleRateMHz + freqMHz);
//    customPlot2->yAxis->setRange(minSpectrum,maxSpectrum);

    //        customPlot2->yAxis2->setRange(-100,20);
    customPlot2->xAxis2->setVisible(true);
    customPlot2->xAxis2->setTickLabels(true);
    customPlot2->yAxis2->setVisible(true);
    customPlot2->yAxis2->setTickLabels(true);

    customPlot2->xAxis->setLabel("Frequency [MHz]");
    customPlot2->yAxis->setLabel("RSSI [dBm]");


    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    customPlot2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom  );

    // set some pens, brushes and backgrounds:

    customPlot2->xAxis->setLabelColor(Qt::white);
    customPlot2->yAxis->setLabelColor(Qt::white);
    customPlot2->xAxis2->setLabelColor(Qt::white);
    customPlot2->yAxis2->setLabelColor(Qt::white);
    customPlot2->xAxis->setBasePen(QPen(Qt::white, 1));
    customPlot2->yAxis->setBasePen(QPen(Qt::white, 1));
    customPlot2->xAxis->setTickPen(QPen(Qt::white, 1));
    customPlot2->yAxis->setTickPen(QPen(Qt::white, 1));
    customPlot2->xAxis2->setBasePen(QPen(Qt::white, 1));
    customPlot2->yAxis2->setBasePen(QPen(Qt::white, 1));
    customPlot2->xAxis2->setTickPen(QPen(Qt::white, 1));
    customPlot2->yAxis2->setTickPen(QPen(Qt::white, 1));

    customPlot2->xAxis->setSubTickPen(QPen(Qt::white, 1));
    customPlot2->yAxis->setSubTickPen(QPen(Qt::white, 1));
    customPlot2->xAxis->setTickLabelColor(Qt::white);
    customPlot2->yAxis->setTickLabelColor(Qt::white);

    customPlot2->xAxis2->setSubTickPen(QPen(Qt::white, 1));
    customPlot2->yAxis2->setSubTickPen(QPen(Qt::white, 1));
    customPlot2->xAxis2->setTickLabelColor(Qt::white);
    customPlot2->yAxis2->setTickLabelColor(Qt::white);

    customPlot2->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    customPlot2->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    customPlot2->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    customPlot2->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    customPlot2->xAxis->grid()->setSubGridVisible(true);
    customPlot2->yAxis->grid()->setSubGridVisible(true);
    customPlot2->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    customPlot2->yAxis->grid()->setZeroLinePen(Qt::NoPen);

    customPlot2->setBackground(plotGradient);
    customPlot2->axisRect()->setBackground(axisRectGradient);

    customPlot2->rescaleAxes();


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    customPlot2RFB->addGraph();
//    customPlot2RFB->graph(0)->setPen(QPen(Qt::cyan)); // line color blue for first graph
//    //    customPlot1->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
//    customPlot2RFB->addGraph();
//    customPlot2RFB->graph(1)->setPen(QPen(Qt::yellow)); // line color red for second graph

//    customPlot2RFB->addGraph();
//    customPlot2RFB->graph(2)->setPen(QPen(Qt::green));

//    customPlot2RFB->addGraph();
//    customPlot2RFB->graph(3)->setPen(QPen(Qt::magenta));

//    customPlot2RFB->addGraph();
//    customPlot2RFB->graph(4)->setPen(QPen(Qt::red));

//    customPlot2RFB->addGraph();
//    customPlot2RFB->graph(5)->setPen(QPen(Qt::gray));

//    customPlot2RFB->xAxis->setRange(-0.5*sampleRateMHz+freqMHz,0.5*sampleRateMHz + freqMHz);
////    customPlot2RFB->yAxis->setRange(minSpectrum,maxSpectrum);

//    //        customPlot2->yAxis2->setRange(-100,20);
//    customPlot2RFB->xAxis2->setVisible(true);
//    customPlot2RFB->xAxis2->setTickLabels(true);
//    customPlot2RFB->yAxis2->setVisible(true);
//    customPlot2RFB->yAxis2->setTickLabels(true);

//    customPlot2RFB->xAxis->setLabel("Frequency [MHz]");
//    customPlot2RFB->yAxis->setLabel("RSSI [dBm]");


//    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
//    customPlot2RFB->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom  );

//    // set some pens, brushes and backgrounds:

//    customPlot2RFB->xAxis->setLabelColor(Qt::white);
//    customPlot2RFB->yAxis->setLabelColor(Qt::white);
//    customPlot2RFB->xAxis2->setLabelColor(Qt::white);
//    customPlot2RFB->yAxis2->setLabelColor(Qt::white);
//    customPlot2RFB->xAxis->setBasePen(QPen(Qt::white, 1));
//    customPlot2RFB->yAxis->setBasePen(QPen(Qt::white, 1));
//    customPlot2RFB->xAxis->setTickPen(QPen(Qt::white, 1));
//    customPlot2RFB->yAxis->setTickPen(QPen(Qt::white, 1));
//    customPlot2RFB->xAxis2->setBasePen(QPen(Qt::white, 1));
//    customPlot2RFB->yAxis2->setBasePen(QPen(Qt::white, 1));
//    customPlot2RFB->xAxis2->setTickPen(QPen(Qt::white, 1));
//    customPlot2RFB->yAxis2->setTickPen(QPen(Qt::white, 1));

//    customPlot2RFB->xAxis->setSubTickPen(QPen(Qt::white, 1));
//    customPlot2RFB->yAxis->setSubTickPen(QPen(Qt::white, 1));
//    customPlot2RFB->xAxis->setTickLabelColor(Qt::white);
//    customPlot2RFB->yAxis->setTickLabelColor(Qt::white);

//    customPlot2RFB->xAxis2->setSubTickPen(QPen(Qt::white, 1));
//    customPlot2RFB->yAxis2->setSubTickPen(QPen(Qt::white, 1));
//    customPlot2RFB->xAxis2->setTickLabelColor(Qt::white);
//    customPlot2RFB->yAxis2->setTickLabelColor(Qt::white);

//    customPlot2RFB->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
//    customPlot2RFB->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
//    customPlot2RFB->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
//    customPlot2RFB->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
//    customPlot2RFB->xAxis->grid()->setSubGridVisible(true);
//    customPlot2RFB->yAxis->grid()->setSubGridVisible(true);
//    customPlot2RFB->xAxis->grid()->setZeroLinePen(Qt::NoPen);
//    customPlot2RFB->yAxis->grid()->setZeroLinePen(Qt::NoPen);

//    customPlot2RFB->setBackground(plotGradient);
//    customPlot2RFB->axisRect()->setBackground(axisRectGradient);

//    customPlot2RFB->rescaleAxes();


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    customPlot3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );

    // set some pens, brushes and backgrounds:

    customPlot3->xAxis->setLabelColor(Qt::white);
    customPlot3->yAxis->setLabelColor(Qt::white);
    customPlot3->xAxis2->setLabelColor(Qt::white);
    customPlot3->yAxis2->setLabelColor(Qt::white);
    customPlot3->xAxis->setBasePen(QPen(Qt::white, 1));
    customPlot3->yAxis->setBasePen(QPen(Qt::white, 1));
    customPlot3->xAxis->setTickPen(QPen(Qt::white, 1));
    customPlot3->yAxis->setTickPen(QPen(Qt::white, 1));
    customPlot3->xAxis2->setBasePen(QPen(Qt::white, 1));
    customPlot3->yAxis2->setBasePen(QPen(Qt::white, 1));
    customPlot3->xAxis2->setTickPen(QPen(Qt::white, 1));
    customPlot3->yAxis2->setTickPen(QPen(Qt::white, 1));

    customPlot3->xAxis->setSubTickPen(QPen(Qt::white, 1));
    customPlot3->yAxis->setSubTickPen(QPen(Qt::white, 1));
    customPlot3->xAxis->setTickLabelColor(Qt::white);
    customPlot3->yAxis->setTickLabelColor(Qt::white);

    customPlot3->xAxis2->setSubTickPen(QPen(Qt::white, 1));
    customPlot3->yAxis2->setSubTickPen(QPen(Qt::white, 1));
    customPlot3->xAxis2->setTickLabelColor(Qt::white);
    customPlot3->yAxis2->setTickLabelColor(Qt::white);

    customPlot3->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    customPlot3->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    customPlot3->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    customPlot3->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    customPlot3->xAxis->grid()->setSubGridVisible(true);
    customPlot3->yAxis->grid()->setSubGridVisible(true);
    customPlot3->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    customPlot3->yAxis->grid()->setZeroLinePen(Qt::NoPen);

    customPlot3->setBackground(plotGradient);
    customPlot3->axisRect()->setBackground(axisRectGradient);

    // configure axis rect:
    customPlot3->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    customPlot3->axisRect()->setupFullAxesBox(true);
    customPlot3->xAxis->setLabel("Frequency [MHz]");
    customPlot3->yAxis->setLabel("Waterfall Size");

    if (firstRun) {
        colorMap = new QCPColorMap(customPlot3->xAxis, customPlot3->yAxis);
        colorScale = new QCPColorScale(customPlot3);
        marginGroup = new QCPMarginGroup(customPlot3);

        customPlot3->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
//        colorScale->dataRangeChanged()
        firstRun = false;


    }

    colorMap->data()->setSize(nFFT, nyWaterfall); // we want the color map to have nx * ny data points


    QVector<int> fftIndex(nFFT);
    for (int i = 0; i < nFFT; ++i) {
        fftIndex[i] = ((double(i)/(nFFT-1)) - 0.5) * sampleRateMHz + freqMHz ;
    }

    colorMap->data()->setRange(QCPRange(fftIndex[0], fftIndex[nFFT-1]), QCPRange(0, nyWaterfall-1)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions

    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale
    colorScale->axis()->setLabel("RSSI [dBm]");
    colorScale->axis()->setLabelColor(Qt::white);
    colorScale->axis()->setTickLabelColor(Qt::white);

    colorMap->setGradient(QCPColorGradient::gpSpectrum);

    customPlot3->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    customPlot3->rescaleAxes();


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
//    customPlot3RFB->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );

//    // set some pens, brushes and backgrounds:

//    customPlot3RFB->xAxis->setLabelColor(Qt::white);
//    customPlot3RFB->yAxis->setLabelColor(Qt::white);
//    customPlot3RFB->xAxis2->setLabelColor(Qt::white);
//    customPlot3RFB->yAxis2->setLabelColor(Qt::white);
//    customPlot3RFB->xAxis->setBasePen(QPen(Qt::white, 1));
//    customPlot3RFB->yAxis->setBasePen(QPen(Qt::white, 1));
//    customPlot3RFB->xAxis->setTickPen(QPen(Qt::white, 1));
//    customPlot3RFB->yAxis->setTickPen(QPen(Qt::white, 1));
//    customPlot3RFB->xAxis2->setBasePen(QPen(Qt::white, 1));
//    customPlot3RFB->yAxis2->setBasePen(QPen(Qt::white, 1));
//    customPlot3RFB->xAxis2->setTickPen(QPen(Qt::white, 1));
//    customPlot3RFB->yAxis2->setTickPen(QPen(Qt::white, 1));

//    customPlot3RFB->xAxis->setSubTickPen(QPen(Qt::white, 1));
//    customPlot3RFB->yAxis->setSubTickPen(QPen(Qt::white, 1));
//    customPlot3RFB->xAxis->setTickLabelColor(Qt::white);
//    customPlot3RFB->yAxis->setTickLabelColor(Qt::white);

//    customPlot3RFB->xAxis2->setSubTickPen(QPen(Qt::white, 1));
//    customPlot3RFB->yAxis2->setSubTickPen(QPen(Qt::white, 1));
//    customPlot3RFB->xAxis2->setTickLabelColor(Qt::white);
//    customPlot3RFB->yAxis2->setTickLabelColor(Qt::white);

//    customPlot3RFB->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
//    customPlot3RFB->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
//    customPlot3RFB->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
//    customPlot3RFB->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
//    customPlot3RFB->xAxis->grid()->setSubGridVisible(true);
//    customPlot3RFB->yAxis->grid()->setSubGridVisible(true);
//    customPlot3RFB->xAxis->grid()->setZeroLinePen(Qt::NoPen);
//    customPlot3RFB->yAxis->grid()->setZeroLinePen(Qt::NoPen);

//    customPlot3RFB->setBackground(plotGradient);
//    customPlot3RFB->axisRect()->setBackground(axisRectGradient);

//    // configure axis rect:
//    customPlot3RFB->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
//    customPlot3RFB->axisRect()->setupFullAxesBox(true);
//    customPlot3RFB->xAxis->setLabel("Frequency [MHz]");
//    customPlot3RFB->yAxis->setLabel("Waterfall Size");

//    if (firstRun) {
//        colorMapRFB = new QCPColorMap(customPlot3RFB->xAxis, customPlot3RFB->yAxis);
//        colorScaleRFB = new QCPColorScale(customPlot3RFB);
//        marginGroupRFB = new QCPMarginGroup(customPlot3RFB);

//        customPlot3RFB->plotLayout()->addElement(0, 1, colorScaleRFB); // add it to the right of the main axis rect
////        colorScale->dataRangeChanged()
//        firstRun = false;
//    }

//    colorMapRFB->data()->setSize(nFFT, nyWaterfall); // we want the color map to have nx * ny data points


////    QVector<int> fftIndex(nFFT);
////    for (int i = 0; i < nFFT; ++i) {
////        fftIndex[i] = ((double(i)/(nFFT-1)) - 0.5) * sampleRateMHz + freqMHz ;
////    }

//    colorMapRFB->data()->setRange(QCPRange(fftIndex[0], fftIndex[nFFT-1]), QCPRange(0, nyWaterfall-1)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions

//    colorScaleRFB->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
//    colorMapRFB->setColorScale(colorScaleRFB); // associate the color map with the color scale
//    colorScaleRFB->axis()->setLabel("RSSI [dBm]");
//    colorScaleRFB->axis()->setLabelColor(Qt::white);
//    colorScaleRFB->axis()->setTickLabelColor(Qt::white);

//    colorMapRFB->setGradient(QCPColorGradient::gpSpectrum);

//    customPlot3RFB->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroupRFB);
//    colorScaleRFB->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroupRFB);

//    customPlot3RFB->rescaleAxes();

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    customPlot4->addGraph();
    customPlot4->graph(0)->setLineStyle(QCPGraph::lsNone);
    customPlot4->graph(0)->setPen(QPen(Qt::cyan)); // line color blue for first graph
    customPlot4->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    customPlot4->addGraph();
    customPlot4->graph(1)->setPen(QPen(Qt::green)); // line color red for second graph
    customPlot4->xAxis->setRange(-2,2);
    customPlot4->yAxis->setRange(-2,2);

    customPlot4->xAxis2->setVisible(true);
    customPlot4->xAxis2->setTickLabels(true);
    customPlot4->yAxis2->setVisible(true);
    customPlot4->yAxis2->setTickLabels(true);

    customPlot4->xAxis->setLabel("Imaginary [I]");
    customPlot4->yAxis->setLabel("Quadrature [Q]");

    customPlot4->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes  );

    // set some pens, brushes and backgrounds:
    customPlot4->xAxis->setLabelColor(Qt::white);
    customPlot4->yAxis->setLabelColor(Qt::white);
    customPlot4->xAxis2->setLabelColor(Qt::white);
    customPlot4->yAxis2->setLabelColor(Qt::white);
    customPlot4->xAxis->setBasePen(QPen(Qt::white, 1));
    customPlot4->yAxis->setBasePen(QPen(Qt::white, 1));
    customPlot4->xAxis->setTickPen(QPen(Qt::white, 1));
    customPlot4->yAxis->setTickPen(QPen(Qt::white, 1));
    customPlot4->xAxis2->setBasePen(QPen(Qt::white, 1));
    customPlot4->yAxis2->setBasePen(QPen(Qt::white, 1));
    customPlot4->xAxis2->setTickPen(QPen(Qt::white, 1));
    customPlot4->yAxis2->setTickPen(QPen(Qt::white, 1));

    customPlot4->xAxis->setSubTickPen(QPen(Qt::white, 1));
    customPlot4->yAxis->setSubTickPen(QPen(Qt::white, 1));
    customPlot4->xAxis->setTickLabelColor(Qt::white);
    customPlot4->yAxis->setTickLabelColor(Qt::white);

    customPlot4->xAxis2->setSubTickPen(QPen(Qt::white, 1));
    customPlot4->yAxis2->setSubTickPen(QPen(Qt::white, 1));
    customPlot4->xAxis2->setTickLabelColor(Qt::white);
    customPlot4->yAxis2->setTickLabelColor(Qt::white);

    customPlot4->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    customPlot4->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    customPlot4->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    customPlot4->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    customPlot4->xAxis->grid()->setSubGridVisible(true);
    customPlot4->yAxis->grid()->setSubGridVisible(true);
    customPlot4->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    customPlot4->yAxis->grid()->setZeroLinePen(Qt::NoPen);


    customPlot4->setBackground(plotGradient);
    customPlot4->axisRect()->setBackground(axisRectGradient);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    customPlot1->setSelectionRectMode(QCP::srmZoom);
    customPlot2->setSelectionRectMode(QCP::srmZoom);
//    customPlot2RFB->setSelectionRectMode(QCP::srmZoom);
    customPlot3->setSelectionRectMode(QCP::srmZoom);
//    customPlot3RFB->setSelectionRectMode(QCP::srmZoom);
    customPlot4->setSelectionRectMode(QCP::srmZoom);



    customPlot2->setContextMenuPolicy(Qt::CustomContextMenu);



}

void MainWindow::onSettingInitialize()
{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // get values

    // RF (A)

    index1 = ui->spinBox_Index1->value();
    index2 = ui->spinBox_Index2->value();
    freqMHz = ui->doubleSpinBox_FreqSingleMHz->value();
    spanMHz = ui->doubleSpinBox_SweepSpanMHz->value();

    startFreqMHz = freqMHz - spanMHz/2;
    stopFreqMHz = freqMHz + spanMHz/2;

    sweepStepSizeMHz = ui->doubleSpinBox_RBW->value();

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // RF (B)

//    index1RFB = ui->spinBox_Index1_2->value();
//    index2RFB = ui->spinBox_Index2_2->value();
//    freqMHzRFB = ui->doubleSpinBox_FreqSingleMHz_2->value();
//    spanMHzRFB = ui->doubleSpinBox_SweepSpanMHz_2->value();

//    startFreqMHzRFB = freqMHzRFB - spanMHzRFB/2;
//    stopFreqMHzRFB = freqMHzRFB + spanMHzRFB/2;

//    sweepStepSizeMHzRFB = ui->doubleSpinBox_RBW_2->value();


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    sampleRateMHz = ui->doubleSpinBox_SampleRateMHz->value();
    avgSize = ui->spinBox_AverageSize->value();
    nFFT = ui->comboBox_nFFT->currentText().toInt();

    mSamples = ui->spinBox_mSamples->value();
    timeFrameUS = ui->doubleSpinBox_TimeFrameUS->value();
    nTimeFrame = (timeFrameUS * sampleRateMHz)/mSamples;
    if (nTimeFrame < 1) {
        nTimeFrame = 1;
    }

    nyWaterfall = ui->spinBox_WaterfallSize->value();

    showMaxHold = ui->actionMax_Hold->isChecked();
    showMinHold = ui->actionMin_Hold->isChecked();
    showSample = ui->actionSample->isChecked();
    showAverage = ui->actionAverage->isChecked();





    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // set values

    // RF (A)

    ui->doubleSpinBox_SweepStartFreqMHz->setValue(startFreqMHz);
    ui->doubleSpinBox_SweepStopFreqMHz->setValue(stopFreqMHz);


    // RF (B)

//    ui->doubleSpinBox_SweepStartFreqMHz_2->setValue(startFreqMHzRFB);
//    ui->doubleSpinBox_SweepStopFreqMHz_2->setValue(stopFreqMHzRFB);


    calcSweepIndices();
    clearWaterfall();

    updateIndex = -1;
    updateCounter = 1 / (ui->verticalSlider->value() * ui->doubleSpinBox_TimeFrameUS->value() * 1e-6);


//    maxSpectrum = DBL_MIN; // adjustment for max calculation
//    minSpectrum = DBL_MAX; // adjustment for min calculation


    resetFilters();



}

void MainWindow::onSignalSlotsConnection()
{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    connect(threadUSRPrx, SIGNAL(dataReady(QVector<double> , QVector<double> )), this, SLOT(onDataReady(QVector<double> , QVector<double> )));
    connect(threadUSRPrx, SIGNAL(usrpStatus(bool, QString)), this, SLOT(onUSRPstatus(bool,QString)));
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    connect(customPlot1, SIGNAL(mouseDoubleClick(QMouseEvent*)), this, SLOT(on_mouseDoubleClickPlot1()));
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(customPlot1->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot1->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot1->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot1->yAxis2, SLOT(setRange(QCPRange)));


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    connect(customPlot2, SIGNAL(mouseDoubleClick(QMouseEvent*)), this, SLOT(on_mouseDoubleClickPlot2()));

    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(customPlot2->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot2->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot2->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot2->yAxis2, SLOT(setRange(QCPRange)));

    connect(customPlot2,SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(contextMenuRequest(QPoint)));
    connect(customPlot2,SIGNAL(mousePress(QMouseEvent*)),this, SLOT(onMousePress(QMouseEvent*)));
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    connect(customPlot3, SIGNAL(mouseDoubleClick(QMouseEvent*)), this, SLOT(on_mouseDoubleClickPlot3()));
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    connect(customPlot4, SIGNAL(mouseDoubleClick(QMouseEvent*)), this, SLOT(on_mouseDoubleClickPlot4()));
}


void MainWindow::on_comboBox_AntennaSingle_currentIndexChanged(int index)
{
    if (usrpDeviceFound) {
//        qDebug() << threadUSRPrx->usrp->get_rx_antennas(0).data();
        if (index == 0) {
            threadUSRPrx->usrp->set_rx_antenna("TX/RX");
            usrpInfo->append("TX/RX Selected");
        }
        else{
            threadUSRPrx->usrp->set_rx_antenna("RX2");
            usrpInfo->append("RX2 Selected");
        }
    }

}




void MainWindow::plotTimeDomain(QVector<double> &dataI, QVector<double> &dataQ)
{


    QVector<double> dataIplt(nFFT), dataQplt(nFFT), xAxisplt(nFFT);



    for (int i = 1; i < nFFT; i++) {
        int k = i * dataI.size()/nFFT;
        dataIplt[i] = dataI[k];
        dataQplt[i] = dataQ[k];
        xAxisplt[i] = (k * 1/(sampleRateMHz));


    }



    customPlot1->graph(0)->setData(xAxisplt, dataIplt);
    customPlot1->graph(1)->setData(xAxisplt, dataQplt);
    customPlot1->replot();

}

void MainWindow::calcSpectrum(QVector<double> &avgFFToverTimeFrame, QVector<double> &fftavgRMS,
                              QVector<double> &fftIndex, QVector<double> &fftVal, QVector<double> &fftIndexSweep,
                              QVector<double> &fftMaxHoldDB, QVector<double> &fftMinHoldDB,
                              double &currentFreqMHz, QVector<double> &sweepArray,
                              QVector<double> &avgRMS, QVector<double> &maxHold,
                              QVector<double> &minHold)
{


    double sweepBWMHz, sweepCenterFreqMHz;

    sweepBWMHz = sweepArray.last() - sweepArray.first() + sampleRateMHz;
    sweepCenterFreqMHz = (sweepArray.first() + sweepArray.last())/2;
    for (int i = 0; i < nFFT; ++i) {

        fftIndex[i] = ((double(i)/(nFFT-1)) - 0.5) * sampleRateMHz + currentFreqMHz ;

        fftVal[i] = 10*std::log10(avgFFToverTimeFrame[i]+0.00001) - 30; // receive power [dBm]
        fftavgRMS[i] = 10*std::log10(avgRMS[i]+0.00001) - 30; // average receive power [dBm]
        fftIndexSweep[i] = ((double(i)/(nFFT-1)) - 0.5) * sweepBWMHz + sweepCenterFreqMHz ;

//        maxSpectrum = std::max(maxSpectrum,fftavgRMS[i]);
//        minSpectrum = std::min(minSpectrum,fftavgRMS[i]);

        if (showMaxHold) {
            fftMaxHoldDB[i] = 10*std::log10(maxHold[i]) - 30; // Max-Hold receive power [dBm]
        }
        if (showMinHold) {
            fftMinHoldDB[i] = 10*std::log10(minHold[i]) - 30; // Min-Hold receive power [dBm]
        }
    }


}

void MainWindow::plotSpectrum(QVector<double> &fftIndex, QVector<double> &sweepIndex,
                              QVector<double> &fftVal, QVector<double> &fftavgRMS,
                              QVector<double> &fftMaxHoldDB, QVector<double> &fftMinHoldDB)
{
    if (showSample) {
        customPlot2->graph(0)->setData(sweepIndex,fftVal);
    }

    if (showAverage) {
        customPlot2->graph(1)->setData(fftIndex,fftavgRMS);
    }

    if (showMaxHold) {
        customPlot2->graph(2)->setData(fftIndex,fftMaxHoldDB);
    }
    if (showMinHold) {
        customPlot2->graph(3)->setData(fftIndex,fftMinHoldDB);
    }

}

void MainWindow::plotWaterfall(QVector<double> &fftavgRMS)
{
    if (fftavgRMS.size()!= colorMap->data()->keySize()) {
        colorMap->data()->setKeySize(fftavgRMS.size());
    }
    waterfallMatrix.push_back(fftavgRMS);
    while (waterfallMatrix.size() > ui->spinBox_WaterfallSize->value()) {
        waterfallMatrix.erase(waterfallMatrix.begin());
    }

    double x, y;
    for (int xIndex=0; xIndex< fftavgRMS.size(); ++xIndex)
    {
        for (int yIndex=0; yIndex<waterfallMatrix.size(); ++yIndex)
        {
            colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
            colorMap->data()->setCell(xIndex, yIndex, waterfallMatrix[yIndex][xIndex]);
        }
    }

    if (autoScaleWaterfall) {
//
//        colorMap->setColorScale(colorScale);
//
        double index1 = DBL_MAX, index2 = DBL_MIN;
        for (int var = 0; var < nFFT; ++var) {
            index1 = std::min(index1,fftavgRMS[var]);
            index2 = std::max(index2,fftavgRMS[var]);

        }
        colorMap->setDataRange(QCPRange(index1,index2));
        autoScaleWaterfall = false;
    }

}

void MainWindow::plotConstellation(QVector<double> &constI, QVector<double> &constQ)
{
    customPlot4->graph(0)->setData(constI, constQ);
    customPlot4->replot();

}

void MainWindow::calcFFT(QVector<double> &dataI, QVector<double> &dataQ,  QVector<double> &avgFFToverTimeFrame, QVector<double> &constI, QVector<double> &constQ)
{

    int fftshiftIndex;


    // size(dataI) = nTimeFrame * mSamples
    fftw_complex *in, *out, *ifft_in ,*ifft_out;
    fftw_plan my_fft, my_ifft;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*nFFT);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*nFFT);
    ifft_in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*nFFT);
    ifft_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*nFFT);

    my_fft = fftw_plan_dft_1d(nFFT, in, out, FFTW_FORWARD, FFTW_ESTIMATE);  //FFTW_ESTIMATE or FFTW_MEASURE
    my_ifft = fftw_plan_dft_1d(nFFT, ifft_in, ifft_out , FFTW_BACKWARD, FFTW_ESTIMATE);  //FFTW_ESTIMATE or FFTW_MEASURE

    for (int m = 0; m < nTimeFrame; ++m) {
        for (int i = 0; i < nFFT; ++i) {
            if (i < mSamples) {
                in[i][REAL] = (double(dataI[i+(m * mSamples)]) ) * weight[i];
                in[i][IMAG] = (double(dataQ[i+(m * mSamples)]) ) * weight[i];
            }
            else {
                in[i][REAL] = 0.;
                in[i][IMAG] = 0.;
            }

        }

        fftw_execute(my_fft);

        for (int i = 0; i < nFFT; ++i) {
            double mag;


            mag = (out[i][REAL] * out[i][REAL] +
                          out[i][IMAG] * out[i][IMAG]);



            if (i<nFFT/2) {
                fftshiftIndex = i+nFFT/2;
            }
            else{
                fftshiftIndex = i-nFFT/2;
            }

            avgFFToverTimeFrame[fftshiftIndex] = avgFFToverTimeFrame[fftshiftIndex] + mag; // take an average for nTimeFrame


            ifft_in[i][REAL] = out[i][REAL] * filterSpecI[i];
            ifft_in[i][IMAG] = out[i][IMAG] * filterSpecQ[i];

        }
        if (m == 0) {
            fftw_execute(my_ifft);

            for (int i = 0; i < nFFT; ++i) {
                constI.push_back(ifft_out[i][REAL]);
                constQ.push_back(ifft_out[i][IMAG]);

            }

        }


    }

    fftw_destroy_plan(my_fft);
    fftw_destroy_plan(my_ifft);
    fftw_free(in);
    fftw_free(out);
    fftw_free(ifft_out);

}

void MainWindow::calcAvgMaxMin(QVector<double> &avgFFToverTimeFrame,
                               int &sCounter, QVector<double> &sweepArrayFreqMHz,
                               QVector<double> &avgRMS, QVector<QVector<double>>&avgMatrix,
                               QVector<double> &maxHold, QVector<double> &minHold,
                               int &avgIndex)
{

    if (testFlag) {
        qDebug() << " sCounter = "  << sCounter;
        qDebug() << " sweepArrayFreqMHz.size() = "  << sweepArrayFreqMHz.size();
    }
    avgIndex ++;

    for (int i = 0; i < nFFT; ++i) {
        if ( sCounter >= 0 ) {
            int k1 = (i+sCounter*nFFT)/sweepArrayFreqMHz.size();

            avgRMS[k1] = avgFFToverTimeFrame[i]/avgSize + avgRMS[k1] - avgMatrix[k1][avgIndex];
            avgMatrix[k1][avgIndex] = avgFFToverTimeFrame[i]/avgSize;

            if (showMaxHold) {
                maxHold[i] = std::max(avgRMS[i],maxHold[i]);
            }
            if (showMinHold) {
                minHold[i] = std::min(avgRMS[i],minHold[i]);
            }
        }

    }
    if (avgIndex == avgSize - 1) {
        avgIndex = -1;
    }

}






void MainWindow::on_comboBox_nFFT_currentIndexChanged(int index)
{
//    onSettingInitialize();
    nFFT = ui->comboBox_nFFT->currentText().toInt();
    clearWaterfall();
    resetFilters();
    resetCustomPlot(2,6);

//    onPlotInitialize();

}

void MainWindow::on_mouseDoubleClickPlot1()
{
    customPlot1->rescaleAxes();
    customPlot1->replot();
}



void MainWindow::on_mouseDoubleClickPlot2()
{
    customPlot2->rescaleAxes();
    customPlot2->replot();
}

void MainWindow::on_mouseDoubleClickPlot3()
{
    autoScaleWaterfall = true;
    customPlot3->rescaleAxes();
    customPlot3->replot();
}

void MainWindow::on_mouseDoubleClickPlot4()
{
    customPlot4->rescaleAxes();
    customPlot4->replot();
}




void MainWindow::on_doubleSpinBox_SampleRateMHz_editingFinished()
{
    sampleRateMHz = ui->doubleSpinBox_SampleRateMHz->value();

    if (usrpDeviceFound) {
        threadUSRPrx->usrp->set_rx_rate(sampleRateMHz * 1e6);
        sampleRateMHz = threadUSRPrx->usrp->get_rx_rate()/1e6;
        ui->doubleSpinBox_SampleRateMHz->setValue(sampleRateMHz);

        usrpInfo->append("Sample Rate = "+ QString::number(sampleRateMHz) + " [MHz]");
        onSettingInitialize();
        onPlotInitialize();
    }
}


void MainWindow::on_spinBox_mSamples_editingFinished()
{
    mSamples = ui->spinBox_mSamples->value();

    if (usrpDeviceFound) {
        threadUSRPrx->mSamples = mSamples;
        usrpInfo->append("Sample Size = "+ QString::number(mSamples));
        onSettingInitialize();
        onPlotInitialize();
    }
}


void MainWindow::on_doubleSpinBox_TimeFrameUS_editingFinished()
{
    onSettingInitialize();
    onPlotInitialize();
}



void MainWindow::on_pushButton_Test_clicked()
{


}


void MainWindow::on_comboBox_WindowType_currentTextChanged(const QString &arg1)
{
    weight = sigpro.windwoing(ui->comboBox_WindowType->currentText(),nFFT);
}





//void MainWindow::on_spinBox_WaterfallSize_editingFinished()
//{
//    //    nyWaterfall = ui->spinBox_WaterfallSize->value();
//    //    colorMap->data()->setSize(nFFT, nyWaterfall);
//    //    onPlotInitialize();

//}


void MainWindow::on_comboBox_Gradient_currentTextChanged(const QString &arg1)
{


    if (arg1=="Grayscale") {
        colorMap->setGradient(QCPColorGradient::gpGrayscale);
    }else if(arg1=="Hot"){
        colorMap->setGradient(QCPColorGradient::gpHot);
    }else if(arg1=="Cold"){
        colorMap->setGradient(QCPColorGradient::gpCold);
    }else if(arg1=="Night"){
        colorMap->setGradient(QCPColorGradient::gpNight);
    }else if(arg1=="Candy"){
        colorMap->setGradient(QCPColorGradient::gpCandy);
    }else if(arg1=="Geography"){
        colorMap->setGradient(QCPColorGradient::gpGeography);
    }else if(arg1=="Ion"){
        colorMap->setGradient(QCPColorGradient::gpIon);
    }else if(arg1=="Thermal"){
        colorMap->setGradient(QCPColorGradient::gpThermal);
    }else if(arg1=="Polar"){
        colorMap->setGradient(QCPColorGradient::gpPolar);
    }else if(arg1=="Spectrum"){
        colorMap->setGradient(QCPColorGradient::gpSpectrum);
    }else if(arg1=="Jet"){
        colorMap->setGradient(QCPColorGradient::gpJet);
    }else if(arg1=="Hues"){
        colorMap->setGradient(QCPColorGradient::gpHues);
    }
    else{
        colorMap->setGradient(QCPColorGradient::gpSpectrum);
    }


}

void MainWindow::contextMenuRequest(QPoint pos)
{

    constRectPos1 = pos;
    QMenu *menu = new QMenu(this);
    menu->popup(customPlot2->mapToGlobal(pos));
    QString text;
    if (!pauseDisplay) {
        text = "Pause";
    }
    else {
        text = "Continue";
    }
    menu->addAction(text,this,SLOT(onPauseDispley()));

    if (dockPlot4->isHidden()) {
        return;
    }

    menu->addAction("Set Constellation Area" , this, SLOT(showConstellationGraph()));

    if (customPlot2->itemCount() > 0) {
        menu->addAction("Remove",this,SLOT(removeRectItem()));
        return;
    }


}

void MainWindow::showConstellationGraph()
{

    showConstFlag = true;
}

void MainWindow::removeRectItem()
{
    while (customPlot2->itemCount() > 0) {
        customPlot2->removeItem(0);
        customPlot2->graph(4)->setVisible(false);
    }
    filterSpecI.clear();
    filterSpecQ.clear();
    for (int i = 0; i < nFFT; ++i) {
        filterSpecI.push_back(1);
        filterSpecQ.push_back(1);

    }

}

void MainWindow::onMousePress(QMouseEvent *event)
{
    if (showConstFlag) {

        if (customPlot2->itemCount() > 0) {
            customPlot2->removeItem(0);
        }

        QPoint pos2 = event->pos();

        constRectItem = new QCPItemRect(customPlot2);

        x1constRectItem = customPlot2->xAxis->pixelToCoord(constRectPos1.x());
        y1constRectItem = customPlot2->yAxis->pixelToCoord(constRectPos1.y());
        x2constRectItem = customPlot2->xAxis->pixelToCoord(pos2.x());
        y2constRectItem = customPlot2->yAxis->pixelToCoord(pos2.y());
        double bwconstRectItem = std::abs(x2constRectItem - x1constRectItem);
        double freqconstRectItem = (x1constRectItem + x2constRectItem) / 2;

        ui->doubleSpinBox_ConstellationCenterFreqMHz->setValue(freqconstRectItem);
        ui->doubleSpinBox_ConstellationBandwidthMHz->setValue(bwconstRectItem);

        constRectItem->setBrush(QColor(255, 200, 20, 50));
        constRectItem->setPen(Qt::NoPen);
        showConstFlag = false;

        updateConstellationRect();
    }

}

void MainWindow::on_actionFind_Devices_triggered()
{
    if (usrpDeviceFound) {
        return;
    }


    threadUSRPrx->gain = ui->spinBox_GaindBsingle->value();
    threadUSRPrx->agc = ui->checkBox_AGC->isChecked();
    threadUSRPrx->rate = sampleRateMHz*1e6;
    threadUSRPrx->mSamples = mSamples;
    threadUSRPrx->nTimeFrame = nTimeFrame;


//    qDebug() << "sweepArrayFreqMHz = " << sweepArrayFreqMHz[0];
    threadUSRPrx->sweepArrayFreqMHz = sweepArrayFreqMHz;
//    threadUSRPrx->sweepArrayAnt = sweepArrayAnt;

    usrpInfo->setText("Creating usrp devices . . . ");
    threadUSRPrx->start();

}


void MainWindow::on_actionStop_Device_triggered()
{
    if (usrpDeviceFound) {
        threadUSRPrx->terminate();
        usrpDeviceFound = false;
    }
    ui->spinBox_mSamples->setEnabled(true);
    //    ui->pushButton_FindDevices->setEnabled(true);
    ui->doubleSpinBox_TimeFrameUS->setEnabled(true);
}





void MainWindow::on_actionAverage_triggered()
{
    showAverage = ui->actionAverage->isChecked();
    customPlot2->graph(1)->setVisible(showAverage);

}


void MainWindow::on_actionSample_triggered()
{
    showSample = ui->actionSample->isChecked();
    customPlot2->graph(0)->setVisible(showSample);
}


void MainWindow::on_actionMax_Hold_triggered()
{

    showMaxHold = ui->actionMax_Hold->isChecked();
    for (int i = 0; i < nFFT; ++i) {
        maxHold[i] = 0;
    }
    customPlot2->graph(2)->setVisible(showMaxHold);

}


void MainWindow::on_actionMin_Hold_triggered()
{
    showMinHold = ui->actionMin_Hold->isChecked();

    for (int i = 0; i < nFFT; ++i) {
        minHold[i] = DBL_MAX;
    }
    customPlot2->graph(3)->setVisible(showMinHold);
}


void MainWindow::on_verticalSlider_valueChanged(int value)
{
    updateCounter = 1 / (value * ui->doubleSpinBox_TimeFrameUS->value() * 1e-6);
}


void MainWindow::on_doubleSpinBox_FreqSingleMHz_valueChanged(double arg1)
{
    freqMHz = arg1;

    // for constellation plot
    if (std::abs(arg1 - ui->doubleSpinBox_ConstellationCenterFreqMHz->value()) > sampleRateMHz/2) {
        customPlot2->graph(4)->data()->clear();
        if (customPlot2->itemCount()>0) {
            customPlot2->removeItem(0);
        }
    }

    if (!usrpDeviceFound) {
        return;
    }


    updateSweepFrequencies(spanMHz);
    calcSweepIndices();
    setUSRPsweepThread(spanMHz);
    clearWaterfall();

}





void MainWindow::on_pushButton_SweepFullSpan_clicked()
{
    if (!usrpDeviceFound) {
        return;
    }
    resetCustomPlot(2,6);
    freqMHz = 825;
    spanMHz = 100;
//    realTimeMode = false;
    ui->doubleSpinBox_SweepSpanMHz->setValue(spanMHz);
    ui->doubleSpinBox_FreqSingleMHz->setValue(freqMHz);
    updateWaterfallRange = true;

}


void MainWindow::on_pushButton_SpanWiFiBand_clicked()
{
    if (!usrpDeviceFound) {
        return;
    }
    resetCustomPlot(2,6);

    freqMHz = 2450;
    spanMHz = 100;
//    realTimeMode = false;
    ui->doubleSpinBox_SweepSpanMHz->setValue(spanMHz);
    ui->doubleSpinBox_FreqSingleMHz->setValue(freqMHz);
    updateWaterfallRange = true;
}




void MainWindow::on_doubleSpinBox_SweepSpanMHz_editingFinished()
{
    if (!usrpDeviceFound) {
        return;
    }
//    testFlag = true;
    double arg1 = ui->doubleSpinBox_SweepSpanMHz->value();

//    if (arg1 <= sampleRateMHz) {
////        realTimeMode = true;
////        realTimeMode = false;
//        usrpInfo->append("~~~~~~~~~~~~~~~~~~~~~~");
//        usrpInfo->append("Realtime Mode");
//        usrpInfo->append("~~~~~~~~~~~~~~~~~~~~~~");
//    }
//    else{
//        realTimeMode = false;
//        usrpInfo->append("~~~~~~~~~~~~~~~~~~~~~~");
//        usrpInfo->append("Sweep Mode");
//        usrpInfo->append("~~~~~~~~~~~~~~~~~~~~~~");
//    }

    updateSweepFrequencies(arg1);
//    qDebug() << "---- 1 -----" ;
    calcSweepIndices();
//    qDebug() << "---- 2 -----" ;
    setUSRPsweepThread(arg1);
//    if (realTimeMode) {
//        return;
//    }
    clearWaterfall();

}


void MainWindow::on_spinBox_GaindBsingle_valueChanged(int arg1)
{
    if (usrpDeviceFound) {
        threadUSRPrx->usrp->set_rx_gain(arg1);
        usrpInfo->append("Gain = "+ QString::number(threadUSRPrx->usrp->get_rx_gain()) + " [dB]");
    }
}


void MainWindow::on_spinBox_WaterfallSize_valueChanged(int arg1)
{
    nyWaterfall = arg1;
    colorMap->data()->setSize(nFFT, nyWaterfall);

//    double r1 = -0.5 * sampleRateMHz + freqMHz ;
//    double r2 = 0.5 * sampleRateMHz + freqMHz ;


//    colorMap->data()->setRange(QCPRange(r1, r2), QCPRange(0, nyWaterfall-1));
//    customPlot3->rescaleAxes();
}


void MainWindow::on_spinBox_AverageSize_valueChanged(int arg1)
{
    avgSize = arg1;
    avgIndex = -1;
    avgMatrix.clear();
    avgRMS.clear();
    for (int i = 0; i < nFFT; ++i) {
        QVector<double> tempVector(avgSize);
        avgMatrix.push_back(tempVector);
        avgRMS.push_back(0);
    }
}


void MainWindow::on_doubleSpinBox_SampleRateMHz_valueChanged(double arg1)
{
    //    sampleRateMHz = arg1;

    //    if (usrpDeviceFound) {
    //        threadUSRPrx->usrp->set_rx_rate(sampleRateMHz * 1e6);
    //        sampleRateMHz = threadUSRPrx->usrp->get_rx_rate()/1e6;
    //        ui->doubleSpinBox_SampleRateMHz->setValue(sampleRateMHz);
    //        double bw = ui->doubleSpinBox_BWsingleMHz->value();
    //        if (sampleRateMHz > bw) {
    //            ui->doubleSpinBox_BWsingleMHz->setValue(sampleRateMHz);
    //        }
    //        usrpInfo->append("Sample Rate = "+ QString::number(sampleRateMHz) + " [MHz]");
    //        onSettingInitialize();
    //        onPlotInitialize();
    //    }

}


void MainWindow::on_actionReset_to_Default_triggered()
{

    if (dockPlot1->isFloating()) {
        dockPlot1->setFloating(false);
    }
    if (dockPlot2->isFloating()) {
        dockPlot2->setFloating(false);
    }
    if (dockPlot3->isFloating()) {
        dockPlot3->setFloating(false);
    }
    if (dockUsrpInfo->isFloating()) {
        dockUsrpInfo->setFloating(false);
    }
    if (dockSettings->isFloating()) {
        dockSettings->setFloating(false);
    }
    if (dockFrameRFA->isFloating()) {
        dockFrameRFA->setFloating(false);
    }


}


void MainWindow::on_doubleSpinBox_ConstellationCenterFreqMHz_valueChanged(double arg1)
{
    if (customPlot2->itemCount() > 0) {
        double center = (x1constRectItem + x2constRectItem) / 2;
        double shiftx = arg1 - center;
        x1constRectItem = x1constRectItem + shiftx;
        x2constRectItem = x2constRectItem + shiftx;
        updateConstellationRect();
    }



}


void MainWindow::on_doubleSpinBox_ConstellationBandwidthMHz_valueChanged(double arg1)
{
    if (customPlot2->itemCount() > 0) {
        double bw = std::abs(x2constRectItem - x1constRectItem);
        double shiftx = (arg1 - bw)/2;

        x1constRectItem = x1constRectItem - shiftx;
        x2constRectItem = x2constRectItem + shiftx;
        updateConstellationRect();
    }

}

void MainWindow::updateConstellationRect()
{
    constRectItem->topLeft->setCoords(x1constRectItem, y1constRectItem );
    constRectItem->bottomRight->setCoords(x2constRectItem , y2constRectItem );
    double bw = std::abs(x2constRectItem - x1constRectItem);

//    int M(100);
    double fc = bw/sampleRateMHz/2;

    filterCoef = sigpro.filtering("",filterLength,fc);


    double fmix = ui->doubleSpinBox_ConstellationCenterFreqMHz->value() - ui->doubleSpinBox_FreqSingleMHz->value();
    QVector<double> mixerI, mixerQ;
    for (int l = 0; l < mSamples; ++l) {
        double t = l/sampleRateMHz;
        double arg = 2 * M_PI * fmix * t;
        mixerI.push_back(cos(arg));
        mixerQ.push_back(sin(arg));
    }


    QVector<double>  filterSpecDB(nFFT);
    fftw_complex *in, *out;
    fftw_plan my_plan;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*nFFT);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*nFFT);
    my_plan = fftw_plan_dft_1d(nFFT, in, out, FFTW_FORWARD, FFTW_ESTIMATE);  //FFTW_ESTIMATE or FFTW_MEASURE


    for (int i = 0; i < nFFT; ++i) {
        if (i < filterLength) {
            in[i][REAL] = double(filterCoef[i] * mixerI[i]) ;
            in[i][IMAG] = double(filterCoef[i] * mixerQ[i]);
        }
        else {
            in[i][REAL] = 0.;
            in[i][IMAG] = 0.;
        }

    }

    fftw_execute(my_plan);

    filterSpec.clear();
    filterSpecI.clear();
    filterSpecQ.clear();
    for (int i = 0; i < nFFT; ++i) {
        filterSpecI.push_back(out[i][REAL]);
        filterSpecQ.push_back(out[i][IMAG]);
        double mag = (out[i][REAL] * out[i][REAL] +
                      out[i][IMAG] * out[i][IMAG]);

        filterSpec.push_back(mag);
    }


    fftw_destroy_plan(my_plan);
    fftw_free(in);
    fftw_free(out);

    QVector<double> fftIndex;
    int fftshiftIndex = 0;
    for (int i = 0; i < nFFT; ++i) {
        if (i<nFFT/2) {
            fftshiftIndex = i+nFFT/2;
        }
        else{
            fftshiftIndex = i-nFFT/2;
        }
        fftIndex.push_back( ((double(i)/(nFFT-1)) - 0.5) * sampleRateMHz + freqMHz) ;

        filterSpecDB[fftshiftIndex] = 10*std::log10(filterSpec[i]) - 30;
    }
    customPlot2->graph(4)->setVisible(true);
    customPlot2->graph(4)->setData(fftIndex,filterSpecDB);
    customPlot2->replot();

}






void MainWindow::on_doubleSpinBox_RBW_valueChanged(double arg1)
{
    sweepStepSizeMHz = arg1;
    updateSweepFrequencies(spanMHz);
    calcSweepIndices();
    setUSRPsweepThread(spanMHz);
    clearWaterfall();
}






void MainWindow::onPauseDispley()
{
    pauseDisplay = !pauseDisplay;
}




void MainWindow::on_spinBox_Index1_valueChanged(int arg1)
{
    index1 = arg1;
}


void MainWindow::on_spinBox_Index2_valueChanged(int arg1)
{
    index2 = arg1;
}






void MainWindow::on_checkBox_AGC_clicked(bool checked)
{

    if (!usrpDeviceFound) {
        return;

    }
    threadUSRPrx->usrp->set_rx_agc(checked);
    ui->spinBox_GaindBsingle->setEnabled(!checked);

}


void MainWindow::on_comboBox_Channel_currentIndexChanged(int index)
{
    std::string subdev;
    if (index == 0) {
        subdev = "A:A";
//        dockFrameRFB->hide();
//        dockFrameRFA->show();
//        RFA = true;
//        RFB = false;
    }
//    else if (index == 1) {
//        subdev = "A:B";
//        dockFrameRFA->hide();
//        dockFrameRFB->show();
//        RFB = true;
//        RFA = false;

//    }
    else if (index == 1) {
        subdev = "A:B";
//        dockFrameRFA->show();
//        dockFrameRFB->show();
//        RFA = true;
//        RFB = true;
//        return;
    }
    threadUSRPrx->usrp->set_rx_subdev_spec(subdev);

//    calcSweepIndices();

}



void MainWindow::clearWaterfall()
{
    avgIndex = -1;
    avgMatrix.clear();
    avgRMS.clear();
    maxHold.clear();
    minHold.clear();

    for (int i = 0; i < nFFT; ++i) {
        QVector<double> tempVector(avgSize);
        avgRMS.push_back(0);
        avgMatrix.push_back(tempVector);
        maxHold.push_back(DBL_MIN);
        minHold.push_back(DBL_MAX);
    }

//    if (RFB) {
//        avgIndexRFB = -1;
//        avgMatrixRFB.clear();
//        avgRMSRFB.clear();
//        maxHoldRFB.clear();
//        minHoldRFB.clear();

//        for (int i = 0; i < nFFT; ++i) {
//            QVector<double> tempVector(avgSize);
//            avgRMSRFB.push_back(0);
//            avgMatrixRFB.push_back(tempVector);
//            maxHoldRFB.push_back(DBL_MIN);
//            minHoldRFB.push_back(DBL_MAX);
//        }
//    }
}

void MainWindow::calcSweepIndices()
{

    // RF (A)

    sweepArrayFreqMHzA.clear();
    sweepArrayFreqMHzA.push_back(freqMHz);


    int i = 1;
    while (freqMHz + i *  sweepStepSizeMHz <= stopFreqMHz) {

        sweepArrayFreqMHzA.push_front(freqMHz - i *  sweepStepSizeMHz);
        sweepArrayFreqMHzA.push_back(freqMHz + i *  sweepStepSizeMHz);
        i++;
    }

//    sizeOfSweepArrayRFA = sweepArrayFreqMHzA.size();

    sweepArrayFreqMHz.clear();
    sweepArrayFreqMHz = sweepArrayFreqMHzA;


//    sweepArrayAnt.clear();
//    sweepArrayRF.clear();
//    for (int var = 0; var < sweepArrayFreqMHz.size(); ++var) {
//        sweepArrayAnt.push_back(ui->comboBox_AntennaSingle->currentIndex());
//        sweepArrayRF.push_back(0);
//    }



//    if (RFB) {
//        sweepArrayFreqMHzB.clear();
//        sweepArrayFreqMHzB.push_back(freqMHzRFB);


//        int i = 1;
//        while (freqMHzRFB + i *  sweepStepSizeMHzRFB <= stopFreqMHzRFB) {

//            sweepArrayFreqMHzB.push_front(freqMHzRFB - i *  sweepStepSizeMHzRFB);
//            sweepArrayFreqMHzB.push_back(freqMHzRFB + i *  sweepStepSizeMHzRFB);
//            i++;
//        }


//        sweepArrayFreqMHz.append(sweepArrayFreqMHzB);

//        for (int var = sweepArrayAnt.size(); var < sweepArrayFreqMHz.size(); ++var) {
//            sweepArrayAnt.push_back(ui->comboBox_AntennaSingle_2->currentIndex());
//            sweepArrayRF.push_back(1);
//        }
//    }

//    for (int k = 0; k < sweepArrayFreqMHz.size(); ++k) {


//        qDebug() << "sweepArrayFreqMHz = " << sweepArrayFreqMHz[k];
//        qDebug() << "sweepArrayRF = " << sweepArrayRF[k];
//        qDebug() << "sizeOfSweepArrayRFA = " << sizeOfSweepArrayRFA;
//        qDebug() << "sizeOfSweepArrayRFB = " << sweepArrayFreqMHz.size() - sizeOfSweepArrayRFA;

//    }

//    for (int k = 0; k < sweepArrayFreqMHzA.size(); ++k) {
//        qDebug() << "sweepArrayFreqMHzA = " << sweepArrayFreqMHzA[k];
//    }
//    for (int k = 0; k < sweepArrayFreqMHzB.size(); ++k) {
//        qDebug() << "sweepArrayFreqMHzB = " << sweepArrayFreqMHzB[k];
//    }


}

void MainWindow::updateSweepFrequencies(double arg1)
{
    double span1 = freqMHz - limitFreqLow;
    double span2 = limitFreqHigh - freqMHz;
    double tempSpan = std::min(span1,span2);
    spanMHz = std::min(2*tempSpan,arg1);


    startFreqMHz = freqMHz - spanMHz/2;
    stopFreqMHz = freqMHz + spanMHz/2;

    ui->doubleSpinBox_SweepStartFreqMHz->setValue(startFreqMHz);
    ui->doubleSpinBox_SweepStopFreqMHz->setValue(stopFreqMHz);

//    if (RFB) {
//        double span1RFB = freqMHzRFB - limitFreqLow;
//        double span2RFB = limitFreqHigh - freqMHzRFB;
//        double tempSpanRFB = std::min(span1RFB,span2RFB);
//        spanMHzRFB = std::min(2*tempSpanRFB,arg1);


//        startFreqMHzRFB = freqMHzRFB - spanMHzRFB/2;
//        stopFreqMHzRFB = freqMHzRFB + spanMHzRFB/2;

//        ui->doubleSpinBox_SweepStartFreqMHz->setValue(startFreqMHzRFB);
//        ui->doubleSpinBox_SweepStopFreqMHz->setValue(stopFreqMHzRFB);
//    }
}

void MainWindow::setUSRPsweepThread(double arg1)
{
    threadUSRPrx->sweepArrayFreqMHz = sweepArrayFreqMHz;
//    threadUSRPrx->sweepArrayAnt = sweepArrayAnt;
    customPlot2->xAxis->setRange(startFreqMHz,stopFreqMHz);
//    if (RFB) {
//        customPlot2RFB->xAxis->setRange(startFreqMHzRFB,stopFreqMHzRFB);
//    }

//    threadUSRPrx->RFB = RFB;

//    threadUSRPrx->usrp->set_rx_dc_offset(ui->checkBox_DCatt->isChecked());
//    threadUSRPrx->usrp->set_rx_agc(ui->checkBox_AGC->isChecked());
    threadUSRPrx->usrp->set_rx_bandwidth(std::min(arg1,sampleRateMHz) * 1e6);
    usrpInfo->append("Bandwidth = "+ QString::number(threadUSRPrx->usrp->get_rx_bandwidth()/1e6) + " [MHz]");

}

void MainWindow::resetCustomPlot(int id, int nGraphs)
{
    if (id == 1) {
        for (int i = 0; i < nGraphs; ++i) {
            customPlot1->graph(i)->setData(QVector<double>(), QVector<double>());
        }
        customPlot1->replot();
        return;

    }
    if (id == 2) {
        for (int i = 0; i < nGraphs; ++i) {
            customPlot2->graph(i)->setData(QVector<double>(), QVector<double>());
        }
        customPlot2->replot();
        return;
    }
    if (id == 4) {
        for (int i = 0; i < nGraphs; ++i) {
            customPlot4->graph(i)->setData(QVector<double>(), QVector<double>());
        }
        customPlot4->replot();
        return;

    }
}

void MainWindow::resetFilters()
{
    weight = sigpro.windwoing(ui->comboBox_WindowType->currentText(),nFFT);
    filterSpecI.clear();
    filterSpecQ.clear();
    for (int i = 0; i < nFFT; ++i) {
        filterSpecI.push_back(1);
        filterSpecQ.push_back(1);

    }
}




void MainWindow::on_pushButton_SpanWiFiBand2_clicked()
{
    if (!usrpDeviceFound) {
        return;
    }

    resetCustomPlot(2,6);

    freqMHz = 5800;
    spanMHz = 150;

    ui->doubleSpinBox_SweepSpanMHz->setValue(spanMHz);
    ui->doubleSpinBox_FreqSingleMHz->setValue(freqMHz);
    updateWaterfallRange = true;


}


void MainWindow::on_pushButton__SpanBand3_clicked()
{
    if (!usrpDeviceFound) {
        return;
    }
    resetCustomPlot(2,6);

    freqMHz = 433;
    spanMHz = 30;
    ui->doubleSpinBox_SweepSpanMHz->setValue(spanMHz);
    ui->doubleSpinBox_FreqSingleMHz->setValue(freqMHz);
    updateWaterfallRange = true;
}


void MainWindow::on_checkBox_DCatt_clicked(bool checked)
{

    if (!usrpDeviceFound) {
        return;

    }
    threadUSRPrx->usrp->set_rx_dc_offset(checked);

}



