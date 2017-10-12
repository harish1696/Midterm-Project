#pragma once

#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
using namespace std;
using namespace cv;

class detectQRcode {
public:
  bool find(const Mat& img);
  void drawBoundary(Mat& img);
  
private:
  vector<Point2f> centers;
  vector<float> moduleSize;
  bool checkRatio(int* statecount);
  bool isCenter(const Mat &img, int* stateCount, int row, int col);
  bool checkDiagonal(const Mat &img, float centerRow, float centerCol, int maxCount, int totalCount);
  float checkVertical(const Mat& img, int startRow, int centerCol, int stateCount, int totalCount);
  float checkHorizontal(const Mat& img, int centerRow, int startCol, int stateCount, int totalCount);
  float calcCenter(int* stateCount, int end);
};


