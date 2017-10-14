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
#include <detectQRcode.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
using namespace std;

#define nan std::numeric_limits<float>::quiet_NaN();

/**
 * @brief  Constructs a object
 */
detectQRcode::detectQRcode() {}

/**
 * @brief Destroys a object
 */
detectQRcode::~detectQRcode() {}

/**
 * @brief detects the presence of QRcode in the given image
 */
bool detectQRcode::find(Mat &img) {
  centers.clear();
  moduleSize.clear();
  int skipRows=3;
  vector<int> stateCount(5,0); //each state represents W->B, B->W transitions
  int currentState = 0; // 

  for( int row=0; row<img.rows; row+=skipRows)
  {
    stateCount = {0,0,0,0,0};
    currentState = 0;
    const uchar* ptr = img.ptr<uchar>(row);
    for( int col = 0; col<img.cols; col++)
    {
       if(ptr[col] < 128)
       {
         // We're at a black pixel
         if(currentState == 1 || currentState == 3 )
          {
            // We were counting white pixels
            // So change the state now

            // W->B transition
            currentState++;
          }
         stateCount[currentState]++;
       }
       else
       {
          if((currentState & 0x1)==1)
          {
             // W->W change
             stateCount[currentState]++;
          }
          else
          {
            // ...but, we were counting black pixels
            if(currentState==4)
            {
              // We found the 'white' area AFTER the finder patter
              // Do processing for it here
              if(checkRatio(stateCount))
              {
                // This is where we do some more checks
                cout << row << endl;
                isCenter(img, stateCount, row, col);
              }
              else
              {
                currentState = 3;
                stateCount[0] = stateCount[2];
                stateCount[1] = stateCount[3];
                stateCount[2] = stateCount[4];
                stateCount[3] = 1;
                stateCount[4] = 0;
                continue;
               }
               stateCount = {0,0,0,0,0};
               currentState = 0;
            }  
            else
            {
              // We still haven't go 'out' of the finder pattern yet
              // So increment the state
              // B->W transition
              currentState++;
              stateCount[currentState]++;
            }
          }
       }
    }
  }
  return true;    
}

void detectQRcode::drawBoundary(Mat &img) {
    sortCenters();
    rectangle(img, corners[0], corners[1], CV_RGB(255, 0, 0), 1, 8, 0);
    
}

void detectQRcode::sortCenters() {
  if(centers.size()==0) {
        return;
    }
    Point2f pt,pt1,pt2,temp;
    for(unsigned int j=0;j<centers.size();j++) {
        temp = centers[j];
        for(unsigned int k=j+1;k<centers.size();k++) {
            if(temp.x>centers[k].x) {
              centers[j]=centers[k];
              centers[k]=temp;
              temp=centers[j];
            } 
        }
    }
    temp = centers[0];  
    if(centers[1].y<temp.y) {
       centers[0]=centers[1];
       centers[1]=centers[2];
       centers[2]=temp;
    }  
    else {
       temp = centers[1];
       centers[1]=centers[2];
       centers[2]=temp;
    }
    for(unsigned int i=0;i<centers.size();i++) {
        pt = centers[i];
        float diff = moduleSize[i]*3.5f;
        if(i==0) 
        {
        pt1.x= pt.x - diff; 
        pt1.y= pt.y - diff;
        }
        if(i==1)
        pt2.x = pt.x + diff;
        if(i==2)
        pt2.y = pt.y + diff;
        cout << pt.x << " : " << pt.y << endl;
    }
    cout << pt1.x << " : " << pt1.y << endl;
    cout << pt2.x << " : " << pt2.y << endl;
    corners.push_back(pt1);
    corners.push_back(pt2);
}  

void detectQRcode::extractQRcode(Mat &img) {
   float diff,sum;
   for(unsigned int i=0; i<moduleSize.size(); i++) {
      sum+=moduleSize[i];
   }
   diff = sum/3;
   Point2f pt(centers[1].x,centers[2].y);
   cout << pt.x << " : " << pt.y << endl;
   centers.push_back(pt);
   
   Point2f diff_top = centers[0]-centers[1];
   Point2f diff_left = centers[0]-centers[2];

    // Calculate the distance between the top-* and *-left points
    float dist_top = sqrt(diff_top.dot(diff_top));
    float dist_left = sqrt(diff_left.dot(diff_left));

    int width = (int)round(dist_top/diff);
    int height = (int)round(dist_left/diff);
    int dimension = ((width+height)/2) + 7;
    
    switch(dimension % 4) {
        case 0:
            dimension += 1;
            break;

        case 1:
            break;

        case 2:
            dimension -= 1;
            break;

        case 3:
            dimension -= 2;
            break;
    }
    cout << dimension << endl;
    vector<Point2f> src;
    src.push_back(Point2f(70, 70));
    src.push_back(Point2f((dimension - 3.5f)*20, 70));
    src.push_back(Point2f(70, (dimension - 3.5f)*20));
    src.push_back(Point2f((dimension - 3.5f)*20, (dimension - 3.5f)*20));

    Mat transform = getPerspectiveTransform(centers, src);
    warpPerspective(img, img, transform, Size(dimension*20, dimension*20), INTER_AREA);
}
/**
 * @brief checks the ratio of W->B,B->W transition
 */ 
void detectQRcode::extractBits(Mat &marker) {
    const int width = marker.cols;
    const int height = marker.rows;
    int blackCount=0;
    int whiteCount=0;
   
    for(int y=0;y<height;y+=20) {
        for(int x=0;x<width;x+=20) {
            for(int i=0;i<20;i++) {
              const uchar* ptr = marker.ptr<uchar>(y+i);
              for (int j=0;j<20;j++) {
                 if(ptr[x+j] > 128) {
                    whiteCount++;
                 } else {
                    blackCount++;
                 }
              }
            }
            if(whiteCount > blackCount) {
                 cout << 1;
            } else {
                 cout << 0;
            }  
            blackCount=0;
            whiteCount=0; 
      }
   cout << endl;    
   }
}
      
bool detectQRcode::checkRatio(vector<int> stateCount)
 {
    int totalCount = 0;
    for(int i=0; i<5; i++)
    {
        int count = stateCount[i];
        totalCount += count;
        if(count==0)
            return false;
    }

    if(totalCount<7)
        return false;

    // Calculate the size of one module
    int moduleSize = ceil(totalCount / 7.0);
    int maxVariance = moduleSize/2;

    bool match= ((abs(moduleSize - (stateCount[0])) < maxVariance) &&
        (abs(moduleSize - (stateCount[1])) < maxVariance) &&
        (abs(3*moduleSize - (stateCount[2])) < 3*maxVariance) &&
        (abs(moduleSize - (stateCount[3])) < maxVariance) &&
        (abs(moduleSize - (stateCount[4])) < maxVariance));

    return match;
 }

bool detectQRcode::isCenter(const Mat& img, vector<int> stateCount, int row, int col) 
{
    int totalCount = 0;
    for(int i=0;i<5;i++) {
        totalCount += stateCount[i];
    } 

    // Cross check along the vertical axis
    float centerCol = calcCenter(stateCount, col);
    float centerRow = checkVertical(img, row, (int)centerCol, stateCount[2], totalCount);
    if(isnan(centerRow)) {
        return false;
    }

    // Cross check along the horizontal axis with the new center-row
    centerCol = checkHorizontal(img, centerRow, centerCol, stateCount[2], totalCount);
    if(isnan(centerCol)) {
        return false;
    }

    // Cross check along the diagonal with the new center row and col
    bool validPattern = checkDiagonal(img, centerRow, centerCol, stateCount[2], totalCount);
    if(!validPattern) {
        return false;
    }
    
    Point2f ptNew(centerCol, centerRow);
    float newModuleSize = totalCount / 7.0f;
    bool found = false;
    int idx = 0;

    // Definitely a finder pattern - but have we seen it before?
    for(Point2f pt : centers) {
        Point2f diff = pt - ptNew;
        float dist = (float)sqrt(diff.dot(diff));

        // If the distance between two centers is less than 10px, they're the same.
        if(dist < 10) {
           pt = pt + ptNew;
           pt.x /= 2.0f; pt.y /= 2.0f;
           moduleSize[idx] = (moduleSize[idx] + newModuleSize)/2.0f;
           found = true;
           break;
        }
        idx++;
    } 
    if(!found) {
        centers.push_back(ptNew);
        moduleSize.push_back(newModuleSize);
    }
    return false;
}

float detectQRcode::checkVertical(const Mat& img, int startRow, int centerCol, int centralCount, int totalCount) {
    int maxRows = img.rows;
    vector<int> checkStateCount (5,0);
    int row = startRow;
    while(row>=0 && img.at<uchar>(row, centerCol)<128) {
        checkStateCount[2]++;
        row--;
    }
    if(row<0) {
        return nan;
    }
    while(row>=0 && img.at<uchar>(row, centerCol)>=128 && checkStateCount[1]<centralCount) {
        checkStateCount[1]++;
        row--;
    }
    if(row<0 || checkStateCount[1]>=centralCount) {
        return nan;
    }

    while(row>=0 && img.at<uchar>(row, centerCol)<128 && checkStateCount[0]<centralCount) {
        checkStateCount[0]++;
        row--;
    }
    if(row<0 || checkStateCount[0]>=centralCount) {
        return nan;
    }
    // Now we traverse down the center
    row = startRow+1;
    while(row<maxRows && img.at<uchar>(row, centerCol)<128) {
        checkStateCount[2]++;
        row++;
    }
    if(row==maxRows) {
        return nan;
    }

    while(row<maxRows && img.at<uchar>(row, centerCol)>=128 && checkStateCount[3]<centralCount) {
        checkStateCount[3]++;
        row++;
    }
    if(row==maxRows || checkStateCount[3]>=totalCount) {
        return nan;
    }

    while(row<maxRows && img.at<uchar>(row, centerCol)<128 && checkStateCount[4]<centralCount) {
        checkStateCount[4]++;
        row++;
    }
    if(row==maxRows || checkStateCount[4]>=centralCount) {
        return nan;
    }
    int totalCheckcount = 0;
    for(int i=0;i<5;i++) {
        totalCheckcount += checkStateCount[i];
    }

    if(5*abs(totalCheckcount-totalCount) >= 2*totalCount) {
        return nan;
    }

    double centerRow = calcCenter(checkStateCount, row);
    if(checkRatio(checkStateCount))
    {
      return centerRow;
    }
    else
    {
      return nan;
    }
}

float detectQRcode::checkHorizontal(const Mat& img, int centerRow, int startCol, int centerCount, int totalCount) {
    int maxCols = img.cols;
    vector<int> stateCount (5,0);

    int col = startCol;
    const uchar* ptr = img.ptr<uchar>(centerRow);
    while(col>=0 && ptr[col]<128) {
        stateCount[2]++;
        col--;
    }
    if(col<0) {
        return nan;
    }

    while(col>=0 && ptr[col]>=128 && stateCount[1]<centerCount) {
        stateCount[1]++;
        col--;
    }
    if(col<0 || stateCount[1]==centerCount) {
        return nan;
    }

    while(col>=0 && ptr[col]<128 && stateCount[0]<centerCount) {
        stateCount[0]++;
        col--;
    }
    if(col<0 || stateCount[0]==centerCount) {
        return nan;
    }
    col = startCol + 1;
    while(col<maxCols && ptr[col]<128) {
        stateCount[2]++;
        col++;
    }
    if(col==maxCols) {
        return nan;
    }

    while(col<maxCols && ptr[col]>=128 && stateCount[3]<centerCount) {
        stateCount[3]++;
        col++;
    }
    if(col==maxCols || stateCount[3]==centerCount) {
        return nan;
    }

    while(col<maxCols && ptr[col]<128 && stateCount[4]<centerCount) {
        stateCount[4]++;
        col++;
    }
    if(col==maxCols || stateCount[4]==centerCount) {
        return nan;
    }
        int newTotalcount = 0;
    for(int i=0;i<5;i++) {
        newTotalcount += stateCount[i];
    }

    if(5*abs(totalCount-newTotalcount) >= totalCount) {
        return nan;
    }

    double centerCol = calcCenter(stateCount, col);
    if(checkRatio(stateCount))
    {
      return centerCol;
    }
    else
    {
      return nan;
    }
}

bool detectQRcode::checkDiagonal(const Mat &img, float centerRow, float centerCol, int maxCount, int totalCount) {
    vector<int> stateCount (5,0);

    int col=centerCol;
    int row=centerRow;
    while(col>=0 && row>=0 && img.at<uchar>(row, col)<128) {
        stateCount[2]++;
        row--;
        col--;
    }
    if(row<0 || col<0) {
        return false;
    }

    while(row>=0 && col>=0 && img.at<uchar>(row, col)>=128 && stateCount[1]<=maxCount) {
        stateCount[1]++;
        row--;
        col--;
    }
    if(row<0 || col<0 || stateCount[1]>maxCount) {
        return false;
    }

    while(row>=0 && col>=0 && img.at<uchar>(row, col)<128 && stateCount[0]<=maxCount) {
        stateCount[0]++;
        row--;
        col--;
    }
    if(stateCount[0]>maxCount) {
        return false;
    }
    int maxCols = img.cols;
    int maxRows = img.rows;
    
    col=centerCol+1;
    row=centerRow+1;
    while(row<maxRows && col<maxCols && img.at<uchar>(row, col)<128) {
        stateCount[2]++;
        row++;
        col++;
    }
    if(row>=maxRows || col>=maxCols) {
        return false;
    }

    while(row<maxRows && col<maxCols && img.at<uchar>(row, col)>=128 && stateCount[3]<maxCount) {
        stateCount[3]++;
        row++;
        col++;
    }
    if(row>=maxRows || col>=maxCols || stateCount[3]>maxCount) {
        return false;
    }

    while(row<maxRows && col<maxCols && img.at<uchar>(row, col)<128 && stateCount[4]<maxCount) {
        stateCount[4]++;
        row++;
        col++;
    }
    if(row>=maxRows || col>=maxCols || stateCount[4]>maxCount) {
        return false;
    }
    int newTotalcount = 0;
    for(int j=0;j<5;j++) {
        newTotalcount += stateCount[j];
    }

    return (abs(totalCount - newTotalcount) < 2*totalCount) && checkRatio(stateCount);
}   

float detectQRcode::calcCenter(vector<int> stateCount, int end)
{
 return (float)(end-stateCount[4]-stateCount[3])-(float)stateCount[2]/2.0f;
}
