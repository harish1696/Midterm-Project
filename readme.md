# Warehouse Bot - Stock Tracking and Counting Module
[![Build Status](https://travis-ci.org/harish1696/Midterm-Project.svg?branch=master)](https://travis-ci.org/harish1696/Midterm-Project)
[![Coverage Status](https://coveralls.io/repos/github/harish1696/Midterm-Project/badge.svg?branch=master)](https://coveralls.io/github/harish1696/Midterm-Project?branch=master)
---

## Overview

Cycle counting has become a common strategy to keep track of the warehouse inventory and prevent any financial losses that occur due to poor management of inventories in industries.But the way it is being done is time-consuming and might be erroneous as it involves human being. Hence it is always better to automate the process of cycle counting with the help of flying robots which will be able to access every nook and corner of the warehouse.

This software module can be integrated into the autonomous flying platform and  when the flying robot is commanded to navigate along the aisles of the warehouse, the module can track and give total count of each product (labelled with QR codes) in the warehouse.

In this version, the module can detect version 1 QRcodes without any hassle. For demonstration purpose, a video file with many QRcodes was compiled to show the efficiency of this module. When a video feed is passed to the module it looks for version 1 QRcode in each and every frame. IF detected it draws a boundary around the QRcode for the inspector at the ground station to know that the module is functioning properly. After the end of video feed, the module constructs a spreadsheet with the count and corresponding product ID value. This spreadsheet can be used for comparison with the data in Inventory management software and hence updates can be made in a giffy. 

Results:Screenshots

![results 1](https://user-images.githubusercontent.com/13302860/31695313-e822fff4-b377-11e7-9608-052684bddf5b.png)
![results 2](https://user-images.githubusercontent.com/13302860/31695316-eae83b78-b377-11e7-8807-e2fde1a3fb66.png)

When the end of file is reached, the module performs count operation and yields the following file in the build folder

![spreadsheet](https://user-images.githubusercontent.com/13302860/31695388-5e5f319c-b378-11e7-93bc-984fd397b0dd.png)

## License
MIT License

Copyright (c) 2017 Harish Sampathkumar

```
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

## Dependencies

Install OpenCV 3.3.0 using the following commands

Install Dependencies
```
sudo apt-get install build-essential checkinstall cmake pkg-config yasm gfortran git
sudo apt-get install libjpeg8-dev libjasper-dev libpng12-dev
# If you are using Ubuntu 14.04
sudo apt-get install libtiff4-dev
# If you are using Ubuntu 16.04
sudo apt-get install libtiff5-dev
sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev
sudo apt-get install libxine2-dev libv4l-dev
sudo apt-get install libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev
sudo apt-get install libqt4-dev libgtk2.0-dev libtbb-dev
sudo apt-get install libatlas-base-dev
sudo apt-get install libfaac-dev libmp3lame-dev libtheora-dev
sudo apt-get install libvorbis-dev libxvidcore-dev
sudo apt-get install libopencore-amrnb-dev libopencore-amrwb-dev
sudo apt-get install x264 v4l-utils
```
Download and Compile OpenCV
```
git clone https://github.com/opencv/opencv.git
cd opencv 
git checkout 3.3.0 
cd ..
git clone https://github.com/opencv/opencv_contrib.git
cd opencv_contrib
git checkout 3.3.0
cd ..
cd opencv
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE \
      -D CMAKE_INSTALL_PREFIX=/usr/local \
      -D INSTALL_C_EXAMPLES=ON \
      -D WITH_TBB=ON \
      -D WITH_V4L=ON \
      -D WITH_QT=ON \
      -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
      -D BUILD_EXAMPLES=ON ..
# find out number of CPU cores in your machine
nproc
# substitute 4 by output of nproc
make -j4
sudo make install
sudo sh -c 'echo "/usr/local/lib" >> /etc/ld.so.conf.d/opencv.conf'
sudo ldconfig
```

## SIP Process
SIP Process is followed to develop the module. It is detailed in the following link.
https://docs.google.com/spreadsheets/d/1u0NBx-Sbwx_unOhIq5AB6d5cziu2KoYzIz7XtidCmJc/edit?usp=sharing

## How to build
```
git clone --recursive https://github.com/harish1696/Midterm-Project
cd <path to repository>
mkdir build
cd build
cmake ..
make
```

## How to run demo
Go to your build directory and run the following command

```
./app/stockCount
```

## How to run tests
Go to your build directory and run the following command

```
./test/cpp-test
```

## How to generate doxygen documentation

```
doxygen ./Doxygen
  

