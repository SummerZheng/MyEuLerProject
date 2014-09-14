#include<iostream>
#include<vector>

using namespace std;

template <typename T>
void print(vector<T> &a){
	for (int i=0; i!=a.size(); ++i)
		cout<<a[i]<<" ";
	cout<<endl;
}

int main(){
	int n = 10001;
	vector<int> prime(n, 1);
    
	prime[0] = 2; prime[1] = 3; prime[2] = 5;
	int prime_ct = 3, curInt=5;
	while (prime_ct!=n){
		curInt+=2;
		int uplimit = floor(sqrt(curInt));
		if (curInt%3!=0 && curInt%5!=0){
			int i = 1;
			while(prime[i]<=uplimit){
				if (curInt%prime[i]==0)
					break;
				else
					++i;
			}
			if (prime[i]*prime[i]>curInt){
				prime[prime_ct++]=curInt;
			}
		}
	}
	cout<<prime[n-1]<<endl;;
	cin.get();
	return 0;
}