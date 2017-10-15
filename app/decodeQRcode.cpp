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
#include <math.h>

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

void decodeQRcode::demask()
{
 vector<int> mask = getMask();
 if(mask[0] == 0 && mask[1] == 0 && mask[2] == 0)
 {
  for(int i=9;i<bits.rows;i++)
   {
    const uchar* ptr = bits.ptr<uchar>(i);
    for(int j=13;j<bits.cols;j++)
    {
      if(j%3==0)
      {
        if(ptr[j]==255) { 
          bits.at<uchar>(i,j) = 0; 
        }
        else if(ptr[j]==0) {
          bits.at<uchar>(i,j) = 255;
        }
      }
    }
   }
 }
 if(mask[0] == 0 && mask[1] == 0 && mask[2] == 255)
 {
  for(int i=9;i<bits.rows;i++)
   {
    for(int j=13;j<bits.cols;j++)
    {
      if((i+j)%3==0)
      {
        cout << i << ":" << j << endl;
        if(bits.at<uchar>(i,j)==255) { 
          bits.at<uchar>(i,j) = 0; 
        }
        else if(bits.at<uchar>(i,j)==0) {
          bits.at<uchar>(i,j) = 255;
        }
      }
    }
   }
 }
 if(mask[0] == 0 && mask[1] == 255 && mask[2] == 0)
 {
  for(int i=9;i<bits.rows;i++)
   {
    const uchar* ptr = bits.ptr<uchar>(i);
    for(int j=13;j<bits.cols;j++)
    {
      if((i+j)%2==0)
      {
        if(ptr[j]==255) { 
          bits.at<uchar>(i,j) = 0; 
        }
        else if(ptr[j]==0) {
          bits.at<uchar>(i,j) = 255;
        }
      }
    }
   }
 }
 if(mask[0] == 0 && mask[1] == 255 && mask[2] == 255)
 {
  for(int i=9;i<bits.rows;i++)
   {
    const uchar* ptr = bits.ptr<uchar>(i);
    for(int j=13;j<bits.cols;j++)
    {
      if(i%2==0)
      {
        if(ptr[j]==255) { 
          bits.at<uchar>(i,j) = 0; 
        }
        else if(ptr[j]==0) {
          bits.at<uchar>(i,j) = 255;
        }
      }
    }
   }
 }
 if(mask[0] == 255 && mask[1] == 0 && mask[2] == 0)
 {
  for(int i=9;i<bits.rows;i++)
   {
    const uchar* ptr = bits.ptr<uchar>(i);
    for(int j=13;j<bits.cols;j++)
    {
      if(((i*j)%3+i*j)%2==0)
      {
        if(ptr[j]==255) { 
          bits.at<uchar>(i,j) = 0; 
        }
        else if(ptr[j]==0) {
          bits.at<uchar>(i,j) = 255;
        }
      }
    }
   }
 }
 if(mask[0] == 255 && mask[1] == 0 && mask[2] == 255)
 {
  for(int i=9;i<bits.rows;i++)
   {
    const uchar* ptr = bits.ptr<uchar>(i);
    for(int j=13;j<bits.cols;j++)
    {
      if(((i*j)%3+i+j)%2==0)
      {
        if(ptr[j]==255) { 
          bits.at<uchar>(i,j) = 0; 
        }
        else if(ptr[j]==0) {
          bits.at<uchar>(i,j) = 255;
        }
      }
    }
   }
 }
 if(mask[0] == 255 && mask[1] == 255 && mask[2] == 0)
 {
  for(int i=9;i<bits.rows;i++)
   {
    const uchar* ptr = bits.ptr<uchar>(i);
    for(int j=13;j<bits.cols;j++)
    {
      if((i/2+j/3)%2==0)
      {
        if(ptr[j]==255) { 
          bits.at<uchar>(i,j) = 0; 
        }
        else if(ptr[j]==0) {
          bits.at<uchar>(i,j) = 255;
        }
      }
    }
   }
 }
 if(mask[0] == 255 && mask[1] == 255 && mask[2] == 255)
 {
  for(int i=9;i<bits.rows;i++)
   {
    const uchar* ptr = bits.ptr<uchar>(i);
    for(int j=13;j<bits.cols;j++)
    {
      if((i/2+j/3)%2==0)
      {
        if(ptr[j]==255) { 
          bits.at<uchar>(i,j) = 0; 
        }
        else if(ptr[j]==0) {
          bits.at<uchar>(i,j) = 255;
        }
      }
    }
   }
 } 
}

vector<int> decodeQRcode::getMask()
{
 vector<int> mask;
 mask.push_back(bits.at<uchar>(8,2));
 mask.push_back(bits.at<uchar>(8,3));
 mask.push_back(bits.at<uchar>(8,4));
 return mask;
}

void decodeQRcode::getData()
{
 data.clear();
 demask();
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
 for(int k=0;k<96;k++) {
   if(k%24==0) { cout << endl; }
   if(k%2==0) { cout << endl; }
   cout << data[k];
 }
}
  
void decodeQRcode::getID()
{
 int length_bits,ID,k;
 ID = 0;
 length_bits=getEncoding(); 
 getLength(length_bits);
 if(length == 1)
 { 
  k=3;
  for(int i=length_bits+4; i<length_bits+8; i++)
   {
    if(data[i] == 0) {
    ID += pow(2,k);
    }
   k--;
   }
 }
 else if(length == 2)
 { 
  k=6;
  for(int i=length_bits+4; i<length_bits+11; i++)
   {
    if(data[i] == 0) {
    ID += pow(2,k);
    }
   k--;
   }
 }
 productID.push_back(ID);
}  

int decodeQRcode::getEncoding()
{
 int no_bits;
 if(data[1]==0) {
   no_bits=8;
   //cout << endl << data[1] << endl; 
 }
 else if(data[2]==0) {
   no_bits=9;
   //cout << endl << data[2] << endl;
 }
 else if(data[3]==0) {
   no_bits=10;
   //cout << endl << data[3] << endl;
 }
 cout << endl << no_bits << endl;
 return no_bits;
}

void decodeQRcode::getLength(int length_bits)
{
 int k = length_bits-1;
 length = 0;
 for(int i=4;i<4+length_bits;i++)
  {
   cout << k << ":" << data[i] << endl;
   if(data[i] == 0) {
   length += pow(2,k);
   }
   k--;
  }
  cout << endl << length << endl;
}

















