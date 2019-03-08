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

double slope( double x1, double y1, double x2, double y2 )
{
	return (y1-y2)/(x2-x1);
}

void move(double speed, double distance, bool isForward)
{
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
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "turtle");

  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);

  geometry_msgs::Twist msg;

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
  bool clockwise, straight;
  speed = 1;

  //Taking turtle to (0,0)
  move(5.5, 1, false);
  rotate(pi/2, 0.2, false);
  move(5.5, 1, true);
  rotate(pi/2, 0.2, true);
  current_angle = 0;

  i = 0;
  while (ros::ok() && i<j)
  {

    geometry_msgs::Twist msg;

    distance = dist(x[i], y[i], x[i+1], y[i+1]);
    angle = atan(slope(x[i], y[i], x[i+1], y[i+1])) - current_angle;

    if(x[i]<x[i+1])
    	angle = angle + pi;

    if(angle>0)
    	bool clockwise = false;
    else
    	bool clockwise = true;

    rotate(angle, angular_speed, clockwise);

    move(distance, speed, true);

    current_angle =angle + current_angle;   
   
    ++i;
  }
 
	return 0;
}