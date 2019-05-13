/*
 * setSkin.hpp
 * 
 * Copyright 2015 Aniket Basu;
 * 
 * This is a .hpp file; which contains a function
 * with the name of setSkin(); This function can be used
 * to detect skin.
 * 
 * this setSkin() function contains some pre-defined OpenCV (Open 
 * Source Computer Vision) functions; it is an user defined function.
 * 
 */

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

Mat setSkin(Scalar mat, Mat input){
	
	float minH = mat.val[0] - 30; 
	float maxH = mat.val[0] + 30; 
	float minS = mat.val[1] - 20; 
	float maxS = mat.val[1] + 20;
	float minV = mat.val[2] - 40; 
	float maxV = mat.val[2] + 40;
	
	//~ float minH = mat.val[0] - 10; 
	//~ float maxH = mat.val[0] + 10; 
	//~ float minS = mat.val[1] - 10; 
	//~ float maxS = mat.val[1] + 10;
	//~ float minV = mat.val[2] - 10; 
	//~ float maxV = mat.val[2] + 10;
	
	cvtColor(input, input, COLOR_BGR2HSV);
	inRange(input, Scalar(minH, minS, minV),  Scalar(maxH, maxS, maxV), input);
	adaptiveThreshold(input, input, 150, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 0);
	blur(input, input, Size(5,5));
	medianBlur(input, input, 5);
	erode( input, input, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
		dilate( input, input, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
			dilate( input, input, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
			erode( input, input, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
return input;
}
