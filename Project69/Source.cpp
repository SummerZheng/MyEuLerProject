#include<iostream>
#include<vector>
#include<time.h>
using namespace std;

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

int phiNcalculation(int n,const vector<int> &primeChart){
	int phiN = n;
	int primeChartIx = 0;
	while(n!=1){
		int factor = primeChart[primeChartIx];
		if(n%factor==0){
			phiN = phiN-phiN/factor;
			while(n%factor==0){
				n /= factor;
			}
		}else{
			primeChartIx++;
		}
	}
	return phiN;
}

void factorize(int n, vector<int> &primeFactor,vector<int> &exponent, const vector<int> &primeChart){
	int factorNum = 0;
	int primeChartIx = 0;
	while(n!=1){
		int factor = primeChart[primeChartIx];
		if(n%factor==0){
			primeFactor[factorNum] = factor;
			while(n%factor==0){
				n /= factor;
				exponent[factorNum]++;
			}
			factorNum++;
		}else{
			primeChartIx++;
		}
	}
	primeFactor.resize(factorNum);
	exponent.resize(factorNum);
}

int main(){
	clock_t t1=clock();
	int maxN = 1000000;
	vector<int> primeChart(maxN);
	generatePrimeChart(primeChart, maxN);
	double maxTotient = 0;
	
	int maxTotientN = 1, i=0;
	while(true){
		int temp = maxTotientN * primeChart[i++];
		if(temp>maxN)
			break;
		else
			maxTotientN = temp;
	}
	cout<<maxTotientN<<endl;
	/*
	
	//vector<bool> checkList(maxN, true);
	for(int n=2; n<=maxN; ++n){
	//for(int n=maxN; n>=2; --n){
		//if(checkList[n-1] == true){			
			vector<int> primeFactor(7);
			vector<int> exponent(7, 0);

			int phiN = phiNcalculation(n, primeChart);
			/*
			factorize(n, primeFactor, exponent, primeChart);
			//print(primeFactor);
			//print(exponent);
			//int factorNum = 1;
			int phiN = n;
			for (int i=0; i!=exponent.size(); ++i){
				//factorNum *= exponent[i]+1;
				phiN = phiN-phiN/primeFactor[i]; 
			}
			
			if((double)n/ phiN  > maxTotient){
				maxTotient = (double)n/ phiN;
				cout<<"max Totient number = "<<maxTotient<<", at n = "<<n<<endl;
			}

			/*
			for(int i=0; i<factorNum-1; ++i){
				int factor = 1, Ix = 0, remainder = i;
				while(remainder!=0){
					int exp = remainder%(exponent[Ix]+1);
					int f = primeFactor[Ix];
					remainder /= (exponent[Ix]+1);
					//cout<<remainder<<" "<<exp<<" "<<f<<endl;
					while(exp){
						factor *= f;
						exp--;
					}				
					Ix++;
				}
				//cout<<factor<<endl;
				checkList[factor-1] = false;
			}
			*/
			
			
			/*
			vector<bool> primeToN(n-1, true);
			for (int idx=0; idx!=primeFactor.size(); ++idx){
				int factor=primeFactor[idx], multiplier=factor;
					while (multiplier<n){
						primeToN[multiplier-1] = false;
						multiplier += factor;
					}
			}
			//print(primeToN);
			int countN=0;
			for(int ix=0; ix!=n-1; ++ix){
				if(primeToN[ix] == true)
					++countN;
			}
			//cout<<n<<" has relative prime number "<<countN<<endl;
			if((double)n/(double)countN  > maxTotient){
				maxTotient = (double)n/(double)countN;
				cout<<"max Totient number = "<<maxTotient<<", at n = "<<n<<endl;
			}
			*/	
	//}
	//	}
	
	clock_t t2=clock();
	cout<<"Total time used "<<(double(t2)-double(t1))/CLOCKS_PER_SEC<<"s"<<endl;
	cin.get();
	return 0;
}