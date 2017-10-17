/**
 * @file detectQRcode.cpp
 * @author Harish Sampathkumar
 * @copyright MIT License
 *
 * @brief Warehouse Robot - Stock Tracking and Counting Module
 *
 * @section Description
 *
 * Test cases
 * 
 *
 */
#include <gtest/gtest.h>
#include <detectQRcode.hpp>
#include <decodeQRcode.hpp>
#include <countID.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <math.h>

using namespace std;
using namespace cv;

TEST(findMethod, should_pass) {
  detectQRcode qr;
  String imageName1( "../testimages/100.JPG" ); 
  String imageName2( "../testimages/Lenna.png" );
  Mat img = imread(imageName1,IMREAD_COLOR);
  resize(img,img,Size(375,500),0,0,CV_INTER_AREA);
  Mat imgBW;
  cvtColor(img, imgBW, CV_BGR2GRAY);
  adaptiveThreshold(imgBW, imgBW, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 51, 0);
  bool found = qr.find(imgBW);
  EXPECT_TRUE(found);
  EXPECT_EQ(1,qr.centers[0].x < qr.centers[1].x);
  EXPECT_EQ(1,qr.centers[0].y < qr.centers[2].y);
  EXPECT_EQ(0,qr.centers[2].x > qr.centers[1].x);
  EXPECT_EQ(0,qr.centers[1].y > qr.centers[2].y);
  img = imread(imageName2,IMREAD_COLOR);
  resize(img,img,Size(375,500),0,0,CV_INTER_AREA);
  cvtColor(img, imgBW, CV_BGR2GRAY);
  adaptiveThreshold(imgBW, imgBW, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 51, 0);
  found = qr.find(imgBW);
  EXPECT_FALSE(found);
}

TEST(drawBoundaryMethod, should_pass) {
  detectQRcode qr;
  String imageName1( "../testimages/100.JPG" ); 
  String imageName2( "../testimages/Lenna.png" );
  Mat img = imread(imageName1,IMREAD_COLOR);
  resize(img,img,Size(375,500),0,0,CV_INTER_AREA);
  Mat imgBW;
  cvtColor(img, imgBW, CV_BGR2GRAY);
  adaptiveThreshold(imgBW, imgBW, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 51, 0);
  bool found = qr.find(imgBW);
  ASSERT_TRUE(found);
  qr.drawBoundary(img);
} 

TEST(extractQRcodeMethod, should_pass) {
  detectQRcode qr;
  String imageName1( "../testimages/100.JPG" ); 
  String imageName2( "../testimages/Lenna.png" );
  Mat img = imread(imageName1,IMREAD_COLOR);
  resize(img,img,Size(375,500),0,0,CV_INTER_AREA);
  Mat imgBW;
  cvtColor(img, imgBW, CV_BGR2GRAY);
  adaptiveThreshold(imgBW, imgBW, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 51, 0);
  bool found = qr.find(imgBW);
  ASSERT_TRUE(found);
  qr.drawBoundary(img);
  found = qr.extractQRcode(img);
  ASSERT_TRUE(found);
  EXPECT_EQ(420, img.rows);
  EXPECT_EQ(420, img.cols);
}
  
TEST(extractBitsMethod, should_pass) {
   detectQRcode qr;
   String imageName1( "../testimages/100.JPG" );
   String imageName2( "../testimages/100.JPG" );
   Mat img = imread(imageName1,IMREAD_COLOR);
   resize(img,img,Size(375,500),0,0,CV_INTER_AREA);
   Mat imgBW;
   cvtColor(img, imgBW, CV_BGR2GRAY);
   adaptiveThreshold(imgBW, imgBW, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 51, 0);
   bool found = qr.find(imgBW);
   ASSERT_TRUE(found);
   qr.drawBoundary(img);
   found = qr.extractQRcode(img);
   ASSERT_TRUE(found);
   cvtColor(img, imgBW, CV_BGR2GRAY);
   adaptiveThreshold(imgBW, imgBW, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 51, 0);
   decodeQRcode qr1, qr2;
   qr1.extractBits(imgBW);
   img = imread(imageName2,IMREAD_COLOR);
   resize(img,img,Size(375,500),0,0,CV_INTER_AREA);
   cvtColor(img, imgBW, CV_BGR2GRAY);
   adaptiveThreshold(imgBW, imgBW, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 51, 0);
   found = qr.find(imgBW);
   ASSERT_TRUE(found);
   qr.drawBoundary(img);
   found = qr.extractQRcode(img);
   ASSERT_TRUE(found);
   cvtColor(img, imgBW, CV_BGR2GRAY);
   adaptiveThreshold(imgBW, imgBW, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 51, 0);
   qr2.extractBits(imgBW);
   for(int i=0; i<qr1.bits.rows; i++) 
    for(int j=0; j<qr1.bits.cols; j++)
      EXPECT_EQ(qr1.bits.at<uchar>(i,j), qr2.bits.at<uchar>(i,j));
}

TEST(getIDMethod, should_pass) {
   detectQRcode qr;
   String imageName1( "../testimages/100.JPG" );
   String imageName2( "../testimages/100.JPG" );
   String imageName3( "../testimages/1101.JPG" );
   Mat img = imread(imageName1,IMREAD_COLOR);
   resize(img,img,Size(375,500),0,0,CV_INTER_AREA);
   Mat imgBW;
   cvtColor(img, imgBW, CV_BGR2GRAY);
   adaptiveThreshold(imgBW, imgBW, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 51, 0);
   bool found = qr.find(imgBW);
   ASSERT_TRUE(found);
   qr.drawBoundary(img);
   found = qr.extractQRcode(img);
   ASSERT_TRUE(found);
   cvtColor(img, imgBW, CV_BGR2GRAY);
   adaptiveThreshold(imgBW, imgBW, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 51, 0);
   decodeQRcode qr1, qr2, qr3;
   qr1.extractBits(imgBW);
   qr1.getData();
   int iD1 = qr1.getID();
   img = imread(imageName2,IMREAD_COLOR);
   resize(img,img,Size(375,500),0,0,CV_INTER_AREA);
   cvtColor(img, imgBW, CV_BGR2GRAY);
   adaptiveThreshold(imgBW, imgBW, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 51, 0);
   found = qr.find(imgBW);
   ASSERT_TRUE(found);
   qr.drawBoundary(img);
   found = qr.extractQRcode(img);
   ASSERT_TRUE(found);
   cvtColor(img, imgBW, CV_BGR2GRAY);
   adaptiveThreshold(imgBW, imgBW, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 51, 0);
   qr2.extractBits(imgBW);
   qr2.getData();
   int iD2 = qr2.getID();
   img = imread(imageName3,IMREAD_COLOR);
   resize(img,img,Size(375,500),0,0,CV_INTER_AREA);
   cvtColor(img, imgBW, CV_BGR2GRAY);
   adaptiveThreshold(imgBW, imgBW, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 51, 0);
   found = qr.find(imgBW);
   ASSERT_TRUE(found);
   qr.drawBoundary(img);
   found = qr.extractQRcode(img);
   ASSERT_TRUE(found);
   cvtColor(img, imgBW, CV_BGR2GRAY);
   adaptiveThreshold(imgBW, imgBW, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 51, 0);
   qr3.extractBits(imgBW);
   qr3.getData();
   int iD3 = qr3.getID();
   EXPECT_EQ(iD1,iD2);
   EXPECT_NE(iD1,iD3);
}

TEST(getCountMethod, should_pass) {
   vector<int> test, sample;;
   sample = {44,532,100,2,7,1100};
   int pID;
   ifstream input;
   input.open("../testimages/rawIDs.txt");
   while(!input.eof()) {
      input >> pID;
      test.push_back(pID);
   }
   input.close();
   countID qr;
   qr.getCount(test);
   EXPECT_EQ(sample,qr.ID);
}


