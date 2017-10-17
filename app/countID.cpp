/**
 * @file detectQRcode.cpp
 * @author Harish Sampathkumar
 * @copyright MIT License
 *
 * @brief Warehouse Robot - Stock Tracking and Counting Module
 *
 * @section Description
 *
 * This module helps count the occurences of eacd Product ID
 * from the set of all ID's detected
 *
 */

#include <iostream>
#include <detectQRcode.hpp>
#include <decodeQRcode.hpp>
#include <countID.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;

/**
 * @brief  Constructs a object
 */
countID::countID() {}

/**
 * @brief Destroys a object
 */
countID::~countID() {}

/**
 * @brief Finds the no. of occurences of each Product ID
 * @param id all the ids collected from video file
 * @return none
 */
void countID::getCount(vector<int> id) {
   // remove the noises in the ID detected in video
   for(int i=3; i<id.size(); i++) {
     if(id[i]!=id[i-1] && id[i]!=id[i-2] && id[i]!=id[i-3] && id[i]!=id[i+1] && id[i]!=id[i+2] && id[i]!=id[i+3]) {
       id[i] = 0;
     }
   }
   int a,c;
   vector<int> id1;
   // differentiate identical ID's appearing consecutively
   for(auto  i : id) {
     if(i == 0) {
       c++;
     }
     else {
       if(c>15) {
         id1.push_back(0);
       }
       c=0;
       id1.push_back(i);
     }
   }
 
   for(int i=0; i<id1.size(); i++) {
     if(id1[i] != id1[i+1]) {
       ID.push_back(id1[i]);
     }
   }  
   // Do the count
   a = 1;
   for(int i=0; i<ID.size(); i++) {
     if(ID[i] != 0) {
       for(int j = i+1; j<ID.size(); j++) {
         if(ID[i] == ID[j]) {
           a++;
           ID[j] = 0;
         }
       }
       Count.push_back(a);
       a = 1;
     }
   }
   
   ID.erase(std::remove(ID.begin(), ID.end(), 0), ID.end());
}  

/**
 * @brief Convert the ID and count in a presentable form
 * @param none
 * @return none
 */      
void countID::convertTocsv() {
   ofstream output;
   output.open("Finalcount.csv");
   output << "ID, Count" << endl;
   for (int i = 0; i<ID.size(); i++) {
     output << ID[i] << "," << Count[i] << endl;
   }
}
        
  

