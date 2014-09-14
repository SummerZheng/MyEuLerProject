#include <iostream>
using namespace std;

int main(){
	int n= 100;
	int sum1 = n*n*(n+1)*(n+1)/4;
	int sum2 = n*(n+1)*(2*n+1)/6;
	cout<<sum1-sum2<<endl;
	cin.get();
	return 0;

}