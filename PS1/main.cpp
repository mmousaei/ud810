#include <iostream>
#include "Hough.h"
#include "ImageProcess.h"
#include <highgui.h>

int main() {

    Hough H;
    ImageProcess process;
    Mat line;
    Mat circle;
    Mat combine;

    line = H.performLineHough("./ps1-input2.png", false);
    circle = H.performCircleHough("./ps1-input2.png", false);

    imwrite("circle2.png", circle);
    imwrite("line2.png", line);
    imwrite("combined2.png", combine);

    combine = (line/2) + (circle/2);
    process.showImage(combine, "Lines and Circles");
    waitKey(0);
    return 0;
}