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

int factorialsum(int n, const vector<int> &factorial){
	int factorialSum = 0;
	int digitN;
	while(n){
		digitN = n%10;
		factorialSum += factorial[digitN]; 
		n/=10;
	}
	return factorialSum;
}

int appearBefore(int n,vector<int> &vec){
	int ix = 0;
	while(ix!=vec.size()){
		if(vec[ix]!=n)
			++ix;
		else
			break;
	}
	return ix==vec.size()?-1: ix;
}

int main(){
	clock_t t1=clock();
	int maxN = 1000000;

	vector<int> factorial(10, 1);
	for (int i=2; i!=factorial.size(); ++i){
		factorial[i] = i * factorial[i-1];
	}

	int maxSize = 2177280; //6*factorial(9)
	vector<int> cyclicLen(maxSize+1, 0);
	for (int n=0; n<=maxN; ++n){
		//print(cyclicLen);
		if(cyclicLen[n]==0){
			int nextN = factorialsum(n, factorial);
			if(cyclicLen[nextN]==0){
				vector<int> factorialChain;
			    factorialChain.push_back(n);
				//print(factorialChain);
				int idx = appearBefore(nextN, factorialChain);
				while(idx == -1){
					factorialChain.push_back(nextN);
					//print(factorialChain);
					nextN = factorialsum(nextN, factorial);
					idx = appearBefore(nextN, factorialChain);
				}
				int thisCyclicLen = factorialChain.size()-idx;
				for(int i=idx; i!=factorialChain.size(); ++i){
					cyclicLen[factorialChain[i]] = thisCyclicLen;
				}
				for(int i=idx-1; i>=0; --i){
					cyclicLen[factorialChain[i]] = ++thisCyclicLen;
				}
			}else{
				cyclicLen[n] = cyclicLen[nextN]+1;
			}
		}
	}

	int targetCyclicN = 60;
	int count = 0;
	for(int n=0; n<=maxN; ++n){
		if(cyclicLen[n]==targetCyclicN)
			 ++count; 
	}

	cout<<"There're "<<count<<" numbers with cyclic length of "<<targetCyclicN<<endl;
	clock_t t2=clock();
	cout<<"Total time used "<<(double(t2)-double(t1))/CLOCKS_PER_SEC<<"s"<<endl;
	cin.get();
	return 0;
}