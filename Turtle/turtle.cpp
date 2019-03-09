#include<iostream>
#include<fstream>
#include<stdio.h>
#include"ros/ros.h"
#include<tf/transform_listener.h>
#include<geometry_msgs/Twist.h>
#include<turtlesim/Spawn.h>
#include <sstream>
#include<string.h>
#include <ctime>
#include<math.h>
#define pi 3.14159

using namespace std;

double dist( double x1, double y1, double x2, double y2 )
{
	return sqrt(pow(x1 - x2, 2)  + pow(y1 - y2, 2));
}

/*void move(double speed, double distance, bool isForward)
{
	//ros::NodeHandle n;
	//ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
	geometry_msgs::Twist msg;
	if(isForward)
		msg.linear.x = abs(speed);
	else
		msg.linear.x = -abs(speed);
	msg.linear.y = 0;
	msg.linear.z = 0;
	msg.angular.x = 0;
	msg.angular.y = 0;
	msg.angular.z = 0;
	double t0 = ros::Time::now().toSec();
	double current_distance = 0.0;
	ros:: Rate loop_rate(100);
	 while(current_distance<distance)
  {
  	cout<<"Running2"<<endl;
    chatter_pub.publish(msg);
    double t1 = ros::Time::now().toSec();
    current_distance = speed*(t1 - t0);
    ros::spinOnce();
    loop_rate.sleep();
  }
  msg.linear.x = 0;
  chatter_pub.publish(msg);
}

void rotate(double angular_speed, double angle, bool isClockwise)
{
	//ros::NodeHandle n;
	//ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
	geometry_msgs::Twist msg;
	if(isClockwise)
		msg.angular.z = -abs(angular_speed);
	else
		msg.angular.z = abs(angular_speed);
	msg.linear.y = 0;
	msg.linear.z = 0;
	msg.angular.x = 0;
	msg.angular.y = 0;
	msg.linear.x = 0;
	double t0 = ros::Time::now().toSec();
	double current_angle = 0.0;
	ros:: Rate loop_rate(10);
	 while(current_angle<angle)
  {
  	cout<<"Running"<<endl;
    chatter_pub.publish(msg);
    double t1 = ros::Time::now().toSec();
    current_angle = angular_speed*(t1 - t0);
    ros::spinOnce();
    loop_rate.sleep();
  }
  msg.angular.z = 0;
  chatter_pub.publish(msg);
}*/

int main(int argc, char **argv)
{
  ros::init(argc, argv, "turtle");

  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);

  //double dist = 10;

  fstream myfile("/home/sharat/Desktop/rrt-star/vel.txt", ios_base::in);
  int i,a, max_points = 40, factor, number_of_lines = 0;
  int count;
  char my_character, c;
  int line;
  //getline(myfile, line);
  count = line;
  //FILE *mfile;
  //mfile = fopen("/home/sharat/Desktop/rrt-star/vel.txt","r");
  myfile >> count;
  //count = (int)count;
  //cout<<count<<endl;
  int* x = new int[count+1];
  int* y = new int[count+1];
  double* path_x = new double[40];
  double* path_y = new double[40];
  i = 2*count + 1;
  cout<<"Outside loop"<<endl;
  
  while(myfile>>line)
  {
    if(i%2==0)
    {
      x[i/2] = line;
    }
    else
    {
      y[i/2] = line;
    }
    i--;
  }
  
  factor = (count / max_points) + 1;
  int j = 0;
  for(i=0; i<count; i++)
  {
    if(i%factor == 0)
    {
      //if()
      path_x[j] = (double)x[i]*11/x[count];
      path_y[j] = (double)y[i]*11/y[count];
      cout<<path_x[j]<<" "<<path_y[j]<<endl;
      j++;
    }
  }
  path_x[j] = 11;
  path_y[j] = 11;
  cout<<path_x[j]<<" "<<path_y[j]<<endl;
  double current_distance, distance, current_angle, angle, rel_angle, speed, angular_speed = 0.2;
  bool clockwise, straight, isForward, isClockwise;
  speed = 1;

  //Taking turtle to (0,0)
  //move(5.5, 1, false);
  
  {
  	isForward = false;
  	speed = 1;
  	distance = 5.5;
	//ros::NodeHandle n;
	//ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
	geometry_msgs::Twist msg;
	if(isForward)
		msg.linear.x = abs(speed);
	else
		msg.linear.x = -abs(speed);
	msg.linear.y = 0;
	msg.linear.z = 0;
	msg.angular.x = 0;
	msg.angular.y = 0;
	msg.angular.z = 0;
	double t0 = ros::Time::now().toSec();
	double current_distance = 0.0;
	ros:: Rate loop_rate(100);
	 while(current_distance<distance)
  {
  	//cout<<"Running2"<<endl;
    chatter_pub.publish(msg);
    double t1 = ros::Time::now().toSec();
    current_distance = speed*(t1 - t0);
    ros::spinOnce();
    loop_rate.sleep();
  }
  msg.linear.x = 0;
  chatter_pub.publish(msg);
}

  //rotate(pi/2, 0.2, false);
	{
		isClockwise = false;
		angle = pi / 2;
		angular_speed = 0.2;
	//ros::NodeHandle n;
	//ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
	geometry_msgs::Twist msg;
	if(isClockwise)
		msg.angular.z = -abs(angular_speed);
	else
		msg.angular.z = abs(angular_speed);
	msg.linear.y = 0;
	msg.linear.z = 0;
	msg.angular.x = 0;
	msg.angular.y = 0;
	msg.linear.x = 0;
	double t0 = ros::Time::now().toSec();
	double current_angle = 0.0;
	ros:: Rate loop_rate(10);
	 while(current_angle<angle)
  {
  	//cout<<"Running"<<endl;
    chatter_pub.publish(msg);
    double t1 = ros::Time::now().toSec();
    current_angle = angular_speed*(t1 - t0);
    ros::spinOnce();
    loop_rate.sleep();
  }
  msg.angular.z = 0;
  chatter_pub.publish(msg);
}
  //move(5.5, 1, true);
  {
  	isForward = true;
  	speed = 1;
  	distance = 5.5;
	//ros::NodeHandle n;
	//ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
	geometry_msgs::Twist msg;
	if(isForward)
		msg.linear.x = abs(speed);
	else
		msg.linear.x = -abs(speed);
	msg.linear.y = 0;
	msg.linear.z = 0;
	msg.angular.x = 0;
	msg.angular.y = 0;
	msg.angular.z = 0;
	double t0 = ros::Time::now().toSec();
	double current_distance = 0.0;
	ros:: Rate loop_rate(100);
	 while(current_distance<distance)
  {
  	//cout<<"Running2"<<endl;
    chatter_pub.publish(msg);
    double t1 = ros::Time::now().toSec();
    current_distance = speed*(t1 - t0);
    ros::spinOnce();
    loop_rate.sleep();
  }
  msg.linear.x = 0;
  chatter_pub.publish(msg);
}
  //rotate(pi/2, 0.2, true);
	{
		isClockwise = true;
		angle = pi / 2;
		angular_speed = 0.3;
	//ros::NodeHandle n;
	//ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
	geometry_msgs::Twist msg;
	if(isClockwise)
		msg.angular.z = -abs(angular_speed);
	else
		msg.angular.z = abs(angular_speed);
	msg.linear.y = 0;
	msg.linear.z = 0;
	msg.angular.x = 0;
	msg.angular.y = 0;
	msg.linear.x = 0;
	double t0 = ros::Time::now().toSec();
	double current_angle = 0.0;
	ros:: Rate loop_rate(10);
	 while(current_angle<angle)
  {
  	//cout<<"Running"<<endl;
    chatter_pub.publish(msg);
    double t1 = ros::Time::now().toSec();
    current_angle = angular_speed*(t1 - t0);
    ros::spinOnce();
    loop_rate.sleep();
  }
  msg.angular.z = 0;
  chatter_pub.publish(msg);
}

  current_angle = 0;

  i = 0;
  while (i<j)
  {

    geometry_msgs::Twist msg;
    cout<<"i = "<<i<<endl;
    distance = dist(path_x[i], path_y[i], path_x[i+1], path_y[i+1]);
    cout<<distance<<endl;
    angle = atan2(path_y[i+1]-path_y[i], path_x[i+1]-path_x[i]);

    //if(x[i]>x[i+1])
    	// angle = angle + pi;

    rel_angle = angle - current_angle;

    cout<<rel_angle<<endl;

    if(rel_angle<0)
    	clockwise = false;
    else
    	clockwise = true;

    //rotate(angle, angular_speed, clockwise);
    {
		isClockwise = clockwise;
		angular_speed = 0.2;
	//ros::NodeHandle n;
	//ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
	geometry_msgs::Twist msg;
	if(isClockwise)
		msg.angular.z = -abs(angular_speed);
	else
		msg.angular.z = abs(angular_speed);
	msg.linear.y = 0;
	msg.linear.z = 0;
	msg.angular.x = 0;
	msg.angular.y = 0;
	msg.linear.x = 0;
	double t0 = ros::Time::now().toSec();
	double cur_angle = 0.0;
	ros:: Rate loop_rate(10);
	 while(cur_angle<abs(rel_angle))
	  {
	  	//cout<<"Running"<<endl;
	    chatter_pub.publish(msg);
	    double t1 = ros::Time::now().toSec();
	    cur_angle = angular_speed*(t1 - t0);
	    ros::spinOnce();
	    loop_rate.sleep();
	  }
	  msg.angular.z = -5*msg.angular.z;
	  chatter_pub.publish(msg);
	}
	msg.angular.z = 0;
	chatter_pub.publish(msg);
    //move(distance, speed, true);
  {
  	isForward = true;
  	speed = 0.5;
	//ros::NodeHandle n;
	//ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
	geometry_msgs::Twist msg;
	if(isForward)
		msg.linear.x = abs(speed);
	else
		msg.linear.x = -abs(speed);
	msg.linear.y = 0;
	msg.linear.z = 0;
	msg.angular.x = 0;
	msg.angular.y = 0;
	msg.angular.z = 0;
	double t0 = ros::Time::now().toSec();
	double current_distance = 0.0;
	ros:: Rate loop_rate(100);
	 while(current_distance<distance)
  {
  	//cout<<"Running2"<<endl;
    chatter_pub.publish(msg);
    double t1 = ros::Time::now().toSec();
    current_distance = speed*(t1 - t0);
    ros::spinOnce();
    loop_rate.sleep();
  }
  msg.linear.x = -5*msg.linear.x;
  chatter_pub.publish(msg);
}
msg.linear.x = 0;
chatter_pub.publish(msg);

current_angle =angle;   
   
    ++i;
  }
 
	return 0;
}