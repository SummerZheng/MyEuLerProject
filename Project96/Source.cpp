#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>

using namespace std;

typedef vector<vector<int>> matrix2D;
typedef vector<matrix2D> matrix3D;

int dim=9, deadEndNum = 999;

void print(const vector<int> &a){
	for (int j=0; j!=a.size(); ++j)
		cout<<a[j]<<" ";
	cout<<endl;
}

void print(const matrix2D &tb){
	for (int i=0; i!=tb.size(); ++i){
		vector<int> row = tb[i];
		print(row);
	}
}

inline bool rowNotFull(matrix2D &sudoku, int r){
	for(int c=0; c!=dim; c++)
		if(sudoku[r][c]==0)
			return true;
	return false;
}
int detNextGrid(matrix2D &sudoku){
	vector<int> rowKnown(dim), colKnown(dim);
	int maxRowKnown, curRKnown, maxColKnown, curCKnown, maxR, maxC;
	maxRowKnown=-1; maxR=0;
	for(int r=0; r!=dim; r++){
		curRKnown=0;
		for(int c=0; c!=dim; c++){
			if(sudoku[r][c]!=0)
				curRKnown++;
		}
		if(curRKnown>maxRowKnown && rowNotFull(sudoku, r)){
			maxRowKnown = curRKnown;
			maxR = r;
		}
	}	
	maxColKnown=-1; maxC=0;
	for(int c=0; c!=dim; c++){
		if(sudoku[maxR][c]==0){
			curCKnown=0;
			for(int r=0; r!=dim; r++){
				if(sudoku[r][c]!=0)
					curCKnown++;
			}
			if(curCKnown>maxColKnown){
				maxColKnown = curCKnown;
				maxC = c;
			}
		}
	}
	return 10*maxR+maxC;
}

inline bool usedRow(matrix2D &sudoku, int n, int r){
	for(int c=0; c!=dim; c++){
		if(sudoku[r][c]==n)
			return true;
	}
	return false;
}

inline bool usedCol(matrix2D &sudoku, int n, int c){
	for(int r=0; r!=dim; r++){
		if(sudoku[r][c]==n)
			return true;
	}
	return false;
}

inline bool usedBox(matrix2D &sudoku, int n, int r, int c){
	int boxR = r/3, boxC = c/3;
	for(int r=boxR*3; r!=boxR*3+3; r++){
		for(int c=boxC*3; c!=boxC*3+3; c++){
			if(sudoku[r][c]==n)
				return true;
		}
	}
	return false;
}

int tryNextNum(matrix2D &sudoku, int r, int c, int startN){
	int trialN = deadEndNum;
	for(int n=startN+1; n<=dim; n++){
		if(usedRow(sudoku, n, r))
			continue;
		if(usedCol(sudoku, n, c))
			continue;
		if(usedBox(sudoku, n, r, c))
			continue;
		trialN = n;
		break;
	}
	return trialN;
}

void solveSudoku(matrix2D &sudoku){
	int grid2try=0;
	for(int r=0; r!=dim; r++){
		for(int c=0; c!=dim; c++){
			if (sudoku[r][c]==0)
				grid2try++;
		}
	}
	vector<int> trialTrajactory(grid2try, -1);
	int trialGridCount = 0;
	int r, c, gridNum;
	while(trialGridCount<grid2try){
		gridNum = detNextGrid(sudoku);
		r=gridNum/10, c=gridNum%10;
		trialTrajactory[trialGridCount++] = gridNum;
		int trialNum = tryNextNum(sudoku, r, c, 0);
		//cout<<"trial row = "<<r+1<<", col = "<<c+1<<", trialN = "<<trialNum<<endl;
		if(trialNum==deadEndNum){
			trialGridCount--;
			do{
				gridNum = trialTrajactory[--trialGridCount];
				r=gridNum/10, c=gridNum%10;
				int startN = sudoku[r][c];
				sudoku[r][c]=0;
				trialNum = tryNextNum(sudoku, r, c, startN);
				//cout<<"trial row = "<<r+1<<", col = "<<c+1<<", trialN = "<<trialNum<<endl;
			}while(trialNum == deadEndNum);
			trialGridCount++;
		}
		sudoku[r][c] = trialNum;
	}
}

int main(){
	int numPuzzles = 50;
	matrix2D sudoku(dim, vector<int>(dim));
	matrix3D sudokuPuzzles(numPuzzles, sudoku);

	string input_filename = "sudoku.txt";
	ifstream infile(input_filename);
	string numstr;
	int n=-1, row=0;
	while (infile.good()){
		getline(infile, numstr);
		//cout<<numstr<<endl;
		if(numstr[0]=='G'){
			n++; row=0;
		}else{
			for(int col=0; col!=9; col++)
				sudokuPuzzles[n][row][col] = numstr[col]-'0';
			row++;
		}
	}

	int outputSum = 0;
	for(int n=0; n!=numPuzzles; n++){
		matrix2D curPuzzle = sudokuPuzzles[n];
		//print(curPuzzle);
		solveSudoku(curPuzzle);
		outputSum += (100*curPuzzle[0][0] + 10*curPuzzle[0][1] + curPuzzle[0][2]);
		//print(curPuzzle);
	}

	cout<<outputSum<<endl;
	cin.get();
	return 0;
}