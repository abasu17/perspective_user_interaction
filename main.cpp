#include "opencv2/opencv.hpp"
#include "chd.hpp"
#include "imageSample.hpp"
#include "setSkin.hpp"
#include "momCal.hpp"
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

//Saturation 
Mat sat_con(Mat img, Mat outpt){
	cvtColor(img, img, COLOR_BGR2HSV);    

	outpt = img;
	for (int i=0; i < outpt.rows ; i++){
		for (int j=0; j < outpt.cols; j++){
			// You need to check this, but I think index 1 is for saturation, but it might be 0 or 2
		int idx = 1;
		int new_value = 0;
		outpt.at<cv::Vec3b>(i,j)[idx] = new_value;
			// or:
			//img.at<cv::Vec3b>(i,j)[idx] += new_value;
		}
	}
	// HSV back to BGR
	cvtColor(outpt, outpt, COLOR_HSV2BGR);
	medianBlur(outpt, outpt, 3);
return outpt;
}

//main function
int main()
{
	int devNo;
	cout << "Enter device number: ";
	cin >> devNo;
	VideoCapture capture;
	capture.open(devNo);
	
	Mat cameraFeed;
	int keyPress;

	while(keyPress != 'e') {
		capture.read(cameraFeed);
		//sat_con(cameraFeed, cameraFeed);
		imshow("Detect", sampling(cameraFeed, 1));
		//sampling(cameraFeed);
		 keyPress = waitKey(1);
	}
	destroyWindow("Detect");
	
	Scalar skin;
	skin = sampling(cameraFeed);
	
	Mat getSkn;
	Mat newFeed;
	Mat contourDet;
	Mat dst;
	Mat dest;
	Mat imgThresholded;
	Mat imageLines = Mat::zeros( cameraFeed.size(), CV_8UC3 );
	//Mat ImgOrgnl;
	int key;
	while(key != 'q'){
		capture.read(newFeed);
		//imshow("Image", newFeed);
		//sat_con(newFeed, newFeed);
		getSkn = setSkin(skin, newFeed);
		//imshow("Skin", getSkn);
		contourDet = detContour(getSkn);
		cvtColor(newFeed, newFeed, COLOR_HSV2BGR);
		addWeighted( newFeed, 1, contourDet, 1, 0.0, dst);
		inRange(dst, Scalar(50, 245, 245), Scalar(255, 255, 255), imgThresholded);
		//imshow("Thres", imgThresholded);
		//Calculate the moments of the thresholded image
		dest = momCal(imgThresholded, dst, endCount);
		//dst = dst + imageLines;
		//imshow("Line", imageLines);
		imshow("Movement", dest);
		key = waitKey(1);
		}
	newFeed.release();
	
	return 0;
}
