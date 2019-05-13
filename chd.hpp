/*
 * chd.hpp
 * 
 * Copyright 2015 Aniket Basu;
 * 
 * This is a .hpp file; where chd is stand for 'Contour'
 * is represented by C, Convex Hull is represented by H & Convexity
 * Defects is represented by D. 
 * 
 * this functions are contains some pre-defined OpenCV (Open 
 * Source Computer Vision) functions; it is an user defined function.
 * 
 */

#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"

int endCount;

using namespace std;
using namespace cv;

int findBiggestContour(vector<vector<Point> > contours){
    int indexOfBiggestContour = -1;
    unsigned int sizeOfBiggestContour = 0;
    for (unsigned int i = 0; i < contours.size(); i++){
        if(contours[i].size() > sizeOfBiggestContour){
            sizeOfBiggestContour = contours[i].size();
            indexOfBiggestContour = i;
        }
    }
    return indexOfBiggestContour;
}

//conture detection
Mat detContour(Mat input){
	endCount = 0;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	RNG rng(12345);
	Point tmpEnd;
	
	findContours( input, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	
	// Draw contours
	Mat drawing = Mat::zeros( input.size(), CV_8UC3 );
	
	vector<vector<int> >hullsI( contours.size() );
	vector<vector<Point> >hull( contours.size() );
	vector<vector<Vec4i> >defect( contours.size() );
	unsigned int s = findBiggestContour(contours);
		convexHull( contours[s], hull[s], false, true );
		convexHull( contours[s], hullsI[s], false, false );
		approxPolyDP( hull[s], hull[s], 18, true);
		if (contours[s].size() > 3){
			convexityDefects( contours[s], hullsI[s], defect[s] );
		}
	
		Scalar color = Scalar( rng.uniform(0, 0), rng.uniform(0, 0), rng.uniform(255, 255) );
		drawContours( drawing, contours, s, color, 3, 8, hierarchy, 0, Point() );
	
	// Draw convexityDefects
			vector<Vec4i>::iterator d=defect[s].begin();
			while( d!=defect[s].end() ) {
				Vec4i& v=(*d);
				int startidx=v[0]; 
					Point ptStart( contours[s][startidx] );
				int endidx=v[1]; 
					Point ptEnd( contours[s][endidx] );
				int faridx=v[2]; 
					Point ptFar( contours[s][faridx] );
				float depth = v[3] / 256;
				if(depth > 50 && depth < 500){
					endCount++;
					stringstream ss;
					ss << endCount;
					string s1 = ss.str();
					circle( drawing, ptEnd, 2, Scalar(0,255,255), 3, CV_AA );
					circle( drawing, ptEnd, 7, Scalar(0,255,255), 2, CV_AA );
					circle( drawing, ptEnd, 12, Scalar(0,255,255), 1, CV_AA );
					putText( drawing, s1, Point(contours[s][endidx-5]), FONT_HERSHEY_PLAIN, 1.2f, Scalar(0, 255, 0), 2);
					}
						d++;
				}
return drawing;
}
