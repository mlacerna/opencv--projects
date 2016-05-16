/* smoothing (blurring) filters
	- noise reduction
	- INTPUT image ip[i,j] = f[i+k,j+l]
	- KERNEL h[i,j]
	- linear filter => op[i,j] = sum(i[i,j]h[k,l])
	- SIMPLEST: normal box filter: obtain the mean of neighbour filters
		K = Scalar::all(1) / (K.cols.size() * K.rows.size())
	- USEFULL: gaussian filter: convolute each ip pixel with kernel
		OP[x,y] = A*e^sum((-n-npeak)^2/2*nvariance^2)) => 1D: n= x, 2D: n = {x,y}, 3D: n = {x,y,z}
	- median filter: uses avg of neigbour pixels
	- bilateral filter: reduce noise 
*/

#include <iostream>
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"

using namespace std;
using namespace cv;

void NormalizeBlockFilter(Mat img, int maxKernelSize, int moveX, int moveY)
{
	Mat result;
	for (int i = 1; i < maxKernelSize; i += 2)
	{
		blur(img, result, Size(i, i), Point(-1, -1));
	}
	char* window = "Normalize Block Filter";
	namedWindow(window,CV_WINDOW_AUTOSIZE);
	imshow(window, result);
	moveWindow(window, moveX, moveY);
}
void GaussianFilter(Mat img, int maxKernelSize, int moveX, int moveY)
{
	Mat result;
	for (int i = 1; i < maxKernelSize; i += 2)
	{
		GaussianBlur(img, result, Size(i, i),0,0);
	}
	char* window = "Gaussian Blur Filter";
	namedWindow(window, CV_WINDOW_AUTOSIZE);
	imshow(window, result);
	moveWindow(window, moveX, moveY);
}
void MedianFilter(Mat img, int maxKernelSize, int moveX, int moveY)
{
	Mat result;
	for (int i = 1; i < maxKernelSize; i += 2)
	{
		medianBlur(img, result, i);
	}
	char* window = "Median Blur Filter";
	namedWindow(window, CV_WINDOW_AUTOSIZE);
	imshow(window, result);
	moveWindow(window, moveX, moveY);
}
void BilateralFilter(Mat img, int maxKernelSize, int moveX, int moveY)
{
	Mat result;
	for (int i = 1; i < maxKernelSize; i += 2)
	{
		bilateralFilter(img, result, i, i * 2, i / 2);
	}
	char* window = "Bilateral Filter";
	namedWindow(window, CV_WINDOW_AUTOSIZE);
	imshow(window, result);
	moveWindow(window, moveX, moveY);
}

void DisplaySmoothing(Mat img, int maxKernelSize)
{
	NormalizeBlockFilter(img, maxKernelSize, 640, 0);
	GaussianFilter(img, maxKernelSize, 1280, 0);
	MedianFilter(img, maxKernelSize, 0, 480);
	BilateralFilter(img, maxKernelSize, 640, 480);
}

