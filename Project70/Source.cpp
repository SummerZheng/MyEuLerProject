#include<iostream>
#include<vector>
#include<string>
#include <algorithm> 
#include<time.h>
using namespace std;

#define maxPhiN 2; 

template <typename T>
void print(vector<T> vec){
	for(int i=0; i!=vec.size(); ++i)
		cout<<vec[i]<<" ";
	cout<<endl;
}

void generatePrimeChart(vector<int> &primeChart, int maxN){
	primeChart[0]=2;
	int primeCount = 1;
	for (int n=3; n<=maxN; ++n){
		int upbound = static_cast<int>(sqrt(n));
		int i=0;
		while(primeChart[i]<=upbound){
			if (n%primeChart[i]==0)
				break;
			else
				++i;
		}
		if (primeChart[i]>upbound)
			primeChart[primeCount++] = n;
	}
	primeChart.resize(primeCount);
}

int phiNcalculation_prescreen(int n,const vector<int> &primeChart){
	int phiN = n;
	unsigned primeChartIx = 0;
	while(n!=1){
		int factor = primeChart[primeChartIx];
		if(n%factor==0){
			// if n has prime factor <20, cannot be smallest phiN
			// return maxPhiN as a marker to be excluded from prescreen
			if (primeChartIx<10){
				return  n/2;
			}else{
				phiN = phiN-phiN/factor;
				while(n%factor==0){
					n /= factor;
				}
			}
		}else{
			if (++primeChartIx == primeChart.size())
				break;
		}
	}
	// if n is a large prime, phiN = n-1, can not be a permutation
	// return maxPhiN as a marker to be excluded from prescreen
	if(phiN==n){
		return n/2;
	}else if(n!=1){
		phiN = phiN-phiN/n;
	}
	return phiN;
}

bool isPermutation(int a, int b){
	string strA = to_string(a), strB =to_string(b);
	if (strA.size()!=strB.size())
		return false;
	else{
		sort(strA.begin(), strA.end());
		sort(strB.begin(), strB.end());
		if(strA == strB)
			return true;
		else 
			return false;
	}
}

int main(){
	clock_t t1=clock();
	int maxN = 10000000;
	int primeChartSize = static_cast<int>(sqrt(maxN)+1);
	vector<int> primeChart(primeChartSize);
	generatePrimeChart(primeChart, primeChartSize);
	
	double minTotient =  maxPhiN;	
	int minTotientN = 1;
	vector<bool> checkList(maxN, true);
	
	for(int n=maxN/10; n<=maxN; ++n){
		if(checkList[n-1] == true){
			//return phiN = -1 if n and phiN contain different number of digits
			//i.e. no chance of being permutation of each other
			int phiN = phiNcalculation_prescreen(n, primeChart);
			//cout<<"phiN of "<<n<< " is "<<phiN<<endl;

			if((double) n/ phiN  < minTotient){
				if(isPermutation(phiN, n)){
					minTotient = (double)n / phiN;
					minTotientN = n;
					//cout<<"phiN of "<<n<< " is "<<phiN<<", and produce minTotient "<<minTotient<<endl;
					int multiplier = n;
					while(multiplier <= maxN){
						checkList[multiplier-1] = false;
						multiplier += n;
					}
				}
			}else{
				int multiplier = n;
				while(multiplier <= maxN){
					checkList[multiplier-1] = false;
					multiplier += n;
				}
			}
		}
	}
	cout<<"n = "<<minTotientN<<" produce minTotient "<<minTotient<<endl;
	clock_t t2=clock();
	cout<<"Total time used "<<(double(t2)-double(t1))/CLOCKS_PER_SEC<<"s"<<endl;
	cin.get();
	return 0;
}