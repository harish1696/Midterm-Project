/**
 * @file detectQRcode.cpp
 * @author Harish Sampathkumar
 * @copyright MIT License
 *
 * @brief Warehouse Robot - Stock Tracking and Counting Module
 *
 * @section Description
 *
 * This module helps detect the presence of QRcodes in a given
 * image frame and draw boundaries around it.
 *
 */

#include <iostream>
#include <decodeQRcode.hpp>
#include <detectQRcode.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;

/**
 * @brief  Constructs a object
 */
decodeQRcode::decodeQRcode() {}

/**
 * @brief Destroys a object
 */
decodeQRcode::~decodeQRcode() {}

void decodeQRcode::extractBits(Mat &code) 
{
    bits.create(21,21,CV_8UC1);
    const int width = code.cols;
    const int height = code.rows;
    int blackCount=0;
    int whiteCount=0;
    for(int y=0;y<height;y+=20) {
        for(int x=0;x<width;x+=20) {
            for(int i=0;i<20;i++) {
              const uchar* ptr = code.ptr<uchar>(y+i);
              for (int j=0;j<20;j++) {
                 if(ptr[x+j] > 128) {
                    whiteCount++;
                 } else {
                    blackCount++;
                 }
              }
            }
            if(whiteCount > blackCount) {
                  bits.at<uchar>(y/20,x/20) = 255;
            } else {
                  bits.at<uchar>(y/20,x/20) = 0;
            }  
            blackCount=0;
            whiteCount=0; 
      }   
   }
   for(int i=0;i<21;i++) {
     const uchar* ptr2 = bits.ptr<uchar>(i);
     for(int j=0;j<21;j++) {
       if(ptr2[j] >128)
       cout << 1;
       else
       cout << 0;
     }
     cout << endl;
   }
}

void decodeQRcode::getData(Mat bits)
{
 data.clear();
 int count=0;
  for(int i=bits.cols-1;i>=14;i-=2) 
  {
   if(count%2==0) 
   {
    cout << count << endl;
    for(int j=bits.rows-1;j>=0;j--) 
    {  
      if(j>8) 
      {
        if(bits.at<uchar>(j,i)==255 && bits.at<uchar>(j,i-1)==255 ) {
          data.push_back(1);
          data.push_back(1);
        }
        if(bits.at<uchar>(j,i)==255 && bits.at<uchar>(j,i-1)==0 ) {
          data.push_back(1);
          data.push_back(0);
        }
        if(bits.at<uchar>(j,i)==0 && bits.at<uchar>(j,i-1)==255 ) {
         data.push_back(0);
         data.push_back(1);
        }
        if(bits.at<uchar>(j,i)==0 && bits.at<uchar>(j,i-1)==0 ) {
          data.push_back(0);
          data.push_back(0);
        }
      }
    }
   }
   if(count%2!=0) 
   {
    cout << count << endl;
    for(int j=0;j<bits.rows;j++) 
    {
      if(j>8) 
      {
        if(bits.at<uchar>(j,i)==255 && bits.at<uchar>(j,i-1)==255 ) {
          data.push_back(1);
          data.push_back(1);
        }
        if(bits.at<uchar>(j,i)==255 && bits.at<uchar>(j,i-1)==0 ) {
          data.push_back(1);
          data.push_back(0);
        }
        if(bits.at<uchar>(j,i)==0 && bits.at<uchar>(j,i-1)==255 ) {
         data.push_back(0);
         data.push_back(1);
        }
        if(bits.at<uchar>(j,i)==0 && bits.at<uchar>(j,i-1)==0 ) {
          data.push_back(0);
          data.push_back(0);
        }
      }
    }
   }
 count++;
 }
 
}
   
 





















