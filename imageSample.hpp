/*
 * imageSample.hpp
 * 
 * Copyright 2015 Aniket Basu;
 * 
 * This is a .hpp file; which contains polymorphism
 * of a function with the name of sampling(); This 
 * function are used in two way; one is to plot the
 * avarage points another is to generate the sampled
 * matrix.
 * 
 * this sampling() polymorphism functions are contains some pre-defined OpenCV (Open 
 * Source Computer Vision) functions; it is an user defined function.
 * 
 */
 
#include "opencv2/opencv.hpp"
#include "pixelAvg.hpp"

using namespace std;
using namespace cv;

void printText(Mat src, string text) {
  int fontFace = FONT_HERSHEY_PLAIN;

  putText(
      src, text,
      Point(src.cols/12 + 2, src.rows/12 + 2),
      fontFace, 1.2f, Scalar(0, 0, 0), 2);
  putText(
      src, text,
      Point(src.cols/12, src.rows/12),
      fontFace, 1.2f, Scalar(254, 254, 254), 1);
}

Scalar sampling(Mat input){
	cvtColor(input, input, COLOR_BGR2HSV);
	Scalar avgPix[10];
	Scalar addAll;
	Scalar avgAll;
	Scalar null;
    avgPix[0] = pixAvg(input, 290, 190, 300, 200);
    avgPix[1] = pixAvg(input, 330, 100, 340, 110);
    avgPix[2] = pixAvg(input, 360, 150, 370, 160);
    avgPix[3] = pixAvg(input, 400, 180, 410, 190);
    avgPix[4] = pixAvg(input, 390, 270, 400, 280);
    avgPix[5] = pixAvg(input, 270, 250, 280, 260);
	avgPix[6] = pixAvg(input, 340, 300, 350, 310);
	avgPix[7] = pixAvg(input, 400, 350, 410, 360);
	avgPix[8] = pixAvg(input, 290, 380, 300, 390);
	avgPix[9] = pixAvg(input, 370, 400, 380, 410);    
	for (int i = 0; i < 10; i++){
		addAll.val[0] = addAll.val[0] + avgPix[i].val[0];
		addAll.val[1] = addAll.val[1] + avgPix[i].val[1];
		addAll.val[2] = addAll.val[2] + avgPix[i].val[2]; 
	}
	avgAll.val[0]= addAll.val[0] / 10;
	avgAll.val[1]= addAll.val[1] / 10;
	avgAll.val[2]= addAll.val[2] / 10;
	//imshow("HSV", input);
	cvtColor(input, input, COLOR_HSV2BGR);
	cout <<ceil(avgAll.val[0]) <<"--"<<ceil(avgAll.val[1])<<"--"<< ceil(avgAll.val[2]);
	return avgAll;
}


Mat sampling(Mat input, int token){
	cvtColor(input, input, COLOR_BGR2HSV);
	medianBlur(input, input, 3);
	Scalar avgPix[10];
	Scalar addAll;
	Scalar avgAll;
	Scalar null;
	string text;
	
	text = string("Cover rectangles with palm and press Enter..");
    printText(input, text);
    
    avgPix[0] = pixAvg(input, 290, 190, 300, 200);
    avgPix[1] = pixAvg(input, 330, 100, 340, 110);
    avgPix[2] = pixAvg(input, 360, 150, 370, 160);
    avgPix[3] = pixAvg(input, 400, 180, 410, 190);
    avgPix[4] = pixAvg(input, 390, 270, 400, 280);
    avgPix[5] = pixAvg(input, 270, 250, 280, 260);
	avgPix[6] = pixAvg(input, 340, 300, 350, 310);
	avgPix[7] = pixAvg(input, 400, 350, 410, 360);
	avgPix[8] = pixAvg(input, 290, 380, 300, 390);
	avgPix[9] = pixAvg(input, 370, 400, 380, 410);	
	cvtColor(input, input, COLOR_HSV2BGR);

return input;
}

