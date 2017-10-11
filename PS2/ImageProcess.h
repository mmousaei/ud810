//
// Created by reza on 7/1/17.
//

#ifndef PS2_IMAGEPROCESS_H
#define PS2_IMAGEPROCESS_H

#include <iostream>
#include <highgui.h>

using namespace std;
using namespace cv;

class ImageProcess {

public:

    ImageProcess();
    void showImage(Mat image, string str);
    Mat borderFix(Mat image, int windowSize);
    double computeSSD(Mat temp_R, Mat temp_L);
    Mat cropRectangle(Mat image, int center_x, int center_y, int windowSize);
    Mat createStrip(Mat image, int center_y, int windowSize);

};


#endif //PS2_IMAGEPROCESS_H
