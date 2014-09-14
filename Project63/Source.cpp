#include<iostream>
#include<math.h>
using namespace std;

int main(){
	int count=1; // to count for 1^1, which is not included in the later loop 
	for (int n=2; n<10; ++n){
		int exp = 1;
		double logN=log(n);
		double equ = (exp-1)*log(10)/exp;
		while(equ<logN){
			++count;
			++exp;
			equ = (exp-1)*log(10)/exp;
		}
	}
	cout<<count<<endl;
	cin.get();
	return 0;
}