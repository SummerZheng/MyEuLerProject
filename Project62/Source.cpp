#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<time.h>

using namespace std;

bool permuteNextUp(vector<int> &vec){
	int ix = vec.size()-1;
	while(ix && vec[ix]<=vec[ix-1])
		--ix;
	if(ix==0)
		return false;
	else{
		int i1 = ix-1, i;
		for (i=vec.size()-1; i!=i1; --i){
			if(vec[i]>vec[i1])
				break;
		}
		swap(vec[i1], vec[i]);
		reverse(vec.begin()+i1+1, vec.end());
		return true;
	}
}

bool isCube(const long long &n, long long &cubic){
	double tempcubic=100, oldcubic;
	do{
		oldcubic=tempcubic;
		tempcubic -= (tempcubic*tempcubic*tempcubic-n)/(3*tempcubic*tempcubic);
	}while(abs(oldcubic-tempcubic)>0.5);
	cubic = static_cast<long long>(tempcubic);
	if(cubic*cubic*cubic==n)
		return true;
	else
		return false;
}

bool isCube(const long long &n){
	long long cubic;
	return isCube(n, cubic);
}

vector<int> num2vec(long long n){
	vector<int> nvec;
	while(n){
		nvec.push_back(n%10);
		n/=10;
	}
	reverse(nvec.begin(), nvec.end());
	return nvec;
}

long long vec2num(const vector<int>& vec){
	long long n=0;
	for(int ix=0; ix!=vec.size(); ++ix){
		n=n*10+vec[ix];
	}
	return n;
}

ostream& operator<<(ostream &os, const vector<int> &vec){
		for(int ix=0; ix!=vec.size(); ++ix)
			os<<vec[ix];
		return os;
}

bool isNumcomb1stappear(vector<int> vec){
	for(int i=0; i!=vec.size()-1; ++i)
		if(vec[i+1])
			if(vec[i]>vec[i+1])
				return false;
	return true;
}
//Insertion Sort
void sortVec(vector<int> &vec){
	for(int i=0; i!=vec.size()-1; ++i){
		int curmin=vec[i];
		for(int j=i+1; j!=vec.size(); ++j){
			if(vec[j]<curmin){
				swap(vec[i], vec[j]);
				curmin=vec[i];
			}
		}
	}
}

bool isPermutation(vector<int> n1, vector<int> n2){
	sortVec(n1);
	sortVec(n2);
	if(n1==n2)
		return true;
	else 
		return false;
}

long long sortDescend(const long long &n){
	vector<int> nVec(num2vec(n));
	sortVec(nVec);
	reverse(nVec.begin(), nVec.end());
	return vec2num(nVec);
}

int main(){
	clock_t t1=clock();
	int targetPer=5, cubePer=0;
	//long long n= 10000000;//41063624;//10000000;//10234566;
	/*
	long long cubic=123;
	cout<<isCube(56623104, cubic)<<endl;
	cout<<cubic<<endl;
	
	vector<int> vec(num2vec(n));
	while(permuteNextUp(vec)){
		if(vec2num(vec)==56623104)
			cout<<vec<<endl;
		if(vec2num(vec)==66430125)
			cout<<vec<<endl;
	}
	cout<<vec2num(vec)<<endl;

	int a[] = {1, 5, 4, 7, 8, 3, 4, 9};
	vector<int> vec(a, end(a));
	sort(vec);
	cout<<vec<<endl;
	*/
	map<long long, pair<short, long long>> cubes;
	long long c=345, n, sorted;
	map<long long,short>::iterator iter;
	while(true){
		n=c*c*c;
		sorted = sortDescend(n);
		if(cubes.find(sorted)==cubes.end())
			cubes.insert(make_pair(sorted, make_pair(1, c)));
		else
			++cubes[sorted].first;
	
		if(cubes[sorted].first == targetPer) 
			break;
		++c;
	}
	
	c=cubes[sorted].second;
    cout<<c<<"^3="<<c*c*c<<" is the smallest number with "<<targetPer<<" cubic permutations"<<endl;
	/*
	vector<int> cubicVec;
	long long c=5000; 
    vector<vector<int>> nVec;
	vector<int> cVec, nv;
	do{
		long long n = c*c*c;
		nv =num2vec(n);
		if(nv.size()==12){
			nVec.push_back(nv);
			cVec.push_back(static_cast<int>(c));
		}
		++c;
	}while(nv.size()<13);
	vector<bool> checkList(nVec.size(), false);
	for(int i=0; i!=nVec.size(); ++i){
		if(checkList[i]==false){
			cubePer=1; 
			checkList[i]=true;
			for(int j=i+1; j!=nVec.size(); ++j){
				if(checkList[j]==false && isPermutation(nVec[i], nVec[j])){
					++cubePer;
					checkList[j]=true;
				}
			}
			if(cubePer==targetPer){
				cout<<nVec[i]<<endl;
				break;
			}
		}
	}
	*/

	clock_t t2=clock();
	cout<<"Total time used: "<<(double(t2)-double(t1))/CLOCKS_PER_SEC<<"s"<<endl;
	cin.get();
	return 0;
}