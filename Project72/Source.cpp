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

long long phiNcalculator(int n, const vector<int> &primeChart){
	long long phiN = n;
	int ix = 0, primefactor;
	while(n!=1){
		if (n%primeChart[ix]==0){
			primefactor = primeChart[ix];
			phiN = phiN-phiN/primefactor;
			while(n%primefactor==0){
				n/=primefactor;
			}
		}else if(++ix == primeChart.size()){
			break;
		}
	}
	return (n==1)?phiN:phiN-phiN/n;
}

int main(){
	clock_t t1 = clock();
	int maxd = 1000000;
	int primeUb = static_cast<int>(sqrt(maxd));
	vector<int> primeChart(primeUb);
	generatePrimeChart(primeChart, primeUb);
	//print(primeChart);

	long long phid, setNum=0;
	for (int d=2; d<=maxd; ++d){
		phid = phiNcalculator(d, primeChart);
		setNum += phid;
	}
	cout<<setNum<<endl;
	clock_t t2 = clock();
	cout<<"Total time used is "<<((double)t2 - (double)t1)/CLOCKS_PER_SEC<<"s"<<endl;
	cin.get();
	return 0;
}