#include<iostream>
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include <opencv\cv.h>

void DisplayImage(cv::Mat IMAGE)
{
	cv::namedWindow("First Image", CV_WINDOW_AUTOSIZE);
	cv::imshow("First Image", IMAGE);
}
void LoadModSave(cv::Mat IMAGE)
{
	// convert to grayscale
	cv::Mat gray_image;
	cv::cvtColor(IMAGE, gray_image, CV_BGR2GRAY);
	// save image
	cv::imwrite("C:/Users/mlacerna/Documents/opencv\  projects/images/gray_image.jpg", gray_image);
	cv::namedWindow("Gray Image", CV_WINDOW_AUTOSIZE);
	cv::imshow("Gray Image", gray_image);
}
void DrawROI(cv::Mat IMAGE)
{
	int x;
	cv::Mat shapeROI(IMAGE, cv::Rect(0, 0, 10,10));
	cv::namedWindow("Rect ROI", CV_WINDOW_AUTOSIZE);
	cv::imshow("Rect ROI", shapeROI);
	cv::Mat sizeROI = IMAGE(cv::Range::all(),cv::Range(100,400));
	cv::namedWindow("Size ROI", CV_WINDOW_AUTOSIZE);
	cv::imshow("Size ROI", sizeROI);
	std::cout << "Image = \n" <<shapeROI.depth();
	std::cin >> x;
}
void sharpen(const cv::Mat myImage, cv::Mat& Result)
{
	/*contrast enhancement alg
	image[i,j] * M, where M => [[0,-1,0],[-1,5,-1],[0,-1,0]]
	kernels: multiply a n x m matrix with a n x m pixel cluster of the image
	-> does not use matrix multiplication but uses matrix convolution
	*/
	Result.create(myImage.size(), myImage.type());
	const int nChannels = myImage.channels();

	for (int j = 1; j < myImage.rows - 1; ++j)
	{
		const uchar* previous = myImage.ptr<uchar>(j - 1);
		const uchar* current = myImage.ptr<uchar>(j);
		const uchar* next = myImage.ptr<uchar>(j + 1);

		uchar* output = Result.ptr<uchar>(j);

		for (int i = nChannels; i < nChannels * (myImage.cols - 1); ++i)
		{
			*output++ = cv::saturate_cast<uchar>(5 * current[i]
				- current[i - nChannels] - current[i + nChannels] - previous[i] - next[i]);
		}
	}

	Result.row(0).setTo(cv::Scalar(0));
	Result.row(Result.rows - 1).setTo(cv::Scalar(0));
	Result.col(0).setTo(cv::Scalar(0));
	Result.col(Result.cols - 1).setTo(cv::Scalar(0));

}
void SharpenImage(cv::Mat IMAGE)
{
	cv::Mat results;
	//sharpen(IMAGE, results);
	cv::Mat kernel = (cv::Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	cv::filter2D(IMAGE, results, IMAGE.depth(), kernel);
	cv::namedWindow("Sharpen", CV_WINDOW_AUTOSIZE);
	cv::imshow("Sharpen", results);
}
void AddImage(cv::Mat src1)
{
	cv::Mat src2, Result;
	src2 = cv::imread("C:/Users/mlacerna/Documents/opencv\  projects/images/text.JPG", CV_LOAD_IMAGE_COLOR);
	/*
		dyadic operator (2 input) -> linear blend: imgAdd = (1-alpha)img1 + alpha*img2
		-> creates a watermark
	*/
	double input, beta, alpha = 0.5;
	std::cout << "Linear Blend";
	std::cout << "Enter Alpha [0 - 1]: ";
	std::cin >> input;
	if (input >= 0.0 && input <= 1.0)
		alpha = input;

	cv::namedWindow("Linear Blend", CV_WINDOW_AUTOSIZE);
	beta = 1.0 - alpha;
	cv::addWeighted(src1, alpha, src2, beta, 5.0, Result);
	cv::imshow("Linear Blend", Result);
}
/*
	img proc operator: function that has 1 or more i/p to produce an o/p
	2 types of transforms
		- point (pixel based): each o/p pixel depends on the corresponding i/p pixel
		- neighborhood (area based)
*/
void ContrastBrightness(cv::Mat IMAGE)
{
	/*
		dst = alpha*image(i,j) + beta,
		alpha: gain (alpha > 0), beta:bias, said to control contrast and brightness 
	*/
	double beta, alpha;
	cv::Mat newImage = cv::Mat::zeros(IMAGE.size(), IMAGE.type());

	std::cout << "Linear Transform\n";
	std::cout << "Enter Alpha [1.0 - 3.0]: "; std::cin >> alpha;
	std::cout << "Enter Beta [0 - 100]: "; std::cin >> beta;

	/*for (int i = 0; i < IMAGE.rows; i++)
	{
		for (int j = 0; j < IMAGE.cols; j++)
		{
			for (int c = 0; c < 3; c++)
			{
				newImage.at<cv::Vec3b>(i, j)[c] = cv::saturate_cast<uchar>(alpha*(IMAGE.at<cv::Vec3b>(i, j)[c]) + beta);
			}
		}
	}*/
	// similar as above loop
	IMAGE.convertTo(newImage, -1, alpha, beta);
	cv::namedWindow("New Image", CV_WINDOW_AUTOSIZE);
	cv::imshow("New Image", newImage);
}


