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
  void getData(Mat bits); 
  void extractBits(Mat &code);
  void demask(vector<int> data);
  int getID(Mat &bits);

  Mat bits;
  vector<int> data;
  vector<int> productID;
private:
  vector<int> getmask(Mat bits);
  vector<int> getEncoding(vector<int> data);
  int getLength(vector<int> bits);
  
  int Length;
};


