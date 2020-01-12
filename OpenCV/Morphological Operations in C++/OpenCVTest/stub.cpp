/********************************************************************************************************************************************************************
* Project: Morphological Operations in C++
*
* Overview:
*	This program exercises the ImageMorpher class to perform morphological operations on an image
*
* Input:
*	Type the image you want to access in main and change the structuring element if desired
*
* Output:
*	Outputs images that have the desired operations performed on them to demonstrate Opencv's ability to process in C++
*********************************************************************************************************************************************************************/
#include "ImageMorpher.h"
int main()
{
	Mat source, structEle;
	
	//Image to be used
	//Avaliable images are ball.jpg, cat.jpg, gpa.png, and gwa.jpg
	string sourceImage = "cat.jpg";

	//Creates a 4x4 square to be the structuring element
	//First arg can be RECT, CROSS or ELLIPSE for the shape of the element
	//Second arg is how to give the element size, in this case, width by heigth
	structEle = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(4, 4));

	ImageMorpher iMorph(sourceImage, structEle);

	//Show the image processed in different ways
	iMorph.ShowOriginal();
	iMorph.ShowEroded();
	iMorph.ShowDilated(); 
	iMorph.ShowOpened(); 
	iMorph.ShowClosed();
	iMorph.ShowGrey();
	iMorph.ShowBinaryThresh();
	iMorph.ShowInverseBinaryThresh();
	iMorph.ShowAverageThreshold();
	iMorph.ShowMeanThreshold();

	//Wait for a keypress to signal the close of windows
	cv::waitKey(0);
	return 0;
}