#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
    
ros::Time last_time_stamp;

void poseCallback(const nav_msgs::Odometry& msg){
     static tf::TransformBroadcaster br;
     tf::Transform transform;
     ros::Time time_now = ros::Time::now();
     ros::Time time_msg = msg.header.stamp;
     transform.setOrigin( tf::Vector3(msg.pose.pose.position.x, msg.pose.pose.position.y, msg.pose.pose.position.z + 0.65) );
     
     transform.setRotation(tf::Quaternion(msg.pose.pose.orientation.x,msg.pose.pose.orientation.y,
     msg.pose.pose.orientation.z,msg.pose.pose.orientation.w));
     if (last_time_stamp < time_now)
     {
       br.sendTransform(tf::StampedTransform(transform, time_now, "world", "pelvis"));
        last_time_stamp = time_now;
     }
     
   }

void poseCallbackLidar(const nav_msgs::Odometry& msg){
     static tf::TransformBroadcaster br;
     tf::Transform transform;
     ros::Time time_now = ros::Time::now();
     ros::Time time_msg = msg.header.stamp;
     transform.setOrigin( tf::Vector3(msg.pose.pose.position.x, msg.pose.pose.position.y - 0.02, msg.pose.pose.position.z + 0.02) );
     
     transform.setRotation(tf::Quaternion(msg.pose.pose.orientation.x,msg.pose.pose.orientation.y,
     msg.pose.pose.orientation.z,msg.pose.pose.orientation.w));
     if (last_time_stamp < time_now)
     {
       br.sendTransform(tf::StampedTransform(transform, time_now, "new_fixed_frame", "camera_init"));
       last_time_stamp = time_now;
     }
   }

   
int main(int argc, char** argv){
     ros::init(argc, argv, "centauro_tf_broadcaster");
   
     ros::NodeHandle node;
     ros::Subscriber sub = node.subscribe("/T265/T265_camera/odom/sample", 10, &poseCallback);
     // ros::Subscriber sub_0 = node.subscribe("/Odometry", 1, &poseCallback);
     last_time_stamp = ros::Time(0);
   
     ros::spin();
     return 0;
   };
