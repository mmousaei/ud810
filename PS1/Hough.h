//
// Created by reza on 6/27/17.
//

#ifndef HOUGHTRANSFORM_HOUGH_H
#define HOUGHTRANSFORM_HOUGH_H

#include <string>
#include <cv.hpp>
#include "ImageProcess.h"

using namespace std;
using namespace cv;

class Hough {

public:


    Hough();
    Mat performLineHough(string str, bool showDetailedProcess);
    Mat performCircleHough(string str, bool showDetailedProcess);


private:

    Mat originalImage;
    Mat edgeImage;
    Mat bluredImage;
    Mat lineH;
    Mat circleH;
    Mat circleH2D;
    ImageProcess::Lines lines;
    Mat lineImage;
    ImageProcess::Circles circles;
    Mat circleImage;

};


#endif //HOUGHTRANSFORM_HOUGH_H
