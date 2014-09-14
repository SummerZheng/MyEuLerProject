#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <time.h>

using namespace std;

typedef long long ll;
typedef set<int>::iterator setIter;	
typedef map<int, set<int>>::iterator mapIter;
typedef map<int, set<int>> myMap;

#define maxNsq 10000
#define maxN maxNsq*maxNsq

void generatePrimeChart(set<int> &primeChart){
	primeChart.insert(2);
	for(int n=3; n<=maxNsq; ++n){
		int upbound = static_cast<int>(sqrt(n));
		setIter ix;
		for(ix=primeChart.begin(); *ix<=upbound; ++ix){
			if(n%*ix==0)
				break;
		}
		if(*ix>upbound)
			primeChart.insert(n);
	}
}

bool isPrime(ll n,const set<int> &primeChart){
	if (n<*--primeChart.end())
		return (primeChart.find(static_cast<int>(n))!=primeChart.end())?true:false;
	int upbound = static_cast<int>(sqrt(n));
	if (upbound>maxNsq)
		cerr<<"factorization of"<<n<<" Need to expand prime list"<<endl;
	setIter ix;
	for(ix=primeChart.begin(); ix!=primeChart.end() && *ix<=upbound; ++ix){
		if(n%*ix==0)
			break;
	}
	if(ix==primeChart.end() || *ix>upbound)
		return true;
	else
		return false;
}

ll concat(const int n1, const int n2){
	string str1= to_string(n1), str2 = to_string(n2);
	string str=str1+str2;
	return stoll(str);
}

bool isoneCompatible(const int &n, const set<int> &compatibles){
	return (compatibles.find(n)!=compatibles.end())?true:false;
}

bool ispreviousCompatible(const int &prime2add, const int curSize, myMap &compatibles,const vector<int> &primeSets){
	if (curSize ==1)
		return true;
	else{
		int j;
		for (j=0; j<=curSize-2; j++){
			if (!isoneCompatible(prime2add, compatibles[primeSets[j]]))
				break;
			}
		return (j>curSize-2)?true:false;
	}
}

bool buildCompatibles(const int curPrime, myMap &compatibles,const set<int> &primeChart){
	if (curPrime==2 || curPrime==5)
		return false;
	if (compatibles.find(curPrime)!=compatibles.end())
		return true;
	//else  compatibles.empty() || (!compatibles.empty() && compatibles.find(curPrime)==compatibles.end())
	setIter j, startIx=++primeChart.find(curPrime);
	set<int> cptPrimes;
	int prime2add;
	for (j=startIx; j!=primeChart.end(); ++j){
		prime2add = *j;
		ll concat1 = concat(prime2add, curPrime);
		ll concat2 = concat(curPrime, prime2add);
		if (concat1>maxN ||concat2>maxN)
			break;
		if(isPrime(concat1, primeChart) && isPrime(concat2, primeChart))
			cptPrimes.insert(prime2add);
	}
	if (!cptPrimes.empty()){
		compatibles.insert(make_pair(curPrime, cptPrimes));
		return true;
	}
	else{
		//cerr<<"No primes are compatible upong concatenation with "<<curPrime<<endl;
		return false;
	}
}

void findNextMinPrime(int &minPrime,const set<int> &primeChart){
	setIter i=++primeChart.find(minPrime);
	if (*i==5)
		++i;
	minPrime = *i;
}

bool addNext(int &curSize, myMap &compatibles, vector<int> &primeSets, const set<int> &primeChart, setIter startIx){
	int curPrime = primeSets[curSize-1];
	setIter i;	
	setIter endIx = compatibles[curPrime].end();
	int prime2add;
	for (i = startIx; i!= endIx; ++i){
		prime2add = *i;
		if(ispreviousCompatible(prime2add, curSize, compatibles, primeSets))
			break;
	}
	if (i!=endIx){ 
		primeSets[curSize++] = prime2add;
		return true;
	}
	else //i==endIx
		return false;
}

void replaceLast(int &curSize,myMap &compatibles,vector<int> &primeSets, const set<int> &primeChart){
	if (curSize==1){
		findNextMinPrime(primeSets[0], primeChart);
		return;
	}
	--curSize;
	setIter startIx = compatibles[primeSets[curSize-1]].find(primeSets[curSize]);
	if(addNext(curSize, compatibles, primeSets, primeChart, ++startIx))
		;
	else
		replaceLast(curSize, compatibles, primeSets, primeChart);
}


int main(){
	clock_t t1=clock();
	set<int> primeChart;
	generatePrimeChart(primeChart);
	
	myMap compatibles;

	int setSize = 5, curSize=0;
	vector<int> primeSets(setSize, 0);
	
	setIter startIter = primeChart.begin();//2 is not concatenate compatible with anything
	primeSets[curSize++] = *startIter;
	buildCompatibles(*startIter, compatibles, primeChart);

	do{
		int curPrime = primeSets[curSize-1];
		if (buildCompatibles(curPrime, compatibles, primeChart)){
			setIter startIx = compatibles[curPrime].begin();
			if (addNext(curSize, compatibles, primeSets, primeChart, startIx));
			else
				replaceLast(curSize, compatibles, primeSets, primeChart);
		}
		else
			replaceLast(curSize, compatibles, primeSets, primeChart);
	}while(curSize!=setSize);
	
	int sum=0;
	for(int i=0; i!=setSize; ++i){
		cout<<primeSets[i]<<" ";
		sum+=primeSets[i];
	}
	cout<<endl;
	cout<<"sum is "<<sum<<endl;
	clock_t t2=clock();
	cout<<"Total time used is "<<(double(t2)-double(t1))/CLOCKS_PER_SEC<<" seconds"<<endl;
	cin.get();
	return 0;
}