#include <iostream>
#include <highgui.h>
#include "ImageProcess.h"
#include "Disparity.h"

using namespace std;
using namespace cv;

int main() {
    Mat leftImage;
    Mat rightImage;
    Mat disparityImage;
    ImageProcess process;
    Disparity disparity;

    rightImage = imread("./pair1-R.png", 0);
    leftImage = imread("./pair1-L.png", 0);

    disparityImage = disparity.ssdDisparity(leftImage, rightImage, 5);

    process.showImage(disparityImage, "Disparity");

    waitKey(0);
    return 0;
}