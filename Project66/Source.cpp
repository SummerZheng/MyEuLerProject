#include<iostream>
#include<set>
#include<time.h>

using namespace std;

typedef long long ll;
typedef set<ll> myset;
typedef set<ll>::iterator setIter;

int main(){	
	clock_t t1=clock();
	myset DChart, sqChart;
	for(ll i=1; i<=31; ++i){
		DChart.insert(i*i);
	}
	const myset::iterator endIter=DChart.end();
	ll maxN = 10000000, D;
	ll yub = static_cast<ll>(sqrt(maxN*maxN/2));
	ll ylb = static_cast<ll>(sqrt(maxN*maxN/100/1000));
	for (ll y=ylb; y!=yub; ++y)
		sqChart.insert(y*y);
	cout<<sqChart.size()<<endl;

	ll n=maxN, nsq, yround;
	while(true){
		nsq = n*n;
		for (D=2; D<=1000; ++D){
			if (DChart.find(D)!=endIter)
				continue;
			if ((nsq-1)%D)
				continue;
			else{
				yround = static_cast<ll>(sqrt((nsq-1)/D));
				if (D*yround*yround+1 ==nsq)
					break;
			}
		}
		if(D==1001)
			--n;
		else
			break;
	}
	
	cout<<n<<"^2-"<<D<<"*"<<yround<<"^2"<<"=1"<<endl;
	/*
	ll maxSq = maxN*maxN;
	cout<<maxSq<<endl;
	for(ll i=1; i<=maxN; ++i){
		sqChart.insert(i*i);
	}

	const myset::iterator endIter=sqChart.end();
	ll maxX=0, maxY, maxD;
	int expandCount=0;
	for(ll D=2; D<=1000; ++D){
		if(sqChart.find(D)!=endIter)
			continue;
		ll xSq, y;
		ll yUpbound = static_cast<ll>(sqrt(maxSq/D));
		for (y=1; y!=yUpbound+1; ++y){
			xSq = D*y*y+1;
			if(sqChart.find(xSq)!=endIter){
				if(xSq>maxX*maxX)
				{maxX = static_cast<ll>(sqrt(xSq)); maxY =y; maxD = D;} 
				break;
			}
		}
		if (y==yUpbound+1){
			//cout<<"D="<<D<<" need to expand the list"<<endl;
			++expandCount;
		}
	}
	
	cout<<maxX<<"^2-"<<maxD<<"*"<<maxY<<"^2"<<"=1"<<endl;
	cout<<expandCount<<endl;
	*/
	clock_t t2=clock();
	cout<<"Total time used "<<(double(t2)-double(t1))/CLOCKS_PER_SEC<<"s"<<endl;
	cin.get();
	return 0;
}