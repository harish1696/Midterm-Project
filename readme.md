# Warehouse Bot - Stock Tracking and Counting Module
[![Build Status](https://travis-ci.org/harish1696/Midterm-Project.svg?branch=master)](https://travis-ci.org/harish1696/Midterm-Project)
[![Coverage Status](https://coveralls.io/repos/github/harish1696/Midterm-Project/badge.svg?branch=master)](https://coveralls.io/github/harish1696/Midterm-Project?branch=master)
---

## Overview

Cycle counting has become a common strategy to keep track of the warehouse inventory and prevent any financial losses that occur due to poor management of inventories in industries.But the way it is being done is time-consuming and might be erroneous as it involves human being. Hence it is always better to automate the process of cycle counting with the help of flying robots which will be able to access every nook and corner of the warehouse.

The module will be able to detect QRcodes ( seen in the pallets in warehouses) from the input video file and decode them containing product ID of each package. The decoded information is then used to keep track of the inventory in the warehouse. The count of each product ID generated after each cycle counting is then used to verify the count in the inventory management software used by the company.

The software module can be integrated into the autonomous flying platform and  when the flying robot is commanded to navigate along the aisles of the warehouse, the module can track and give total count of each product (labelled with QR codes) in the warehouse.


## Week 1 Sprint Planning
SIP Process is followed to develop the module. It is detailed in the following link.
https://docs.google.com/spreadsheets/d/1u0NBx-Sbwx_unOhIq5AB6d5cziu2KoYzIz7XtidCmJc/edit?usp=sharing

## Standard install via command-line
```
git clone --recursive https://github.com/harish1696/Midterm-Project
cd <path to repository>
mkdir build
cd build
cmake ..
make
Run tests: ./test/cpp-test
Run program: ./app/shell-app
```

## Building for code coverage 
```
sudo apt-get install lcov
cmake -D COVERAGE=ON -D CMAKE_BUILD_TYPE=Debug ../
make
make code_coverage
```
This generates a index.html page in the build/coverage sub-directory that can be viewed locally in a web browser.

## Working with Eclipse IDE ##

## Installation

In your Eclipse workspace directory (or create a new one), checkout the repo (and submodules)
```
mkdir -p ~/workspace
cd ~/workspace
git clone --recursive https://github.com/harish1696/Midterm-Project
```

In your work directory, use cmake to create an Eclipse project for an [out-of-source build] of cpp-boilerplate

```
cd ~/workspace
mkdir -p boilerplate-eclipse
cd boilerplate-eclipse
cmake -G "Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug -D CMAKE_ECLIPSE_VERSION=4.7.0 -D CMAKE_CXX_COMPILER_ARG1=-std=c++14 ../cpp-boilerplate/
```

## Import

Open Eclipse, go to File -> Import -> General -> Existing Projects into Workspace -> 
Select "boilerplate-eclipse" directory created previously as root directory -> Finish

# Edit

Source files may be edited under the "[Source Directory]" label in the Project Explorer.


## Build

To build the project, in Eclipse, unfold boilerplate-eclipse project in Project Explorer,
unfold Build Targets, double click on "all" to build all projects.

## Run

1. In Eclipse, right click on the boilerplate-eclipse in Project Explorer,
select Run As -> Local C/C++ Application

2. Choose the binaries to run (e.g. shell-app, cpp-test for unit testing)


## Debug


1. Set breakpoint in source file (i.e. double click in the left margin on the line you want 
the program to break).

2. In Eclipse, right click on the boilerplate-eclipse in Project Explorer, select Debug As -> 
Local C/C++ Application, choose the binaries to run (e.g. shell-app).

3. If prompt to "Confirm Perspective Switch", select yes.

4. Program will break at the breakpoint you set.

5. Press Step Into (F5), Step Over (F6), Step Return (F7) to step/debug your program.

6. Right click on the variable in editor to add watch expression to watch the variable in 
debugger window.

7. Press Terminate icon to terminate debugging and press C/C++ icon to switch back to C/C++ 
perspetive view (or Windows->Perspective->Open Perspective->C/C++).


## Plugins

- CppChEclipse

    To install and run cppcheck in Eclipse

    1. In Eclipse, go to Window -> Preferences -> C/C++ -> cppcheclipse.
    Set cppcheck binary path to "/usr/bin/cppcheck".

    2. To run CPPCheck on a project, right click on the project name in the Project Explorer 
    and choose cppcheck -> Run cppcheck.


- Google C++ Sytle

    To include and use Google C++ Style formatter in Eclipse

    1. In Eclipse, go to Window -> Preferences -> C/C++ -> Code Style -> Formatter. 
    Import [eclipse-cpp-google-style][reference-id-for-eclipse-cpp-google-style] and apply.

    2. To use Google C++ style formatter, right click on the source code or folder in 
    Project Explorer and choose Source -> Format

[reference-id-for-eclipse-cpp-google-style]: https://raw.githubusercontent.com/google/styleguide/gh-pages/eclipse-cpp-google-style.xml

- Git

    It is possible to manage version control through Eclipse and the git plugin, but it typically requires creating another project. If you're interested in this, try it out yourself and contact me on Canvas.
