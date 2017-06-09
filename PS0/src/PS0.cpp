/*
 * PS0.cpp
 *
 *  Created on: Jun 8, 2017
 *      Author: Mohammadreza Mousaei
 */

#include <cv.h>
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <highgui.h>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{


	Mat girl = imread("input/girl.jpg");
	Mat tree = imread("input/tree.jpg");


	if(girl.empty() || tree.empty())
	{
		cout << "Image Cannot Load" << endl;
		return -1;
	}

	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	imshow("Original Image", girl);

	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	imshow("Original Image", tree);


	Mat channels[3];
	Mat girl_b, girl_g, girl_r, girl_swapped, tree_b, tree_g, tree_r, tree_swapped;

	//// Problem 2

	split(girl,channels);	//Split color image into B,G,R monochrome images

	girl_b = channels[0];
	girl_g = channels[1];
	girl_r = channels[2];

	channels[2] = girl_b;
	channels[0] = girl_r;

	merge(channels, 3, girl_swapped);	//Merge 3 monochrome images to RGB image

	split(tree,channels);

	tree_b = channels[0];
	tree_g = channels[1];
	tree_r = channels[2];

	channels[2] = tree_b;
	channels[0] = tree_r;

	merge(channels, 3, tree_swapped);


	// Uncomment to show output windows (and write into output folder)

/*	namedWindow("Red Channel", CV_WINDOW_AUTOSIZE);
	imwrite("ps0-2-1-c.png", girl_r);
	imshow("Red Channel", girl_r);

	namedWindow("Green Channel", CV_WINDOW_AUTOSIZE); //This one is selected as the best monochrome image
	imwrite("ps0-2-1-b.png", girl_g);
	imshow("Green Channel", girl_g);

	namedWindow("Swapped Picture", CV_WINDOW_AUTOSIZE);
	imwrite("output/ps0-2-1-a.png", girl_swapped);
	imshow("Swapped Picture", girl_swapped);

	namedWindow("Red Channel", CV_WINDOW_AUTOSIZE);
	imwrite("ps0-2-1-c.png", tree_r);
	imshow("Red Channel", tree_r);

	namedWindow("Green Channel", CV_WINDOW_AUTOSIZE); //This one is selected as the best monochrome image
	imwrite("ps0-2-1-b.png", tree_g);
	imshow("Green Channel", tree_g);

	namedWindow("Swapped Picture", CV_WINDOW_AUTOSIZE);
	imwrite("output/ps0-2-1-a.png", tree_swapped);
	imshow("Swapped Picture", tree_swapped);*/

	//// Problem 3

	int h = girl.rows;
	int w = girl.cols;
	int Px = (w - 100) / 2; // X for top-left corner of the rectangle we want to take from image
	int Py = (h - 100) / 2; // Y for ...

	Rect rect(Px, Py, 100, 100); //using the rect(Point_x, Point_y, width, height)

	Mat combined = girl_r.clone();
	Mat cropped(girl_g, rect);
	cropped.copyTo(combined(rect));


	// Uncomment to show output windows (and write into output folder)

/*	namedWindow("Combined Cropped", CV_WINDOW_AUTOSIZE);
	imwrite("output/ps0-3-a-1.png", tree_swapped);
	imshow("Combined Cropped", combined);*/

	//// Problem 4

	  double min, max;
	  minMaxLoc(girl_g, &min, &max);

	  cout << "Min: " << min << endl;
	  cout << "Max: " << max << endl;

	  Scalar mean, std;
	  meanStdDev(girl_g, mean, std);

	  cout << "Mean: " << mean[0] << endl;
	  cout << "Standard deviation: " << std[0] << endl;


	  Scalar girl_mean, girl_std;
	  meanStdDev(girl, girl_mean, girl_std);

	  Mat girl_normalized;
	  girl_normalized = (girl - girl_mean) / std[0] * 10 + girl_mean;
	  imwrite("output/ps0-4-b-1.png", girl_normalized);


	//// Problem 5

	  Mat girl_g_noised = girl.clone();
	  girl_g_noised.convertTo(girl_g_noised, CV_64F);
	  Mat noise(girl.size(), CV_64F);
	  randn(noise, 0 ,50); // Using randn(Mat, mean, std) , Play with std to see the effect of noise
	  split(girl_g_noised, channels);
	  channels[1] += noise;
	  merge(channels, 3, girl_g_noised);

	  imwrite("output/ps0-5-a-1.png", girl_g_noised);

	  Mat girl_b_noised = girl.clone();
	  girl_b_noised.convertTo(girl_b_noised, CV_64F);
	  Mat noise_b(girl.size(), CV_64F);
	  randn(noise_b, 0 ,50); // Using randn(Mat, mean, std) , As you can see, it affects the picture so little because most of the data is stored in green channel
	  split(girl_b_noised, channels);
	  channels[0] += noise_b;
	  merge(channels, 3, girl_b_noised);

	  imwrite("output/ps0-5-b-1.png", girl_b_noised);


	waitKey(0);

  return 0;
}
