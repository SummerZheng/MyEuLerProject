#include <iostream>
#include <vector>
using namespace std;

bool isPrime(int curNum, vector<int> &prime_ct){
	int upBound = sqrt(curNum);
	for (int i=0; prime_ct[i]<=upBound; ++i){
		if (curNum%prime_ct[i]==0)
			return false;
	}
	return true;
}

int main(){
	int MaxNum = 2000000;
	int nChart = sqrt(MaxNum);
	
	vector<int> prime_chart(nChart);
	prime_chart[0] = 2;
	int primeCt = 1, curNum =3;
	long long sum = 2;
	while(primeCt!=nChart){
		if (isPrime(curNum, prime_chart)){
			prime_chart[primeCt++]=curNum;
			sum+=curNum;
			curNum+=2;
		}
		else curNum+=2;
	}
	
	while(curNum<=MaxNum){
		if (isPrime(curNum, prime_chart)){
			sum+=curNum;
			curNum+=2;
		}
		else curNum+=2;
	}
	
	cout<<prime_chart[nChart-1]<<endl;
	cout<<sum<<endl;
	cin.get();
	return 0;
}
