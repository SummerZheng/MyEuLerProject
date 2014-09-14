#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
#include<math.h>
#include<time.h>

using namespace std;

void generatePrimeArr(vector<int> &primeVec, int maxN){
	primeVec[0] = 2;
	int ct=1;
	for(int n=3; n<=maxN; n++){
		int facLimit = static_cast<int>(sqrt(n));
		int i;
		for(i=0; primeVec[i]<=facLimit;i++){
			if(n%primeVec[i]==0)
				break;
		}
		if(primeVec[i]>facLimit){
			primeVec[ct++] = n;
		}
	}
	primeVec.resize(ct);
}

//find the last idx which is smaller or equal to maxprime4th
int myFind(int &num2find,vector<int> &primeVec,int startIdx, int endIdx){
	if(endIdx==startIdx)
		return startIdx;
	else if(endIdx==startIdx+1)
		return primeVec[endIdx]<=num2find?endIdx:startIdx;
	int midIdx = (startIdx+endIdx)/2;
	if(primeVec[midIdx]>num2find)
		endIdx = midIdx;
	else
		startIdx = midIdx;	
	return myFind(num2find, primeVec, startIdx, endIdx);
}

int main(){
	int upLimit = 50000000;
	int maxN = static_cast<int>(sqrt(upLimit));
	vector<int> primeVec(maxN);
	set<int> numSet;
	generatePrimeArr(primeVec, maxN);

	clock_t t1 = clock();
	
	vector<int> sqVec(maxN);
	vector<int> cbVec(maxN);
	vector<int> Vec4thpow(maxN);
	for(int i=0; i!=primeVec.size(); i++){
		sqVec[i] = primeVec[i]*primeVec[i];
		cbVec[i] = sqVec[i]*primeVec[i];
		Vec4thpow[i] = cbVec[i]*primeVec[i];
	}

	int ct=0;
	for(int i2 = 0; i2!=primeVec.size(); i2++){
		for(int i3 = 0; i3!=primeVec.size(); i3++){
			int n1 = sqVec[i2]+cbVec[i3];
			if(n1>upLimit)
				break;
			for(int i4 = 0; i4!=primeVec.size(); i4++){
				int n= n1+Vec4thpow[i4];
				if(n>upLimit)
					break;
				else if(numSet.count(n)==0){
					numSet.insert(n);
					ct++;
				}
			}
		}
	}
	/*
	int maxPrime4th = static_cast<int>(sqrt(sqrt(upLimit)));	
	int maxIdx4th = myFind(maxPrime4th, primeVec, 0, primeVec.size()-1);
	for(int p4idx = maxIdx4th; p4idx>=0; p4idx--){
		int add4 = primeVec[p4idx]*primeVec[p4idx]*primeVec[p4idx]*primeVec[p4idx];
		int leftN1 = upLimit-add4;

		int maxPrime3rd = static_cast<int>(pow(leftN1, 1.0/3.0));
		int maxIdx3rd = myFind(maxPrime3rd, primeVec, 0, primeVec.size()-1);
		//cout<<"prime4 "<<primeVec[p4idx]<<endl;
		//cout<<"prime3 "<<maxPrime3rd<<", number found "<<primeVec[maxIdx3rd]<<", next up "<<primeVec[maxIdx3rd+1]<<endl;
		for(int p3idx = maxIdx3rd; p3idx>=0; p3idx--){
			int add3 = primeVec[p3idx]*primeVec[p3idx]*primeVec[p3idx];
			int leftN2 = leftN1 - add3;
			int maxPrime2nd = static_cast<int>(sqrt(leftN2));
			int maxIdx2nd = myFind(maxPrime2nd, primeVec, 0, primeVec.size()-1);
			for(int p2idx = maxIdx2nd; p2idx>=0; p2idx--){
				int add2 = primeVec[p2idx]*primeVec[p2idx];
				//cout<<"prime2 "<<maxPrime2nd<<", number found "<<primeVec[maxIdx2nd]<<", next up "<<primeVec[maxIdx2nd+1]<<endl;
				int num = add4+add3+add2;
				if(numSet.count(num)==0){
					ct ++;
					numSet.insert(num);
				}
			}
		}
	}
	*/
	cout<<ct<<endl;
	clock_t t2 = clock();
	cout<<(t2-t1)/CLOCKS_PER_SEC<<"s used."<<endl;
	cin.get();
	return 0;
}