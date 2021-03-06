#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Empty.h>

#include <geometry_msgs/PoseArray.h>
#include "alghago_msgs/BadukalArray.h"


#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <eigen3/Eigen/Dense>


using namespace std;
using namespace cv;

#define FILTER_CNT 5

struct Badukal
{
    enum BADUKAL_COLOR {BLACK, WHITE};
    int color;
    double x;
    double y;
};

class BadukpanExtractor
{
    image_transport::ImageTransport it_;
    image_transport::Subscriber camera_sub_;

    image_transport::Publisher processed_pub_;

    ros::Publisher badukal_pub_;
    ros::Subscriber badukpan_fit_sub_;

    Mat warpPerspectiveMatrix_;

    bool isFirst_;
    int count_;
    int badukal_count_;

    int filterCount_;

    vector<Badukal> badukalPoints_[FILTER_CNT];


public:

    BadukpanExtractor(ros::NodeHandle& nh);
    virtual ~BadukpanExtractor() {}


private:
    void imageCallback(const sensor_msgs::ImageConstPtr& msg);
    void badukpanFitCallback(const std_msgs::EmptyConstPtr msg);
    void fitBadukpan(Mat &srcImg);
    void scanBadukal(Mat &srcImg, Mat &badukpanImg);

};

