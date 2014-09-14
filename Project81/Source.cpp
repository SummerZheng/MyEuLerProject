#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <limits>
using namespace std;

typedef vector<vector<int>> matrix2D; 
#define maxInt  numeric_limits<int>::max()

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

int optimalPath2way(const matrix2D &matrix, int i, int j,matrix2D &minPathSum,matrix2D &optimalPath){
	if (minPathSum[i][j]<maxInt)
		return minPathSum[i][j];
	else{
		int minSum = maxInt;
		if(j==0){
			if (i==0){
				minSum = matrix[i][j];
				optimalPath[i][j] = -1;
			}else{
				minSum = optimalPath2way(matrix, i-1, j,minPathSum,optimalPath) + matrix[i][j];
				optimalPath [i][j] = 3;//meaning down
			}
		}else if(i==0){
			minSum = optimalPath2way(matrix, i, j-1,minPathSum,optimalPath) + matrix[i][j];
			optimalPath [i][j] = 2;//meaning right
		}else{
			int path2 = optimalPath2way(matrix, i, j-1,minPathSum,optimalPath);
			int path3 = optimalPath2way(matrix, i-1, j,minPathSum,optimalPath);
			if(path2<=path3){
				minSum = path2+ matrix[i][j];
				optimalPath [i][j] = 2;
			}else{
				minSum = path3 + matrix[i][j];
				optimalPath [i][j] = 3;
			}
		}
		minPathSum[i][j] = minSum;
		return minSum;
	}
}

void print_path(const matrix2D &matrix, const matrix2D &optimalPath, int i, int j){
	if (i==0 && j==0)
		cout<<matrix[i][j]<<" ";
	else{	
		if(optimalPath[i][j]==2)
			print_path(matrix, optimalPath, i, j-1);
		else
			print_path(matrix, optimalPath, i-1, j);
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
	print(matrix);
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

	matrix2D minPathSum2way(matSize, vector<int>(matSize, maxInt));
	matrix2D optimalPath(matSize, vector<int>(matSize, 0));
	
	cout<<optimalPath2way(matrix, matSize-1, matSize-1, minPathSum2way, optimalPath)<<endl;
	//print(minPathSum2way);
	//print(optimalPath);
	print_path(matrix, optimalPath,  matSize-1, matSize-1);
	
	cin.get();
	return 0;
}