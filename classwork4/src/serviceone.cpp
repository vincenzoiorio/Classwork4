#include "ros/ros.h"
#include "classwork4/fileservice.h"
#include <geometry_msgs/Pose.h>
#include <tf/transform_listener.h>


using namespace std;

bool service_callback( classwork4::fileservice::Request &req, classwork4::fileservice::Response &res) {


tf::TransformListener listener;
tf::StampedTransform transform;
        try {
            listener.lookupTransform(req.frame_a.data, req.frame_b.data, ros::Time(0), transform);
        }
        catch (tf::TransformException ex){
        ROS_ERROR("%s",ex.what());
        return false;
        //ros::Duration(1.0).sleep();
        }
  geometry_msgs::Pose pose;
  pose.position.x = transform.getOrigin().x();
  pose.position.y = transform.getOrigin().y();
  pose.position.z = transform.getOrigin().z();

  // Set the orientation of the pose based on the rotation of the transform
  tf::Quaternion q = transform.getRotation();
  pose.orientation.x = q.x();
  pose.orientation.y = q.y();
  pose.orientation.z = q.z();
  pose.orientation.w = q.w();

  // Set the response to the computed pose
  res.pose = pose;

return true;
}




int main (int argc, char** argv){

ros::init(argc, argv, "service_server");
ros::NodeHandle n;


//Initialize the service object: name of the service and callback function
//	Like subscribers, also tje callback function can be declared as a class function
ros::ServiceServer service = n.advertiseService("trservice", service_callback);

//Call the spin function to maintain the node alive
ROS_INFO("Ready to accept requests");
ros::spin();

    return 0;
}