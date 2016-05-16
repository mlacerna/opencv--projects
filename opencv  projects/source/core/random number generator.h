#include<iostream>
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include <opencv\cv.h>

using namespace cv;
using namespace std;

void Random_Lines(Mat img, char* window, RNG rng, int number);
void Random_Rectangles(Mat img, char* window, RNG rng, int number);
void Random_Ellipses(Mat img, char* window, RNG rng, int number);
void Random_Circles(Mat img, char* window, RNG rng, int number);
void Random_Polylines(Mat img, char* window, RNG rng, int number);
void Random_Filled_Polygons(Mat img, char* window, RNG rng, int number);
static Scalar randomColor(RNG& rng);

void RandNumGen()
{
	cv::RNG rng(0xFFFFFFFF);
	Mat image = Mat::zeros(400, 400, CV_8UC3);
	namedWindow("RNG", CV_WINDOW_AUTOSIZE);
	Random_Circles(image, "RNG", rng, 500);
	putText(image, "TEXT TESTING", Point(100, 200), FONT_HERSHEY_COMPLEX,1,Scalar(0,0,0),5,8,false);
	imshow("RNG", image);
}
void Random_Lines(Mat img, char* window, RNG rng,int number)
{
	int lineType = 8;
	Point pt1, pt2;
	for (int i = 0; i < number; i++)
	{
		pt1.x = rng.uniform(1, 400);
		pt1.y = rng.uniform(1, 400);
		pt2.x = rng.uniform(1, 400);
		pt2.y = rng.uniform(1, 400);

		line(
			img,
			pt1,
			pt2,
			randomColor(rng),
			rng.uniform(1, 10),
			lineType,
			0
			);
	}
}
void Random_Rectangles(Mat img, char* window, RNG rng, int number)
{
	int lineType = 8;
	Point pt1, pt2;
	for (int i = 0; i < number; i++)
	{
		pt1.x = rng.uniform(1, 400);
		pt1.y = rng.uniform(1, 400);
		pt2.x = rng.uniform(1, 400);
		pt2.y = rng.uniform(1, 400);

		rectangle(
			img,
			pt1,
			pt2,
			randomColor(rng),
			rng.uniform(1, 10),
			lineType,
			0
			);
	}
}
void Random_Ellipses(Mat img, char* window, RNG rng, int number) 
{
	int lineType = 8;
	double angle = 0.0;
	Point pt1, pt2;
	for (int i = 0; i < number; i++)
	{
		pt1.x = rng.uniform(1, 400);
		pt1.y = rng.uniform(1, 400);
		pt2.x = rng.uniform(1, 400);
		pt2.y = rng.uniform(1, 400);
		angle = std::rand()% 361;
		ellipse(
			img,
			pt1,
			Size(pt2.x,pt2.y),
			angle,
			0,
			360,
			randomColor(rng),
			rng.uniform(1, 10),
			lineType,
			0
			);
	}
}
void Random_Circles(Mat img, char* window, RNG rng, int number) 
{
	int lineType = 8;
	int rad;
	Point pt1, pt2;
	for (int i = 0; i < number; i++)
	{
		pt1.x = rng.uniform(1, 400);
		pt1.y = rng.uniform(1, 400);
		pt2.x = rng.uniform(1, 400);
		pt2.y = rng.uniform(1, 400);
		rad = std::rand() % 100;
		circle(
			img,
			pt1,
			rad,
			randomColor(rng),
			rng.uniform(-1,10),
			lineType,
			0
			);
	}
}

static Scalar randomColor(RNG& rng)
{
	int icolor = (unsigned)rng;
	return Scalar(icolor & 255, (icolor >> 8) & 255, (icolor >> 16) & 255);
}
