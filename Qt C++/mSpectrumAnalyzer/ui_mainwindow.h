/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionRecord;
    QAction *actionOpen;
    QAction *actionRecent_Files;
    QAction *actionClose;
    QAction *actionFind_Devices;
    QAction *actionStop_Device;
    QAction *actionHelp;
    QAction *actionAbout_me;
    QAction *actionAverage;
    QAction *actionSample;
    QAction *actionMax_Hold;
    QAction *actionMin_Hold;
    QAction *actionDual_Channel;
    QAction *actionReset_to_Default;
    QAction *actionSweep;
    QWidget *centralwidget;
    QGridLayout *gridLayout_5;
    QFrame *frame_RFA;
    QGridLayout *gridLayout_13;
    QGroupBox *groupBox_Sweep;
    QGridLayout *gridLayout_4;
    QSpacerItem *verticalSpacer_5;
    QGridLayout *gridLayout_SweepStartStop;
    QLabel *label_SweepStartFreqMHz;
    QDoubleSpinBox *doubleSpinBox_SweepStartFreqMHz;
    QDoubleSpinBox *doubleSpinBox_SweepStopFreqMHz;
    QLabel *label_SweepStopFreqMHz;
    QGridLayout *gridLayout_FullSpan;
    QLabel *label_RBW;
    QSpinBox *spinBox_GaindBsingle;
    QPushButton *pushButton__SpanBand3;
    QCheckBox *checkBox_AGC;
    QLabel *label_Channel;
    QPushButton *pushButton_SpanWiFiBand2;
    QPushButton *pushButton_SpanWiFiBand;
    QSpinBox *spinBox_Index1;
    QPushButton *pushButton_SweepFullSpan;
    QSpinBox *spinBox_Index2;
    QComboBox *comboBox_Channel;
    QDoubleSpinBox *doubleSpinBox_RBW;
    QCheckBox *checkBox_DCatt;
    QFrame *frame_freq;
    QGridLayout *gridLayout_9;
    QGridLayout *gridLayout_Freq;
    QComboBox *comboBox_AntennaSingle;
    QLabel *label_ant;
    QDoubleSpinBox *doubleSpinBox_SweepSpanMHz;
    QLabel *label_SweepSpanMHz;
    QLabel *label_freq;
    QDoubleSpinBox *doubleSpinBox_FreqSingleMHz;
    QFrame *frame_Settings;
    QGridLayout *gridLayout_6;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_Rate;
    QSlider *verticalSlider;
    QTabWidget *tabWidget_Settings;
    QWidget *tab_Spectrum;
    QGridLayout *gridLayout_8;
    QGridLayout *gridLayout_Spec;
    QLabel *label_FFTsize;
    QLabel *label_WindowType;
    QSpinBox *spinBox_AverageSize;
    QLabel *label_AverageSize;
    QComboBox *comboBox_nFFT;
    QComboBox *comboBox_WindowType;
    QSpacerItem *verticalSpacer_Spectrum;
    QWidget *tab_Display;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_Waterfall;
    QLabel *label_WaterfallGradient;
    QSpinBox *spinBox_WaterfallSize;
    QComboBox *comboBox_Gradient;
    QLabel *label_WaterfallSize;
    QSpacerItem *verticalSpacer_Waterfall;
    QWidget *tab_Constellation;
    QGridLayout *gridLayout_11;
    QHBoxLayout *horizontalLayout;
    QLabel *label_ConstellationCenterFreq;
    QDoubleSpinBox *doubleSpinBox_ConstellationCenterFreqMHz;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_ConstellationBW;
    QDoubleSpinBox *doubleSpinBox_ConstellationBandwidthMHz;
    QSpacerItem *verticalSpacer_4;
    QPushButton *pushButton_Test;
    QGroupBox *groupBox_BoardConfiguration;
    QGridLayout *gridLayout_7;
    QGridLayout *gridLayout_Channel;
    QLabel *label_mSamples;
    QLabel *label_SampleRate;
    QDoubleSpinBox *doubleSpinBox_TimeFrameUS;
    QLabel *label_TimeIntervalMS;
    QSpinBox *spinBox_mSamples;
    QDoubleSpinBox *doubleSpinBox_SampleRateMHz;
    QSpacerItem *verticalSpacer_6;
    QMenuBar *menubar;
    QMenu *menuData;
    QMenu *menuDisplay;
    QMenu *menuWindow;
    QMenu *menuDevice;
    QMenu *menuAbout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1024, 768);
        MainWindow->setMinimumSize(QSize(1024, 768));
        MainWindow->setDockOptions(QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        actionRecord = new QAction(MainWindow);
        actionRecord->setObjectName("actionRecord");
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        actionRecent_Files = new QAction(MainWindow);
        actionRecent_Files->setObjectName("actionRecent_Files");
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName("actionClose");
        actionFind_Devices = new QAction(MainWindow);
        actionFind_Devices->setObjectName("actionFind_Devices");
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("network-server");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionFind_Devices->setIcon(icon);
        actionStop_Device = new QAction(MainWindow);
        actionStop_Device->setObjectName("actionStop_Device");
        QIcon icon1;
        iconThemeName = QString::fromUtf8("system-shutdown");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionStop_Device->setIcon(icon1);
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName("actionHelp");
        actionAbout_me = new QAction(MainWindow);
        actionAbout_me->setObjectName("actionAbout_me");
        actionAverage = new QAction(MainWindow);
        actionAverage->setObjectName("actionAverage");
        actionAverage->setCheckable(true);
        actionAverage->setChecked(true);
        actionSample = new QAction(MainWindow);
        actionSample->setObjectName("actionSample");
        actionSample->setCheckable(true);
        actionMax_Hold = new QAction(MainWindow);
        actionMax_Hold->setObjectName("actionMax_Hold");
        actionMax_Hold->setCheckable(true);
        actionMin_Hold = new QAction(MainWindow);
        actionMin_Hold->setObjectName("actionMin_Hold");
        actionMin_Hold->setCheckable(true);
        actionDual_Channel = new QAction(MainWindow);
        actionDual_Channel->setObjectName("actionDual_Channel");
        actionDual_Channel->setCheckable(true);
        QIcon icon2;
        iconThemeName = QString::fromUtf8("document-open-recent");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionDual_Channel->setIcon(icon2);
        actionReset_to_Default = new QAction(MainWindow);
        actionReset_to_Default->setObjectName("actionReset_to_Default");
        actionSweep = new QAction(MainWindow);
        actionSweep->setObjectName("actionSweep");
        actionSweep->setCheckable(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_5 = new QGridLayout(centralwidget);
        gridLayout_5->setObjectName("gridLayout_5");
        frame_RFA = new QFrame(centralwidget);
        frame_RFA->setObjectName("frame_RFA");
        frame_RFA->setMinimumSize(QSize(300, 400));
        frame_RFA->setMaximumSize(QSize(320, 16777215));
        frame_RFA->setFrameShape(QFrame::StyledPanel);
        frame_RFA->setFrameShadow(QFrame::Raised);
        gridLayout_13 = new QGridLayout(frame_RFA);
        gridLayout_13->setObjectName("gridLayout_13");
        groupBox_Sweep = new QGroupBox(frame_RFA);
        groupBox_Sweep->setObjectName("groupBox_Sweep");
        groupBox_Sweep->setEnabled(true);
        gridLayout_4 = new QGridLayout(groupBox_Sweep);
        gridLayout_4->setObjectName("gridLayout_4");
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_5, 5, 0, 1, 1);

        gridLayout_SweepStartStop = new QGridLayout();
        gridLayout_SweepStartStop->setObjectName("gridLayout_SweepStartStop");
        label_SweepStartFreqMHz = new QLabel(groupBox_Sweep);
        label_SweepStartFreqMHz->setObjectName("label_SweepStartFreqMHz");

        gridLayout_SweepStartStop->addWidget(label_SweepStartFreqMHz, 0, 0, 1, 1);

        doubleSpinBox_SweepStartFreqMHz = new QDoubleSpinBox(groupBox_Sweep);
        doubleSpinBox_SweepStartFreqMHz->setObjectName("doubleSpinBox_SweepStartFreqMHz");
        doubleSpinBox_SweepStartFreqMHz->setReadOnly(true);
        doubleSpinBox_SweepStartFreqMHz->setMinimum(70.000000000000000);
        doubleSpinBox_SweepStartFreqMHz->setMaximum(5990.000000000000000);
        doubleSpinBox_SweepStartFreqMHz->setValue(2400.000000000000000);

        gridLayout_SweepStartStop->addWidget(doubleSpinBox_SweepStartFreqMHz, 0, 1, 1, 1);

        doubleSpinBox_SweepStopFreqMHz = new QDoubleSpinBox(groupBox_Sweep);
        doubleSpinBox_SweepStopFreqMHz->setObjectName("doubleSpinBox_SweepStopFreqMHz");
        doubleSpinBox_SweepStopFreqMHz->setReadOnly(true);
        doubleSpinBox_SweepStopFreqMHz->setMinimum(80.000000000000000);
        doubleSpinBox_SweepStopFreqMHz->setMaximum(6000.000000000000000);
        doubleSpinBox_SweepStopFreqMHz->setValue(2500.000000000000000);

        gridLayout_SweepStartStop->addWidget(doubleSpinBox_SweepStopFreqMHz, 1, 1, 1, 1);

        label_SweepStopFreqMHz = new QLabel(groupBox_Sweep);
        label_SweepStopFreqMHz->setObjectName("label_SweepStopFreqMHz");

        gridLayout_SweepStartStop->addWidget(label_SweepStopFreqMHz, 1, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout_SweepStartStop, 0, 0, 1, 1);

        gridLayout_FullSpan = new QGridLayout();
        gridLayout_FullSpan->setObjectName("gridLayout_FullSpan");
        label_RBW = new QLabel(groupBox_Sweep);
        label_RBW->setObjectName("label_RBW");

        gridLayout_FullSpan->addWidget(label_RBW, 0, 0, 1, 1);

        spinBox_GaindBsingle = new QSpinBox(groupBox_Sweep);
        spinBox_GaindBsingle->setObjectName("spinBox_GaindBsingle");
        spinBox_GaindBsingle->setEnabled(false);
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        spinBox_GaindBsingle->setFont(font);
        spinBox_GaindBsingle->setMinimum(0);
        spinBox_GaindBsingle->setMaximum(90);
        spinBox_GaindBsingle->setValue(35);

        gridLayout_FullSpan->addWidget(spinBox_GaindBsingle, 5, 1, 1, 1);

        pushButton__SpanBand3 = new QPushButton(groupBox_Sweep);
        pushButton__SpanBand3->setObjectName("pushButton__SpanBand3");

        gridLayout_FullSpan->addWidget(pushButton__SpanBand3, 2, 0, 1, 1);

        checkBox_AGC = new QCheckBox(groupBox_Sweep);
        checkBox_AGC->setObjectName("checkBox_AGC");
        checkBox_AGC->setChecked(true);

        gridLayout_FullSpan->addWidget(checkBox_AGC, 5, 0, 1, 1);

        label_Channel = new QLabel(groupBox_Sweep);
        label_Channel->setObjectName("label_Channel");

        gridLayout_FullSpan->addWidget(label_Channel, 6, 0, 1, 1);

        pushButton_SpanWiFiBand2 = new QPushButton(groupBox_Sweep);
        pushButton_SpanWiFiBand2->setObjectName("pushButton_SpanWiFiBand2");

        gridLayout_FullSpan->addWidget(pushButton_SpanWiFiBand2, 3, 1, 1, 1);

        pushButton_SpanWiFiBand = new QPushButton(groupBox_Sweep);
        pushButton_SpanWiFiBand->setObjectName("pushButton_SpanWiFiBand");

        gridLayout_FullSpan->addWidget(pushButton_SpanWiFiBand, 3, 0, 1, 1);

        spinBox_Index1 = new QSpinBox(groupBox_Sweep);
        spinBox_Index1->setObjectName("spinBox_Index1");
        spinBox_Index1->setMinimum(2);
        spinBox_Index1->setMaximum(4096);
        spinBox_Index1->setValue(256);

        gridLayout_FullSpan->addWidget(spinBox_Index1, 4, 0, 1, 1);

        pushButton_SweepFullSpan = new QPushButton(groupBox_Sweep);
        pushButton_SweepFullSpan->setObjectName("pushButton_SweepFullSpan");

        gridLayout_FullSpan->addWidget(pushButton_SweepFullSpan, 2, 1, 1, 1);

        spinBox_Index2 = new QSpinBox(groupBox_Sweep);
        spinBox_Index2->setObjectName("spinBox_Index2");
        spinBox_Index2->setMinimum(4);
        spinBox_Index2->setMaximum(4096);
        spinBox_Index2->setValue(256);

        gridLayout_FullSpan->addWidget(spinBox_Index2, 4, 1, 1, 1);

        comboBox_Channel = new QComboBox(groupBox_Sweep);
        comboBox_Channel->addItem(QString());
        comboBox_Channel->addItem(QString());
        comboBox_Channel->setObjectName("comboBox_Channel");

        gridLayout_FullSpan->addWidget(comboBox_Channel, 6, 1, 1, 1);

        doubleSpinBox_RBW = new QDoubleSpinBox(groupBox_Sweep);
        doubleSpinBox_RBW->setObjectName("doubleSpinBox_RBW");
        doubleSpinBox_RBW->setDecimals(3);
        doubleSpinBox_RBW->setMinimum(0.001000000000000);
        doubleSpinBox_RBW->setMaximum(56.000000000000000);
        doubleSpinBox_RBW->setSingleStep(0.500000000000000);
        doubleSpinBox_RBW->setValue(50.000000000000000);

        gridLayout_FullSpan->addWidget(doubleSpinBox_RBW, 0, 1, 1, 1);

        checkBox_DCatt = new QCheckBox(groupBox_Sweep);
        checkBox_DCatt->setObjectName("checkBox_DCatt");
        checkBox_DCatt->setChecked(false);

        gridLayout_FullSpan->addWidget(checkBox_DCatt, 7, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout_FullSpan, 2, 0, 1, 1);


        gridLayout_13->addWidget(groupBox_Sweep, 1, 0, 1, 1);

        frame_freq = new QFrame(frame_RFA);
        frame_freq->setObjectName("frame_freq");
        frame_freq->setFrameShape(QFrame::StyledPanel);
        frame_freq->setFrameShadow(QFrame::Raised);
        gridLayout_9 = new QGridLayout(frame_freq);
        gridLayout_9->setObjectName("gridLayout_9");
        gridLayout_Freq = new QGridLayout();
        gridLayout_Freq->setObjectName("gridLayout_Freq");
        comboBox_AntennaSingle = new QComboBox(frame_freq);
        comboBox_AntennaSingle->addItem(QString());
        comboBox_AntennaSingle->addItem(QString());
        comboBox_AntennaSingle->setObjectName("comboBox_AntennaSingle");
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        comboBox_AntennaSingle->setFont(font1);
        comboBox_AntennaSingle->setEditable(false);

        gridLayout_Freq->addWidget(comboBox_AntennaSingle, 3, 1, 1, 1);

        label_ant = new QLabel(frame_freq);
        label_ant->setObjectName("label_ant");

        gridLayout_Freq->addWidget(label_ant, 3, 0, 1, 1);

        doubleSpinBox_SweepSpanMHz = new QDoubleSpinBox(frame_freq);
        doubleSpinBox_SweepSpanMHz->setObjectName("doubleSpinBox_SweepSpanMHz");
        doubleSpinBox_SweepSpanMHz->setFont(font1);
        doubleSpinBox_SweepSpanMHz->setDecimals(3);
        doubleSpinBox_SweepSpanMHz->setMinimum(0.001000000000000);
        doubleSpinBox_SweepSpanMHz->setMaximum(5900.000000000000000);
        doubleSpinBox_SweepSpanMHz->setSingleStep(5.000000000000000);
        doubleSpinBox_SweepSpanMHz->setValue(50.000000000000000);

        gridLayout_Freq->addWidget(doubleSpinBox_SweepSpanMHz, 1, 1, 1, 1);

        label_SweepSpanMHz = new QLabel(frame_freq);
        label_SweepSpanMHz->setObjectName("label_SweepSpanMHz");

        gridLayout_Freq->addWidget(label_SweepSpanMHz, 1, 0, 1, 1);

        label_freq = new QLabel(frame_freq);
        label_freq->setObjectName("label_freq");

        gridLayout_Freq->addWidget(label_freq, 0, 0, 1, 1);

        doubleSpinBox_FreqSingleMHz = new QDoubleSpinBox(frame_freq);
        doubleSpinBox_FreqSingleMHz->setObjectName("doubleSpinBox_FreqSingleMHz");
        QFont font2;
        font2.setPointSize(20);
        font2.setBold(true);
        doubleSpinBox_FreqSingleMHz->setFont(font2);
        doubleSpinBox_FreqSingleMHz->setMouseTracking(false);
        doubleSpinBox_FreqSingleMHz->setMinimum(70.000000000000000);
        doubleSpinBox_FreqSingleMHz->setMaximum(5960.000000000000000);
        doubleSpinBox_FreqSingleMHz->setSingleStep(5.000000000000000);
        doubleSpinBox_FreqSingleMHz->setValue(463.000000000000000);

        gridLayout_Freq->addWidget(doubleSpinBox_FreqSingleMHz, 0, 1, 1, 1);


        gridLayout_9->addLayout(gridLayout_Freq, 0, 0, 1, 1);


        gridLayout_13->addWidget(frame_freq, 0, 0, 1, 1);


        gridLayout_5->addWidget(frame_RFA, 0, 0, 1, 1);

        frame_Settings = new QFrame(centralwidget);
        frame_Settings->setObjectName("frame_Settings");
        frame_Settings->setMinimumSize(QSize(300, 400));
        frame_Settings->setMaximumSize(QSize(320, 16777215));
        frame_Settings->setFrameShape(QFrame::StyledPanel);
        frame_Settings->setFrameShadow(QFrame::Raised);
        gridLayout_6 = new QGridLayout(frame_Settings);
        gridLayout_6->setObjectName("gridLayout_6");
        verticalSpacer_7 = new QSpacerItem(20, 240, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_7, 3, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_Rate = new QLabel(frame_Settings);
        label_Rate->setObjectName("label_Rate");

        horizontalLayout_2->addWidget(label_Rate);

        verticalSlider = new QSlider(frame_Settings);
        verticalSlider->setObjectName("verticalSlider");
        verticalSlider->setMinimum(10);
        verticalSlider->setMaximum(50);
        verticalSlider->setValue(25);
        verticalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(verticalSlider);


        gridLayout_6->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        tabWidget_Settings = new QTabWidget(frame_Settings);
        tabWidget_Settings->setObjectName("tabWidget_Settings");
        tabWidget_Settings->setMinimumSize(QSize(300, 150));
        tabWidget_Settings->setMaximumSize(QSize(300, 16777215));
        tab_Spectrum = new QWidget();
        tab_Spectrum->setObjectName("tab_Spectrum");
        gridLayout_8 = new QGridLayout(tab_Spectrum);
        gridLayout_8->setObjectName("gridLayout_8");
        gridLayout_Spec = new QGridLayout();
        gridLayout_Spec->setObjectName("gridLayout_Spec");
        label_FFTsize = new QLabel(tab_Spectrum);
        label_FFTsize->setObjectName("label_FFTsize");

        gridLayout_Spec->addWidget(label_FFTsize, 0, 0, 1, 1);

        label_WindowType = new QLabel(tab_Spectrum);
        label_WindowType->setObjectName("label_WindowType");

        gridLayout_Spec->addWidget(label_WindowType, 1, 0, 1, 1);

        spinBox_AverageSize = new QSpinBox(tab_Spectrum);
        spinBox_AverageSize->setObjectName("spinBox_AverageSize");
        spinBox_AverageSize->setEnabled(true);
        spinBox_AverageSize->setMinimum(1);
        spinBox_AverageSize->setMaximum(2048);
        spinBox_AverageSize->setSingleStep(1);
        spinBox_AverageSize->setValue(8);

        gridLayout_Spec->addWidget(spinBox_AverageSize, 2, 1, 1, 1);

        label_AverageSize = new QLabel(tab_Spectrum);
        label_AverageSize->setObjectName("label_AverageSize");

        gridLayout_Spec->addWidget(label_AverageSize, 2, 0, 1, 1);

        comboBox_nFFT = new QComboBox(tab_Spectrum);
        comboBox_nFFT->addItem(QString());
        comboBox_nFFT->addItem(QString());
        comboBox_nFFT->addItem(QString());
        comboBox_nFFT->addItem(QString());
        comboBox_nFFT->addItem(QString());
        comboBox_nFFT->addItem(QString());
        comboBox_nFFT->setObjectName("comboBox_nFFT");

        gridLayout_Spec->addWidget(comboBox_nFFT, 0, 1, 1, 1);

        comboBox_WindowType = new QComboBox(tab_Spectrum);
        comboBox_WindowType->addItem(QString());
        comboBox_WindowType->addItem(QString());
        comboBox_WindowType->addItem(QString());
        comboBox_WindowType->addItem(QString());
        comboBox_WindowType->addItem(QString());
        comboBox_WindowType->addItem(QString());
        comboBox_WindowType->setObjectName("comboBox_WindowType");

        gridLayout_Spec->addWidget(comboBox_WindowType, 1, 1, 1, 1);


        gridLayout_8->addLayout(gridLayout_Spec, 0, 0, 1, 1);

        verticalSpacer_Spectrum = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_8->addItem(verticalSpacer_Spectrum, 1, 0, 1, 1);

        tabWidget_Settings->addTab(tab_Spectrum, QString());
        tab_Display = new QWidget();
        tab_Display->setObjectName("tab_Display");
        gridLayout_3 = new QGridLayout(tab_Display);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_Waterfall = new QGridLayout();
        gridLayout_Waterfall->setObjectName("gridLayout_Waterfall");
        label_WaterfallGradient = new QLabel(tab_Display);
        label_WaterfallGradient->setObjectName("label_WaterfallGradient");

        gridLayout_Waterfall->addWidget(label_WaterfallGradient, 1, 0, 1, 1);

        spinBox_WaterfallSize = new QSpinBox(tab_Display);
        spinBox_WaterfallSize->setObjectName("spinBox_WaterfallSize");
        spinBox_WaterfallSize->setMinimum(8);
        spinBox_WaterfallSize->setMaximum(128);
        spinBox_WaterfallSize->setValue(64);

        gridLayout_Waterfall->addWidget(spinBox_WaterfallSize, 0, 1, 1, 1);

        comboBox_Gradient = new QComboBox(tab_Display);
        comboBox_Gradient->addItem(QString());
        comboBox_Gradient->addItem(QString());
        comboBox_Gradient->addItem(QString());
        comboBox_Gradient->addItem(QString());
        comboBox_Gradient->addItem(QString());
        comboBox_Gradient->addItem(QString());
        comboBox_Gradient->addItem(QString());
        comboBox_Gradient->addItem(QString());
        comboBox_Gradient->addItem(QString());
        comboBox_Gradient->addItem(QString());
        comboBox_Gradient->addItem(QString());
        comboBox_Gradient->addItem(QString());
        comboBox_Gradient->setObjectName("comboBox_Gradient");

        gridLayout_Waterfall->addWidget(comboBox_Gradient, 1, 1, 1, 1);

        label_WaterfallSize = new QLabel(tab_Display);
        label_WaterfallSize->setObjectName("label_WaterfallSize");

        gridLayout_Waterfall->addWidget(label_WaterfallSize, 0, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_Waterfall, 0, 0, 1, 1);

        verticalSpacer_Waterfall = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_Waterfall, 1, 0, 1, 1);

        tabWidget_Settings->addTab(tab_Display, QString());
        tab_Constellation = new QWidget();
        tab_Constellation->setObjectName("tab_Constellation");
        gridLayout_11 = new QGridLayout(tab_Constellation);
        gridLayout_11->setObjectName("gridLayout_11");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_ConstellationCenterFreq = new QLabel(tab_Constellation);
        label_ConstellationCenterFreq->setObjectName("label_ConstellationCenterFreq");

        horizontalLayout->addWidget(label_ConstellationCenterFreq);

        doubleSpinBox_ConstellationCenterFreqMHz = new QDoubleSpinBox(tab_Constellation);
        doubleSpinBox_ConstellationCenterFreqMHz->setObjectName("doubleSpinBox_ConstellationCenterFreqMHz");
        doubleSpinBox_ConstellationCenterFreqMHz->setMinimum(100.000000000000000);
        doubleSpinBox_ConstellationCenterFreqMHz->setMaximum(5950.000000000000000);
        doubleSpinBox_ConstellationCenterFreqMHz->setValue(465.000000000000000);

        horizontalLayout->addWidget(doubleSpinBox_ConstellationCenterFreqMHz);


        gridLayout_11->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_ConstellationBW = new QLabel(tab_Constellation);
        label_ConstellationBW->setObjectName("label_ConstellationBW");

        horizontalLayout_3->addWidget(label_ConstellationBW);

        doubleSpinBox_ConstellationBandwidthMHz = new QDoubleSpinBox(tab_Constellation);
        doubleSpinBox_ConstellationBandwidthMHz->setObjectName("doubleSpinBox_ConstellationBandwidthMHz");
        doubleSpinBox_ConstellationBandwidthMHz->setMinimum(0.010000000000000);
        doubleSpinBox_ConstellationBandwidthMHz->setMaximum(50.000000000000000);
        doubleSpinBox_ConstellationBandwidthMHz->setValue(10.000000000000000);

        horizontalLayout_3->addWidget(doubleSpinBox_ConstellationBandwidthMHz);


        gridLayout_11->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 93, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_11->addItem(verticalSpacer_4, 2, 0, 1, 1);

        pushButton_Test = new QPushButton(tab_Constellation);
        pushButton_Test->setObjectName("pushButton_Test");

        gridLayout_11->addWidget(pushButton_Test, 3, 0, 1, 1);

        tabWidget_Settings->addTab(tab_Constellation, QString());

        gridLayout_6->addWidget(tabWidget_Settings, 0, 0, 1, 1);

        groupBox_BoardConfiguration = new QGroupBox(frame_Settings);
        groupBox_BoardConfiguration->setObjectName("groupBox_BoardConfiguration");
        groupBox_BoardConfiguration->setEnabled(true);
        groupBox_BoardConfiguration->setMinimumSize(QSize(300, 150));
        gridLayout_7 = new QGridLayout(groupBox_BoardConfiguration);
        gridLayout_7->setObjectName("gridLayout_7");
        gridLayout_Channel = new QGridLayout();
        gridLayout_Channel->setObjectName("gridLayout_Channel");
        label_mSamples = new QLabel(groupBox_BoardConfiguration);
        label_mSamples->setObjectName("label_mSamples");

        gridLayout_Channel->addWidget(label_mSamples, 5, 0, 1, 1);

        label_SampleRate = new QLabel(groupBox_BoardConfiguration);
        label_SampleRate->setObjectName("label_SampleRate");

        gridLayout_Channel->addWidget(label_SampleRate, 7, 0, 1, 1);

        doubleSpinBox_TimeFrameUS = new QDoubleSpinBox(groupBox_BoardConfiguration);
        doubleSpinBox_TimeFrameUS->setObjectName("doubleSpinBox_TimeFrameUS");
        doubleSpinBox_TimeFrameUS->setDecimals(1);
        doubleSpinBox_TimeFrameUS->setMinimum(100.000000000000000);
        doubleSpinBox_TimeFrameUS->setMaximum(18360.000000000000000);
        doubleSpinBox_TimeFrameUS->setSingleStep(100.000000000000000);
        doubleSpinBox_TimeFrameUS->setValue(5100.000000000000000);

        gridLayout_Channel->addWidget(doubleSpinBox_TimeFrameUS, 6, 1, 1, 1);

        label_TimeIntervalMS = new QLabel(groupBox_BoardConfiguration);
        label_TimeIntervalMS->setObjectName("label_TimeIntervalMS");

        gridLayout_Channel->addWidget(label_TimeIntervalMS, 6, 0, 1, 1);

        spinBox_mSamples = new QSpinBox(groupBox_BoardConfiguration);
        spinBox_mSamples->setObjectName("spinBox_mSamples");
        spinBox_mSamples->setEnabled(true);
        spinBox_mSamples->setReadOnly(false);
        spinBox_mSamples->setMinimum(100);
        spinBox_mSamples->setMaximum(16384);
        spinBox_mSamples->setSingleStep(10);
        spinBox_mSamples->setValue(1020);

        gridLayout_Channel->addWidget(spinBox_mSamples, 5, 1, 1, 1);

        doubleSpinBox_SampleRateMHz = new QDoubleSpinBox(groupBox_BoardConfiguration);
        doubleSpinBox_SampleRateMHz->setObjectName("doubleSpinBox_SampleRateMHz");
        doubleSpinBox_SampleRateMHz->setEnabled(true);
        doubleSpinBox_SampleRateMHz->setFont(font1);
        doubleSpinBox_SampleRateMHz->setMinimum(1.000000000000000);
        doubleSpinBox_SampleRateMHz->setMaximum(56.000000000000000);
        doubleSpinBox_SampleRateMHz->setSingleStep(1.000000000000000);
        doubleSpinBox_SampleRateMHz->setValue(50.000000000000000);

        gridLayout_Channel->addWidget(doubleSpinBox_SampleRateMHz, 7, 1, 1, 1);


        gridLayout_7->addLayout(gridLayout_Channel, 1, 0, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_7->addItem(verticalSpacer_6, 2, 0, 1, 1);


        gridLayout_6->addWidget(groupBox_BoardConfiguration, 2, 0, 1, 1);


        gridLayout_5->addWidget(frame_Settings, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1024, 22));
        menuData = new QMenu(menubar);
        menuData->setObjectName("menuData");
        menuDisplay = new QMenu(menubar);
        menuDisplay->setObjectName("menuDisplay");
        menuWindow = new QMenu(menubar);
        menuWindow->setObjectName("menuWindow");
        menuDevice = new QMenu(menubar);
        menuDevice->setObjectName("menuDevice");
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName("menuAbout");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuDevice->menuAction());
        menubar->addAction(menuData->menuAction());
        menubar->addAction(menuDisplay->menuAction());
        menubar->addAction(menuWindow->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menuData->addSeparator();
        menuData->addAction(actionRecord);
        menuData->addSeparator();
        menuData->addAction(actionOpen);
        menuData->addAction(actionRecent_Files);
        menuData->addSeparator();
        menuData->addAction(actionClose);
        menuData->addSeparator();
        menuDisplay->addSeparator();
        menuDisplay->addAction(actionSweep);
        menuDisplay->addAction(actionSample);
        menuDisplay->addSeparator();
        menuDisplay->addAction(actionAverage);
        menuDisplay->addSeparator();
        menuDisplay->addAction(actionMax_Hold);
        menuDisplay->addAction(actionMin_Hold);
        menuDisplay->addSeparator();
        menuWindow->addAction(actionReset_to_Default);
        menuWindow->addSeparator();
        menuDevice->addAction(actionFind_Devices);
        menuDevice->addSeparator();
        menuDevice->addAction(actionStop_Device);
        menuDevice->addSeparator();
        menuAbout->addSeparator();
        menuAbout->addSeparator();
        menuAbout->addAction(actionHelp);
        menuAbout->addAction(actionAbout_me);

        retranslateUi(MainWindow);

        tabWidget_Settings->setCurrentIndex(0);
        comboBox_nFFT->setCurrentIndex(3);
        comboBox_Gradient->setCurrentIndex(9);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionRecord->setText(QCoreApplication::translate("MainWindow", "Record", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionRecent_Files->setText(QCoreApplication::translate("MainWindow", "Recent Files", nullptr));
        actionClose->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
        actionFind_Devices->setText(QCoreApplication::translate("MainWindow", "Find", nullptr));
        actionStop_Device->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        actionHelp->setText(QCoreApplication::translate("MainWindow", "Help", nullptr));
        actionAbout_me->setText(QCoreApplication::translate("MainWindow", "About me!", nullptr));
        actionAverage->setText(QCoreApplication::translate("MainWindow", "Average", nullptr));
        actionSample->setText(QCoreApplication::translate("MainWindow", "Sample", nullptr));
        actionMax_Hold->setText(QCoreApplication::translate("MainWindow", "Max Hold", nullptr));
        actionMin_Hold->setText(QCoreApplication::translate("MainWindow", "Min Hold", nullptr));
        actionDual_Channel->setText(QCoreApplication::translate("MainWindow", "Dual", nullptr));
        actionReset_to_Default->setText(QCoreApplication::translate("MainWindow", "Dock to Mainwindow", nullptr));
        actionSweep->setText(QCoreApplication::translate("MainWindow", "Sweep", nullptr));
        groupBox_Sweep->setTitle(QString());
        label_SweepStartFreqMHz->setText(QCoreApplication::translate("MainWindow", "Start Freq. [MHz]", nullptr));
        label_SweepStopFreqMHz->setText(QCoreApplication::translate("MainWindow", "Stop Freq. [MHz]", nullptr));
        label_RBW->setText(QCoreApplication::translate("MainWindow", "RBW [MHz]", nullptr));
        pushButton__SpanBand3->setText(QCoreApplication::translate("MainWindow", "433 MHz", nullptr));
        checkBox_AGC->setText(QCoreApplication::translate("MainWindow", "AGC", nullptr));
        label_Channel->setText(QCoreApplication::translate("MainWindow", "Channel (RF)", nullptr));
        pushButton_SpanWiFiBand2->setText(QCoreApplication::translate("MainWindow", "5.8 GHz", nullptr));
        pushButton_SpanWiFiBand->setText(QCoreApplication::translate("MainWindow", "2.4 GHz", nullptr));
        pushButton_SweepFullSpan->setText(QCoreApplication::translate("MainWindow", "800 MHz", nullptr));
        comboBox_Channel->setItemText(0, QCoreApplication::translate("MainWindow", "A", nullptr));
        comboBox_Channel->setItemText(1, QCoreApplication::translate("MainWindow", "A, B", nullptr));

        checkBox_DCatt->setText(QCoreApplication::translate("MainWindow", "DC Attenuation", nullptr));
        comboBox_AntennaSingle->setItemText(0, QCoreApplication::translate("MainWindow", "TX/RX", nullptr));
        comboBox_AntennaSingle->setItemText(1, QCoreApplication::translate("MainWindow", "RX2", nullptr));

        label_ant->setText(QCoreApplication::translate("MainWindow", "Antenna", nullptr));
        label_SweepSpanMHz->setText(QCoreApplication::translate("MainWindow", "Span [MHz]", nullptr));
        label_freq->setText(QCoreApplication::translate("MainWindow", "Frequency [MHz]", nullptr));
        label_Rate->setText(QCoreApplication::translate("MainWindow", "Update Rate", nullptr));
        label_FFTsize->setText(QCoreApplication::translate("MainWindow", "FFT Size", nullptr));
        label_WindowType->setText(QCoreApplication::translate("MainWindow", "Window Type", nullptr));
        label_AverageSize->setText(QCoreApplication::translate("MainWindow", "Average Size", nullptr));
        comboBox_nFFT->setItemText(0, QCoreApplication::translate("MainWindow", "64", nullptr));
        comboBox_nFFT->setItemText(1, QCoreApplication::translate("MainWindow", "128", nullptr));
        comboBox_nFFT->setItemText(2, QCoreApplication::translate("MainWindow", "256", nullptr));
        comboBox_nFFT->setItemText(3, QCoreApplication::translate("MainWindow", "512", nullptr));
        comboBox_nFFT->setItemText(4, QCoreApplication::translate("MainWindow", "1024", nullptr));
        comboBox_nFFT->setItemText(5, QCoreApplication::translate("MainWindow", "2048", nullptr));

        comboBox_WindowType->setItemText(0, QCoreApplication::translate("MainWindow", "Rectangular", nullptr));
        comboBox_WindowType->setItemText(1, QCoreApplication::translate("MainWindow", "Hann", nullptr));
        comboBox_WindowType->setItemText(2, QCoreApplication::translate("MainWindow", "Hamming", nullptr));
        comboBox_WindowType->setItemText(3, QCoreApplication::translate("MainWindow", "FlatTop", nullptr));
        comboBox_WindowType->setItemText(4, QCoreApplication::translate("MainWindow", "Blackman", nullptr));
        comboBox_WindowType->setItemText(5, QCoreApplication::translate("MainWindow", "Blackman-Harris ", nullptr));

        tabWidget_Settings->setTabText(tabWidget_Settings->indexOf(tab_Spectrum), QCoreApplication::translate("MainWindow", "Spectrum", nullptr));
        label_WaterfallGradient->setText(QCoreApplication::translate("MainWindow", "Waterfall Gradient", nullptr));
        comboBox_Gradient->setItemText(0, QCoreApplication::translate("MainWindow", "Grayscale", nullptr));
        comboBox_Gradient->setItemText(1, QCoreApplication::translate("MainWindow", "Hot", nullptr));
        comboBox_Gradient->setItemText(2, QCoreApplication::translate("MainWindow", "Cold", nullptr));
        comboBox_Gradient->setItemText(3, QCoreApplication::translate("MainWindow", "Night", nullptr));
        comboBox_Gradient->setItemText(4, QCoreApplication::translate("MainWindow", "Candy", nullptr));
        comboBox_Gradient->setItemText(5, QCoreApplication::translate("MainWindow", "Geography", nullptr));
        comboBox_Gradient->setItemText(6, QCoreApplication::translate("MainWindow", "Ion", nullptr));
        comboBox_Gradient->setItemText(7, QCoreApplication::translate("MainWindow", "Thermal", nullptr));
        comboBox_Gradient->setItemText(8, QCoreApplication::translate("MainWindow", "Polar", nullptr));
        comboBox_Gradient->setItemText(9, QCoreApplication::translate("MainWindow", "Spectrum", nullptr));
        comboBox_Gradient->setItemText(10, QCoreApplication::translate("MainWindow", "Jet", nullptr));
        comboBox_Gradient->setItemText(11, QCoreApplication::translate("MainWindow", "Hues", nullptr));

        label_WaterfallSize->setText(QCoreApplication::translate("MainWindow", "Waterfall Size", nullptr));
        tabWidget_Settings->setTabText(tabWidget_Settings->indexOf(tab_Display), QCoreApplication::translate("MainWindow", "Waterfall", nullptr));
        label_ConstellationCenterFreq->setText(QCoreApplication::translate("MainWindow", "Center Freq. [MHz]", nullptr));
        label_ConstellationBW->setText(QCoreApplication::translate("MainWindow", "Bandwidth [MHz]", nullptr));
        pushButton_Test->setText(QCoreApplication::translate("MainWindow", "Test", nullptr));
        tabWidget_Settings->setTabText(tabWidget_Settings->indexOf(tab_Constellation), QCoreApplication::translate("MainWindow", "Constellation", nullptr));
        groupBox_BoardConfiguration->setTitle(QString());
        label_mSamples->setText(QCoreApplication::translate("MainWindow", "Sample Size", nullptr));
        label_SampleRate->setText(QCoreApplication::translate("MainWindow", "Sample Rate [MHz]", nullptr));
        label_TimeIntervalMS->setText(QCoreApplication::translate("MainWindow", "Time Frame [us]", nullptr));
        menuData->setTitle(QCoreApplication::translate("MainWindow", "Data", nullptr));
        menuDisplay->setTitle(QCoreApplication::translate("MainWindow", "Display", nullptr));
        menuWindow->setTitle(QCoreApplication::translate("MainWindow", "Window", nullptr));
        menuDevice->setTitle(QCoreApplication::translate("MainWindow", "Device", nullptr));
        menuAbout->setTitle(QCoreApplication::translate("MainWindow", "About", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
