#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> matrix2D;

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
void print(const vector<T> &a){
	for (int j=0; j!=a.size(); ++j)
		cout<<a[j]<<" ";
	cout<<endl;
}

int SplitWayTable_TopDown(matrix2D &splitWayTable, int NtoSplit, int maxSubN){
	//cout<<"NtoSplit = "<<NtoSplit<<"; maxSubN = "<<maxSubN<<endl;
	if(splitWayTable[NtoSplit][maxSubN]>=0)
		return splitWayTable[NtoSplit][maxSubN];
	if(maxSubN==0){
		splitWayTable[NtoSplit][maxSubN] = 1;
	}else{
		if (NtoSplit == maxSubN)
			splitWayTable[NtoSplit][maxSubN] = SplitWayTable_TopDown(splitWayTable, NtoSplit, maxSubN-1) + 1;
		else{
			int nextNtoSplit = NtoSplit-maxSubN-1;
			int nextMaxSubN = nextNtoSplit>maxSubN?maxSubN:nextNtoSplit;
			splitWayTable[NtoSplit][maxSubN] = SplitWayTable_TopDown(splitWayTable, NtoSplit, maxSubN-1) + SplitWayTable_TopDown(splitWayTable, nextNtoSplit, nextMaxSubN);		
		}
	}
	return splitWayTable[NtoSplit][maxSubN];
}
/*
int calculateSumWays(int nTosplit, int maxSubN, const vector<vector<int>> &splitWayTable){
	if (maxSubN == 1){
		return 1;
	}else{
		int numWays = 0;
		//cout<<nTosplit<<" "<<maxSubN;
		int row = nTosplit-maxSubN-1;
		maxSubN = (nTosplit-maxSubN)>=maxSubN? maxSubN: nTosplit-maxSubN;
		//cout<<"new maxSubN "<<maxSubN<<endl;
		//cout<<"numWays:";
		for(int i=1; i<=maxSubN; ++i){
			//cout<<" + "<<splitWayTable[row][i-1];
			numWays += splitWayTable[row][i-1];
		}
		//cout<<" = "<<numWays<<endl;
		return  numWays;
	}
}

void constructSplitTable_BottomUp(vector<vector<int>> &splitWayTable){
	int size = splitWayTable.size();
	for (int i=0; i!=size; ++i){
		splitWayTable[i][0] = 1;	//1 way to split n = 1 + 1+ ..+1 (n x 1)
		splitWayTable[i][i] = 1;	//1 way to split n = n (1 x n)
	}
	for (int i=1; i!=size; ++i){
		for(int j=1; j<i; ++j){
			splitWayTable[i][j] = calculateSumWays(i+1, j+1, splitWayTable);
		}
		//print(splitWayTable);
		//cout<<endl;
	}
}
*/
int main(){
	int maxN = 5;
	matrix2D splitWayTable(maxN, vector<int>(maxN, -1));
	/*
	constructSplitTable_BottomUp(splitWayTable);
	//print(splitWayTable);

	int numWays = 0;
	for (int i=1; i<maxN; ++i){
		numWays += splitWayTable[maxN-1][i-1];
	}
	cout<<"There are "<<numWays<<" ways to split "<<maxN<<endl;
	*/
	cout<<"There are "<<SplitWayTable_TopDown(splitWayTable, maxN-1, maxN-1)-1<<" ways to split "<<maxN<<endl;
	//print(splitWayTable);

	cin.get();
	return 0;
}