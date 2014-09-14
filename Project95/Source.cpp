#include<iostream>
#include<vector>
#include<set>
#include<time.h>

using namespace std;

template <typename T>
void print(vector<T> &vec){
	for(int i=0; i!=vec.size(); ++i)
		cout<<vec[i]<<" ";
	cout<<endl;
}

void generatePrime(vector<int> &primeN, int maxN){
	primeN[0] = 2;
	int ct=1;
	for(int n=3; n<=maxN; n++){
		int fmax = (int)sqrt(n);
		int ix;
		for(ix=0; primeN[ix]<=fmax; ix++){
			if(n%primeN[ix]==0)
				break;
		}
		if(primeN[ix]>fmax)
			primeN[ct++] = n;
	}
	primeN.resize(ct);
}

int nextN(int n, vector<int> &primeN){
	if (n==1)
		return n;
	int nori = n;
	vector<int> factor(7, 1);
	vector<int> expon(7, 0);
	int fct=0;
	while(n!=1){
		for(int ix=0; ix!=primeN.size(); ix++){
			if(n%primeN[ix]==0){
				int f = primeN[ix];
				factor[fct] = f;
				while(n%f==0){
					expon[fct]++;
					n/=f;
				}
				fct++;
			}
		}
	}
	int factorSum = 1;
	for(int i=0; i!=fct; i++){
		int fSum=0, f=1;
		for(int j=0; j<=expon[i]; j++){
			fSum += f;
			f*=factor[i];
		}
		factorSum*=fSum;
	}
	//print(factor);
	//print(expon);
	return factorSum-nori;
}

bool firstAppear(vector<int> &trace,int curI){
	for(int i=0; i!=trace.size(); i++)
		if(trace[i]==curI)
			return false;
	return true;
}

int find1stAppear(vector<int> &trace,int curI){
	for(int i=0; i!=trace.size(); i++)
		if(trace[i]==curI)
			return i;
	return -1;
}

void initiateFactorSum(vector<int> &vec){
	int maxN = vec.size()-1;
	for(int i=1; i<maxN; i++){
		for(int j=2*i; j<=maxN; j+=i){
			vec[j] += i;
		}
	}
}

int main(){
	clock_t t1= clock();
	int maxN = 1000000;

	vector<int> factorSum(maxN+1, 0);
	initiateFactorSum(factorSum);
	//print(factorSum);
	int maxL = 0;
	//vector<int> primeN(maxN, 0);
	//generatePrime(primeN, maxN);
	/*
	cout<<nextN(12496, primeN)<<endl;
	cout<<nextN(14288, primeN)<<endl;
	cout<<nextN(15472, primeN)<<endl;
	cout<<nextN(14536, primeN)<<endl;
	cout<<nextN(14264, primeN)<<endl;
	*/
	vector<int> recordArr(maxN+1, 0);
	for(int i=1; i<=maxN; i++){
		if(recordArr[i])
			continue;
		else{
			int curI;
			vector<int> trace;
			trace.push_back(i);
			for(curI = factorSum[i]; curI<=maxN && !recordArr[curI] && firstAppear(trace, curI); curI = factorSum[curI]){
				//cout<<curI<<endl;
				trace.push_back(curI);
			}
			if(curI>maxN || recordArr[curI]==-1){
				for(int ix=0; ix!=trace.size(); ix++)
					recordArr[trace[ix]] = -1;
			}else{
				int loopSz, idx1st=trace.size(), ix;
				if(recordArr[curI])
					loopSz = recordArr[curI];
				else{
					idx1st = find1stAppear(trace, curI);
					loopSz = trace.size()-idx1st;
				}
				for(ix=trace.size()-1; ix>=idx1st; ix--)
					recordArr[trace[ix]] = loopSz;
				for(ix=idx1st-1; ix>=0; ix--)
					recordArr[trace[ix]] = -1;
				if(loopSz>maxL){
					maxL = loopSz;
					for(int ix=0; ix!=trace.size(); ix++)
						cout<<trace[ix]<<" ";
					cout<<endl;
					if(idx1st==trace.size())
						cout<<i<<" generate a chain of length "<<maxL<<endl;
					else
						cout<<trace[idx1st]<<" generate a chain of length "<<maxL<<endl;
				}
			}
		}
	}
	clock_t t2= clock();
	cout<<"total time used "<<(t2-t1)/CLOCKS_PER_SEC<<"s"<<endl;
	cin.get();
	return 0;
}