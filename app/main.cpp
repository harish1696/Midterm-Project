#include <iostream>
#include <opencv2/opencv.hpp>
#include <detectQRcode.hpp>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
  if(argc == 1)
  {
    cout << "Usage: " << argv[0] << " <image>" << endl;
    exit(0);
  }
  Mat img = imread(argv[1]);
  Mat imgBW;
  cvtColor(img, imgBW, CV_BGR2GRAY);
  adaptiveThreshold(imgBW, imgBW, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 51, 0);
  return 0;
  qrReader qr = qrReader();
  bool found = reader.find(imgBW);
  if(found) 
  {
    reader.drawFinders(img);
  }
  imshow("image", img);
  waitKey(0);

  return 0;
}
}
