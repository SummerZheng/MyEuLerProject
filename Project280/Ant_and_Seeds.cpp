/*
 * Ant and seeds
 * A laborious ant walks randomly on a 5x5 grid. The walk starts from the central square. At each step, the ant moves to an adjacent square at random, without leaving the grid; thus there are 2, 3 or 4 possible moves at each step depending on the ant's position.
 *
 * At the start of the walk, a seed is placed on each square of the lower row. When the ant isn't carrying a seed and reaches a square of the lower row containing a seed, it will start to carry the seed. The ant will drop the seed on the first empty square of the upper row it eventually reaches.
 *
 * What's the expected number of steps until all seeds have been dropped in the top row? 
 * Give your answer rounded to 6 decimal places.
 */

#include<iostream>
#include<vector>
#include<assert.h>

using namespace std;
typedef vector<vector<int> > grid;
enum direction {up, down, left, right, n_direction};
#define sz 5

template<typename T>
void print(const vector<T> & vec){
  for(int i = 0; i!= vec.size(); i++){
    cout <<vec[i]<<" "; 
  }
  cout <<endl;
}

template<typename T>
void print(const vector<vector<T> >& mat){
  for(int i = 0; i!= mat.size(); i++){
    print(mat[i]);
  }
  cout <<endl;
}

void printGrid(vector<vector<int> >& mat, const int& r, const int& c){
  int ori_val = mat[r][c];
  // mark ant position
  mat[r][c] = 999;
  print(mat);
  mat[r][c] = ori_val;
}

void placeSeed(grid& myGrid){
  for (int col = 0; col != sz; col++){
    myGrid[0][col] = 0;
    myGrid[sz-1][col] = 1;
  } 
}

inline bool out_of_grid(const int& r, const int& c){
  if ( r < 0 || r >= sz || c < 0 || c >= sz)
    return true;
  else
    return false;
}

inline bool stopSatisfied(const grid& myGrid){
  for (int i = 0; i!= sz; i++) {
    if (myGrid[0][i] != 1)
      return false;
  }
  return true;
}

void nextStep(int& i, int& j, int& steps){
  direction dir = static_cast<direction>(rand() % n_direction);
  int i0 = i, j0 = j;
  switch(dir){
    case up: j--; break;
    case down: j++; break;
    case direction::left: i--; break;
    case direction::right: i++; break;
  }
  if (out_of_grid(i, j)) {
    i = i0;
    j = j0;
    nextStep(i, j, steps);
  } else {
    steps++;
  }
}

void go_find_seed(grid& myGrid, int &r, int &c, int &steps, int r0){
  while (r != 4 || myGrid[r][c] == 0) {
    nextStep(r, c, steps);
    //printGrid(myGrid, r, c);
  }
  assert(myGrid[r][c] == 1);
  myGrid[r][c]--;
}

void carry_until_drop(grid& myGrid, int &r, int &c, int &steps, int r0){
  while (r != 0 || myGrid[r][c] > 0){
    nextStep(r, c, steps);
    //printGrid(myGrid, r, c);
  }
  assert(myGrid[r][c] == 0);
  myGrid[r][c]++;
}

int ant_move_seed(grid& myGrid) {
  int steps = 0;
  int r = 2, c = 2, r0;
  while (!stopSatisfied(myGrid)) {
    go_find_seed(myGrid, r, c, steps, r0);
    carry_until_drop(myGrid, r, c, steps, r0);
  }
  return steps; 
}

int main(){
  grid myGrid(sz, vector<int>(sz, 0));
  int Ntot = 1000000;
  double avgSteps = 0;
  for (int sim = 0; sim != Ntot; sim++){
    placeSeed(myGrid);    // Initialize the grid
    srand(sim);           // set random seed for simulation sim
    avgSteps = (avgSteps * sim + ant_move_seed(myGrid)) / (sim + 1);
    if (sim % 10000 == 0)
       cout << "ave move at iteration " << sim << " is " << printf("%10.7f", avgSteps) << "steps" << endl;
  }
  cout << "ave move is " << printf("%10.7f" , avgSteps) << "steps" << endl;
  return 0;
}
