#include <iostream>
#include <vector>

using namespace std;

int  gcd(int a, int b){
	int c; 
	while (b != 0){
		c = b;
        b = a % b;
		a = c;
	 }
    return a;
}

int main(){
	int maxd = 1000000;
	int mindiff = 100, diff;
	int n;
	for (int d=maxd; d>=2; --d){
		n = (3*d%7==0)? 3*d/7 -1: 3*d/7;
		diff = 3*d - 7*n;
		if (diff<mindiff && gcd(n, d)==1){
			mindiff = diff;
			cout<<n<<"/"<<d<<" yields min diff "<<mindiff<<endl;
		}
	}
	cin.get();
	return 0;
}