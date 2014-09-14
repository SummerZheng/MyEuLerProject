#include<iostream>
#include<vector>
#include<set>
#include<string>
using namespace std;

void swap(vector<int> &vec,int i, int j){
	int temp = vec[i];  vec[i] = vec[j]; vec[j] =temp;
}

void reverse(vector<int> &vec,int i, int j){
	for(int il = i, ir = j; il<ir; il++, ir--){
		swap(vec, il, ir);
	}
}

bool permuteNextUp(vector<int> &vec){
	int i, j;
	for(i=vec.size()-1; i>0; i--){
		if(vec[i]>vec[i-1])
			break;
	}
	if(i==0)
		return false;
	j=i;
	for(i=vec.size()-1; ; i--){
		if(vec[i]>vec[j-1])
			break;
	}
	swap(vec, j-1, i);
	reverse(vec, j, vec.size()-1);
	return true;
}

int main(){
	int maxConsecCt=0;
	
	vector<vector<int>> opVec(71, vector<int>(3, 0));
	int ct=0;
	//64
	for(int i1 = 0; i1!=4; i1++){
		for(int i2 = 0; i2!=4; i2++){
			for(int i3=0; i3!=4; i3++){
				opVec[ct][0] = i1;
				opVec[ct][1] = i2;
				opVec[ct][2] = i3;
				ct++;
			}
		}
	}
	//7
	opVec[ct][0] = 0; opVec[ct][1] = -1; opVec[ct++][2] = 0;
	opVec[ct][0] = 0; opVec[ct][1] = -1; opVec[ct++][2] = 1;
	opVec[ct][0] = 1; opVec[ct][1] = -1; opVec[ct++][2] = 1;
	opVec[ct][0] = 0; opVec[ct][1] = -2; opVec[ct++][2] = 0;
	opVec[ct][0] = 0; opVec[ct][1] = -2; opVec[ct++][2] = 1;
	opVec[ct][0] = 1; opVec[ct][1] = -2; opVec[ct++][2] = 0;
	opVec[ct][0] = 1; opVec[ct][1] = -2; opVec[ct++][2] = 1;


	string opstring;
	opstring.push_back('+');
	opstring.push_back('-');
	opstring.push_back('*');
	opstring.push_back('/');
	cout<<ct<<endl;

	for(int a=1; a!=7; a++){
		for(int b=a+1; b!=8; b++){
			for(int c=b+1; c!=9; c++){
				for(int d=c+1; d<=9; d++){
	set<double> expVal;
	vector<int> digit;
	digit.push_back(a);
	digit.push_back(b);
	digit.push_back(c);
	digit.push_back(d);

	do{
		for(int i=0; i!=71; i++){
			double result; 
			if(i<=64){
				result = digit[0];
				for(int j=1; j<=3; j++){
				int op = opVec[i][j-1];
				switch(op){
				case 0:
					result+=digit[j]; break;
				case 1:
					result-=digit[j]; break;
				case 2:
					result*=digit[j]; break;
				case 3:
					result/=digit[j]; break;
				}
				}
			}else{
				int ele1 = opVec[i][0]==0?digit[0]+digit[1]:digit[0]-digit[1];
				int ele2 = opVec[i][2]==0?digit[2]+digit[3]:digit[2]-digit[3];
				result = opVec[i][1]==-1?double(ele1)*ele2: double(ele1)/ele2;
			}
			if(result>0 && int(result)==result && expVal.count(result)==0){
				//cout<<result<<" = "<<digit[0]<<opstring[opVec[i][0]]<<digit[1]<<opstring[opVec[i][1]]<<digit[2]<<opstring[opVec[i][2]]<<digit[3]<<endl;
				expVal.insert(result);
			}
		}
	}while(permuteNextUp(digit));

	int consecCt=0;
	for(auto iter=expVal.begin(); iter!=expVal.end(); iter++){
		if(iter==expVal.begin())
			if(*iter==1)
				++consecCt;
			else
				break;
		if(next(iter)==expVal.end()){
			++consecCt;
			break;
		}
		if(*iter == *next(iter)-1)
			++consecCt;
		else
			break;
	}

	if(consecCt>maxConsecCt){
		maxConsecCt = consecCt;
		cout<<a<<b<<c<<d<<" "<<maxConsecCt<<endl;
	}
				}
			}
		}
	}
	cout<<maxConsecCt<<endl;
	cin.get();
	return 0;
}