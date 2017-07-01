//
// Created by reza on 6/27/17.
//

#include "ImageProcess.h"
#include <highgui.h>

using namespace std;

using namespace cv;


ImageProcess::ImageProcess() {

}

void ImageProcess::showImage(Mat image, string windowName) {
    namedWindow(windowName, WINDOW_AUTOSIZE);
    imshow(windowName, image);
}

Mat ImageProcess::performEdge(Mat image, int lowThreshold) {
    Mat edge;
    Canny(image, edge, lowThreshold, lowThreshold*3);
    return edge;
}

Mat ImageProcess::performBlur(Mat image, int size) {
    Mat blured;
    if(!size%2)  size++; // Making sure size is odd
    blur(image, blured, Size(size, size));
    return blured;
}

Mat ImageProcess::performGaussianBlur(Mat image, int size, int Xsigma = 1, int Ysigma = 0) {
    Mat blured;
    if(!size%2)  size++; // Making sure size is odd
    GaussianBlur(image, blured, Size(size, size), Xsigma, Ysigma);
    return blured;
}

Mat ImageProcess::initializeLineHoughArray(Mat image) {
    int height = image.rows;
    int width = image.cols;
    double maxHeight = 2*sqrt(width*width + height*height) + 1;
    double maxWidth = 180;
    double d = 0;
    int d_ind = 0;
    Mat H;
    H = Mat(maxHeight, maxWidth, CV_64F, Scalar(0));
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            if(image.at<bool>(Point(i,j)))
            {
                for(int theta = 0; theta < 180; theta+=1)
                {
                    d =  i*cos(theta*CV_PI/180) + j*sin(theta*CV_PI/180);
                    d_ind = cvRound(d);
                    H.at<double>(d_ind+((maxHeight-1)/2), theta)++;
                }
            }
        }
    }

    return H;
}

vector<double> ImageProcess::maxElement2D(Mat array) {
    int height = array.rows;
    int width = array.cols;
    double max_e = 0;
    vector<double> P(3);
    P[0] = 0;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(array.at<double>(i, j) > max_e)
            {
                max_e = array.at<double>(i, j);
                P[1] = i;
                P[2] = j;
            }
        }
    }
    P[0] = max_e;
    return P;
}

ImageProcess::Lines ImageProcess::findLineHoughPeak(Mat H, int num_peaks, int nhood) {

    Lines lines;
    vector<double > P;
    int Dlow, Dhigh, Tlow, Thigh;
    bool TlowFlag = false;
    bool ThighFlag = false;
    for(int k = 0; k < num_peaks; k++) {
        P = maxElement2D(H);
        H.at<double>(P[1], P[2]) = 0;
        /// Eliminating all the neighborhood of the max element
        Dlow = MAX(0, P[1] - nhood);
        Dhigh = P[1] + nhood;
        Tlow = P[2] - nhood;
        if (Tlow < 0) {
            Tlow = 0;
            TlowFlag = true;
        }
        Thigh = P[2] + nhood;
        if (Thigh > 180) {
            Thigh = 180;
            ThighFlag = true;
        }
        for (int i = Dlow; i <= Dhigh; i++) {
            for (int j = Tlow; j <= Thigh; j++) {
                H.at<double>(i, j) = 0;
            }
        }
        if (TlowFlag) {
            TlowFlag = false;
            Thigh = 180;
            Tlow = 180 + P[2] - nhood;
            for (int i = Dlow; i <= Dhigh; i++) {
                for (int j = Tlow; j <= Thigh; j++) {
                    H.at<double>(i, j) = 0;
                }
            }
        }
        if (ThighFlag) {
            ThighFlag = false;
            Tlow = 0;
            Thigh = 180 - (P[2] + nhood);
            for (int i = Dlow; i <= Dhigh; i++) {
                for (int j = Tlow; j <= Thigh; j++) {
                    H.at<double>(i, j) = 0;
                }
            }
        }

        lines.D.push_back(P[1] - (H.rows-1)/2);
        lines.Theta.push_back(P[2]);
    }
    return lines;
}

Mat ImageProcess::drawLines(Mat image, Lines lines, int num_lines) {
    int height = image.rows;
    int width = image.cols;
    int maxHeight = 2*sqrt(width*width + height*height)+1;
    for(int i = 0; i < num_lines; i++)
    {
        if(abs(lines.Theta[i]) < 1)
        {
            line(image, Point(lines.D[i] , 0), Point(lines.D[i] , height), Scalar(0, 255, 0), 2);
        }
        else if(abs(90 - lines.Theta[i]) < 1)
        {
            line(image, Point(0, lines.D[i] ), Point(width, lines.D[i] ), Scalar(0, 255, 0), 2);
        }
        else
        {
            int Y0 = (lines.D[i])/sin(lines.Theta[i]*CV_PI/180) ;
            int Yw = ( (lines.D[i]) - width*cos(lines.Theta[i]*CV_PI/180))/sin(lines.Theta[i]*CV_PI/180);
            line(image, Point(0, Y0), Point(width, Yw), Scalar(0, 255, 0), 2);
        }
    }
    return image;
}

Mat ImageProcess::initializeCircleHoughArray(Mat image) {
    int height = image.rows;
    int width = image.cols;
    double maxHeight = 2*sqrt(width*width + height*height) + 1;
    double maxWidth = 180;
    double d = 0;
    double a, b, MaxH = 0;
    int a_int, b_int;
    int d_ind = 0;
    Mat H;
    int dim[] = {image.cols, image.rows, MAX(image.rows, image.cols)};
    H = Mat(3, dim, CV_64F, Scalar(0));
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            if(image.at<bool>(Point(i,j)))
            {
                for(int r = 10; r < MAX(image.rows, image.cols); r++)
                {
                    for(int theta = 0; theta < 360; theta++)
                    {
                        a = (double) i + r * cos((double) theta * CV_PI / 180);
                        b = (double) j + r * sin((double) theta * CV_PI / 180);
                        a_int = (int) a;
                        b_int = (int) b;
                        if( a > 0 && a < image.rows && b < image.cols && b > 0)
                        {
                            H.at<double>(a_int, b_int, r)++;
                            if(H.at<double>(a_int, b_int, r) > MaxH) MaxH = H.at<double>(a_int, b_int, r);
                        }
                    }
                }

            }
        }
    }

    return H;
}

Mat ImageProcess::CircleHoughArray2D(Mat H, int zCross, int height, int width) {
    Mat P(width, height, CV_64F, Scalar(0));
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            P.at<double>(i,j) =  H.at<double>(i,j,zCross);
        }
    }
    return P;
}

vector<double> ImageProcess::maxElement3D(Mat array) {
    int height = array.size[1];
    int width = array.size[0];
    int z = array.size[2];
    double max_e = 0;
    vector<double> P(4);
    P[0] = 0;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            for(int k = 0; k < z; k++)
            {
                if(array.at<double>(i, j, k) > max_e)
                {
                    max_e = array.at<double>(i, j, k);
                    P[1] = i;
                    P[2] = j;
                    P[3] = k;
                }
            }
        }
    }
    P[0] = max_e;
    return P;
}

ImageProcess::Circles ImageProcess::findCircleHoughPeak(Mat H, int num_peaks, int nhood) {
    Circles C;
    vector<int> Dvec;
    vector<int> Tvec;
    int Dtemp;
    int Ttemp;
    int aLow, aHigh, bLow, bHigh, rLow, rHigh;
    Dvec.push_back(Dtemp);
    vector<double> P;
    int Tlflag = 0;
    int Thflag = 0;

    for (int k = 0; k < num_peaks; k++) {
        P = maxElement3D(H);
        H.at<double>(P[1], P[2], P[3]) = 0;
        /// Eliminating all the neighborhood of the max element
        aLow = MAX(0, (int) P[1] - nhood);
        aHigh = MIN((int) P[1], H.size[0]);
        bLow = MAX(0, (int) P[2] - nhood);
        bHigh = MIN((int) P[2], H.size[1]);
        rLow = MAX(0, (int) P[3] - nhood);
        rHigh = MIN((int) P[3], H.size[2]);

        for (int i = aLow; i <= aHigh; i++) {
            for (int j = bLow; j <= bHigh; j++) {
                for (int k = rLow; k <= rHigh; k++) {
                    H.at<double>(i, j, k) = 0;
                }
            }
        }

        C.a.push_back((int) P[1]);
        C.b.push_back((int) P[2]);
        C.r.push_back((int) P[3]);
        cout << "Circle#" << k << " with Center (" << P[1] << ", " << P[2] << ") and Radius " << P[3] << endl;
    }
    return C;
}

Mat ImageProcess::drawCircles(Mat image, ImageProcess::Circles circles, int num_circles) {
    for(int i = 0; i < num_circles; i++)
    {
        circle(image, Point(circles.a[i], circles.b[i]), circles.r[i], Scalar(0,255,0), 2);
    }
    return image;
}


//    //cerr<<"KHIAR saladi!  ";
//
//
//    for(int i = 0; i < num_peaks; i++)
//    {
//        circle(image, Point(C.b[i], C.a[i]), C.r[i], Scalar(0,255,0), 2);
//    }
//
//    namedWindow("Circle");
//    imshow("Circle", image);
//    waitKey(0);

