#include <iostream>
#include <fstream>
#include "lib/TCPClient/TCPClient.h"
#include <opencv2/opencv.hpp>

//#define DEBUG

using namespace std;
using namespace cv;

double xCenter = 0.0;
double yCenter = 0.0;

void computeErrors(const Mat &img, double &e_x, double &e_y);
bool sendData(TCPClient &tcp, const double &e_x, const double &e_y);

int main( )
{
    double e_x = 0.0, e_y = 0.0;
    fstream fou;
    Mat frame, temp;
    VideoCapture capture;
    TCPClient tcp;

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
    
    if (!tcp.setup("127.0.0.1", 11999))
    {
        cout << "Can setup TCP protocol" << endl;
        exit(EXIT_FAILURE);
    }

    capture.open("Video.wmv", CV_CAP_FFMPEG );
    if (!capture.isOpened())
    {
        cout << "Can not open camera/video" << endl;
        exit(EXIT_FAILURE);
    }

    capture.read(frame);

    xCenter= frame.size().width / 2;
    yCenter = frame.size().height / 2;

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
        sendData(tcp, e_x, e_y);
        
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

    double s = 0.0, max = 0.0, iMax = 0;
    findContours(img, contours, hyerarchy, CV_RETR_TREE, CHAIN_APPROX_NONE);

   for( int i = 1; i< contours.size(); i++ ) //contour 0 is the frame
   {
       s = contourArea(contours[i], false);
       if (s > max)
       {
           max = s;
           iMax = i;
       }
   }

    Moments moment = moments(contours[iMax], true);

    e_x = moment.m10/moment.m00 - xCenter;
    e_y = moment.m01/moment.m00 - yCenter;
}

bool sendData(TCPClient &tcp, const double &e_x, const double &e_y)
{
    string data = to_string(e_x);
    data += " ";
    data += to_string(e_y);

    return tcp.Send(data);
}
