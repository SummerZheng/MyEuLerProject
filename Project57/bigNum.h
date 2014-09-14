#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
#pragma once

class bigNum
{
private:
	vector<int> numVec;
public:
	bigNum(void):numVec(vector<int>()){}
	~bigNum(void){}
	bigNum(const bigNum &bn):numVec(bn.numVec){}
	bigNum(vector<int> &vec):numVec(vec){}
	bigNum(int n):numVec(vector<int>()){
		if(n==0)
			numVec.push_back(0);
		while(n){
			numVec.push_back(n%10);
			n/=10;
		}
		reverse(numVec.begin(), numVec.end());
	}

	bigNum& operator = (const bigNum &rhs){
		numVec=rhs.numVec;
		return *this;
	}

	int bigNumdigitSum(){
		int sum=0;
		for (int ix=0; ix!=numVec.size(); ++ix)
			sum+=numVec[ix];
		return sum;
	}

	unsigned getDigitNum() const{
		return numVec.size();
	}

	string bgnum2Str() const{
		string str;
		for (int ix=0; ix!=getDigitNum(); ++ix)
			str.append(to_string(numVec[ix]));
		return str;
	}

	bigNum& push_front(const int n){
		reverse(numVec.begin(), numVec.end());
		numVec.push_back(n);
		reverse(numVec.begin(), numVec.end());
		return *this;
	}

	bool operator==(const bigNum &cp) const{
		string str1 = bgnum2Str();
		string str2 = cp.bgnum2Str();
		return (str1==str2);
	}

	bool operator==(const int &n) const{
		bigNum bg(n);
		return (*this==bg);
	}

	bool operator!=(const int &n) const{
		bigNum bg(n);
		return !(*this==bg);
	}
	
	bool operator > (const bigNum &rhs) const{
		if (numVec.size()>rhs.getDigitNum())
			return true;
		else if (numVec.size()<rhs.getDigitNum())
			return false;
		else{
			for(int ix=0; ix!=numVec.size(); ++ix){
				if (numVec[ix]==rhs.numVec[ix])
					continue;
				else if (numVec[ix]>rhs.numVec[ix])
					return true;
				else
					return false;
			}
			return false;
		}
	}

	bool operator >= (const bigNum &rhs) const{
		return ((*this>rhs) || (*this==rhs));
	}

	bool operator <= (const bigNum &rhs) const{
		return !(*this>rhs);
	}

	bool operator < (const bigNum &rhs) const{
		return !(*this>rhs || *this==rhs);
	}

	friend bigNum operator+(const bigNum &lhs, const bigNum &rhs){
		bigNum sumBN;
		int iter1 = lhs.getDigitNum(), iter2 = rhs.getDigitNum();
		int jinwei =0, temp = 0;
		while(iter1 != 0 && iter2 != 0){
			temp = lhs.numVec[--iter1]+rhs.numVec[--iter2]+jinwei;
			sumBN.numVec.push_back(temp%10);
			jinwei =temp/10;
		}
		if(iter1==0){
			while(iter2!=0){
			temp = rhs.numVec[--iter2]+jinwei;
			sumBN.numVec.push_back(temp%10);
			jinwei =temp/10;
			}
		}
		if(iter2==0){
			while(iter1!=0){
			temp = lhs.numVec[--iter1]+jinwei;
			sumBN.numVec.push_back(temp%10);
			jinwei =temp/10;
			}
		}
		while(jinwei){
			sumBN.numVec.push_back(jinwei%10);
			jinwei/=10;
		}
		reverse(sumBN.numVec.begin(), sumBN.numVec.end());
		return sumBN;
	}

	bigNum& operator+=(const bigNum &rhs){
		*this = *this+rhs;
		return *this;
	}

	bigNum& trimHeadingZero(){
		reverse(numVec.begin(), numVec.end());
		int ix=numVec.size();
		while(numVec[--ix]==0)
			numVec.pop_back();
		reverse(numVec.begin(), numVec.end());
		return *this;
	}

	bigNum& operator-=(const bigNum &rhs){
		//assume diff>=0, i.e. numVec.size()>=rhs.getDigitNum();
		int jiewei = 0;
		int deltaIter = numVec.size()-rhs.getDigitNum();
		for (int i=numVec.size(); i!=0; --i){
			int subtractor;
			if((i-deltaIter)>=1)
				subtractor = rhs.numVec[i-1-deltaIter];
			else
				subtractor=0;
			if ((numVec[i-1]-jiewei) < subtractor){
				numVec[i-1] -= (subtractor+jiewei-10);
				jiewei = 1;
			}
			else{
				numVec[i-1] -= (subtractor+jiewei);
				jiewei = 0;
			}
		}
		trimHeadingZero();
		return *this;
	}

	friend bigNum operator-(const bigNum &lhs, const bigNum &rhs){
		bigNum diff(lhs);
		diff-=rhs;
		return diff;
	}

	bigNum& operator*=(const bigNum &rhs){
		bigNum totProduct(0);
		for(int i=rhs.getDigitNum(); i!=0; --i){
			int digitMul = rhs.numVec[i-1];
			int jinwei=0, temp=0;
			bigNum digitProduct;
			for (int j = numVec.size(); j!=0; --j){
				temp = numVec[j-1]*digitMul+jinwei;
				digitProduct.numVec.push_back(temp%10);
				jinwei = temp/10;
			}
			while(jinwei){
				digitProduct.numVec.push_back(jinwei%10);
				jinwei/=10;
			}
			reverse(digitProduct.numVec.begin(), digitProduct.numVec.end());
			int shift=rhs.getDigitNum()-i;
			while(shift--)
				digitProduct.numVec.push_back(0);
			totProduct += digitProduct;
		}
		*this = totProduct;
		return *this;
	}

	bigNum& operator*=(const int &n){
		bigNum multiplier(n);
		return (*this*=multiplier);
	}

	friend bigNum operator*(const bigNum &lhs, const bigNum &rhs){
		bigNum product(lhs);
		product*=rhs;
		return product;
	}

	friend bigNum operator*(const bigNum &lhs, const int &n){
		bigNum product(lhs);
		product*=n;
		return product;
	}

	friend bigNum operator*(const int &n, const bigNum &rhs){
		bigNum product(rhs);
		product*=n;
		return product;
	}

	bigNum& operator/=(const bigNum &divisor){
		if(divisor==0)
			cerr<<"error: division by 0"<<endl;
		if(divisor==1)  //trivial case, but can happen quite frequently;
			return *this;
		else if (*this==0)
			return *this;
		else{
			bigNum nextDividend(0);
			bigNum quotient(0);
			
			int iter=-1;
			while(iter!=numVec.size()-1){
				int vacantDig=0;
				while(nextDividend<divisor && iter!=numVec.size()-1){
					if (nextDividend==0)
						nextDividend.numVec[0] = numVec[++iter];
					else
						nextDividend.numVec.push_back(numVec[++iter]);
					if(quotient!=0 && vacantDig)
						quotient.numVec.push_back(0);
					++vacantDig;
				}
				if(nextDividend>=divisor){
					int digitQuotient=0;
					while(nextDividend>=divisor){
						nextDividend -= divisor;
						++digitQuotient;
					}
					if (quotient==0)
						quotient.numVec[0] = digitQuotient;
					else
						quotient.numVec.push_back(digitQuotient);
				}
			}
			bigNum remainder(nextDividend);
			*this = quotient;
			return *this;
		}
	}

	friend bigNum operator/(const bigNum &dividend, const bigNum &divisor){
		bigNum quotient(dividend);
		quotient/=divisor;
		return quotient;
	}

	friend bigNum operator%(const bigNum&dividend, const bigNum &divisor){
		bigNum quotient(dividend/divisor);
		bigNum remainder = dividend-quotient*divisor;
		return remainder;
	}

	friend ostream &operator<<(ostream &os, const bigNum &bgNum){
		int ix=0;
		//while(bgNum.numVec[++ix]==0);
		while(ix!=bgNum.numVec.size())
			cout<<bgNum.numVec[ix++]<<" ";
		return os;
	}
};



/*
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
	
	*/