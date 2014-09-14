#include<iostream>
#include<vector>
#include<time.h>

using namespace std;

void generatePrimeChart(vector<int> &primeChart, int maxN){
	primeChart[0]=2;
	int primeCount =1;
	for (int n=3; n<=maxN; n+=2){
		int upbound= static_cast<int>(sqrt(n));
		int ix=0;
		while(primeChart[ix]<=upbound){
			if(n%primeChart[ix]==0)
				break;
			else
				++ix;
		}
		if(primeChart[ix]>upbound)
			primeChart[primeCount++]=n;
	}
	primeChart.resize(primeCount);
}

void sieveGeneratePrimeChart(vector<int> &primeChart, vector<bool> &isPrime, int maxN){
	int primeCount=0, curPrime;
	int maxFac = static_cast<int>(sqrt(maxN));
	isPrime[0]=false;
	primeCount =1; //since all even number except 2 are not primes, only start from 3, and check the odd idx of isPrime,
	for (int i = 2; i!=maxN; i+=2){
		if (isPrime[i]){
			curPrime = i+1;
			primeChart[primeCount++] = curPrime;
			if(curPrime<maxFac){
				for (int n = curPrime*curPrime; n<=maxN; n+=curPrime)
				isPrime[n-1]= false;
			}
		}
	}
	primeChart.resize(primeCount);
}

bool isPrime(const long long &n, const vector<int> &primeChart){
	int maxFac = static_cast<int>(sqrt(n));
	int ix=0;
	while(primeChart[ix]<=maxFac && n%primeChart[ix])
		++ix;
	if (primeChart[ix]>maxFac)
		return true;
	else
		return false;
}

bool isPrime(const long long &n, const vector<int> &primeChart,int &lookUpIx){
	while(primeChart[lookUpIx]<n)
		++lookUpIx;
	if(primeChart[lookUpIx]==n)
		return true;
	else
		return false;
}

void print(vector<int> &vec){
	for(int ix=0; ix!=vec.size(); ++ix)
		cout<<vec[ix]<<" ";
	cout<<endl;
}

int main(){
	int maxN=1000000;
	vector<int> primeChart(maxN);
	vector<bool> isPrimeChart(maxN, true);
	clock_t t1=clock();
	generatePrimeChart(primeChart, maxN);
	//sieveGeneratePrimeChart(primeChart, isPrimeChart, maxN);
	cout<<"There are "<<primeChart.size()<<" primes below "<<maxN<<endl;
	clock_t t2=clock();
	cout<<"Total time is "<<(double(t2)-double(t1))/CLOCKS_PER_SEC<<"s"<<endl;
	
	//vector<long long> diagonalPrime;	
	int lookUpix=0, primeCount=0;
	long long sqlen=1, totN=1, diagonalN=1;;
	double per = 1;
	while(per>0.1 && sqlen<maxN){
		sqlen+=2;
		diagonalN += 4;
		totN = sqlen*sqlen;
		for(int i=3; i!=0; --i){
			long long n = totN-i*(sqlen-1);
			bool flag;
			if (n<=maxN)
				flag = isPrime(n, primeChart, lookUpix);
			else
				flag = isPrime(n, primeChart);
			if(flag){
				++primeCount;
				//diagonalPrime.push_back(n);
			}
		}
		per = double(primeCount)/double(diagonalN);
		if (sqlen==maxN-1)
			cout<<per<<endl;
	}
	//print(diagonalPrime);
	cout<<"the first time that per drop below 10% is square length "<<sqlen<<" with total primes of "<<primeCount<<endl;
	clock_t t3=clock();
	cout<<"Total time is "<<(double(t3)-double(t2))/CLOCKS_PER_SEC<<"s"<<endl;
	
	cin.get();
	return 0;
}