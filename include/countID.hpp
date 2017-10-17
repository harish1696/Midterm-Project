#pragma once

#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

class countID {
public:
  countID();
  ~countID();
  void getCount(vector<int> id);
  void convertTocsv();

  vector<int> Count;
  vector<int> ID;
};
