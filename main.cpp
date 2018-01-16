#include <opencv2/opencv.hpp>
#include "lib/TCPClient/TCPClient.h"
#include "lib/Utility/utility.h"
#include "lib/mavlink/v2.0/common/mavlink.h"
#include "Object.h"

#define __DEBUG__

using namespace cv;
using namespace std;

bool calibrationMode = false;

int H_MIN = 0;
int H_MAX = 256;
int S_MIN = 0;
int S_MAX = 256;
int V_MIN = 0;
int V_MAX = 256;

const int FRAME_WIDTH = 213;
const int FRAME_HEIGHT = 160;
const float INV_SCALE_FACTOR = 640 / FRAME_WIDTH;

const int MAX_NUM_OBJECTS = 5;
const int MIN_OBJECT_AREA = FRAME_HEIGHT * FRAME_WIDTH / 25;
const int MAX_OBJECT_AREA = FRAME_HEIGHT * FRAME_WIDTH / 1.5;

const string windowName = "Original Image";
const string windowName1 = "HSV Image";
const string windowName2 = "Thresholded Image";
const string windowName3 = "After Morphological Operations";
const string trackbarWindowName = "Trackbars";

Mat dst, detected_edges;
Mat src, src_gray;
int edgeThresh = 1;
int ratio = 3;
int filter_kernel_size = 3;
int erode_kernel_size = 2;
int dilate_kernel_size = 4;

TCPClient tcp;

bool sendData(TCPClient &tcp, const uint16_t &x, const uint16_t &y);

void createTrackbars();
void drawObject(vector<Object> theObjects, Mat &frame);
void morphOps(Mat &thresh);
void trackFilteredObject(Mat threshold, Mat HSV, Mat &cameraFeed);
void trackFilteredObject(Object theObject, Mat threshold, Mat HSV, Mat &cameraFeed);

int main()
{
    int num_frames = 0;
    time_t start, end;

    VideoCapture capture;
    Mat cameraFeed;
    Mat threshold;
    Mat HSV, im_Grey;

    Object blue("blue"), yellow("yellow"), red("red"), green("green");

    Utility::initTime();

    if (calibrationMode) {
        createTrackbars();
    }

    capture.open(1);
    if (!capture.isOpened()) return EXIT_FAILURE;

    capture.set(CV_CAP_PROP_FPS, 30);
    capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);

    //if (!tcp.setup("127.0.0.1", 11999)) return EXIT_FAILURE;

    time(&start);
    for (;;)
    {
        capture.read(cameraFeed);
        src = cameraFeed;
        while (!src.data)
        {
            capture.read(cameraFeed);
            src = cameraFeed;
        }
        cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
        if (calibrationMode)
        {
            cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
            inRange(HSV, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold);
            morphOps(threshold);

#ifdef __DEBUG__
            imshow(windowName2, threshold);
            imshow(windowName1, HSV);
#endif
            dst.create(src.size(), src.type());
            cvtColor(src, src_gray, CV_BGR2GRAY);

            trackFilteredObject(threshold, HSV, cameraFeed);
        }
        else
        {
            cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
            inRange(HSV, green.getHSVmin(), green.getHSVmax(), threshold);
            morphOps(threshold);
#ifdef __DEBUG__
            imshow(windowName2, threshold);
#endif
            trackFilteredObject(red, threshold, HSV, cameraFeed);
        }
#ifdef __DEBUG__
        imshow(windowName, cameraFeed);
#endif
        ++num_frames;
        time(&end);
        double seconds = difftime(end, start);
        if (seconds >= 1.0) {
            cout << "Frame per second: " << num_frames << " Time: " <<
                 seconds << endl;
            time(&start);
            num_frames = 0;
        }
#ifdef __DEBUG__
        if (waitKey(10) == 'q')
            break;
#endif
    }
    return 0;
}

bool sendData(TCPClient &tcp, const uint16_t &x, const uint16_t &y) {
    mavlink_message_t msg;
    uint8_t sendBuff[MAVLINK_MAX_PACKET_LEN];

    mavlink_msg_coord_icv_pack(0, 0, &msg, x, y);
    uint16_t len = mavlink_msg_to_send_buffer(sendBuff, &msg);

    return tcp.Send(sendBuff, len);
}

void createTrackbars() {

#ifdef __DEBUG__
    namedWindow(trackbarWindowName, 0);
    createTrackbar("H_MIN", trackbarWindowName, &H_MIN, H_MAX);
    createTrackbar("H_MAX", trackbarWindowName, &H_MAX, H_MAX);
    createTrackbar("S_MIN", trackbarWindowName, &S_MIN, S_MAX);
    createTrackbar("S_MAX", trackbarWindowName, &S_MAX, S_MAX);
    createTrackbar("V_MIN", trackbarWindowName, &V_MIN, V_MAX);
    createTrackbar("V_MAX", trackbarWindowName, &V_MAX, V_MAX);
    createTrackbar("Erode", trackbarWindowName, &erode_kernel_size, 8);
    createTrackbar("Dilate", trackbarWindowName, &dilate_kernel_size, 8);
    createTrackbar("Filter", trackbarWindowName, &filter_kernel_size, 8);
#endif

}

void drawObject(vector<Object> theObjects, Mat &frame) {

    for (unsigned int i = 0; i < theObjects.size(); i++) {

        circle(frame, Point(theObjects.at(i).getXPos(), theObjects.at(i).getYPos()), 10, Scalar(0, 0, 255));
        putText(frame, Utility().intToString(theObjects.at(i).getXPos()) + " , " +
                       Utility().intToString(theObjects.at(i).getYPos()),
                Point(theObjects.at(i).getXPos(), theObjects.at(i).getYPos() + 20), 1, 1, Scalar(0, 255, 0));
        putText(frame, theObjects.at(i).getType(), Point(theObjects.at(i).getXPos(), theObjects.at(i).getYPos() - 30),
                1, 2, theObjects.at(i).getColor());
    }
}

void morphOps(Mat &thresh) {

    Mat erodeElement = getStructuringElement(MORPH_RECT, Size(2 * erode_kernel_size + 1, 2 * erode_kernel_size + 1));
    Mat dilateElement = getStructuringElement(MORPH_RECT, Size(2 * dilate_kernel_size + 1, 2 * dilate_kernel_size + 1));

    erode(thresh, thresh, erodeElement);
    erode(thresh, thresh, erodeElement);

    dilate(thresh, thresh, dilateElement);
    dilate(thresh, thresh, dilateElement);
}

void trackFilteredObject(Mat threshold, Mat HSV, Mat &cameraFeed) {
    vector<Object> objects;
    Mat temp;
    threshold.copyTo(temp);

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

    double refArea = 0;
    bool objectFound = false;
    if (hierarchy.size() > 0) {
        int numObjects = hierarchy.size();

        if (numObjects < MAX_NUM_OBJECTS) {
            for (int index = 0; index >= 0; index = hierarchy[index][0]) {
                Moments moment = moments((Mat) contours[index]);
                double area = moment.m00;

                if (area > MIN_OBJECT_AREA) {
                    Object object;

                    object.setXPos(moment.m10 / area);
                    object.setYPos(moment.m01 / area);

                    objects.push_back(object);

                    objectFound = true;

                } else objectFound = false;
            }

            if (objectFound == true) {
#ifdef __DEBUG__
                drawObject(objects, cameraFeed);
#endif
            }
        }
#ifdef __DEBUG__
        else putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
#endif
    }
}

void trackFilteredObject(Object theObject, Mat threshold, Mat HSV, Mat &cameraFeed) {
    int max_area_idx = 0;
    int max_area = 0;
    //vector <Object> objects;
    Mat temp;
    threshold.copyTo(temp);

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
    //cout << contours.size() << endl;
    for (unsigned int i = 0; i < contours.size(); i++) {
        int area = contourArea(contours.at(i));
        if (area > max_area) {
            max_area = area;
            max_area_idx = i;
        } else
            continue;
    }
    if (max_area > MIN_OBJECT_AREA) {
        uint32_t time;
        Moments mu;
        mu = moments(contours[max_area_idx], true);
        Point2f mc;
        mc = Point2f(mu.m10 / mu.m00, mu.m01 / mu.m00);

        //OBJECT FOUND
#ifdef __DEBUG__
        circle(cameraFeed, mc, 5, Scalar(255, 255, 255));
#endif
        //sendData(tcp, mc.x, mc.y);
    }
}