/********************************************************************************************************************************************************************
* Author:		Brett Sprague
* Filename:		ImageMorpher.cpp
* Date Created: 1/2/2019
*********************************************************************************************************************************************************************/
#include "ImageMorpher.h"

/********************************************************************************************************************************************************************
* Purpose: Gives the ImageMorpher an image and a structuring element to work with
*
* Precondition:
*
*
* Postcondition:
*	If the source image cannot be found an exception is thrown
*	Otherwise, the source image and structuring element are stored and a greyscale version of the image is created and stored
*********************************************************************************************************************************************************************/
ImageMorpher::ImageMorpher(string sourceImageName, Mat structEle) : m_structEle(structEle)
{
	//Set the image file to a Mat for processing
	m_source = imread(sourceImageName);

	//Check if the image name was invalid
	if (m_source.empty())
		throw "Cannot find source image";

	//Convert the image from coloured to greyscale and store it in m_greySource
	cvtColor(m_source, m_greySource, cv::COLOR_BGR2GRAY);
}

/********************************************************************************************************************************************************************
* Purpose: Display the source image
*
* Precondition:
*	
*
* Postcondition:
*	Opens a window showing a picture of the source image
*********************************************************************************************************************************************************************/
void ImageMorpher::ShowOriginal()
{
	//Create a window with the name Original Image
	namedWindow("Original Image", WINDOW_AUTOSIZE);
	//Show the image m_source on the window named Original Image
	imshow("Original Image", m_source);
}

/********************************************************************************************************************************************************************
* Purpose: Display an eroded image of the source
*
* Precondition:
*	
*
* Postcondition:
*	Opens a window showing the source image after erosion
*********************************************************************************************************************************************************************/
void ImageMorpher::ShowEroded()
{
	Mat eroded;

	//Erode the source image with m_structEle as the structuring element and store it in "eroded"
	erode(m_source, eroded, m_structEle);

	namedWindow("Eroded Image", WINDOW_AUTOSIZE);
	imshow("Eroded Image", eroded);
}

/********************************************************************************************************************************************************************
* Purpose: Display a dilated image of the source
*
* Precondition:
*
*
* Postcondition:
*	Opens a window showing the source image after dilation
*********************************************************************************************************************************************************************/
void ImageMorpher::ShowDilated()
{
	Mat dilated;

	//Dilate the source image with m_structEle as the structuring element and store it in "dilated"
	dilate(m_source, dilated, m_structEle);

	namedWindow("Dilated Image", WINDOW_AUTOSIZE);
	imshow("Dilated Image", dilated);
}

/********************************************************************************************************************************************************************
* Purpose: Display an opened image of the source
*
* Precondition:
*
*
* Postcondition:
*	Opens a window showing the source image after opening
*********************************************************************************************************************************************************************/
void ImageMorpher::ShowOpened()
{
	Mat opened;

	//Open the source image with m_structEle as the structuring element and store it in "opened"
	Open(opened, m_structEle);

	namedWindow("Opened Image", WINDOW_AUTOSIZE);
	imshow("Opened Image", opened);
}

/********************************************************************************************************************************************************************
* Purpose: Display a closed image of the source
*
* Precondition:
*
*
* Postcondition:
*	Opens a window showing the source image after closing
*********************************************************************************************************************************************************************/
void ImageMorpher::ShowClosed()
{
	Mat closed;

	//Close the source image with m_structEle as the structuring element and store it in "closed"
	Close(closed, m_structEle);

	namedWindow("Closed Image", WINDOW_AUTOSIZE);
	imshow("Closed Image", closed);
}

/********************************************************************************************************************************************************************
* Purpose: Display a greyscale version of the source
*
* Precondition:
*
*
* Postcondition:
*	Opens a window showing the greyscale source
*********************************************************************************************************************************************************************/
void ImageMorpher::ShowGrey()
{
	imshow("Greyscale Image", m_greySource);
}

/********************************************************************************************************************************************************************
* Purpose: Display a greyscale of the source after binary thresholding
*
* Precondition:
*	
*
* Postcondition:
*	Opens a window showing the greyscale source image after binary thresholding
*********************************************************************************************************************************************************************/
void ImageMorpher::ShowBinaryThresh()
{
	Mat binaryThreshed;

	//Store the image after thresholding into binaryThreshed. Give the threshold value, the max threshold value and the type of thresholding to be done
	threshold(m_greySource, binaryThreshed, m_MAX_THRESH_VAL / 2, m_MAX_THRESH_VAL, CV_THRESH_BINARY);

	namedWindow("Binary Threshold");
	imshow("Binary Threshold", binaryThreshed);
}

/********************************************************************************************************************************************************************
* Purpose: Display a greyscale of the source after inverse binary thresholding
*
* Precondition:
*
*
* Postcondition:
*	Opens a window showing the greyscale source image after inverse binary thresholding
*********************************************************************************************************************************************************************/
void ImageMorpher::ShowInverseBinaryThresh()
{
	Mat inverseBinaryThreshed;

	//Store the image after thresholding into binaryThreshed. Give the threshold value, the max threshold value and the type of thresholding to be done
	threshold(m_greySource, inverseBinaryThreshed, m_MAX_THRESH_VAL / 2, m_MAX_THRESH_VAL, CV_THRESH_BINARY_INV);

	namedWindow("Inverse Binary Threshold");
	imshow("Inverse Binary Threshold", inverseBinaryThreshed);
}

/********************************************************************************************************************************************************************
* Purpose: Display a greyscale of the source after average thresholding
*
* Precondition:
*
*
* Postcondition:
*	Opens a window showing the greyscale source image after average thresholding
*********************************************************************************************************************************************************************/
void ImageMorpher::ShowAverageThreshold()
{
	Mat avgThreshed;
	double threshVal;

	double intensity, totalIntensity = 0;

	//Traverse each pixel in the image and add its intensity to totalIntensity
	for (int x = 0; x < m_source.cols; ++x)
	{
		for (int y = 0; y < m_source.rows; ++y)
		{
			intensity = m_greySource.at<uchar>(y, x);
			totalIntensity += intensity;
		}
	}

	//Divide the total intensity by the total number of pixels to get the new threshold value
	threshVal = totalIntensity / m_source.total();

	//Find the average threshold with the calculated value
	threshold(m_greySource, avgThreshed, threshVal, m_MAX_THRESH_VAL, CV_THRESH_BINARY);

	namedWindow("Average Threshold");
	imshow("Average Threshold", avgThreshed);
}

/********************************************************************************************************************************************************************
* Purpose: Display a greyscale of the source after mean thresholding
*
* Precondition:
*
*
* Postcondition:
*	Opens a window showing the greyscale source image after mean thresholding
*********************************************************************************************************************************************************************/
void ImageMorpher::ShowMeanThreshold()
{
	Mat meanThreshed;
	double threshVal;

	double foregroundIntensity = 0, backgroundIntensity = 0, intensity, averageForeground, averageBackground;
	int foregroundPixels = 0, backgroundPixels = 0;

	//Traverse each pixel and consider it foreground if it is above the simple threshold and background if it is equal to or below the simple threshold
	for (int x = 0; x < m_source.cols; ++x)
	{
		for (int y = 0; y < m_source.rows; ++y)
		{
			intensity = m_greySource.at<uchar>(y, x);
			if (intensity > (m_MAX_THRESH_VAL / 2))
			{
				foregroundIntensity += intensity;
				++foregroundPixels;
			}
			else
			{
				backgroundIntensity += intensity;
				++backgroundPixels;
			}
		}
	}
	
	//Find the average intensity of foreground pixels
	averageForeground = foregroundIntensity / foregroundPixels;
	//Find the average intensity of background pixels
	averageBackground = backgroundIntensity / backgroundPixels;

	//Find the average intensity of the sum of the average foreground intensity and the average background intensity
	threshVal = (averageForeground + averageBackground) / 2;

	//Find the mean threshold with the calculated value
	threshold(m_greySource, meanThreshed, threshVal, m_MAX_THRESH_VAL, CV_THRESH_BINARY);
	
	namedWindow("Mean Threshold");
	imshow("Mean Threshold", meanThreshed);
}

/********************************************************************************************************************************************************************
* Purpose: Performs the morphological opening process and stores it in the passed through Mat
*
* Precondition:
*
*
* Postcondition:
*	Performs erosion then dilation on the Mat and stores it in the one passed through
*********************************************************************************************************************************************************************/
void ImageMorpher::Open(Mat& opened, Mat structEle)
{
	//Erode from source and store in opened
	erode(m_source, opened, structEle);
	//Dilate from opened and store back to opened
	dilate(opened, opened, structEle);
}

/********************************************************************************************************************************************************************
* Purpose: Performs the morphological closing process and stores it in the passed through Mat
*
* Precondition:
*
* Postcondition:
*	Performs dilation then erosion on the Mat and stores it in the one passed through
*********************************************************************************************************************************************************************/
void ImageMorpher::Close(Mat& closed, Mat structEle)
{
	//Dilate from source and store it in closed
	dilate(m_source, closed, structEle);
	//Erode from closed and store back to closed
	erode(closed, closed, structEle);
}
