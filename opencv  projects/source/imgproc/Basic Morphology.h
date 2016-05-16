/* morphology operators: process images based on shapes
	- apply structuring element to input image 
	- used for noise removal, isolation/ joining elements in images, etc
	common morphology operators
	- dilation: cause bright pixels to grow 
		- convoluting input image (A) with some of the kernel (B) 
		- B is the anchor point, usually the center of the kernel
		- compute the MAX pixel value when overlapped by B and replace 
		the pixel with the anchor point position

	- erotion: cause bright pixels to shrink
		- convoluting input image (A) with some of the kernel (B)
		- B is the anchor point, usually the center of the kernel
		- compute the MIN pixel value when overlapped by B and replace
		the pixel with the anchor point position

	- opening: used to remove small objects in bright on dark foregrounds
		- erosion then dialation 

	- closing: remove small holes  (dark regions)
		- dilation then erosion

	- morph gradient: used to find the outline of an object (show contours)
		- difference between dialtion and erosion

	- top hat: difference between raw image and its opening
	- bottom hat: difference between closing and its raw image
*/

#include <iostream>
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"

using namespace std;
using namespace cv;

void ErodeFilter(Mat img, int element_type, int erosion_size)
{
	Mat result;
	Point anchor = Point(-1,-1);
	int erosion_type;
	switch (element_type)
	{
		case 0: 
			erosion_type = MORPH_RECT;
			break;
		case 1:
			erosion_type = MORPH_CROSS;
			break;
		default:
			erosion_type = MORPH_ELLIPSE;
			break;
	}
	Mat element = getStructuringElement(erosion_type, 
										Size(2 * erosion_size + 1, 2 * erosion_size + 1), 
										anchor);

	erode(img, result, element);
	imshow("ErodeFilter", result);
	moveWindow("ErodeFilter", 650, 0);
}
void DilateFilter(Mat img, int element_type, int dilation_size)
{
	Mat result;
	Point anchor = Point(-1, -1);
	int dilation_type;
	switch (element_type)
	{
	case 0:
		dilation_type = MORPH_RECT;
		break;
	case 1:
		dilation_type = MORPH_CROSS;
		break;
	default:
		dilation_type = MORPH_ELLIPSE;
		break;
	}
	Mat element = getStructuringElement(dilation_type,
		Size(2 * dilation_size+1, 2 * dilation_size+1 ),
		anchor);

	dilate(img, result, element);
	imshow("DilateFilter", result);
	moveWindow("DilateFilter", 1300, 0);
}
void MorphOperations(int, void*);

Mat raw, result;
int morph_elem = 0;
int morph_size = 0;
int morph_operator = 0;
int const max_operator = 4;
int const max_elem = 2;
int const max_kernel_size = 21;
char* window_name = "Morphology Operators";

void MorphOpControl(Mat img)
{
	raw = img;
	namedWindow(window_name, CV_WINDOW_AUTOSIZE);
	//Morphology Operators trackbar
	createTrackbar("Operator:\n 0: Opening - 1: Closing \n 2: Gradient - 3: Top Hat \n 4: Black Hat",
		window_name,
		&morph_operator,
		max_operator,
		MorphOperations
		);

	//Element Type trackbar
	createTrackbar("Element:\n 0: Rect - 1: Cross - 2: Ellipse ",
		window_name,
		&morph_elem,
		max_elem,
		MorphOperations
		);

	//Kernel size trackbar
	createTrackbar("Kernel Size:\n 2n +1 ",
		window_name,
		&morph_size,
		max_kernel_size,
		MorphOperations
		);

	MorphOperations(0, 0);
	waitKey(0);
}

void MorphOperations(int, void*)
{
	int operations = morph_operator + 5;
	Mat element = getStructuringElement(
		morph_elem,
		Size(2 * morph_size + 1, 2 * morph_size + 1),
		Point(morph_size, morph_size)
	);

	morphologyEx(raw, result, operations, element);
	imshow(window_name, result);
}


