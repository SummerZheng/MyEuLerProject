#include<iostream>
#include<vector>

using namespace std;


bool split_ab(int c, int sum, vector<int> bmod10, int &a,int &b){
	for (int brmd10 = (sum- c)/20; brmd10<=c/10; ++brmd10){
		for (int i=0; i!=bmod10.size(); ++i){
		b = 10*brmd10+bmod10[i];
		a = sum-b-c;
		if ((a*a+b*b)==c*c)
			return true;
		}
	}
	return false;
}
int main(){
	int sum = 1000;
	int a, b, c;
	bool flag = false;
	vector<int> bmod10(2, 0); 
	bmod10[0]=0;bmod10[1]=5;
	c=sum/3+1;

	while(!flag && c++!=sum/2){
		flag = split_ab(c, sum, bmod10, a, b);
	}
	cout<<a<<" "<<b<<" "<<c<<endl;
	cout<<a*b*c<<endl;
	cin.get();
	return 0;
}