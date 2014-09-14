#include<iostream>
#include<vector>
#include<time.h>
#include "bigNum.h"

using namespace std;

int main(){
	clock_t t1=clock();
	int maxSum=0, maxSumN=0, maxSumExp=0;
	for (int n=1; n<100; ++n){
		bigNum bgN(1);
		for (int exp=1; exp<100; ++exp){
			bgN*=n;
			int curSum = bgN.bigNumdigitSum();
			if (curSum>maxSum){
				maxSum = curSum; maxSumN = n; maxSumExp = exp;
				cout<<n<<"^"<<exp<<" = "<<bgN<<", with digit sum of "<<maxSum<<endl;
			}
		}
	}
	cout<<maxSum<<endl;
	clock_t t=clock()-t1;
	cout<<"total time = "<<(double)t<<endl;
	cin.get();
	return 0;
}

