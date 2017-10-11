//
// Created by reza on 7/1/17.
//

#include "ImageProcess.h"

ImageProcess::ImageProcess() {

}

void ImageProcess::showImage(Mat image, string str) {
    namedWindow(str);
    imshow(str, image);
}

Mat ImageProcess::borderFix(Mat image, int windowSize) {
    if(!(windowSize%2)) throw invalid_argument("in function ImageProcess::cropRectangle, windowSize should be odd");
    Mat border;
    int dim[] = {image.rows + (windowSize-1), image.cols + (windowSize-1)};
    border = Mat(2, dim, CV_8U, Scalar(0));
    Rect rect((windowSize-1)/2, (windowSize-1)/2, image.cols, image.rows);
    image.copyTo(border(rect));
    return border;
}

double ImageProcess::computeSSD(Mat temp_R, Mat temp_L) {
    if(temp_L.size != temp_R.size || temp_L.rows != temp_L.cols)
    {
        throw invalid_argument("in ImageProcess::computeSSD, two templates should be rectangular and with the same size!");
    }
    double SSD = 0;

    int size = temp_L.rows;
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            SSD += (temp_L.at<uchar>(j,i) - temp_R.at<uchar>(j,i))*(temp_L.at<uchar>(j,i) - temp_R.at<uchar>(j,i));
        }
    }

    return SSD;
}

Mat ImageProcess::cropRectangle(Mat image, int center_x, int center_y, int windowSize) {
    if(!(windowSize%2)) {
        throw invalid_argument("in function ImageProcess::cropRectangle, windowSize should be odd");
    }
    Rect rect(center_x - (windowSize-1)/2, center_y - (windowSize-1)/2, windowSize, windowSize);
    Mat cropped(image, rect);

    return cropped;
}

Mat ImageProcess::createStrip(Mat image, int center_y, int windowSize) {
    if(!(windowSize%2) || 1) {
        throw invalid_argument("CHECK THIS FUNCTION, POSITION IS NOT ACCURATE. in function ImageProcess::cropRectangle, windowSize should be odd");
    }
    Mat strip;
    int dim[] = {windowSize, image.cols};
    strip = Mat(2, dim, CV_8U, Scalar(0));
    for(int i = 0; i < windowSize; i++)
    {
        for(int j = 0; j < image.cols; j++)
        {
            strip.at<uchar>(i, j) = image.at<uchar>(i + center_y - (windowSize-1)/2, j);
        }
    }
    return strip;
}





