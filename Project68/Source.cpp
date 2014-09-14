#include <iostream>
#include <vector>
using namespace std;

bool isFivegon(const vector<int> &l, const vector<int> &c){
	int sum5gon = l[0] + c[0] + c[1];
	for(int ix=1; ix!=5; ++ix){
		int sum = l[ix] + c[ix] +c[(ix+1)%5];
		if(sum!=sum5gon)
			return false;
	}
	return true;
}

void swap(vector<int> &vec, int i, int j){
	int temp = vec[i];
	vec[i] = vec[j];
	vec[j] = temp;
}


void reverse(vector<int> &vec, int startIx, int endIx){
	for (int delta = 0; delta!= (endIx-startIx-1)/2; ++delta){
		swap(vec, startIx+delta, endIx-delta);
	}
}

bool permuteUp(vector<int> &vec){
	int i=4, j=4;
	while(i>0 && vec[i-1] >= vec[i]){
		i--;
	}
	if(i==0)
		return false;
	else{
		while(vec[j] <= vec[i-1])
			j--;
		swap(vec, i-1, j);
		reverse(vec, i, vec.size()-1);
		return true;
	}
}


void print5gon(const vector<int> &l, const vector<int> &c){
	for(int ix=0; ix!=5; ++ix){
		cout << l[ix] << " " << c[ix] <<" "<< c[(ix+1)%5] <<" ; ";
	}
	cout<<endl;
}


int main(){
	 int a[] = {6, 7, 8, 9, 10};
	 int b[] = {1, 2, 3, 4, 5};
	 vector<int> l(begin(a), end(a));
	 vector<int> cstart(begin(b), end(b));
	 do{
		 vector<int> c(cstart);
		 do{
			 if (isFivegon(l, c))
				 print5gon(l, c);
		 }while(permuteUp(c));
	 }while(permuteUp(l));
	 cin.get();
	 return 0;
 }