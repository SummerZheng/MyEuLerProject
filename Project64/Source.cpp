#include<iostream>
#include<vector>
#include<time.h>

using namespace std;
int getGCD(int numerator, int denominator){
	int temp;
	while(denominator){
		temp=numerator%denominator;
		numerator = denominator;
		denominator=temp;
	}
	return numerator;
}

void print(vector<int> vec){
	for (int i=0; i!=vec.size(); ++i)
		cout<<vec[i]<<" ";
	cout<<endl;
}

bool appeared(const int &numerator, const int &denominator,const vector<int> &denVec, const vector<int> &numVec, int &i){
	for(i=0; i!=denVec.size(); ++i){
		if (numerator==numVec[i] && denominator==denVec[i])
			break;
	}
	if (i==denVec.size())
		return false;
	else
		return true;
}

void Prob64LongerVersion();
void Prob64ShortVersion();
//squre roots fraction expansion
int main(){
	clock_t t1 = clock();
	Prob64LongerVersion();
	//Prob64ShortVersion();
	clock_t t2 = clock();
	cout<<"total time used is "<<(double(t2)-double(t1))/CLOCKS_PER_SEC<<"s"<<endl;
	cin.get();
	return 0;
}

void Prob64ShortVersion(){
	int oddPeriodCount=0;
	int maxN=10000;
	for (int n=1; n<=maxN; ++n){
		int sqrtNint = static_cast<int>(sqrt(n));
		if(sqrtNint*sqrtNint==n)
			continue;
		else{
			int m = sqrtNint, d = 1;
			int a;
			vector<int> fractionExpand;
			do{
				d = (n-m*m)/d;
				a = (sqrtNint+m)/d;
				m = d*a-m;
				fractionExpand.push_back(a);
			}while(m!=sqrtNint || d!=1);
			//print(fractionExpand);
			if(fractionExpand.size()%2)
				++oddPeriodCount;
		}
	}
	cout<<oddPeriodCount<<endl;
}

void Prob64LongerVersion(){
		int oddPeriodCount=0;
	int maxN=10000;
	for (int n=1; n<=maxN; ++n){
		int sqrtNint = static_cast<int>(sqrt(n));
		if(sqrtNint*sqrtNint==n)
			continue;
		else{
			int denomiMinus = sqrtNint, numerator = 1, denominator, coeff=1;
			int a, gcd;
			vector<int> fractionExpand;
			vector<int> denVec, numVec;
			int firstIdx=0;
			do{			
				denVec.push_back(denomiMinus);
				numVec.push_back(numerator);
				denominator = n-denomiMinus*denomiMinus;
				a = numerator*(sqrtNint+denomiMinus)/denominator;
			    fractionExpand.push_back(a);
				gcd = getGCD(numerator, denominator);
				denominator/=gcd; numerator/=gcd;
				denomiMinus = a*denominator- denomiMinus*numerator;
				numerator = denominator;			    
			}while(!appeared(numerator, denomiMinus,denVec, numVec, firstIdx));
						
			if((fractionExpand.size()-firstIdx)%2){
				++oddPeriodCount;
				//cout<<n<<" has "<<fractionExpand.size()-firstIdx<<" digits expansion from idx "<<firstIdx<<" :"<<endl;;
				//print(fractionExpand);
				//cout<<endl;
			}
		}
	}
	cout<<oddPeriodCount<<endl;
}