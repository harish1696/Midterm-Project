#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <detectQRcode.hpp>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
  String imageName( "../heinz.jpg" ); // by default
  if( argc > 1)
    {
        imageName = argv[1];
    }
 
  Mat img = imread(imageName,IMREAD_COLOR);
  Mat imgBW;
  cvtColor(img, imgBW, CV_BGR2GRAY);
  adaptiveThreshold(imgBW, imgBW, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 51, 0);
  return 0;
  detectQRcode qr = detectQRcode();
  bool found = qr.find(imgBW);
  if(found) 
  {
    qr.drawBoundary(img);
  }
  imshow("image", img);
  waitKey(0);

  return 0;
}

