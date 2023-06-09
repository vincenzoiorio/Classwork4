#include "ros/ros.h"
#include "classwork4/fileservice.h"
#include <geometry_msgs/Pose.h>
#include <tf/transform_broadcaster.h>

using namespace std;

int main(int argc, char** argv) {
    ros::init(argc, argv, "client_broadcaster");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<classwork4::fileservice>("trservice");
    
    classwork4::fileservice srv;

    srv.request.frame_a.data="/lbr_iiwa_link_0";
    srv.request.frame_b.data="/lbr_iiwa_link_7";


    ROS_INFO("Waiting for the client server");
	client.waitForExistence(); 
	ROS_INFO("Client server up now");


    if (!client.call(srv)) {
		ROS_ERROR("Error calling the service");
		return 1;
	}
    /* while(ros::ok()){

        }
        */
       
	//Just print the output
	cout << "Service output: " << srv.response.pose << endl;



    // ros::Rate r(50);
  
    return 0;
}
