//
// Created by reza on 6/27/17.
//

#ifndef HOUGHTRANSFORM_IMAGE_H
#define HOUGHTRANSFORM_IMAGE_H

#include <iostream>
#include <cv.hpp>

using namespace std;
using namespace cv;

class ImageProcess {

public:

    struct Lines
    {
        vector<double > D;
        vector<double > Theta;
    };

    struct Circles{
        vector<double > a;
        vector<double > b;
        vector<double > r;
    };

    ImageProcess();
    void showImage(Mat image, string windowName);
    Mat performEdge(Mat image, int lowThreshold);
    Mat performBlur(Mat image, int size);
    Mat performGaussianBlur(Mat image, int size, int Xsigma, int Ysigma);
    Mat initializeLineHoughArray(Mat image);
    vector<double> maxElement2D(Mat array);
    ImageProcess::Lines findLineHoughPeak(Mat H, int num_peaks, int nhood);
    Mat drawLines(Mat image, Lines lines, int num_lines);
    Mat initializeCircleHoughArray(Mat image);
    vector<double> maxElement3D(Mat array);
    Mat CircleHoughArray2D(Mat H, int zCross, int height, int width);
    ImageProcess::Circles findCircleHoughPeak(Mat H, int num_peaks, int nhood);
    Mat drawCircles(Mat image, Circles circles, int num_circles);

private:




};


#endif //HOUGHTRANSFORM_IMAGE_H
