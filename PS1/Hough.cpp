//
// Created by reza on 6/27/17.
//

#include "Hough.h"
#include <iostream>
#include <string>
#include <highgui.h>
#include "ImageProcess.h"




Hough::Hough()
{}

Mat Hough::performLineHough(string str, bool showDetailedProcess) {
    originalImage = imread(str);
    ImageProcess process;

    bluredImage = process.performGaussianBlur(originalImage, 9, 2, 2);

    edgeImage = process.performEdge(bluredImage, 80);

    lineH = process.initializeLineHoughArray(edgeImage);
    vector<double> maxH;
    maxH = process.maxElement2D(lineH);

    lines = process.findLineHoughPeak(lineH, 4, 9);

    lineImage = process.drawLines(originalImage, lines, 6);

    if(showDetailedProcess)
    {
        process.showImage(originalImage, "Original");
        process.showImage(bluredImage, "Blur");
        process.showImage(edgeImage, "Edge");
        process.showImage(4*lineH/maxH[0], "HoughArray");
        process.showImage(lineImage, "Lines");
        waitKey(0);
    }

    return lineImage;
}

Mat Hough::performCircleHough(string str, bool showDetailedProcess) {
    originalImage = imread(str);
    ImageProcess process;

    bluredImage = process.performGaussianBlur(originalImage, 9, 2, 2);

    edgeImage = process.performEdge(bluredImage, 80);

    circleH = process.initializeCircleHoughArray(edgeImage);
    circleH2D = process.CircleHoughArray2D(circleH, 10, edgeImage.rows, edgeImage.cols);

    vector<double> maxH;
    maxH = process.maxElement2D(circleH2D);

    circles = process.findCircleHoughPeak(circleH, 30, 19);

    circleImage = process.drawCircles(originalImage, circles, 30);

    if(showDetailedProcess)
    {
        process.showImage(originalImage, "Original");
        process.showImage(bluredImage, "Blur");
        process.showImage(edgeImage, "Edge");
        process.showImage(2*circleH2D/maxH[0], "HoughArray");
        process.showImage(circleImage, "Circle");
        waitKey(0);
    }

    return  circleImage;
}
