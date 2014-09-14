#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
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
void print(const vector<T> &vec){
	for (int j=0; j!=vec.size(); ++j)
		cout<<vec[j]<<" ";
	cout<<endl;
}

vector<int> get_encryptKey(int keyIdx){
	vector<int> encryptKey(3);
	int base = 26;
	int idx = 2;
	while(keyIdx){
		int offset = keyIdx%base;
		keyIdx/=base;
		encryptKey[idx] = 'a'+offset;
		idx--;
	}
	while(idx>=0){
		encryptKey[idx--] = 'a';
	}
	return encryptKey;
}


long convert_base10to2(int int_base10){
	long binaryInt = 0;
	int remainder=int_base10, subtractVal = 1, binaryAddval = 1; 
	while(remainder){
		while (2*subtractVal <= remainder){
			subtractVal *= 2;
			binaryAddval *= 10;
		}
		binaryInt += binaryAddval;
		remainder -= subtractVal;
		binaryAddval = 1; 
		subtractVal = 1;
	}
	return binaryInt;
}

int XORcalculater(long b1, long b2){
	int base10xor = 0;
	int addval = 1;
	int tempb1, tempb2;
	while(b1 || b2){
		tempb1 = b1%10;
		tempb2 = b2%10;
		base10xor += (tempb1==tempb2? 0: addval); 
		addval *= 2;
		b1/=10;
		b2/=10;
	}
	return base10xor;
}

bool InWordSet(int wordnum){
	if(wordnum>=65 && wordnum<=90)
		return true;
	else if(wordnum>=97 && wordnum<=122)
		return true;
	else if(wordnum>=48 && wordnum<=57)
		return true;
	else{
		switch (wordnum){
		case '.':case ',':case ' ':case '*':case '!':case '\'':case ':':case '(':case ')':case';':
			return true;
		default:
			return false;
		}
	}
	
}

int main(){
	ifstream infile("cipher1.txt");
	string numstr;
	int maxSize = 6000, wordcount = 0;
	vector<int> numVec(maxSize, 0);

	char delim = ',';
	while (infile.good()){
		getline(infile, numstr);
		stringstream ss(numstr);
		string item;
		while (getline(ss, item, delim)) {
			stringstream(item) >> numVec[wordcount++];
		}
	}


	vector<int> numVec1(numVec.begin(), numVec.begin()+wordcount);	
	//print(numVec1);
	int maxTranslatable = 0;
	int maxKeychoices = 26*26*26;
	for (int keyIdx = 0; keyIdx != maxKeychoices; keyIdx++){
		vector<char> charVec(numVec1.size(), 'a');
		vector<int> encryptKey = get_encryptKey(keyIdx);
		vector<long> binaryKey(3);
		for(int i=0; i!=3; ++i){
			binaryKey[i] = convert_base10to2(encryptKey[i]);
		}

		int charIdx = 0;
		while (charIdx!=numVec1.size()){
			int translatedInt = XORcalculater(convert_base10to2(numVec1[charIdx]), binaryKey[charIdx%3] );
			if (InWordSet(translatedInt)){
				charVec[charIdx] = (char)translatedInt;
				++charIdx;
			}else{
				charVec[charIdx] = (char)translatedInt;
				++charIdx;
				break;
			}
		}

		if (charIdx == numVec1.size()){
			cout<<"The encryption key is ";
			for(int i=0; i!=3; ++i){
				cout<<(char) encryptKey[i]<<" ";
			}
			cout<<endl;
			print(charVec);
			int ascIISum = 0;
			for(int i=0; i!=numVec1.size(); ++i){
				ascIISum += charVec[i];
			}
			cout<<"the ascII sum of all the words is "<<ascIISum<<endl;
		}

	}
	cin.get();
	return 0;
}