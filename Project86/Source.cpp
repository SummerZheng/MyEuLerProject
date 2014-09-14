#include<iostream>
#include<vector>
#include<set>
#include<time.h>

using namespace std;

int main(){
	int M = 2000, m;
	set<int> sqSet;
	vector<int> sqArr(3*M, 0);
	for(int i=1; i!=3*M; i++){
		int n = i*i;
		sqSet.insert(n);
		sqArr[i-1] = n;
	}

	clock_t t1 = clock();
	vector<int> dpArr(M+1, 0);
	for(m=1; m<=M; ++m){
		int c=m, cSq = sqArr[c-1], ct=0;
		for(int l=c+1; l<=3*M && sqArr[l-1]<=5*cSq; ++l){
			int abSq = sqArr[l-1]-cSq;
			if(sqSet.count(abSq)>0){
				int aPlusb = static_cast<int>(sqrt(abSq));
				ct += min(c, aPlusb-1)-(aPlusb-1)/2;
				//cout<<aPlusb<<" "<<c<<" "<<ct<<endl;
			}
		}
		dpArr[m] = dpArr[m-1]+ct;
		if(dpArr[m]>1000000)
			break;
	}
	cout<<m<<" "<<dpArr[m]<<endl;
	clock_t t2 = clock();	
	//cout<<dpArr[M]<<endl;
	cout<<(t2-t1)/CLOCKS_PER_SEC<<"s"<<endl;
	cin.get();
	return 0;
}
