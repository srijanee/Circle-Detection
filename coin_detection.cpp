

#include<iostream>
#include<opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>


#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;

int min_distance_centre= 80;
int canny_edge = 300;
int high_threshold = 150;
void createTrackbars()

{
	{
		namedWindow("trackbar", 1);
		createTrackbar("track1", "trackbar", &min_distance_centre, 200);
		createTrackbar("track2", "trackbar", &high_threshold, 300);
		//createTrackbar("track3", "trackbar", &canny_edge, 350);
	}
}
int main()
{
	Mat image, img2;

	image = imread("E:/wallpapers/default_wallpaper20(1).jpg", CV_LOAD_IMAGE_GRAYSCALE);
	img2 = image;
	//namedWindow("original", 1);
	//imshow("original", img2);
	createTrackbars();


	while (1)
	{
		vector<Vec3f> coin;
		cout << "min_distance_centre : " << min_distance_centre << endl;
		cout << "high_threshold: " << high_threshold << endl;
		HoughCircles(image, coin, CV_HOUGH_GRADIENT, 2, min_distance_centre, canny_edge, high_threshold, 0, 0);


		int l = coin.size();


		cout << "\n The number of coins is: " << l << "\n\n";


		for (size_t i = 0; i < coin.size(); i++)
		{
			Point center(cvRound(coin[i][0]), cvRound(coin[i][1]));

			int radius = cvRound(coin[i][2]);

			circle(image, center, 3, Scalar(0, 255, 0), -1, 8, 0);

			circle(image, center, radius, Scalar(0, 0, 255), 3, 8, 0);
			// circle outline
			cout << " Center location for circle " << i + 1 << " :" << center << "\n Diameter : " << 2 * radius << "\n";
		}
		cout << "\n";

		namedWindow("Coin Counter", CV_WINDOW_AUTOSIZE);


		imshow("Coin Counter", image);
		waitKey(0); // Wait for infinite time for a key press.
		image = imread("E:/wallpapers/default_wallpaper20(1).jpg", CV_LOAD_IMAGE_GRAYSCALE);
	}
	return 0;	// Return from main function.

}