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
  vector<int> extractBits(Mat &marker);
  void demask(vector<int> bits);
  int getID(vector<int> bits);
  
  vector<int> productID;
private:
  vector<int> getmask(vector<int> bits);
  vector<int> getEncoding(vector<int> bits);
  int getLength(vector<int> bits);
  
  int Length;
};


