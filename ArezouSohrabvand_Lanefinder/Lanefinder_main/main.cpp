#define _CRT_SECURE_NO_WARNINGS
#include <opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int MinH = 0;
int MaxH = 179;

int MinS = 0;
int MaxS = 255;

int MinV = 0;
int MaxV = 255;

int MinC = 120;
int MaxC = 150;

const string windowName = "original";
const string windowName1 = "HSV Image";
const string windowName2 = "Treashold Image";
const string AdjusmentWindow= "Fine Tuning";
bool Road = true;

void on_trackbar(int, void*) {};

void setRoad(int MinHue = 70, int MaxHue = 179, int MinSat = 0, int MaxSat = 87, int MinValue = 0, int MaxValue = 77, int MinCanny = 50, int MaxCanny = 150)
{
	MinH = MinHue;
	MaxH = MaxHue;

	MinS = MinSat;
	MaxS = MaxSat;

	MinV = MinValue;
	MaxV = MaxValue;

	MinC = MinCanny;
	MaxC = MaxCanny;

}

void createTrackbars()
{
	if (Road == true) { setRoad(); }
	namedWindow(AdjusmentWindow, 0);
	char TrackBarName[50];
	sprintf(TrackBarName, "MinH", MinH);
	sprintf(TrackBarName, "MaxH", MaxH);
	sprintf(TrackBarName, "MinS", MinS);
	sprintf(TrackBarName, "MaxS", MaxS);
	sprintf(TrackBarName, "MinV", MinV);
	sprintf(TrackBarName, "MaxV", MaxV);
	sprintf(TrackBarName, "MinCanny", MinC);
	sprintf(TrackBarName, "MaxCanny", MaxC);


	createTrackbar("MinH",AdjusmentWindow, &MinH, MinH,on_trackbar);
	createTrackbar("MaxH", AdjusmentWindow ,&MaxH, MaxH, on_trackbar);
	createTrackbar("MinS", AdjusmentWindow, &MinS, MinS, on_trackbar);
	createTrackbar("MaxS", AdjusmentWindow, &MaxS, MaxS, on_trackbar);
	createTrackbar("MinV", AdjusmentWindow, &MinV, MinV, on_trackbar);
	createTrackbar("MaxV", AdjusmentWindow, &MaxV, MaxV, on_trackbar);
	createTrackbar("MinC", AdjusmentWindow, &MinC, MinC, on_trackbar);
	createTrackbar("MaxC", AdjusmentWindow, &MaxC, MaxC, on_trackbar);
}

int main()
{
	VideoCapture capture("roadLane.mp4");
	if (!capture.isOpened())
	{
		cout << "error";
		return -1;
	}

	createTrackbars();
	Mat threshold, capt_Image, HSV_Img, dst;
	while (1)
	{
		capture >> capt_Image;
		resize(capt_Image, capt_Image, Size(500, 640));
		Rect const box(100, 295, 320, 185);
		Mat ROI = capt_Image(box);

		GaussianBlur(ROI, dst, Size(3, 3),1.5,1.5);
		Mat k = getStructuringElement(MORPH_RECT,Size(3,3));
		morphologyEx(ROI, ROI, MORPH_CLOSE, k);
		Canny(ROI, dst, MinC, MaxC, 3);
		cvtColor(ROI, HSV_Img, COLOR_RGB2HSV);
		inRange(ROI, Scalar(70, 179, 0), Scalar(87, 0, 77), threshold);
		vector<Vec4i>lines;
		double rho=1;
		double theta = CV_PI / 180;
		int threshold = 50;
		double minLineLength = 10;
		double maxLineGap = 300;
		HoughLinesP(dst, lines, rho, theta, threshold, minLineLength, maxLineGap);
		int linetickness = 10;
		int lineType = LINE_4;
		for (size_t i = 0; i < lines.size(); i++)
		{
			Vec4i l = lines[i];
			Scalar greenColor = Scalar(0, 250, 0);
			line(ROI, Point(l[0], l[1]), Point(l[2], l[3]), greenColor, linetickness, lineType);
		}
		imshow(windowName, capt_Image);
		//imshow(windowName1, HSV_Img);
		//imshow(windowName2, ROI);
		if (waitKey(20) == 27)
		{
			cout << "esc";
			break;
		}


	}
	{

	}
}