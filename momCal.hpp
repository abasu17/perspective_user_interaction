/*
 * momCal.hpp
 * 
 * Copyright 2015 Aniket Basu;
 * 
 * This is a .hpp file; which contains a function
 * with the name of momCal(); This function can be used
 * to detect momentum.
 * 
 * this momCal() function contains some pre-defined OpenCV (Open 
 * Source Computer Vision) functions; it is an user defined function.
 * 
 */


#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <math.h>
#include "sendKey.hpp"

using namespace std;
using namespace cv;

	int iLastX = 0; 
	int iLastY = 0;
	Mat output;
	Rect rect;
	
Mat momCal(Mat tempMat, Mat dst, int FingTips){
		
		Moments oMoments = moments(tempMat);

		double dM01 = oMoments.m01;
		double dM10 = oMoments.m10;
		double dArea = oMoments.m00;
		
			if (dArea > 10000){
				//current position
				int posX = dM10 / dArea;
				int posY = dM01 / dArea;        
        
				if((iLastX == 0)&&(iLastY == 0)&&(FingTips == 4)){
						iLastX = posX;
						iLastY = posY;
						if ((iLastX > 105)&&(iLastY > 105)){
							rect = Rect(iLastX-110, iLastY-110, 220, 220);
							printf("iLastX:%d, IlastY:%d\n",iLastX,iLastY);
							}
						else if (iLastX < 105){
							rect = Rect(0, iLastY-110, 220, 220);
							printf("iLastX:%d, IlastY:%d\n",iLastX,iLastY);
							}
						else if (iLastY < 105){
							rect = Rect(iLastX-110, 0, 220, 220);
							printf("iLastX:%d, IlastY:%d\n",iLastX,iLastY);
							}
						else if ((iLastX < 105)&&(iLastY < 105)){
							rect = Rect(0, 0, 220, 220);
							printf("iLastX:%d, IlastY:%d\n",iLastX,iLastY);
							}
						}
						
				rectangle( dst, Point( iLastX-102, iLastY-102 ), Point( iLastX+102, iLastY+102 ), Scalar( 0, 255, 255 ), 2, 8);				
				dst(rect).copyTo(output);
				
				if (iLastX > 0 && iLastY > 0 && posX > 0 && posY > 0){
		
					circle( dst, Point(posX, posY), 2, Scalar(0,255,0), 5, CV_AA );
					
					int diff = posX - iLastX;
					int diff_UD = posY - iLastY;
						printf("Diff:%d\n",diff);
						printf("Diff_UD:%d\n",diff_UD);
					if (((diff > 100)||(diff < -100))&&((diff_UD > -100)&&(diff_UD < 100))){	
						//Next Image
						if ((FingTips == 1)&&(diff > 100)){
							evntNext();
							}
						//Previous Image
						else if ((FingTips == 1)&&(diff < -100)){
							evntPrev();
							}
						}
					/*if (((diff_UD > -100)&&(diff_UD < 100))&&((diff < 100)&&(diff > -100))){
						//ZoomIN Image
						if (FingTips == 2){
							evntZoomIN();
							}
						//ZoomOUT Image
						else if (FingTips == 3){
							evntZoomOUT();
							}
						}
					if (((diff_UD < -100)||(diff_UD > 100))&&((diff < 100)&&(diff > -100))){
						//Zoom Image UP
						if ((FingTips == 1)&&(diff_UD < -100)){
							evntZoomINMoveU();
							}
						//Zoom Image DOWN
						else if ((FingTips == 1)&&(diff_UD > 100)){
							evntZoomINMoveD();
							}
						}*/
					//~ if (FingTips == 2){	
						//~ //Move Up
						//~ if (diff_UD < -100){
							//~ evntZoomINMoveU();
							//~ }
						//~ //Move Down
						//~ if (diff_UD > 100){
							//~ evntZoomINMoveD();
							//~ }
						//~ //Move Right
						//~ if (diff > 100){
							//~ evntZoomINMoveR();
							//~ }
						//~ //Move Left
						//~ if (diff < -100){
							//~ evntZoomINMoveR();
							//~ }
						//~ }
					}
				}
	
	if (output.data)
		return output;
	else
		return dst;
}
