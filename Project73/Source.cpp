#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

template <typename T>
void print(vector<T> &vec){
	for(int i=0; i!=vec.size(); ++i)
		cout<<vec[i]<<" ";
	cout<<endl;
}

void generatePrimeChart(vector<int> &primeChart, int primeUb){
	primeChart[0]=2;
	int primeNum = 1;
	for(int n=3; n<= primeUb; ++n){
		int factorUb = static_cast<int>(sqrt(n));
		int idx = 0;
		while(primeChart[idx]<= factorUb){
			if(n%primeChart[idx] == 0)
				break;
			else
				++idx;
		}
		if(primeChart[idx]>factorUb){
			primeChart[primeNum++] = n;
		}
	}
	primeChart.resize(primeNum);
}

void factorize(int n, vector<int> &factors, const vector<int> &primeChart){
	int factorNum = 0, factor;
	int factorUb = static_cast<int>(sqrt(n));
	for(int i=0; i!=primeChart.size() && primeChart[i]<=factorUb; ++i){
		if(n%primeChart[i]==0){
			factor = primeChart[i];
			factors[factorNum++] = factor;
			while(n%factor == 0)
				n /= factor;
		}
	}
	if(n!=1)
		factors[factorNum++]  = n;
}

int main(){
	clock_t t1 = clock();
	int maxd = 12000;
	int primeUb = static_cast<int>(sqrt(maxd));
	vector<int> primeChart(primeUb);
	generatePrimeChart(primeChart, primeUb);
	//print(primeChart);

	vector<int> factors(6), zeroVec(6, 0);
	int setNum=0, lowerN, upperN;
	for (int d=2; d<=maxd; ++d){
		//cout<<d<<endl;
		factors = zeroVec;
		factorize(d, factors, primeChart);
		//print(factors);
		lowerN = d/3+1;
		upperN = d%2==0?d/2-1:d/2;
		for(int n=lowerN; n<=upperN; ++n){
			int i=0;
			while(factors[i]!=0){
				if(n%factors[i]==0)
					break;
				else 
					++i;
			}
			if(factors[i]==0)
				++setNum;
		}
	}
	cout<<setNum<<endl;
	clock_t t2 = clock();
	cout<<"Total time used is "<<((double)t2 - (double)t1)/CLOCKS_PER_SEC<<"s"<<endl;
	cin.get();
	return 0;
}