#include<iostream>

using namespace std;
typedef long long ll;

template<typename T>
T gcd(T a, T b){
	T c=a;
	while(b){
		c = a%b;
		a = b;
		b = c;
	}
	return a;
}

bool validPair(ll a, ll b){
	ll f1 = a-b, f2 = a+b-1;
	ll c = gcd(a, b);
	a/=c; b/=c;
	if(f1%(c*c)==0)
		f1/=(c*c);
	else
		return false;
	if(f2%(a*b)==0)
		f2/=(a*b);
	else
		return false;
	if(f1*f2==2)
		return true;
	else 
		return false;
}

bool validPair(ll c, ll aS, ll bS){	
	if(gcd(aS, bS)!=1)
		return false;
	ll a = c*aS, b = c*bS; 
	if((a+b-1)%(aS*bS)!=0)
		return false;
	if((a-b)/(c*c)*((a+b-1)/(aS*bS))!=2)
		return false;
	else 
		return true;
}

int main(){
	ll target = static_cast<ll>(pow(10, 12));
	for (ll c=45500; c!=2000000; c++){
		double bSdouble = sqrt((c*c-1)/2);
		ll bS = static_cast<int>(bSdouble);
		if(bS==bSdouble){
			if(gcd(bS, c)==1)
				cout<<"blue disc: "<<c*(bS+c)<<", total disc: "<<(2*bS+c)*c<<endl;
		}
		bSdouble = sqrt(2*c*c-1);
		bS = static_cast<int>(bSdouble);
		if(bS == bSdouble){
			if(gcd(bS, c)==1)
			cout<<"blue disc: "<<c*(bS+2*c)<<", total disc: "<<2*(bS+c)*c<<endl;
		}
	}
	cin.get();
	return 0;
}
	