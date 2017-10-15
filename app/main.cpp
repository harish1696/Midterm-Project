#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <detectQRcode.hpp>
#include <decodeQRcode.hpp>

using namespace std;
using namespace cv;


int main(int argc, char* argv[])
{
  int count =1;
  String imageName( "../Qrcode2.JPG" ); // by default
  if( argc > 1)
    {
        imageName = argv[1];
    }
 
  Mat img = imread(imageName,IMREAD_COLOR);
  resize(img,img,Size(375,500),0,0,CV_INTER_AREA);
  cout << img.cols << " : " << img.rows << endl;
  Mat imgBW;
  cvtColor(img, imgBW, CV_BGR2GRAY);
  adaptiveThreshold(imgBW, imgBW, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 51, 0);
  detectQRcode qr;
  bool found = qr.find(imgBW);
  if(found) 
  {
     cout << count++ << endl;
     qr.drawBoundary(img);
  }
  qr.extractQRcode(img);
  cvtColor(img, imgBW, CV_BGR2GRAY);
  adaptiveThreshold(imgBW, img, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 51, 0);
  //imshow("image", img);
  decodeQRcode qr1;
  qr1.extractBits(img);
  qr1.getData();
  qr1.getID();
  for(int i=0;i<qr1.productID.size();i++)
    cout<<endl<<qr1.productID[i]<<endl;
  waitKey(0);

  return 0;
}

