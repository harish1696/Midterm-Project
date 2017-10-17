/**
 * @file detectQRcode.cpp
 * @author Harish Sampathkumar
 * @copyright MIT License
 *
 * @brief Warehouse Robot - Stock Tracking and Counting Module
 *
 * @section Description
 *
 * This module helps detect the presence of QRcodes in a given
 * image frame and draw boundaries around it.
 *
 */

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <detectQRcode.hpp>
#include <decodeQRcode.hpp>

using namespace std;
using namespace cv;


int main()
{
  int count =1;
  vector<int> ID;
  String imageName( "../Demo.avi" ); // by default
  VideoCapture cap(imageName);
  while(1) {
  Mat img;
  cap.read(img);
  if(img.empty()) {
  cout << "END" << endl;
  break;
  }
  cout << img.cols << " : " << img.rows << endl;
  Mat imgBW;
  // convert the image to binary image
  cvtColor(img, imgBW, CV_BGR2GRAY);
  adaptiveThreshold(imgBW, imgBW, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 51, 0);
  // initialize object of class detectQRcode
  detectQRcode qr;
  // check if the image contains QRcode
  bool found = qr.find(imgBW);
  // if image contains QRcode draw boundary around it
  if(found) {
     cout << count++ << endl;
     qr.drawBoundary(img);
  }
  // display the image with/without detected QRcode
  imshow("image",img);
  // extract the QRcode and convert it to binary
  if(found)
  found = qr.extractQRcode(img);
  cvtColor(img, imgBW, CV_BGR2GRAY);
  adaptiveThreshold(imgBW, img, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 51, 0);
  // intialize object of class decodeQRcode
  decodeQRcode qr1;
  // get the product ID stored in QRcode
  if(found) {
  qr1.extractBits(img);
  qr1.getData();
  ID.push_back(qr1.getID());
  }
  ID.push_back(0);
  ofstream out;
  out.open("file.txt");
  for(auto& i : ID)
    out<<i<<endl;
  out.close();
  //for(auto& i : ID)
  //  cout<<endl<<i<<endl;
  waitKey(30);
  }
  return 0;
}

