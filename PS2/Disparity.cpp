//
// Created by reza on 7/1/17.
//

#include "Disparity.h"
#include "ImageProcess.h"


Disparity::Disparity() {

}

Mat Disparity::ssdDisparity(Mat image_L, Mat image_R, int windowSize) {
    if(image_L.rows != image_R.rows || image_L.cols != image_R.cols || !(windowSize%2))
    {
        throw invalid_argument("in Disparity::ssdDisparity, two images should be with the same size and windowSize should be odd!");
    }
    ImageProcess process;
    bordered_L = process.borderFix(image_L, windowSize);
    bordered_R = process.borderFix(image_R, windowSize);
    process.showImage(bordered_R, "bordered_R");
    process.showImage(bordered_L, "bordered_L");

    ssdMin = INT_MAX;
    disparity = image_L.clone();
    int cnt = 0;
    for (int i = (windowSize-1)/2; i < image_L.cols + (windowSize-1)/2; i++)
    {
        for(int j = (windowSize-1)/2; j < image_L.rows + (windowSize-1)/2; j++)
        {
            ssdMin = INT_MAX;
            cropped_L = process.cropRectangle(bordered_L, i, j, windowSize);
            for (int k = (windowSize-1)/2; k < image_L.cols + (windowSize-1)/2; k++)
            {
                cropped_R = process.cropRectangle(bordered_R, k, j, windowSize);
                ssdTemp = process.computeSSD(cropped_R, cropped_L);
                //cerr << ssdTemp << endl;
                if(ssdTemp < ssdMin)
                {
                    ssdMin = ssdTemp;
                    disparityTemp = k - i;

                    if (disparityTemp < 0)
                    {
                        cnt++;
                    }
                }
                //cout << disparityTemp;
                disparity.at<uchar>(j - (windowSize-1)/2, i - (windowSize-1)/2) = (uchar) disparityTemp;
            }

        }
    }




    //cout << cnt;




    return disparity;
}

