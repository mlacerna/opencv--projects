#include<iostream>
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include <opencv\cv.h>

#define w 400

/* DRAWING SHAPES
structures used for drawing
Point: define pixel location (x,y)
Scalar: 4 element vector used to pass pixel valuse
*/
using namespace cv;

void DrawLine(Mat img, Point start, Point end);
void DrawEllipse(Mat img, double angle);
void DrawFilledCircle(Mat img, Point center);
void DrawPolygon(Mat img);

void DrawAtom(Mat img, char* window);
void DrawRook(Mat img, char* window);

void draw()
{
	char atom_window[] = "Drawing 1: Atom";
	char rook_window[] = "Drawing 2: Rook";
	Mat atom_image = Mat::zeros(w, w, CV_8UC3);
	Mat rook_image = Mat::zeros(w, w, CV_8UC3);

	DrawAtom(atom_image, atom_window);
	DrawRook(rook_image, rook_window);
}

void DrawAtom(Mat img, char* window)
{
	DrawEllipse(img, 90);
	DrawEllipse(img, 0);
	DrawEllipse(img, 45);
	DrawEllipse(img, -45);
	DrawFilledCircle(img, Point(w / 2.0, w / 2.0));
	namedWindow(window, CV_WINDOW_AUTOSIZE);
	imshow(window, img);
}
void DrawRook(Mat img, char* window)
{
	DrawPolygon(img);
	rectangle(
		img,
		Point(0, 7 * w / 8.0),
		Point(w, w),
		Scalar(0, 255, 255),
		-1,
		8);
	DrawLine(img, Point(0, 15 * w / 16), Point(w, 15 * w / 16));
	DrawLine(img, Point(w/4, 7 * w / 8), Point(w/4, w));
	DrawLine(img, Point(w/2, 7 * w / 8), Point(w/2, w));
	DrawLine(img, Point(3*w/4, 7*w/8), Point(3*w/4,w));
	namedWindow(window, CV_WINDOW_AUTOSIZE);
	
	imshow(window, img);
}
void DrawLine(Mat img, Point start, Point end)
{
	int thickness = 2;
	int lineType = 8;
	// opencv function
	line
		(
			img, 
			start, 
			end, 
			Scalar(0, 0, 0), 
			thickness, 
			lineType
		);
}
void DrawEllipse(Mat img, double angle)
{
	int thickness = 2;
	int lineType = 8;
	ellipse
		(
			img, 
			Point(w / 2.0, w / 2.0), 
			Size(w / 4.0, w / 16), 
			angle, 
			0, 
			360, 
			Scalar(0, 255, 0), 
			thickness, 
			lineType
		);
}
void DrawFilledCircle(Mat img, Point center)
{
	int thickness = -1;
	int lineType = 8;
	circle
		(
			img,
			center,
			w/32.0,
			Scalar(255,0, 0),
			thickness,
			lineType
		);
}
void DrawPolygon(Mat img)
{
	int lineType = 8;
	Point rook_points[1][20];
	rook_points[0][0] = Point(w / 4.0, 7 * w / 8.0);
	rook_points[0][1] = Point(3 * w / 4.0, 7 * w / 8.0);
	rook_points[0][2] = Point(3 * w / 4.0, 13 * w / 16.0);
	rook_points[0][3] = Point(11 * w / 16.0, 13 * w / 16.0);
	rook_points[0][4] = Point(19 * w / 32.0, 3 * w / 8.0);
	rook_points[0][5] = Point(3 * w / 4.0, 3 * w / 8.0);
	rook_points[0][6] = Point(3 * w / 4.0, w / 8.0);
	rook_points[0][7] = Point(26 * w / 40.0, w / 8.0);
	rook_points[0][8] = Point(26 * w / 40.0, w / 4.0);
	rook_points[0][9] = Point(22 * w / 40.0, w / 4.0);
	rook_points[0][10] = Point(22 * w / 40.0, w / 8.0);
	rook_points[0][11] = Point(18 * w / 40.0, w / 8.0);
	rook_points[0][12] = Point(18 * w / 40.0, w / 4.0);
	rook_points[0][13] = Point(14 * w / 40.0, w / 4.0);
	rook_points[0][14] = Point(14 * w / 40.0, w / 8.0);
	rook_points[0][15] = Point(w / 4.0, w / 8.0);
	rook_points[0][16] = Point(w / 4.0, 3 * w / 8.0);
	rook_points[0][17] = Point(13 * w / 32.0, 3 * w / 8.0);
	rook_points[0][18] = Point(5 * w / 16.0, 13 * w / 16.0);
	rook_points[0][19] = Point(w / 4.0, 13 * w / 16.0);

	const Point* ppt[1] = { rook_points[0] };
	int npt[] = { 20 };
	fillPoly(
		img,
		ppt,
		npt,
		1,
		Scalar(255, 255, 255),
		lineType);

}

