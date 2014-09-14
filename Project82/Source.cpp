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

void optimalPath3way_BottomUp(const matrix2D &matrix, matrix2D &minPathSum,matrix2D &optimalPath){
	//cout<<"i = "<<i<<"; j = "<<j<<endl;
	int matSize = matrix.size();
	for(int i=0; i!=matSize; ++i){
		minPathSum[i][0] = matrix[i][0];
		optimalPath[i][0] = -1;
	}
	for(int j=1; j!=matSize; ++j){
		vector<int> leftPathSum(matSize, 0);
		for(int i=0; i!=matSize; ++i){
			leftPathSum[i] = minPathSum[i][j-1] + matrix[i][j];
		}
		for(int i=0; i!=matSize; ++i){
			int path3 = i==0? maxInt:minPathSum[i-1][j];
			int path2 = minPathSum[i][j-1];
			int path1 = maxInt, colSum = 0, tempSum;
			int idx1 = i+1;
			while(idx1!=matSize && colSum<path1){
				tempSum = colSum + leftPathSum[idx1];
				colSum += matrix[idx1][j];
				idx1++;
				if(tempSum<path1){
					path1 = tempSum;
				}
			}
			int minPath = min(min(path1, path2), path3);
			minPathSum[i][j] = minPath + matrix[i][j];
			if(minPath==path1)
				optimalPath[i][j]=1;
			else if(minPath==path2)
				optimalPath[i][j]=2;
			else
				optimalPath[i][j]=3;
		}
	}
}

void print_path(const matrix2D &matrix, const matrix2D &optimalPath, int i, int j){
	if (j==0)
		cout<<matrix[i][j]<<" ";
	else{	
		if(optimalPath[i][j]==2)
			print_path(matrix, optimalPath, i, j-1);
		else if(optimalPath[i][j]==1)
			print_path(matrix, optimalPath, i+1, j);
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
	
	matrix2D minPathSum3way(matSize, vector<int>(matSize, maxInt));
	matrix2D optimalPath(matSize, vector<int>(matSize, maxInt));
	int minSum=maxInt, minSumRow;

	optimalPath3way_BottomUp(matrix, minPathSum3way, optimalPath);
	print(minPathSum3way);
	cout<<endl;
	print(optimalPath);

	for(int row = 0; row!=matSize; ++row){
		if(minPathSum3way[row][matSize-1]<minSum){
			minSum = minPathSum3way[row][matSize-1];
			minSumRow = row;
			//cout<<"current min 3way path sum is "<<minSum<<endl;
			//print_path(matrix, optimalPath,  row, matSize-1);
			//cout<<endl;
		}
	}
	cout<<"min 3way path sum is "<<minSum<<endl;
	print_path(matrix, optimalPath,  minSumRow, matSize-1);
	
	cin.get();
	return 0;
}