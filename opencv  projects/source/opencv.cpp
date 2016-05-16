#include <opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat img(500, 1000, CV_8UC3, Scalar(0, 0, 100));
	if (img.empty())
	{
		cout << "Error: Cannot load image";
		return -1;
	}

	cvNamedWindow("Test Window", CV_WINDOW_AUTOSIZE);
	imshow("Test Window", img);
	waitKey(0);
	return 0;
}