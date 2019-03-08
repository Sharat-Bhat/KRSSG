#include<iostream>
#include<cstdio>

using namespace std;

int n, *U, *D, *L;
enum state {start,down, halt, up, stop} motion;
int direction(int floor)
{
	int upstart, downstart;
	U[floor]=0;
	L[floor]=0;
	D[floor]=0;
	for(int i=floor+1; i<=n; i++)
	{
		if(U[i]!=0 || L[i]!=0)
		{
			upstart = i - floor;
			break;
		}
		else
			upstart = n+1;
	}
	for(int i=floor-1; i>=0; i--)
	{
		if(D[i]!=0 || L[i]!=0)
		{
			downstart = floor - i;
			break;
		}
		else
			downstart = n+1;
	}
	//cout<<"Upstart "<<upstart<<endl;
	//cout<<"Downstart "<<downstart<<endl;
	if(upstart==downstart && upstart!=n+1)
		return 1;
	else if(upstart>downstart)
		return -1;
	else if(downstart>upstart)
		return 1;
	else
	{
		for(int i=0; i<floor; i++)
		{
			if(U[i]!=0)
			{
				downstart = floor - i;
				break;
			}
		}
		for(int i=n; i>floor; i--)
		{
			if(D[i]!=0)
			{
				upstart = i - floor;
				break;
			}
		}
		//cout<<"Upstart"<<upstart<<endl;
		//cout<<"Downstart"<<downstart<<endl;
		if(downstart == n+1)
			return 0;
		else if(downstart>=upstart)
			return 1;
		else
			return -1;
	}
}
enum state move(enum state motion, int floor)
{
	switch(motion)
	{
		case start:
			//int upstart, downstart;
			int dir;
			dir = direction(floor);
			//cout<<"Direction: "<<dir<<endl;
			if(dir>0)
				return move(up, floor);
			else if(dir<0)
				return move(down, floor);
			else
				return move(stop, floor);

		case halt:
			cout<<" - "<<floor<<endl;
			L[floor] = 0;
			return motion;

		case down:
			D[floor] = 0;
			//cout<<"Down "<<floor<<endl;
			if(floor == 0)
			{
				L[floor] = 0;
				return move(up, floor);
			}
			else
			{
				if(D[floor-1] == 1 || L[floor-1] == 1 || (U[floor-1]==1 && floor==1))
				{
					D[floor-1] = 0;
					move(halt, floor-1);
					for(int i=0; i<=n; i++)
					{
						if((U[i]!=0 || D[i]!=0 || L[i]!=0) && i!=floor)
						{
							return move(down, floor-1);
						}
					}
					return move(stop, floor);
				}
				return move(down, floor-1);
			}

		case up:
			U[floor] = 0;
			//cout<<"Up "<<floor<<endl;
			if(floor == n)
			{
				L[floor] = 0;
				return move(down, floor);
			}
			else
			{
				if(U[floor+1] == 1 || L[floor+1] == 1 || (D[floor+1]==1 && floor==n-1))
				{
					U[floor+1] = 0;
					move(halt, floor+1);
					for(int i=0; i<=n; i++)
					{
						if((U[i]!=0 || D[i]!=0 || L[i]!=0) && i!=floor)
						{
							return move(up, floor+1);
						}
					}
					return move(stop, floor);
				}
				return move(up, floor+1);
			}
			
		default:
			cout<<"Stop"<<endl;
			return stop;
	}
}

int main()
{
	int c, s;
	cout<<"Enter number of floors: ";
	cin>>n;
	D = new int[n+1];
	L = new int[n+1];
	U = new int[n+1];
	for(int i=0; i<=n; i++)
	{
		D[i] = 0;
		U[i] = 0;
		//cout<<i<<endl;
		L[i] = 0;
	}
	cout<<"Lift buttons pressed (enter -1 if you have completed giving this input): ";
	while(1)
	{
		cin>>c;
		if(c >= 0 && c <= n)
		{
			L[c] = 1;
		}
		else
			break;
	}
	cout<<"Up buttons pressed (enter -1 if you have completed giving this input): ";
	while(1)
	{
		cin>>c;
		if(c >= 0 && c <= n)
		{
			*(U+c) = 1;
		}
		else
			break;
	}
	cout<<"Down buttons pressed (enter -1 if you have completed giving this input): ";
	while(1)
	{
		cin>>c;
		if(c >= 0 && c <= n)
		{
			*(D+c) = 1;
		}
		else
			break;
	}
	cout<<"Enter starting point: ";
	cin>>s;
	if(s<0 || s > n)
		cout<<"Invalid start point!\n";
	else
	{
		cout<<" - "<<s<<endl;
		move(start, s);
	}
	return 0;
}