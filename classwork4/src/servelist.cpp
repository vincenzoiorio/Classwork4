#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <classwork4/fileservice.h>
#include <tf/transform_listener.h>

using namespace std;

bool service_callback( classwork4::fileservice::Request &req, classwork4::fileservice::Response &res) {
  tf::TransformListener listener;
  cout << "Service frame received: " << endl;
  //We know that the service is called with 2 parameters: frame_a and frame_b
	// These parameters are put in a data structure called req
	cout << req.frame_a.data << req.frame_b.data << endl;

	//The return value is store in the res datastracture
	cout << "Returning the frame_b in the frame_a: " << endl;
	
  //res.sum.data = req.x.data + req.y.data;
  //res.pose

 tf::StampedTransform transform;
        try {
            //listener.lookupTransform(req.frame_b.data, req.frame_a.data, ros::Time(0), transform); //se mettere nome
            listener.lookupTransform("/lbr_iiwa_link_7", "/lbr_iiwa_link_0", ros::Time(0), transform);
        }
        catch (tf::TransformException ex){
            ROS_ERROR("%s",ex.what());
            ros::Duration(1.0).sleep();
        }

        ROS_INFO_STREAM(" Transform:" << 
        
            transform.getOrigin().x() << ", " << 
            transform.getOrigin().y() << ", " <<
            transform.getOrigin().z() << ", " << 
            transform.getRotation().x() << ", " << 
            transform.getRotation().y() << ", " << 
            transform.getRotation().z()
        );




	return true;

}


int main(int argc, char** argv) {

    ros::init(argc, argv, "server_listener");

    ros::NodeHandle nh;
    ros::ServiceServer service = nh.advertiseService("trservice", service_callback);
    
    ros::spin();

    return 0;
}
