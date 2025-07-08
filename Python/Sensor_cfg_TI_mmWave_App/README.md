# mmWave sensors Configuration Desktop Application 

This GUI application is developed and referenced on [mmWave Demo Visualizer](https://dev.ti.com/gallery/view/mmwave/mmWave_Demo_Visualizer/ver/3.6.0/) for configuring mmWave sensors. 
With this software, you can customize more configuration parameters. It supports IWR6843ISK, AWR1642BOOST, IWR1843BOOST.

## 1. Flash the mmWave sensors 
The binary image can be found from [TI's Resource Explorer](https://dev.ti.com/tirex/explore/node?node=A__AEIJm0rwIeU.2P1OBWwlaA__radar_toolbox__1AslXXD__LATEST).
After downloading the Radar Toolbox, go to the folder ~/radar_toolbox_3_10_00_05/source/ti/examples/Out_Of_Box_Demo/prebuilt_binaries,
the related image can be find out in this path. You need to download the TI's [UniFlash](https://www.ti.com/tool/UNIFLASH) to flash the sensors. 
Please follow step on how to flash the sensors on TI website by reading the User Guide: [IWR6843ISK](https://www.ti.com/tool/IWR6843ISK), [AWR1642BOOST](https://www.ti.com/tool/AWR1642BOOST), and [IWR1843BOOST](https://www.ti.com/tool/IWR1843BOOST).

## 2. How to get the Configuration file from the mmWave Demo Visualizer 
To use this GUI desktop application, you firstly go to the following [mmWave Demo Visualizer](https://dev.ti.com/gallery/view/mmwave/mmWave_Demo_Visualizer/ver/3.6.0/). 
- Select the related sensor at Setup Details 
- Click Options: Serial Port Configuration and choose the respective ports 
- Click "SEND CONFIG TO MMWAVE DEVICE" to check the sensor is working accordingly, you will see the plots if it works.
- Click "SAVE CONFIG TO PC" to save the configuration file "*.cfg", which need to import into the GUI Desktop Application.
This config can be customized with the application. 


## 3. How to use the desktop application

At **~/Sensor_cfg_TI_mmWave_App/dist/** path, you can launch the standalone application either **Sensor_cfg_TI_mmWave_App(Linux_Ubuntu)** or **Sensor_cfg_TI_mmWave_App(Window).exe**
 based on your OS.

Connect the sensor to computer after launching the application. It will detect the available port. 

- Select the respective port at "Data" and "Command" sections. 
- Import the "*.cfg" file from the mmWave Demo Visualizer to the application at "Browse Config (*.CFG)"
- Click "Connect" and "Send Configuration"
- You need to click "Send Configuration" whenever the configuration parameters have been changed at the application. 
- If you want to restart, you can press the "NRST" button from the sensor's hardware device. 

For more information, you can reference on either the documentation or the video tutorial. 

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Copyright (c) 2024, <Mohammad Alaee, Min Bo Bo Kyaw>, university of luxembourg
website: https://radarmimo.com/
All rights reserved.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
3. All advertising materials mentioning features or use of this software
    must display the following acknowledgement:
    "This product includes software developed by <Mohammad Alaee>,
    https://radarmimo.com/"

THIS SOFTWARE IS PROVIDED BY <COPYRIGHT HOLDER> ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# https://radarmimo.com/
Email: info@radarmimo.com, mohammad.alaee@uni.lu, min.kyaw@uni.lu
Code written by : Mohammad Alaee, Min Bo Bo Kyaw
Compatible Sensors: xWR6843, xWR1843, xWR1642
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
