#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"
#include<iostream>
#include<queue>
#include<math.h>
#include<cstdlib>
#include<vector>
#include<time.h>
#include<fstream>

#define step_size 30
#define range 35
#define branch_color 64
#define path_color 192

using namespace cv;
using namespace std;

Mat img, img1, img2, img3;

struct coordinate
{
	int x;
	int y;
	int index;
	int prev_index;
	int height;
};

struct CompareHeight { 
    bool operator() (coordinate const& p1, coordinate const& p2) 
    { 
        // return "true" if "p1" is ordered  
        // before "p2", for example: 
        return p1.height > p2.height; 
    } 
}; 

void binary()
{
	for(int i=0; i<img1.rows; i++)
	{
		for(int j=0; j<img1.cols; j++)
		{
			if(img1.at<uchar>(i,j) >= 127)
				img1.at<uchar>(i,j) = 255;
			else
				img1.at<uchar>(i,j) = 0;
		}
	}
}

double dist( coordinate p1, coordinate p2 )
{
	return sqrt(pow(p1.x - p2.x, 2)  + pow(p1.y - p2.y, 2));
}

int rrt_star(coordinate start, coordinate end, vector<coordinate> pixel)
{
	priority_queue <coordinate, vector <coordinate>, CompareHeight> nbd;
	coordinate point, temp;
	int count=0, min_index, min_height, ins_x, ins_y, i, j, k, iter = 1;
	bool reach = false, flag;
	double min_dist, gap;
	//cout<<"P0\n";
	start.prev_index = -1;
	start.height = 0;
	start.index = 0;
	pixel.push_back(start);
	//cout<<"P1\n";
	imshow("wind", img2);
	imshow("win", img1);
	waitKey(0);
	while(iter>0)
	{
		flag = false;
		//Checking if destination is reached
		if(reach == false && dist(pixel[count], end) < step_size)
		{
			end.prev_index = count;
			count++;
			end.index = count;
			line(img2, Point(pixel[count].y, pixel[count].x), Point(pixel[count-1].y, pixel[count-1].x), branch_color, 1);
			pixel.push_back(end);
			reach = true;
			//waitKey(0);
		}
		min_dist = img.rows + img.cols;
		point.x = ((double) rand() / RAND_MAX) * img.rows;
		point.y = ((double) rand() / RAND_MAX) * img.cols;
		for(i=0; i<=count; i++)
		{
			gap = dist(point, pixel[i]);
			//Checking if a point lies in the neighbourhood of the newly generated point
			if(gap < range)
			{
				flag = true;
				//Checking if the path is obstacle free: If yes, then pushed into the priority queue
					for(j = 1; j <= gap; j++)
					{
						ins_y = pixel[i].y + (point.y - pixel[i].y)*j/gap;
						ins_x = pixel[i].x + (point.x - pixel[i].x)*j/gap;
						if(img1.at<uchar>(ins_x, ins_y) == 255)
							break;
					}
					if(j > gap)
					{
						nbd.push(pixel[i]);
					}
			}
			//If no point lies in the neighbourhood, then minimum distance is calculated
			if(flag == false)
			{
				if(gap < min_dist)
				{
					min_dist = gap;
					min_index = i;
				}
			}
		}
		//If no point lies in the neighbourhood, then function as RRT
		if(flag == false)
		{
			temp.x = pixel[min_index].x + (point.x - pixel[min_index].x)*step_size/min_dist;
			temp.y = pixel[min_index].y + (point.y - pixel[min_index].y)*step_size/min_dist;
				for(j = 1; j <= step_size; j++)
				{
					ins_y = pixel[min_index].y + (point.y - pixel[min_index].y)*j/step_size;
					ins_x = pixel[min_index].x + (point.x - pixel[min_index].x)*j/step_size;
					if(img1.at<uchar>(ins_x, ins_y) == 255)
						break;
				}
				if(j > step_size)
				{
					//img2.at<uchar>(temp.x, temp.y) = 127;
					line(img2,Point(pixel[min_index].y, pixel[min_index].x),Point(temp.y, temp.x), branch_color, 1);
					count++;
					temp.prev_index = min_index;
					temp.index = count;
					temp.height = pixel[min_index].height + 1;
					pixel.push_back(temp);
				}
			imshow("win", img1);
			imshow("wind", img2);
			//if(count < 145)
			//{				
				waitKey(1);
			/*}
			else
			{
				waitKey(0);
			}*/
		}
		//Reassigning nodes to a better path
		else 
		{
			//cout<<"priority_queue size = "<<nbd.size()<<endl;
			if(!nbd.empty())
			{
				count++;
				temp = nbd.top();
				//cout<<temp.height<<endl;
				point.index = count;
				point.height = temp.height + 1;
				point.prev_index = temp.index;
				pixel.push_back(point);
				line(img2,Point(pixel[temp.index].y, pixel[temp.index].x),Point(point.y, point.x), branch_color, 1);
				nbd.pop();
				while(!nbd.empty())
				{
					temp = nbd.top();
					//cout<<temp.height<<endl;
					if(temp.height >= point.height + 1)
					{
						gap = dist(temp, point);
						for(j = 1; j <= gap; j++)
						{
							ins_y = temp.y + (point.y - temp.y)*j/gap;
							ins_x = temp.x + (point.x - temp.x)*j/gap;
							if(img1.at<uchar>(ins_x, ins_y) == 255)
								break;
						}
						if(j>gap)
						{
							line(img2,Point(pixel[temp.prev_index].y, pixel[temp.prev_index].x),Point(temp.y, temp.x), 0, 1);
							pixel[temp.index].prev_index = point.index;
							pixel[temp.index].height = point.height + 1;
							line(img2,Point(pixel[temp.index].y, pixel[temp.index].x),Point(point.y, point.x), branch_color, 1);
						}
					}
					nbd.pop();
					imshow("win", img1);
					imshow("wind", img2);
					//if(count < 145)
					//{				
						waitKey(1);
					/*}
					else
					{
						waitKey(0);
					}*/
				}
			}
		}
		//cout<<count<<endl;
		//Drawing the new path
		if(reach == true){
			k = end.index;
			int c = 0;
			img1 = img3.clone();
			while(pixel[k].prev_index != -1)
			{
				line(img1,Point(pixel[k].y, pixel[k].x),Point(pixel[pixel[k].prev_index].y, pixel[pixel[k].prev_index].x), path_color, 1);
				line(img2,Point(pixel[k].y, pixel[k].x),Point(pixel[pixel[k].prev_index].y, pixel[pixel[k].prev_index].x), path_color, 1);
				c++;
				cout<<c<<" "<<pixel[k].x<<" "<<pixel[k].y<<endl;
				k = pixel[k].prev_index;
				//waitKey(20);
				imshow("win", img1);
				imshow("wind", img2);
			}
			cout<<c<<" "<<pixel[k].x<<" "<<pixel[k].y<<endl;
			iter--;
			waitKey(200);
		}
		//cout<<"Iteration = "<<iter<<endl;
	}	
	waitKey(0);
}

int main()
{
	srand(time(NULL));
	coordinate start, end;
	img = imread("task2.png",0);
	start.x = 0;
	start.y = 0;
	img1 = img.clone();
	end.x = img.rows - 1;
	end.y = img.cols - 1;
	//cout<<"Hopeless me\n";
	vector<coordinate> pixel;
	binary();
	img2 = img1.clone();
	img3 = img1.clone();
	dilate(img1, img1, 5);
	//cout<<"Hi\n";
	rrt_star(end, start, pixel);
	return 0;
}
