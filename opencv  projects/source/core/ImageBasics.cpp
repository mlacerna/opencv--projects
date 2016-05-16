#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include <opencv\cv.h>
#include <iostream>
#include "mat_basics.h"
#include "DrawShapes.h"
#include "random number generator.h"
#include "dft.h"


int main(int argc, char** argv) 
{
	cv::Mat image;
	image = cv::imread("C:/Users/mlacerna/Documents/opencv\  projects/images/MyPic.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		std::cout << "Could not open image file" << std::endl;
	}
	while (true)
	{
		char answer,k;
		SharpenImage(image);

		k = cvWaitKey(0);
		std::cout << "Re-Run program (y or n) "; std::cin >> answer;
		if (answer != 'y')
		{
			cv::destroyAllWindows();
			break;
		}			
	}
}
