#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;
int clen = 5;

string::const_iterator find_next(string::const_iterator iter, int &prod, const string &str){
	if(iter>str.end()-clen)
		return str.end()-clen;
	prod = 1;
	for (int j = 1; j<=clen; ++j){
		if((*iter)=='0')
			return find_next(++iter, prod, str);
		else{
			prod *= (*iter++-'0');
		}
	}
	return iter-5;
}

int main(){
	ifstream infile;
	infile.open("num_text.txt");

	if(infile.fail()){
		cerr<<"error: unable to open input file"<<endl;
		cin.get();
		return -1;
	}

	string numstr, curline;
    while (infile.good()){
	  getline(infile, curline);
	  //cout<<curline<<endl;
	  numstr+=curline;
    }
	infile.close();                

	
	int product=1;
	string::const_iterator iter=find_next(numstr.begin(), product, numstr);
	int maxProduct = product;
	
	while (iter!=numstr.end()-5){
		if(*(iter+5)=='0')
			iter = find_next((iter+6), product, numstr);	
		else{
			product = product*(*(iter+5)-'0')/(*iter-'0');
			++iter;
		}
		if(product>maxProduct){
			maxProduct = product;			
			cout<<maxProduct<<"=";
			for (int i=0; i<5; ++i)
				cout<<*(iter+i)<<" ";
			cout<<endl;
		}	
	}
	//cout<<*iter<<endl;
	cout<<maxProduct<<endl;
	cin.get();
	return 0;
}
