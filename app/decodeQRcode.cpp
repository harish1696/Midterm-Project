/**
 * @file detectQRcode.cpp
 * @author Harish Sampathkumar
 * @copyright MIT License
 *
 * @brief Warehouse Robot - Stock Tracking and Counting Module
 *
 * @section Description
 *
 * This module helps decode the extracted QRcodes by finding
 * the product ID stored in the Qrcode
 *
 */
#include <math.h>
#include <iostream>
#include <decodeQRcode.hpp>
#include <detectQRcode.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using std::cout;
using std::endl;
using std::vector;

/**
 * @brief  Constructs a object
 */
decodeQRcode::decodeQRcode() {
  length = 0;
}

/**
 * @brief Destroys a object
 */
decodeQRcode::~decodeQRcode() {}

/**
 * @brief Converts the QRcode into 1's and 0's
 * @param code an image representing version 1 QRcode
 * @return none
 */
void decodeQRcode::extractBits(Mat &code) {
  bits.create(21, 21, CV_8UC1);
  // initializes variables to count number of white and black cells
  int blackCount = 0;
  int whiteCount = 0;
  // loop to extract the bits stored in the version 1 QRcode
  for (int y = 0; y < code.rows; y += 20) {
     for (int x = 0; x < code.cols; x += 20) {
        for (int i = 0 ; i < 20 ; i++) {
          const uchar* ptr = code.ptr<uchar>(y + i);
          for (int j = 0; j < 20; j++) {
             if (ptr[x + j] > 128) {
                whiteCount++;
             } else {
                blackCount++;
             }
          }
        }
        if (whiteCount > blackCount) {
        bits.at<uchar>(y / 20, x / 20) = 255;
         } else {
        bits.at<uchar>(y / 20, x / 20) = 0;
      }
      blackCount = 0;
      whiteCount = 0;
     }
  }
}

/**
 * @brief Finds the mask used in QRcode and demask it
 * @param none
 * @return none
 */
void decodeQRcode::demask() {
  // get the masking scheme used from the extracted bits
  vector<int> mask = getMask();

  // if the mask is black->black->black
  if (mask[0] == 0 && mask[1] == 0 && mask[2] == 0) {
  for (int i = 9; i < bits.rows; i++) {
    const uchar* ptr = bits.ptr<uchar>(i);
    for (int j = 13; j < bits.cols; j++) {
      if (j % 3 == 0) {
        if (ptr[j] == 255) {
          bits.at<uchar>(i, j) = 0;
        } else if (ptr[j] == 0) {
          bits.at<uchar>(i, j) = 255;
        }
      }
    }
  }
  }
  // if the mask is black->black->white
  if (mask[0] == 0 && mask[1] == 0 && mask[2] == 255) {
  for (int i = 9; i < bits.rows; i++) {
    for (int j = 13; j < bits.cols; j++) {
      if ((i + j) % 3 == 0) {
        if (bits.at<uchar>(i, j) == 255) {
          bits.at<uchar>(i, j) = 0;
        } else if (bits.at<uchar>(i, j) == 0) {
          bits.at<uchar>(i, j) = 255;
        }
      }
    }
  }
  }
  // if the mask is black->white->black
  if (mask[0] == 0 && mask[1] == 255 && mask[2] == 0) {
  for (int i = 9; i < bits.rows; i++) {
    const uchar* ptr = bits.ptr<uchar>(i);
    for (int j = 13; j < bits.cols; j++) {
      if ((i+j) % 2 == 0) {
        if (ptr[j] == 255) {
          bits.at<uchar>(i, j) = 0;
        } else if (ptr[j] == 0) {
          bits.at<uchar>(i, j) = 255;
        }
      }
    }
  }
  }
  // if the mask is black->white->white
  if (mask[0] == 0 && mask[1] == 255 && mask[2] == 255) {
  for (int i = 9; i < bits.rows; i++) {
    const uchar* ptr = bits.ptr<uchar>(i);
    for (int j = 13; j < bits.cols; j++) {
      if (i % 2 == 0) {
        if (ptr[j] == 255) {
          bits.at<uchar>(i, j) = 0;
        } else if (ptr[j] == 0) {
          bits.at<uchar>(i, j) = 255;
        }
      }
    }
  }
  }
  // if the mask is white->black->black
  if (mask[0] == 255 && mask[1] == 0 && mask[2] == 0) {
  for (int i = 9; i < bits.rows; i++) {
    const uchar* ptr = bits.ptr<uchar>(i);
    for (int j = 13; j < bits.cols; j++) {
      if (((i * j) % 3 + i * j) % 2 == 0) {
        if (ptr[j] == 255) {
          bits.at<uchar>(i, j) = 0;
        } else if (ptr[j] == 0) {
          bits.at<uchar>(i, j) = 255;
        }
      }
    }
  }
  }
  // if the mask is white->black->white
  if (mask[0] == 255 && mask[1] == 0 && mask[2] == 255) {
  for (int i = 9; i < bits.rows; i++) {
    const uchar* ptr = bits.ptr<uchar>(i);
    for (int j = 13; j < bits.cols; j++) {
      if (((i * j) % 3 + i + j) % 2 == 0) {
        if (ptr[j] == 255) {
          bits.at<uchar>(i, j) = 0;
        } else if (ptr[j] == 0) {
          bits.at<uchar>(i, j) = 255;
        }
      }
    }
  }
  }
  // if the mask is white->white->black
  if (mask[0] == 255 && mask[1] == 255 && mask[2] == 0) {
  for (int i = 9; i < bits.rows; i++) {
    const uchar* ptr = bits.ptr<uchar>(i);
    for (int j = 13; j < bits.cols; j++) {
      if ((i / 2 + j / 3) % 2 == 0) {
        if (ptr[j] == 255) {
          bits.at<uchar>(i, j) = 0;
        } else if (ptr[j] == 0) {
          bits.at<uchar>(i, j) = 255;
        }
      }
    }
  }
  }
  // if the mask is white->white->white
  if (mask[0] == 255 && mask[1] == 255 && mask[2] == 255) {
  for (int i  =9; i < bits.rows; i++) {
    const uchar* ptr = bits.ptr<uchar>(i);
    for (int j = 13; j < bits.cols; j++) {
      if (((i * j) % 2 + (i * j) % 3) == 0) {
        if (ptr[j] == 255) {
          bits.at<uchar>(i, j) = 0;
        } else if (ptr[j] == 0) {
          bits.at<uchar>(i, j) = 255;
        }
      }
    }
  }
  }
}

/**
 * @brief Finds the mask used in QRcode
 * @param none
 * @return none
 */
vector<int> decodeQRcode::getMask() {
  // find the mask used by accessing (8,2),(8,3) & (8,4)
  vector<int> mask;
  mask.push_back(bits.at<uchar>(8, 2));
  mask.push_back(bits.at<uchar>(8, 3));
  mask.push_back(bits.at<uchar>(8, 4));
  return mask;
}

/**
 * @brief Collects the data stored in the form of vector
 * @param none
 * @return none
 */
void decodeQRcode::getData() {
  // clear the data stored each time a new id is detected
  data.clear();
  // demask the extracted bits of 21x21 QRcode
  demask();
  int count = 0;
  // traverse the bits of QRcode to extract data stored
  for (int i = bits.cols - 1; i >= 14; i -= 2) {
  // traverse bottom to top during odd iterations
  if (count % 2 == 0) {
    cout << count << endl;
    for (int j = bits.rows - 1; j >= 0; j--) {
      // avoid finder and timing patterns
      if (j > 8) {
        if (bits.at<uchar>(j, i) == 255 && bits.at<uchar>(j, i - 1) == 255) {
          data.push_back(1);
          data.push_back(1);
        }
        if (bits.at<uchar>(j, i) == 255 && bits.at<uchar>(j, i - 1) == 0) {
          data.push_back(1);
          data.push_back(0);
        }
        if (bits.at<uchar>(j, i) == 0 && bits.at<uchar>(j, i - 1) == 255) {
         data.push_back(0);
         data.push_back(1);
        }
        if (bits.at<uchar>(j, i) == 0 && bits.at<uchar>(j, i - 1) == 0) {
          data.push_back(0);
          data.push_back(0);
        }
      }
    }
  }
  // traverse top to bottom during odd iterations
  if (count % 2 != 0) {
    cout << count << endl;
    for (int j = 0; j < bits.rows; j++) {
      // avoid finder and timing patterns
      if (j > 8) {
        if (bits.at<uchar>(j, i) == 255 && bits.at<uchar>(j, i - 1) == 255) {
          data.push_back(1);
          data.push_back(1);
        }
        if (bits.at<uchar>(j, i) == 255 && bits.at<uchar>(j, i - 1) == 0) {
          data.push_back(1);
          data.push_back(0);
        }
        if (bits.at<uchar>(j, i) == 0 && bits.at<uchar>(j, i - 1) == 255) {
         data.push_back(0);
         data.push_back(1);
        }
        if (bits.at<uchar>(j, i) == 0 && bits.at<uchar>(j, i - 1) == 0) {
          data.push_back(0);
          data.push_back(0);
        }
      }
    }
  }
  count++;
  }
}

/**
 * @brief Finds the product ID stored in the QRcode
 * @param none
 * @return none
 */  
  int decodeQRcode::getID() {
  int length_bits, ID, k;
  ID = 0;
  k = 0;
  // find the encoding scheme used
  length_bits = getEncoding();
  // find the length of the data
  getLength(length_bits);
  // find the 3 numeric digits stored for every 10 bits
  if (length % 3 == 0) {
    for (int j = 0; j < length / 3; j++) {
     k = 9;
     for (int i = length_bits + 4 + (10 * j);
          i < length_bits + 4 + (10 * (j + 1)); i++) {
      if (data[i] == 0) {
       ID += pow(2, k);
      }
     k--;
     }
    }
  } else if (length % 3 == 1) {
  int j;
  for (j = 0; j < length / 3; j++) {
     ID *= pow(1000, j);
     k = 9;
     for ( int i = length_bits + 4 + (10 * j);
                  i < length_bits + 4 + (10 * (j + 1)); i++) {
      if (data[i] == 0) {
       ID += pow(2, k);
      }
     k--;
     }
    }
    k = 3;
    ID *= 10;
    for (int i = length_bits + 4 + (10 * j);
          i < length_bits + 8 + (10 * j); i++) {
      if (data[i] == 0) {
       ID += pow(2, k);
      }
    k--;
    }
  } else if (length % 3 == 2) {
  int j;
  for (j = 0; j < length / 3; j++) {
     ID *= pow(1000, j);
     k = 9;
     for (int i = length_bits + 4 + (10 * j);
           i < length_bits + 4 + (10 * (j + 1)); i++) {
      if (data[i] == 0) {
       ID += pow(2, k);
      }
     k--;
     }
    }
    k = 6;
    ID *= 100;
    for (int i = length_bits + 4 + (10 * j);
            i < length_bits + 11 + (10 * j); i++) {
      if (data[i] == 0) {
        ID += pow(2, k);
      }
    k--;
    }
  }
  // store the product ID
  return ID;
}

/**
 * @brief Gets the encoding scheme used in the QRcode
 * @param none
 * @return none
 */
int decodeQRcode::getEncoding() {
  int no_bits = 0;
  // if encoding scheme is binary
  if (data[1] == 0) {
  no_bits = 8;
  } else if (data[2] == 0) {  // if encoding scheme is alphanumeric
  no_bits = 9;
  } else if (data[3] == 0) {  // if encoding scheme is numeric
  no_bits = 10;
  }
  return no_bits;
}

/**
 * @brief Gets the length of data encoded in the QRcode
 * @param length_bits that contains the number of bits 
 * to look for the length of the data stored
 * @return none
 */
void decodeQRcode::getLength(int length_bits) {
  int k = length_bits - 1;
  length = 0;
  for (int i = 4; i < 4 + length_bits; i++) {
  if (data[i] == 0) {
  length += pow(2, k);
  }
  k--;
  }
}

















