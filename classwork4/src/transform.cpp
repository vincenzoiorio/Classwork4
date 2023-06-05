#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <classwork4/fileservice.h>
#include <tf/transform_broadcaster.h>
using namespace std;

int main(int argc, char **argv)
{
    
  ros::init(argc, argv, "service_client");
  ros::NodeHandle nh;
   
  // Create the service client
  ros::ServiceClient client = nh.serviceClient<classwork4::fileservice>("trservice");

  // Create a tf broadcaster
  static tf::TransformBroadcaster br;

  while(ros::ok())
  {
    // Call the service to get the transformation between lbr_iiwa_link_0 and lbr_iiwa_link_7
    classwork4::fileservice srv;
    
    srv.request.frame_a.data= "lbr_iiwa_link_0";
    srv.request.frame_b.data = "lbr_iiwa_link_7";
    if (client.call(srv))
    {
      // Create a tf::Transform object based on the computed pose
      tf::Transform transform;
      transform.setOrigin(tf::Vector3(srv.response.pose.position.x,
                                      srv.response.pose.position.y,
                                      srv.response.pose.position.z));
      transform.setRotation(tf::Quaternion(srv.response.pose.orientation.x,
                                            srv.response.pose.orientation.y,
                                            srv.response.pose.orientation.z,
                                            srv.response.pose.orientation.w));

      // Broadcast the transform as a dynamic tf
      br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "lbr_iiwa_link_0", "lbr_iiwa_link_7"));
       
    }
    else
    {
      ROS_ERROR("Failed to call service");
    }

    // Sleep for some time before calling the service again
    ros::Duration(0.1).sleep();
  }

  return 0;
}
