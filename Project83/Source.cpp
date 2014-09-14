#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

#define maxInt  numeric_limits<int>::max()
typedef vector<vector<int>> matrix2D; 

template<typename T>
void print(const vector<vector<T>> &tb){
	for (int i=0; i!=tb.size(); ++i){
		vector<T> row = tb[i];
		print(row);
	}
}

template<typename T>
void print(const vector<T> &a){
	for (int j=0; j!=a.size(); ++j)
		cout<<a[j]<<" ";
	cout<<endl;
}

void optimalPath4way_IterConstruction(const matrix2D &matrix,matrix2D &minPathSum4way, matrix2D &optimalPath){
	int matSize = matrix.size();
	int changeN = 1;
	while(changeN>0){
		changeN = 0;
		for(int i=0; i!=matSize; ++i){
			for(int j=0; j!=matSize; ++j){
				int path1 = maxInt, path2 = maxInt, path3 = maxInt, path4 = maxInt;
				if(i!=0)
					path3 = minPathSum4way[i-1][j];
				if(i!=matSize-1)
					path1 = minPathSum4way[i+1][j];
			
				if(j!=matSize-1)
					path4 = minPathSum4way[i][j+1];
				if(j!=0)
					path2 = minPathSum4way[i][j-1];
				int minPath = min(min(path1, path2), min(path3, path4));
				if (minPath!=maxInt){
				if ((minPath+matrix[i][j]) < minPathSum4way[i][j]){
					++changeN;
					minPathSum4way[i][j] = minPath + matrix[i][j];
					if(minPath==path1)
						optimalPath[i][j]=1;
					else if(minPath==path2)
						optimalPath[i][j]=2;
					else if(minPath==path3)
						optimalPath[i][j]=3;
					else
						optimalPath[i][j]=4;				
				}
				}
			}
		}
	}
}

/*
int optimalPath4way_TopDown(const matrix2D &matrix, matrix2D &minPathSum,matrix2D &optimalPath, int i, int j, int forbidDir, int curSum, int curMin){
	cout<<"i = "<<i<<"; j = "<<j<<endl;
	if (minPathSum[i][j]<maxInt)
		return minPathSum[i][j];
	if (i==0 && j==0){
		minPathSum[0][0] = matrix[0][0];
		optimalPath[0][0] = -1;
		return minPathSum[i][j];
	}

	curSum +=matrix[i][j];
	if(curSum>curMin)
		return maxInt;

	int matSize = matrix.size();
	int path1, path2, path3, path4;
	
	if(curMin == maxInt){
	int minAdj = maxInt;
	if(i!=0)
		if(minPathSum[i-1][j]<minAdj)
			minAdj = minPathSum[i-1][j];
	if(i!=matSize-1)
		if(minPathSum[i+1][j]<minAdj)
			minAdj = minPathSum[i+1][j];
	if(j!=0)
		if(minPathSum[i][j-1]<minAdj)
			minAdj = minPathSum[i][j-1];
	if(j!=matSize-1)
		if(minPathSum[i][j+1]<minAdj)
			minAdj = minPathSum[i][j+1];
	if(minAdj!=maxInt){
		curMin = minAdj+curSum;
		curSum = minAdj+matrix[i][j];
	}
	}
	
	if(i==matSize-1 || forbidDir==1){
		path1 = maxInt;
	}else{
		path1 = optimalPath4way_TopDown(matrix, minPathSum, optimalPath, i+1, j, 3, curSum, curMin);
	}
	
	if(i==0 || forbidDir==3){
		path3 = maxInt;
	}else{
		path3 = optimalPath4way_TopDown(matrix, minPathSum, optimalPath, i-1, j, 1, curSum, curMin);
	}

	if(j==0 || forbidDir==2){
		path2 = maxInt;
	}else{
		path2 = optimalPath4way_TopDown(matrix, minPathSum, optimalPath, i, j-1, 4, curSum, curMin);
	}

	if(j==matSize-1 || forbidDir==4){
		path4 = maxInt;
	}else{
		path4 = optimalPath4way_TopDown(matrix, minPathSum, optimalPath, i, j+1, 2, curSum, curMin);
	}

	int minPath = min(min(path1, path2), min(path3, path4));
	if (minPath<minPathSum[i][j]){
	minPathSum[i][j] = minPath + matrix[i][j];
	if(minPath==path1)
		optimalPath[i][j]=1;
	else if(minPath==path2)
		optimalPath[i][j]=2;
	else if(minPath==path3)
		optimalPath[i][j]=3;
	else
		optimalPath[i][j]=4;
	//print(minPathSum);
	//cout<<endl;
	//cin.get();
	return minPathSum[i][j];
	}else
		return minPathSum[i][j];
}
*/
void print_path(const matrix2D &matrix, const matrix2D &optimalPath, int i, int j){
	if (i==0 && j==0)
		cout<<matrix[i][j]<<" ";
	else{	
		if(optimalPath[i][j]==2)
			print_path(matrix, optimalPath, i, j-1);
		else if(optimalPath[i][j]==1)
			print_path(matrix, optimalPath, i+1, j);
		else if(optimalPath[i][j]==3)
			print_path(matrix, optimalPath, i-1, j);
		else
			print_path(matrix, optimalPath, i, j+1);
		cout<<matrix[i][j]<<" ";
	}
}

int main(){	
	/*
	int mat[5][5] ={
		{131,	673,	234,	103,	18},
		{201,	96,		342,	965,	150},
		{630,	803,	746,	422,	111},
		{537,	699,	497,	121,	956},
		{805,	732,	524,	37,	    331},
	};
	
	int matSize = 5;
	matrix2D matrix(matSize, vector<int>(matSize));
	for(int row = 0; row!=matSize; ++row){
		for (int col = 0; col!=matSize; col++){
			 matrix[row][col] = mat[row][col];
		}
	}
	*/
	
	ifstream infile("matrix.txt");
	string numstr;
	int matSize = 80, line = 0, col;
	matrix2D matrix(matSize, vector<int>(matSize));

	char delim = ',';
	while (infile.good()){
		getline(infile, numstr);
		stringstream ss(numstr);
		string item;
		col = 0;
		while (getline(ss, item, delim)) {
			stringstream(item) >> matrix[line][col++];
		}
		line++;
	}
	
	matrix2D minPathSum4way(matSize, vector<int>(matSize, maxInt));
	matrix2D optimalPath(matSize, vector<int>(matSize, maxInt));

	minPathSum4way[0][0] = matrix[0][0];
	optimalPath[0][0]= -1;
	optimalPath4way_IterConstruction(matrix, minPathSum4way, optimalPath);
	cout<<"min 4way path sum is "<<minPathSum4way[matSize-1][matSize-1]<<endl;

	//int curSum = 0, curMin = maxInt;
	//cout<<"min 4way path sum is "<<optimalPath4way_TopDown(matrix, minPathSum4way, optimalPath,  matSize-1, matSize-1, 0, curSum, curMin)<<endl;
	
	//print(minPathSum4way);
	//cout<<endl;
	//print(optimalPath);
	//print_path(matrix, optimalPath,  matSize-1, matSize-1);
	
	cin.get();
	return 0;
}