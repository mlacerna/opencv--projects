#include <iostream>
#include "opencv2\highgui\highgui.hpp"
#include "linear smooth filters.h"
#include "Basic Morphology.h"

int main(int argc, char** argv)
{
	int max_ksize, element, iterations;
	cv::Mat image;
	image = cv::imread("C:/Users/mlacerna/Documents/opencv\  projects/images/MyPic.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		std::cout << "Could not open image file" << std::endl;
	}
	while (true)
	{
		cv::namedWindow("Original", CV_WINDOW_AUTOSIZE);
		cv::imshow("Original", image);
		cv::moveWindow("Original", 0, 0);
		/*std::cout << "Enter element type (0,1,2) : ";
		std::cin >> element;
		std::cout << "Enter kernel size: ";
		std::cin >> max_ksize;
		ErodeFilter(image, element, max_ksize);
		DilateFilter(image, element, max_ksize);*/
		MorphOpControl(image);

		char answer, k;
		k = cvWaitKey(0);
		std::cout << "Re-Run program (y or n) "; std::cin >> answer;
		if (answer != 'y')
		{
			cv::destroyAllWindows();
			break;
		}
	}
}