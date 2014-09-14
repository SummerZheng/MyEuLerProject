#include<iostream>
#include<set>
#include<string>
#include<vector>
#include<algorithm>
#include<time.h>

using namespace std;

template<typename T>
void print(const vector<T> &a){
	for (int j=0; j!=a.size(); ++j)
		cout<<a[j]<<" ";
	cout<<endl;
}

template<typename T>
void print(const set<T> &a){
	for (auto iter=a.begin(); iter!=a.end(); ++iter)
		cout<<*iter<<" ";
	cout<<endl;
}

int formatize(int n){
	string str = to_string(n);
	sort(str.begin(), str.end());
	int fn = 0;
	for(int i=0; i!=str.length(); i++){
		fn = 10*fn+str[i]-'0';
	}
	return fn;
}

int nextN(int n){
	int nextNum = 0;
	int digit;
	while(n){
		digit = n%10;
		nextNum += digit*digit;
		n/=10;
	}
	return nextNum; 
		//formatize(nextNum);
}


int main(){
	clock_t t1 = clock();
	int target = 10000000;
	int sz = static_cast<int>(81*log10(target)+1);
	cout<<sz<<endl;
	int ct=0;
	vector<bool> hashArr(sz, false);
	hashArr[89] = true;
	for(int i=2; i!=sz; i++){
		if(hashArr[i]){
			ct++;
			continue;
		}else{
			vector<int> chain;
			int curN;
			for(curN = i; curN>=i && curN!=89; curN = nextN(curN)){
				//cout<<curN<<endl;
				chain.push_back(curN);
			}
			if(curN==89 || hashArr[curN]){
				for(int ix = 0; ix!=chain.size(); ix++){
					hashArr[chain[ix]] = true;
				}
				ct++;
			}
		}
	}
	for(int i=sz; i<target; i++){
		if(hashArr[nextN(i)])
			ct++;
	}
	cout<<ct<<endl;
	clock_t t2 = clock();
	cout<<"total time used "<<(t2-t1)/CLOCKS_PER_SEC<<"s"<<endl;
	cin.get();
	return 0;
}