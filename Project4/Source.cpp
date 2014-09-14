#include<iostream>
using namespace std;
#define upperbound 999


bool isPalindrom(int testnum){
	testnum%=100001;
	testnum%=10010;
	if (testnum%1100==0)
		return true;
	else
		return false;
}

int main(){	
	int lowerbound = 100;
	int m1, m2;
	int palidrom = 0; 
	for (m1=upperbound; m1>lowerbound ; --m1){
		for (m2 = m1; m2>lowerbound; --m2){
			if (m1*m2>palidrom){
				if (isPalindrom(m1*m2)){
					palidrom = m1*m2;
					cout<<m1<<"*"<<m2<<"="<<palidrom<<endl;
					lowerbound = m2;
				}
			}
		}
	}



	cout<<palidrom<<endl;
	cout<<m1<<endl;
	cout<<m2<<endl;
	
			
	cin.get();
	return 0;
}