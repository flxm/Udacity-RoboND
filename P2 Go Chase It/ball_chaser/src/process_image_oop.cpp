#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Image Processor class
class ImageProcessor {

private:
  // Define a global client that can request services
  ros::ServiceClient client;

  // This function calls the command_robot service to drive the robot in the specified direction
  void drive_robot(float linear_x, float angular_z) {
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = linear_x;
    srv.request.angular_z = angular_z;

    if (!client.call(srv)) {
      ROS_ERROR("Failed to call service /ball_chaser/command_robot");
    }
  }
  
public:
  // Constructor
  ImageProcessor(ros::NodeHandle *n) {
    // Define a client service capable of requesting services from command_robot
    client = n->serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n->subscribe("/camera/rgb/image_raw", 10, &ImageProcessor::process_image_callback, this);
  }

  // This callback function continuously executes and reads the image data
  void process_image_callback(const sensor_msgs::Image img) {
    const int white_pixel = 255;

    bool found = false;
    int x_min = img.step;
    int x_max = -1;

    for (int y=img.height*0.4; y < img.height*0.6; y++) {
      for (int x=0; x < img.step; x+=3) {
        int i = y * img.step + x;
        if (img.data[i] == white_pixel && img.data[i+1] == white_pixel && img.data[i+2] == white_pixel) {
          found = true;
          if (x<x_min) x_min = x;
          if (x>x_max) x_max = x;
        }
      }
    }

    if (found) {
      // center of ball
      int center = (x_min + x_max) / 2;

      // determine horizontal position in percent
      float pos = (float)center / img.step;

      // Turn left or right or go straight
      if (pos < 0.3) {
        drive_robot(0.0, 0.5);
      } else if (pos > 0.7) {
        drive_robot(0.0, -0.5);
      } else {
        drive_robot(1.0, 0.0);
      }
    } else {
      // no ball detected, stop robot
      drive_robot(0.0, 0.0);
    }
  }
};


int main(int argc, char** argv) {
  // Initialize the process_image node and create a handle to it
  ros::init(argc, argv, "process_image");

  // Create a ROS NodeHandle object
  ros::NodeHandle n;

  // Instantiate image processor
  ImageProcessor ip(&n);

  // Handle ROS communication events
  ros::spin();

  return 0;
}
