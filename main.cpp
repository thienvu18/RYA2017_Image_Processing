#include <iostream>
#include "lib/TCPClient/TCPClient.h"
#include "lib/mavlink/v2.0/common/mavlink.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const int FRAME_WIDTH = 213;
const int FRAME_HEIGHT = 160;
const float INV_SCALE_FACTOR = 640/FRAME_WIDTH;

const int MIN_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/25;

bool sendData(TCPClient &tcp, const uint16_t &x, const uint16_t &y);

int main(int argc, char** argv)
{
    TCPClient tcp;

    Mat frame, temp;
    VideoCapture capture;

    vector< vector<Point> > contours;
    vector<Vec4i> hyerarchy;

    double s = 0.0, max = 0.0;
    uint32_t iMax = 0;

    if (argc < 3)
    {
        exit(EXIT_FAILURE);
    }
    const int16_t THRESHOLD_MIN = atoi(argv[1]);
    const int16_t THRESHOLD_MAX = atoi(argv[2]);

    while (!tcp.setup("127.0.0.1", 11999))
    {
        cout << "Can not setup TCP protocol, retrying..." << endl;
    }

    capture.open(0);
    while (!capture.isOpened())
    {
        cout << "Can not open camera/video, retrying..." << endl;
    }
    capture.set(CV_CAP_PROP_FPS, 30);
    capture.set(CV_CAP_PROP_FRAME_WIDTH,FRAME_WIDTH);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,FRAME_HEIGHT);

    int num_frames;
    time_t start,end;
    time(&start);

    capture.read(frame);

    while (!frame.empty())
    {
        cvtColor(frame, temp, CV_BGR2GRAY);
        GaussianBlur(temp, temp, Size(15, 15), 0, 0);
        threshold(temp, temp, THRESHOLD_MIN, THRESHOLD_MAX,THRESH_BINARY);

        findContours(temp, contours, hyerarchy, CV_RETR_TREE, CHAIN_APPROX_NONE);
        for( int i = 1; i< contours.size(); i++ ) //contour 0 is the frame
        {
            s = contourArea(contours[i], false);
            if (s > max)
            {
                max = s;
                iMax = i;
            }
        }
        if (max > MIN_OBJECT_AREA)
        {
            Moments mu = moments(contours[iMax], true);
            sendData(tcp, static_cast<uint16_t>(INV_SCALE_FACTOR * mu.m10/mu.m00) , static_cast<uint16_t>(INV_SCALE_FACTOR * mu.m01/mu.m00));
        }
        else sendData(tcp, 65001, 65001);



        capture.read(frame);

        ++num_frames;
        time(&end);
        double seconds = difftime(end, start);
        if (seconds >= 1.0)
        {
            cout << "Frame per second: " << num_frames << endl;
            time(&start);
            num_frames = 0;
        }
    }

    capture.release();

    return 0;
}

bool sendData(TCPClient &tcp, const uint16_t &x, const uint16_t &y)
{
    mavlink_message_t msg;
    uint8_t sendBuff[MAVLINK_MAX_PACKET_LEN];

    mavlink_msg_coord_icv_pack(0, 0, &msg, x, y);
    uint16_t len = mavlink_msg_to_send_buffer(sendBuff, &msg);

    //cout << "n bytes: " << len << endl;
    return tcp.Send(sendBuff, len);
}
