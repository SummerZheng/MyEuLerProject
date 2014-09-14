#include<iostream>
#include<vector>
using namespace std;

typedef long long ll;

template<typename T>
void print(const vector<vector<T>> &tb){
	for (int i=0; i!=tb.size(); ++i){
		vector<T> row = tb[i];
		for (int j=0; j!=row.size(); ++j)
			cout<<row[j]<<" ";
		cout<<endl;
	}
}

template<typename T>
void print(const vector<T> &a){
	for (int j=0; j!=a.size(); ++j)
		cout<<a[j]<<" ";
	cout<<endl;
}

int maxN=200;
vector<ll> dpArr(maxN+1, -1);

ll F(int m, int n){
	if(n==-1)
		return 1;
	if(dpArr[n]==-1){
		if(n<m)
			dpArr[n] = 1;
		else{
			ll ct = 1; //left is empty
			//start from diff loc, and garanteed to place at least one block
			for(int startpos = 0; startpos<=n-m; startpos++){
				//diff block length
				for(int blockl=m; blockl<=n-startpos; blockl++){
					//one insulator block
					ct += F(m, n-startpos-blockl-1);
					//cout<<"start pos "<<startpos<<", block length "<<blockl<<", remainder length "<<n-startpos-blockl-1<<", ways "<<F(m, n-startpos-blockl-1)<<endl;
				}
			}
			dpArr[n] = ct;
		}
	}
	return dpArr[n];
}

/*
int minL = 51, totL, numBlock;
vector<vector<ll>> dpArr(numBlock+1, vector<ll>(totL+1, -1));

ll numSplit(int numBlock, int L2split){
	//cout<<"split "<<L2split<<" with "<<numBlock<<" blocks"<<endl;
	if(dpArr[numBlock][L2split]==-1){
		if(numBlock==0)
			dpArr[numBlock][L2split] = 1;
		else if(L2split<numBlock*minL)
			dpArr[numBlock][L2split] = 0;
		else{
			ll ct=0;
			//for(int n=1; n<=numBlock; n++){
				for(int l=minL; l<=L2split-(numBlock-1)*minL; l++){
					ct += (l-minL+1)*numSplit(numBlock-1, L2split-l);
					//cout<<"split "<<L2split-l<<" with "<<numBlock-1<<" blocks has "<<numSplit(numBlock-1, L2split-l)<<" ways"<<endl;
				}
			//}
			dpArr[numBlock][L2split]= ct;
		}
		//cout<<"split "<<L2split<<" with "<<numBlock<<" blocks has "<<dpArr[numBlock][L2split]<<" ways"<<endl;
		//print(dpArr);
	}	
	return dpArr[numBlock][L2split];
}
*/

int main(){
	ll ct=0;
	for(int n=100; n!=200; n++){
		ct = F(50, n);
		if(ct>1000000){
			cout<<"totL = "<<n<<endl;
			break;
		}
	}
	/*
	for(int n=0; n<=numBlock; n++){
		dpArr = vector<vector<ll>>(numBlock+1, vector<ll>(totL+1, -1));
		ct += numSplit(n, totL);
	}
	cout<<endl;
	
	for(totL=100; totL<=300; totL++){
		ct=0;
		numBlock = totL/minL;
		for(int n=0; n<=numBlock; n++){
			dpArr = vector<vector<ll>>(numBlock+1, vector<ll>(totL+1, -1));
			ct += numSplit(n, totL);
		}
		if(ct>1000000){
			cout<<"totL = "<<totL<<endl;
			break;
		}
	}
	*/
	cout<<"total number of ways to split "<<ct<<endl;
	
	print(dpArr);
	cin.get();
	return 0;
}