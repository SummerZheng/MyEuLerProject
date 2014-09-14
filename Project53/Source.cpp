#include<iostream>

using namespace std;

int main(){
	int term=0, minLimit = 1000000;
	for (int n=1; n<=100; ++n){
		for (int r=1; r<=n/2; ++r){
			long long factorial = 1;
			for (int i = 1; i!=r+1; ++i)
				factorial *= (n+1-i);
			for (int i = 1; i!=r+1; ++i)
				factorial /= (r+1-i);
			if (factorial>=minLimit){
				term += (n-2*r+1);
				cout<<"C_"<<n<<"^"<<r<<" is greater than "<<minLimit<<", and "<<(n-2*r+1)<<" terms are added"<<endl;
				break;
			}
		}
	}
	cout<<"We have "<<term<<" terms  greater than "<<minLimit<<endl;
	cin.get();
	return 0;
}