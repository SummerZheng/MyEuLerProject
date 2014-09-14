#include<iostream>
#include<string>
#include <algorithm>
using namespace std;

bool isAnagram(int oriN, int newN){	
	string oristr=to_string(oriN), newstr = to_string(newN);
	sort(oristr.begin(), oristr.end()); 
	sort(newstr.begin(), newstr.end());
	if(oristr==newstr)
		return true;
	else 
		return false;
	/*
	size_t found;
	for(int i=0; i!=oristr.size(); ++i){
		found = newstr.find(oristr[i]);
		if(found == string::npos)
			return false;
		found = oristr.find(newstr[i]);
		if(found == string::npos)
			return false;
	}
	return true;
	*/

}

void nextN(int &n, int &multipleUpboud){
	if(6*++n <= multipleUpboud)
		return;
	else{
		n=multipleUpboud;
		multipleUpboud*=10;
	}
}

int main(){
	int n=100000, multipleUpbound = 1000000;
	/*
	cout<<ispermute(125874, 251748)<<endl;
	nextN(n, multipleUpbound);
	cout<<n<<" "<<multipleUpbound<<endl;
	n=199999;
	nextN(n, multipleUpbound);
	cout<<n<<" "<<multipleUpbound<<endl;
	*/
	bool flag = false;
    while(!flag){
		int i=2;
		while(i++<=6)
			if(!isAnagram(n, i*n))				
				break;

		if (i<=6)
			nextN(n, multipleUpbound);
		else
			flag = true;
	}

	cout<<"The minimun permuted multiples is "<<n<<endl;
	cout<<"And is multiples are "<<2*n<<" "<<3*n<<" "<<4*n<<" "<<5*n<<" "<<6*n<<endl;
	cin.get();
	return 0;
}