#include<iostream>
#include<vector>
using namespace std;

//return the next smallest prime factor of int a
int factorization(const long long a, const int d){
	for (int divider = d; divider<=ceil(sqrt(a)); divider+=2){
		if (a%divider==0)
			return divider;
	}
	return a;
}

void printvector(const vector<int> &a){
	for (int i=0; i!=a.size(); ++i)
		cout<<a[i]<<" ";
	cout<<endl;
}


int main(){
	//long long bignum = 600851475143;
	long bignum = 86139;
	/*
	long long sqrt_ll = sqrt(bignum);
	long sqrt_long = sqrt(bignum);
	int sqrt_int = sqrt(bignum);
	cout<<bignum<<endl;
	cout<<sqrt_ll<<endl;
	cout<<sqrt_long<<endl;
	cout<<sqrt_int<<endl;
	*/
	vector<int> factors;
	//int maxprimefactor = 0;
	int divider = 2;
	while (bignum%divider ==0)
		bignum/=divider;
	if (bignum!=1){
	divider = 3;
		while (bignum!=1){
			divider = factorization(bignum, divider);
			factors.push_back(divider);
			bignum/=divider;		
	}
	}
	
	printvector(factors);
	cout<<divider<<endl;
	cin.get();
}
