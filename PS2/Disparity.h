//
// Created by reza on 7/1/17.
//

#ifndef PS2_DISPARITY_H
#define PS2_DISPARITY_H

#include <iostream>
#include <highgui.h>

using namespace std;
using namespace cv;

class Disparity {

public:
    Disparity();
    Mat ssdDisparity(Mat image_L, Mat image_R, int windowSize);

private:
    Mat bordered_L;
    Mat bordered_R;
    Mat cropped_L;
    Mat cropped_R;
    double ssdTemp;
    double ssdMin;
    double disparityTemp;
    Mat disparity;
    Mat disparityNorm;
    double maxDisparity;
};


#endif //PS2_DISPARITY_H
