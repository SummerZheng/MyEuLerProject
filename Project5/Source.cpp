#include <iostream>
#include <vector>
using namespace std;

//greatest common divisor
int gcd(int a, int b){
	if(b==0)
		return a;
	else
		return(gcd(b, a%b));
}

template <typename T>
void printvector(const vector<T> &a){
	for (int i=0; i!=a.size(); ++i)
		cout<<a[i]<<" ";
	cout<<endl;
}

/*
int main(){
	int n=20;
	vector<int> LCM(n, 1);
	
	//least common multiple
	for (int i=1; i!=n; ++i){
		LCM[i] = i/gcd(LCM[i-1], i)*LCM[i-1]; 
	}

	printvector(LCM);
	cin.get();
	return 0;
}
*/

int main(){
	int n = 20;
	vector<int> multiplier(n, 1);
	for (int i=1; i!=n; ++i){
		multiplier[i] = multiplier[i-1]+1; 
	}
	int lcm=1;

	for (int i=1; i!=n; ++i){
		if (multiplier[i]!=1){
			for (int j=i+1; j!=n; ++j){
				multiplier[j] /= gcd(multiplier[j], multiplier[i]);
			}
			lcm*=multiplier[i];
		}
		
	}
	cout<<lcm<<endl;
	printvector(multiplier);
	cin.get();
	return 0;
}