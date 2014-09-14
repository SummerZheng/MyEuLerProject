#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

void generatePrimeChart(vector<int> &primeChart, const int &maxN){
	primeChart[0]=2;
	int primeCount=1;
	for(int n=3; n<=maxN; ++n){
		int upbound = static_cast<int>(sqrt(n));
		int ix;
		for(ix=0; primeChart[ix]<=upbound; ++ix){
			if(n%primeChart[ix]==0)
				break;
		}
		if(primeChart[ix]>upbound)
			primeChart[primeCount++]=n;
	}
	primeChart.resize(primeCount);
}

bool isPrime(int n,const vector<int> &primeChart){
	int upbound = static_cast<int>(sqrt(n));
	int ix;
	for(ix=0; primeChart[ix]<=upbound; ++ix){
			if(n%primeChart[ix]==0)
				break;
	}
	if(primeChart[ix]>upbound)
		return true;
	else
		return false;
}
int main(){
	int maxN=1000;
	vector<int> primeChart(maxN);
	generatePrimeChart(primeChart, maxN);

	for (int n=10000; n!=100000; ++n){
		if(isPrime(n, primeChart)){
		}
	}

	cin.get();
	return 0;
}