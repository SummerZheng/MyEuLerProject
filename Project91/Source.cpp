#include<iostream>

using namespace std;

int getGCD(int a, int b){
	int c;
	while(b){	
		c=a%b;
		a=b;
		b=c;
	}
	return a;
}

int main(){
	cout<<getGCD(5, 5)<<endl;
	int N=50;
	int ct = 3*N*N;
	int internalRecCt=0;
	int pct=0, nct=0;
	for(int x1=1; x1<N; x1++){
		for(int y1 = x1; y1<=N; y1++){
			int gcd = getGCD(x1, y1);
			int dirY = -x1/gcd;
			int dirX = y1/gcd;
			int posM = 1, negM = 1;
			while( x1+posM*dirX<=N && y1+posM*dirY>=0){
				internalRecCt++;
				posM++;
				pct++;
			}
			if(y1==x1)
				continue;
			while( x1-negM*dirX>=0 && y1-negM*dirY<=N){
				internalRecCt++;
				nct++;
				negM++;
			}
		}
	}
	cout<<pct<<" "<<nct<<endl;
	cout<<ct+2*internalRecCt<<endl;
	cin.get();
	return 0;
}