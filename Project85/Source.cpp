#include<vector>
#include<iostream>

using namespace std;

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
	for (int j=0; j!=10; ++j)
		cout<<a[j]<<" ";
	cout<<endl;
}

int main(){
	int maxN = 2000;
	vector<int> vec(maxN, 0);
	vec[0] = 1;
	for(int m=1; m!=maxN; m++){
		vec[m] = vec[m-1] + m + 1;
	}
	int targetN = 2000000;
	int minDiff = abs(vec[maxN-1]-targetN);
	int recN;
	int ct=0;
	for(int i=0; i!=maxN; i++){
		for(int j=1; j!=maxN; ){
			ct++;
			recN = vec[i]*vec[j];
			if(abs(recN-targetN)<minDiff){
				minDiff = abs(recN-targetN);
				cout<<i<<" "<<j<<" produce "<<recN<<endl;
			}
			if(recN-targetN>minDiff)
				break;
			if(recN<targetN/4)
				j=2*j;
			else
				j++;
		}
	}
	cout<<"total number of rectangle checked "<<ct<<endl;
	cin.get();
	return 0;
}