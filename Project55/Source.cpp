#include<iostream>
#include<vector>
#include "bigNum.h"

using namespace std;

int main(){
	int lychrelN = 0;
	int maxN = 10000, maxIter = 51;
	/*
	bigNum bgNum(9122187);
	bigNum a(137289);
	a+=bgNum;
	cout<<a<<endl;
	*/
	for (int n=1; n!=maxN; ++n){
		bigNum bgNum(n);
		int iter = 1;
		while(iter!=maxIter){
			bgNum += bgNum.bigNumReverse();
			if (bgNum.ispalindrome())
				break;
			else
				++iter;
		}
		if (iter==maxIter){
			cout<<n<<" is a lychrel Number"<<endl;
			++lychrelN;
		}
	}
	
	cout<<lychrelN<<endl;
	cin.get();
	return 0;
}