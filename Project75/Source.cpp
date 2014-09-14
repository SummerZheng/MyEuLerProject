#include<iostream>
#include<vector>

using namespace std;

int gcd(int a, int b){
	int c;
	while(a%b!=0){
		c = a%b;
		a = b;
		b = c;
	}
	return b;
}

int main(){
	int L=1500000;
	vector<int> rightTriangleCount(L, 0);
	int count = 0;

	int a, b, c, l, basel;
	int maxMN = static_cast<int>(sqrt(L/2));
	for(int n=1; n!=maxMN-1; ++n){
		for(int m=n+1; m!=maxMN; ++m){
			if(gcd(m, n)==1 && (m-n)%2!=0){
				c = m*m+n*n;
				a = m*m-n*n;
				b = 2*m*n;
				//if(gcd(a, c)==1){
				basel=a+b+c;
				l = basel;
				while(l<=L){
					rightTriangleCount[l-1]++;
					if(rightTriangleCount[l-1]==1)
						count++;
					if(rightTriangleCount[l-1]==2)
						count--;
					l += basel;
					/*
					if(l == 120){
						int multiplier = l/basel;
						cout<<"("<<a<<", "<<b<<", "<<c<<")"<<endl;
						cout<<"("<<multiplier*a<<", "<<multiplier*b<<", "<<multiplier*c<<")"<<endl;
						cout<<endl;
					}
					*/
				}
				//}
			}
		}
	}

	cout<<count<<endl;
	
	cin.get();
	return 0;
}