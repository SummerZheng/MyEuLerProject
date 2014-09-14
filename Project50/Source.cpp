#include<iostream>
#include<vector>
#include<time.h>
using namespace std;

void createPrimeChart(vector<int> &primeChart, int maxN){
	primeChart[0] = 2;
	int numPrime = 1, ix;
	for (int n=3; n<=maxN; n=n+2){
		int upbound = static_cast<int>(sqrt(n));
		for (ix = 0; primeChart[ix]<=upbound; ++ix)
			if(n%primeChart[ix]==0)
				break;
		if(primeChart[ix]>upbound)
			primeChart[numPrime++]=n;
	}
	primeChart.resize(numPrime);
}

bool isPrime(vector<int> &primeChart, int ele, int &endIx){
	int startIx=0, midIx = (startIx+endIx)/2;
	do{
		if (primeChart[midIx]>ele)
			endIx = midIx;
		else if (primeChart[midIx]<ele)
			startIx = midIx;
		else
			return true;
		midIx = (startIx+endIx)/2;
	}while(midIx>startIx);
	return false;
}

void print(const vector<int> &vec){
	for (int i=0; i!=vec.size(); ++i)
		cout<<vec[i]<<" ";
	cout<<endl;
}

void print(const vector<vector<int>> &sqMatrix){
	for (int i=0; i!=sqMatrix.size(); ++i){
		for (int j=0; j!=sqMatrix.size(); ++j)
			cout<<sqMatrix[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
}

void calConsecutiveNum(int startIx,int endIx,const int & curPrime, int &maxConsecNum, int &thatPrime){
	int consec = endIx-startIx+1;
	if (consec>maxConsecNum){
		maxConsecNum = consec;
		thatPrime = curPrime;
		cout<<curPrime<<" is the sum of "<<maxConsecNum<<" consecutive numbers"<<endl;
	}
}


bool isPrime(const int n, const vector<int> &primeChart){
	int upbound = static_cast<int>(sqrt(n));
	for (int i=0; primeChart[i]<=upbound; ++i)
		if(n%primeChart[i]==0)
			return false;
	return true;
}

bool bsearch(int n, vector<int> primeChart){
	int startIx = 0, endIx = primeChart.size()-1, midIx = (startIx+endIx)/2;
	do{
		if(primeChart[midIx]> n)
			endIx = midIx;
		else if(primeChart[midIx]<n)
			startIx = midIx;
		else
			return true;
		midIx = (startIx+endIx)/2;
	}while(midIx>startIx);
	return false;
}

int main(){
	int maxN =1000000;
	vector<int> primeChart(maxN);
	createPrimeChart(primeChart, maxN);

	int maxConsecNum=0, thatPrime=0;
	clock_t t=clock();
	int primeN = primeChart.size();
	
	vector<int> primeSum(primeN, 0);
	primeSum[0] = primeChart[0];
	for(int i = 1; i!=primeN; ++i)
		primeSum[i] = primeSum[i-1]+primeChart[i];

	cout<<bsearch(41, primeChart)<<endl;
	int sum = 0;
	for (int i=0; i!=primeN; ++i){
		sum = primeChart[i];
		 for(int j = i+1;j !=primeN; j++){
         sum += primeChart[j];
		 if (sum>maxN)
			 break;
		 if (isPrime(sum, primeChart))
		 //if (bsearch(sum, primeChart))
			 calConsecutiveNum(i, j, sum, maxConsecNum, thatPrime);
		 }
	}
	
	/*
	for (int ix=0; ix!=primeChart.size(); ++ix){
		int curPrime = primeChart[ix];
		int startIx=0, endIx=0;
		int sum=0;
		while (endIx <= ix){
			while (sum>curPrime && startIx <= endIx)
				sum -= primeChart[startIx++];
			if (sum==curPrime){
				calConsecutiveNum(startIx, endIx, curPrime, maxConsecNum, thatPrime);
				break;
			}
			else
				sum +=primeChart[endIx++];
		}
	}
	*/
	cout<<thatPrime<<" is the sum of "<<maxConsecNum<<", maximum consecutive numbers of primes"<<endl;
	printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
	cin.get();
	return 0;
}