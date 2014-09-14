#include <iostream>
#include <vector> 
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

int totL = 50;
vector<ll> dpArr(totL+1, -1); 
/*
//Problem 116
ll F(int n, int l){
	if(dpArr[l]==-1){
		if(l<n)
			dpArr[l] = 1;
		else{
			ll ct=1;
			for(int startpos=0; startpos<=l-n; startpos++){
				ct += F(n, l-startpos-n);
				//cout<<"start pos "<<startpos<<" remainder length "<<l-startpos-n<<" ways "<<F(n, l-startpos-n)<<endl;
			}
			dpArr[l] = ct;
		}
	}
	return dpArr[l];
}
*/

//Problem 116
ll F(int l){
	if(dpArr[l]==-1){
		if(l<2)
			dpArr[l] = 1;
		else{
			ll ct=1;
			for(int n=2; n<=4; n++){
				for(int startpos=0; startpos<=l-n; startpos++){
					ct += F(l-startpos-n);
					//cout<<"start pos "<<startpos<<" remainder length "<<l-startpos-n<<" ways "<<F(n, l-startpos-n)<<endl;
				}
			}
			dpArr[l] = ct;
		}
	}
	return dpArr[l];
}
int main(){
	ll ct=0;
	/*
	ct += F(2, totL)-1;
	cout<<F(2, totL)<<endl;
	dpArr = vector<ll>(totL+1, -1); 
	ct += F(3, totL)-1;
	cout<<F(3, totL)<<endl;
	dpArr = vector<ll>(totL+1, -1); 
	ct += F(4, totL)-1;
	cout<<F(4, totL)<<endl;
	*/
	ct = F(50);
	cout<<ct<<endl;
	cin.get();
	return 0;
}