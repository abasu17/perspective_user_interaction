/*
 * pixelAvg.hpp
 * 
 * Copyright 2015 Aniket Basu;
 * 
 * This is a .hpp file; which contains a function
 * with the name of pixAvg(); This function can be used
 * to calculate average colour of pixels.
 * 
 * this pixAvg() function contains some pre-defined OpenCV (Open 
 * Source Computer Vision) functions; it is an user defined function.
 * 
 */
 
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

CvScalar pixAvg (Mat img, int xS, int yS, int xE, int yE){
	Mat output;
	Scalar avgImg;
	rectangle( img, Point( xS, yS ), Point( xE, yE ), Scalar( 0, 255, 255 ), 1, 8);
	Rect rect = Rect(xS+1, yS+1, 9, 9);
	img(rect).copyTo(output);
	avgImg = mean(output);
	return avgImg;
}
