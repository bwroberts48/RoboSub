/**********************************************************************************************************************************************************************************************************************
* Author:		Brett Sprague
* Filename:		ImageMorpher.h
* Date Created: 1/2/2020
*
* Class: ImageMorpher
*
* Purpose: Process and display images
*
* Manager functions:
*	ImageMorpher(string sourceImageName, Mat structEle)
*		Takes the name of the image to be used and the structuring element for processing
*
* Methods:
*	void ShowOriginal()
*		Displays the original image
*
*	void ShowEroded()
*		Displays the image after erosion by the class' structuring element
*
*	void ShowDilated()
*		Displays the image after dilation by the class' structuring element
*
*	void ShowOpened()
*		Displays the image after opening by the class' structuring element
*
*	void ShowClosed()
*		Displays the image after closing by the class' structuring element
*
*	void ShowGrey()
*		Displays a greyscale version of the original image
*
*	void ShowBinaryThresh()
*		Displays the image after binary thresholding
*
*	void ShowInverseBinaryThresh()
*		Displays the image after inverse binary thresholding
*
*	void ShowAverageThreshold()
*		Displays the image after average thresholding
*
*	void ShowMeanThreshold()
*		Displays the image after mean thresholding
*
*	void Open(Mat source, Mat& opened, Mat structEle)
*		Performs the opening process on the source image
***********************************************************************************************************************************************************************************************************************/
#pragma once
#include<opencv2/opencv.hpp>
#include<iostream>
using cv::Mat;
using cv::imread;
using cv::namedWindow;
using cv::WINDOW_AUTOSIZE;
using cv::threshold;
using std::string;

class ImageMorpher
{
public:
	ImageMorpher(string sourceImageName, Mat structEle);
	
	//Basic Processing
	void ShowOriginal();
	void ShowEroded();
	void ShowDilated();
	void ShowOpened();
	void ShowClosed();
	void ShowGrey();

	//Thresholding
	void ShowBinaryThresh();
	void ShowInverseBinaryThresh();
	void ShowAverageThreshold();
	void ShowMeanThreshold();
private:
	void Open(Mat& opened, Mat structEle);
	void Close(Mat& closed, Mat structEle);

	Mat m_source, m_greySource, m_structEle;
	const int m_MAX_THRESH_VAL = 255;
};

