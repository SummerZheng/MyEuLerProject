#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>

using namespace std;

template<typename T>
void print(const vector<T> &a){
	for (int j=0; j!=a.size(); ++j)
		cout<<a[j]<<" ";
	cout<<endl;
}

bool findDelCandidate(vector<string> &key, vector<int> &delCandidate){
	bool flag = false;
	for(int i=0; i!=key.size(); i++){
		if(!key[i].empty()){
			flag = true;
			++delCandidate[key[i][0]-'0'];
		}
	}
	return flag;
}

void countFreq(vector<string> &key, vector<int> &delcan, vector<int> &freq){
	for(int i=0; i!=key.size(); i++){
		if(key[i].length()>=2){
			for(int j=1; j!=key[i].length(); j++){
				if(delcan[key[i][j]-'0']>=0){
			switch(key[i][j]){
				case '0':
					freq[0]++;
					break;
				case '1':
					freq[1]++;
					break;
				case '2':
					freq[2]++;
					break;
				case '3':
					freq[3]++;
					break;
				case '6':
					freq[6]++;
					break;
				case '8':
					freq[8]++;
					break;
				case '9':
					freq[9]++;
					break;
				default:
					cout<<"char""<<key[][]<< not considered"<<endl;
			}
				}
			}
		}
	}
}

char findMinFreqKey(vector<int> &delCan, vector<int> &freq){
	int minKeyval = numeric_limits<int>::max(), minKey=-1;
	for(int i=0; i!=10; i++){
		if(delCan[i]!=-1 && freq[i]<minKeyval){
			minKeyval = freq[i];
			minKey = i;
		}
	}
	cout<<minKey<<endl;
	if(minKey!=-1)
		return minKey+'0';
	else
		return 'f';
}

void delminKey(vector<string> &key,char delKey){
	for(int i=0; i!=key.size(); i++){
		if(!key[i].empty()){
			if(key[i][0]==delKey){
				key[i] = key[i].substr(1, key[i].length()-1);
			}
		}
	}
}

void reset(vector<int> &a, vector<int> &b){
	a = vector<int>(10, -1);
	b = vector<int>(10, -1);
}

int main(){
	int N=50;
	vector<string> key(N); 
	ifstream infile("keylog.txt");
	string str;
	int i=0;
	while(getline(infile, str)){
		key[i++] = str;
	}

	string passcode;
	vector<int> freq(10, -1);
	vector<int> delCandidate(10, -1);
	while(findDelCandidate(key, delCandidate)){
		countFreq(key, delCandidate, freq);
		char delKey = findMinFreqKey(delCandidate, freq);
		cout<<delKey<<endl;
		passcode.append(1, delKey);
		print(delCandidate);
		print(freq);
		delminKey(key, delKey);
		print(key);
		reset(freq, delCandidate);
	}
	
	cout<<passcode<<endl;
	cin.get();
	return 0;
}