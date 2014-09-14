#include<iostream>

using namespace std;

int main(){
	double x=64;
	double y=x;
	double deltay=1, convergeAlpha = 0.0001;
	do{
		deltay = (y*y-x)/2/x;
		y-=deltay;
	}while(deltay>convergeAlpha);
	cout<<"sqrt("<<x<<") = "<<y<<endl;
	cin.get();
	return 0;
}