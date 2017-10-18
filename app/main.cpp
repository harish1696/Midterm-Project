/**
 * @file detectQRcode.cpp
 * @author Harish Sampathkumar
 * @copyright MIT License
 *
 * @brief Warehouse Robot - Stock Tracking and Counting Module
 *
 * @section Description
 *
 * Detection, Decoding and Counting of QRcodes
 * 
 *
 */


#include <iostream>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <detectQRcode.hpp>
#include <decodeQRcode.hpp>
#include <countID.hpp>

using std::cout;
using std::endl;

int main() {
  vector<int> ID;
  String imageName("../testfiles/Demo.avi");  // by default
  cv::VideoCapture cap(imageName);
  while (1) {
  cv::Mat img;
  cap.read(img);
  if (img.empty()) {
  cout << "END" << endl;  // display END at end of file
  break;
  }
  cv::Mat imgBW;
  // convert the image to binary image
  cv::cvtColor(img, imgBW, CV_BGR2GRAY);
  cv::adaptiveThreshold(imgBW, imgBW, 255,
           CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 51, 0);
  // initialize object of class detectQRcode
  detectQRcode qr;
  // check if the image contains QRcode
  bool found = qr.find(imgBW);
  // if image contains QRcode draw boundary around it
  if (found) {
     qr.drawBoundary(img);
  }
  // display the image with/without detected QRcode
  cv::imshow("image", img);
  // extract the QRcode and convert it to binary
  if (found)
  found = qr.extractQRcode(img);
  cv::cvtColor(img, imgBW, CV_BGR2GRAY);
  cv::adaptiveThreshold(imgBW, img, 255,
           CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 51, 0);
  // intialize object of class decodeQRcode
  decodeQRcode qr1;
  // get the product ID stored in QRcode
  if (found) {
  qr1.extractBits(img);
  qr1.getData();
  ID.push_back(qr1.getID());
  }
  ID.push_back(0);
  waitKey(30);
  }
  countID qr2;
  qr2.getCount(ID);
  qr2.convertTocsv();
  return 0;
}

