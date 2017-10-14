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
  detectQRcode();
  ~detectQRcode();
  bool find(Mat &img);
  void drawBoundary(Mat &img);
  void extractQRcode(Mat &img);
  void extractBits(Mat &marker);
  
private:
  vector<Point2f> centers;
  vector<Point2f> corners;
  vector<float> moduleSize;
  void sortCenters();
  bool checkRatio(vector<int> statecount);
  bool isCenter(const Mat &img, vector<int> stateCount, int row, int col);
  bool checkDiagonal(const Mat &img, float centerRow, float centerCol, int maxCount, int totalCount);
  float checkVertical(const Mat& img, int startRow, int centerCol, int stateCount, int totalCount);
  float checkHorizontal(const Mat& img, int centerRow, int startCol, int stateCount, int totalCount);
  float calcCenter(vector<int> stateCount, int end);
};


