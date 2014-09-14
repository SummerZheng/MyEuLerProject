#include<iostream>
#include<vector>
using namespace std;
#pragma once

class bigNum
{
private:
	static const int defaultSZ = 50;
	vector<int> numVec;
	int digitN;
public:
	bigNum(void);
	~bigNum(void);
	bigNum(const bigNum &bn):numVec(bn.numVec), digitN(bn.numVec.size()){}
	bigNum(int n, int N=defaultSZ):numVec(N, 0){
		int ix = numVec.size();
		while(n){
			numVec[--ix]=n%10;
			n/=10;
			++digitN;
		}
	}

	bigNum& operator = (const bigNum &rhs){
		numVec = rhs.numVec;
		digitN = rhs.digitN;
		return *this;
	}

	bigNum& operator*=(const int &n){
		bigNum ori(*this);
		*this = bigNum(0);
		int nthDig=0, ncopy=n;
		int len = numVec.size()-1;
		while(ncopy){
			++nthDig;
			bigNum digitMul(0);
			int jinwei=0;
			int multiplier = ncopy%10;
			for (int ix=len; ix>=0; --ix){
				digitMul.numVec[ix] = ori.numVec[ix]*multiplier+jinwei;
				jinwei = digitMul.numVec[ix]/10;
				digitMul.numVec[ix]%=10;
			}
			jinwei = 0;
			for (int ix=len+1-nthDig; ix>=0; --ix){
				numVec[ix] += digitMul.numVec[ix+nthDig-1]+jinwei;
				jinwei = numVec[ix]/10;
				numVec[ix]%=10;
			}
			ncopy/=10;
		}
		return *this;
	}

	bigNum& operator+=(const bigNum &rhs){
		int jinwei = 0;
		for (int ix=numVec.size()-1; ix>=0; --ix){
			numVec[ix] = numVec[ix] + rhs.numVec[ix]+jinwei;
			jinwei = numVec[ix]/10;
			numVec[ix]%=10;
		}
		return *this;
	}



	bigNum bigNumReverse(){
		bigNum reversed(*this);
		int startIx=-1;
		while(numVec[++startIx]==0);
		int bigNumLen = numVec.size()-startIx;
		int delta = 0; 
		for ( ; delta!=bigNumLen; ++delta)
			reversed.numVec[startIx+delta] = numVec[numVec.size()-1-delta];
		return reversed;
	}
	
	int bigNumdigitSum(){
		int sum=0;
		for (int ix=0; ix!=numVec.size(); ++ix)
			sum+=numVec[ix];
		return sum;
	}

	friend ostream &operator<<(ostream &os, const bigNum &bgNum){
		int ix=-1;
		while(bgNum.numVec[++ix]==0);
		while(ix!=bgNum.numVec.size())
			cout<<bgNum.numVec[ix++]<<" ";
		return os;
	}

	bool ispalindrome(){
		int startIx=-1;
		while(numVec[++startIx]==0);
		int bigNumLen = numVec.size()-startIx;
		int delta = 0; 
		for ( ; delta!=bigNumLen/2; ++delta)
			if (numVec[startIx+delta]!= numVec[numVec.size()-1-delta])
				break;
		if (delta==bigNumLen/2)
			return true;
		else return false;
	}
};



