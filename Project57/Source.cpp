#include<iostream>
#include<string>
#include<vector>
#include"Fraction.h"
#include"bigNum.h"
#include<time.h>
#include"Problem57.cpp"
using namespace std;

int digitNum(bigNum n){
	return n.getDigitNum();
}

void Problem57();
void Problem65();

int main(){
	clock_t t1=clock();
	Problem65();
	clock_t t2=clock();
	cout<<"Total process took "<<(double(t2)-double(t1))/CLOCKS_PER_SEC<<" seconds"<<endl;
	cin.get();
	return 0;
}

void Problem65(){
	int sizeN=100;
	vector<int> eGenerator(sizeN, 1);
	eGenerator[0]=2;
	for(int i=1; i<sizeN; ++i){
		if((i+1)%3==0)
			eGenerator[i]=2*(i+1)/3;
	}
	Fraction fracPart(0,1);
	while(sizeN!=1){
		--sizeN;
		(fracPart+=eGenerator[sizeN]).inverse();
	}
	fracPart+=eGenerator[0];
	cout<<fracPart<<endl;
	cout<<fracPart.getNumeroator().bigNumdigitSum()<<endl;
}


void Problem57(){
	/*
	int a[] = {1,3,5,8,7,6,4,3,1,8,0,7,6,5};
	vector<int> b0(a, end(a));
	bigNum b1(b0);
	bigNum b2(153483);
	cout<<(b1%b2)<<endl;

	
	Fraction f1(3, 4), f2(1, 6);
	cout<<f1.inverse()<<endl;
	*/
	
	Fraction lastF(1, 2);
	Fraction ithApprox;
	int iter=1, count=0, maxIter=1000;
	do{
		ithApprox = 1+lastF;
		lastF = (2+lastF).inverse();
		if(digitNum(ithApprox.getNumeroator())>digitNum(ithApprox.getDenominator())){
			//cout<<ithApprox<<endl;
			++count;
		}
	}while(iter++<=maxIter);
	cout<<"There are "<<count<<" fractions contain a numerator with more digits than denominator."<<endl;
}