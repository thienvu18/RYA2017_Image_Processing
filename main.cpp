#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

#define DEBUG

#define WIDTH 320
#define HEIGHT 240

using namespace std;
using namespace cv;

void computeErrors(const Mat &img, double &e_x, double &e_y);

int main( )
{
    double e_x = 0.0, e_y = 0.0;
    fstream fou;
    Mat frame, temp;
    VideoCapture capture;

#ifdef DEBUG
   namedWindow("Thresold", WINDOW_AUTOSIZE);
   namedWindow("Orginal", WINDOW_AUTOSIZE);
   namedWindow("Gray", WINDOW_AUTOSIZE);
   namedWindow("Gauss", WINDOW_AUTOSIZE);
#endif

    fou.open("out.txt", ios::out);
    if (!fou.is_open())
    {
        cout << "Can not open output file" << endl;
        exit(EXIT_FAILURE);
    }

    capture.open("Video 1.wmv");
    if (!capture.isOpened())
    {
        cout << "Can not open camera/video" << endl;
        exit(EXIT_FAILURE);
    }

    capture.read(frame);

    while (!frame.empty())
    {
#ifdef DEBUG
        imshow("Orginal", frame);
#endif

        cvtColor(frame, temp, CV_BGR2GRAY);
#ifdef DEBUG
        imshow("Gray", temp);
#endif

        GaussianBlur(temp, temp, Size(15, 15), 0, 0);
#ifdef DEBUG
        imshow("Gauss", temp);
#endif

        threshold(temp, temp, 85, 255,THRESH_BINARY);
#ifdef DEBUG
        imshow("Thresold", temp);
#endif

        computeErrors(temp, e_x, e_y);
        fou << e_x << " " << e_y << endl;
        
#ifdef DEBUG
        waitKey(1);
#endif

        capture.read(frame);
    }

    capture.release();
    fou.close();

    return 0;
}

void computeErrors(const Mat &img, double &e_x, double &e_y)
{
    vector< vector<Point> > contours;
    vector<Vec4i> hyerarchy;

    double s = 0, max = 0, iMax = 0;
    findContours(img, contours, hyerarchy, CV_RETR_TREE, CHAIN_APPROX_NONE);


   for( int i = 1; i< contours.size(); i++ )
   {
       s = contourArea(contours[i], false);
       if (s > max)
       {
           max = s;
           iMax = i;
       }
   }

    Moments moment = moments(contours[1], true);

    e_x = moment.m10/moment.m00 - WIDTH;
    e_y = moment.m01/moment.m00 - HEIGHT;
}
