/*
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
    
    srv.request.frame_a.data="/lbr_iiwa_link_7";
    srv.request.frame_b.data="/lbr_iiwa_link_0";


    ROS_INFO("Waiting for the client server");
	client.waitForExistence(); 
	ROS_INFO("Client server up now");


    if (!client.call(srv)) {
		ROS_ERROR("Error calling the service");
		return 1;
	}
    
    tf::TransformBroadcaster br;
    tf::Transform transform;
    ros::Rate r(100);


    while(ros::ok()){

    tf::Quaternion q;
    q.setRPY(0, 0, 0);  // Angoli di rollio, beccheggio e imbardata
    q.normalize();
    transform.setRotation(q);
    
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(),srv.request.frame_a.data ,srv.request.frame_b.data ));
   
    r.sleep();
    }
    
       



	//Just print the output    
    cout << "Service output: " <<endl<<srv.response.pose << endl;
    return 0;
}
*/
#include "ros/ros.h"
#include "classwork4/fileservice.h"
#include <geometry_msgs/Pose.h>
#include <tf/transform_broadcaster.h>

using namespace std;

int main(int argc, char** argv) {
    ros::init(argc, argv, "client_broadcaster");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<classwork4::fileservice>("trservice");
    string frame_a;
    string frame_b;
    
    tf::Transform transform;
    tf::TransformBroadcaster br;
    tf::Quaternion q;

    classwork4::fileservice srv;
    cout << "Choose the frame a"<<endl;
    cin>>frame_a;
    cout << "Choose the frame b"<<endl;
    cin>>frame_b;
   


    ROS_INFO("Waiting for the client server");
	client.waitForExistence(); 
	ROS_INFO("Client server up now");
    ros::Rate r(100);
while(ros::ok()){

    if (!client.call(srv)) {
		ROS_ERROR("Error calling the service");
		return 1;
	}
     srv.request.frame_a.data=frame_a;
     srv.request.frame_b.data=frame_b;
	//Just print the output
	cout << "Service output: " << srv.response.pose << endl;

    
        // Set the translation of the transform
        transform.setOrigin(tf::Vector3(
            srv.response.pose.position.x,
            srv.response.pose.position.y,
            srv.response.pose.position.z
        ));
        
        // Set the rotation of the transform
        q.setRPY(srv.response.pose.orientation.x,srv.response.pose.orientation.y,srv.response.pose.orientation.z);
        transform.setRotation(q);

        // Broadcast the transform between frame_a and frame_b
        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), frame_a, frame_b));


     r.sleep();
}
    return 0;
}