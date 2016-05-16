#include <opencv2\highgui\highgui.hpp>
#include <opencv\cv.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char** argv)
{
	IplImage *img = cvLoadImage("C:/Users/mlacerna/Documents/opencv\  projects/images/MyPic.jpg", CV_LOAD_IMAGE_UNCHANGED); //read the image data in the file "MyPic.JPG" and store it in 'img'
	
	cvNamedWindow("MyWindow", CV_WINDOW_AUTOSIZE); //create a window with the name "MyWindow"
	cvShowImage("MyWindow", img); //display the image which is stored in the 'img' in the "MyWindow" window
	
	//erode & diplay image
	cvErode(img, img, 0, 2);
	cvNamedWindow("Eroded");
	cvShowImage("Eroded", img);

	waitKey(0); //wait infinite time for a keypress
	cvDestroyAllWindows();

	return 0;
}
