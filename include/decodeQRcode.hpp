#pragma once

#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

class decodeQRcode {
public:
  decodeQRcode();
  ~decodeQRcode();
  void extractBits(Mat &code);
  void getData(); 
  void getID();
  vector<int> productID;

private:
  void demask();
  vector<int> getMask();
  int getEncoding();
  void getLength(int length_bits);
  Mat bits;
  vector<int> data;
  int length;
};


