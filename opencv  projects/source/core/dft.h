#include<iostream>
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include <opencv\cv.h>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

void DiscFourTrans(Mat img) 
{
	// expand image to optimal size
	Mat dest;
	int y = getOptimalDFTSize(img.rows);
	int x = getOptimalDFTSize(img.cols);
	copyMakeBorder(img, dest, 0, y - img.rows, 0, x - img.cols, BORDER_CONSTANT, Scalar::all(255));

	// create storage for both real and complex values
	Mat planes[] = { Mat_<float>(dest),Mat::zeros(dest.size(),CV_32F) };
	Mat complexI;
	merge(planes,2, complexI);

	// calculate the DFT
	dft(complexI, complexI);

	/* find the magnitude from real and complex values
	M = sqrt(Re(DFT(I))^2 + Im(DFT(I))^2)
	planes[0] = Re(DFT(I)), planes[1] = Im(DFT(I))*/
	split(complexI, planes);
	magnitude(planes[0], planes[1], planes[0]);
	Mat magI = planes[0];

	/* switch to log scale, M = log(1+M)*/
	magI += Scalar::all(1);
	log(magI, magI);

	// crop and rearrange
	magI = magI(Rect(0, 0, magI.cols&-2 , magI.rows&-2));

	int cx = magI.cols / 2;
	int cy = magI.rows / 2;

	// create ROI per quadrant
	Mat q0(magI, Rect(0, 0, cx, cy)); //topleft
	Mat q1(magI, Rect(cx, 0, cx, cy)); // topright
	Mat q2(magI, Rect(0, cy, cx, cy)); //buttomleft
	Mat q3(magI, Rect(cx, cy, cx, cy)); // buttomright

	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	//normalize
	normalize(magI, magI, 0, 1, CV_MINMAX);
	imshow("Dest", dest);
	imshow("spectrum magnitude", magI);
}


