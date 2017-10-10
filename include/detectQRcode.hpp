#pragma once

#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

class detectQRcode() {
public:
  bool find(const Mat& img);
  void draw(Mat& img);
  
private:
  vector<point2f> center;
  vector<float> moduleSize;
  bool checkRatio(int* statecount);
  bool isCenter(const Mat &img, int* stateCount, int row, int col);
  bool checkDiagonal(const Mat &img, float centerRow, float centerCol, int maxCount, int stateCountTotal);
  float checkVertical(const Mat& img, int startRow, int centerCol, int stateCount, int stateCountTotal);
  float checkHorizontal(const Mat& img, int centerRow, int startCol, int stateCount, int stateCountTotal);
  float calcCenter(int* stateCount, int end);
}


