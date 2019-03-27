/*
		sudoku solver using simple backtracking
		

*/


#include<iostream>
#include<vector>
using namespace std;

void intializeer(vector<vector<bool>> &Grid) {
	for (int i = 0; i < Grid.size(); i++)
		for (int k = 0; k < Grid.size(); k++) {
			Grid[i][k] = false;
		}
}

int getSubGridN(int row, int col) {
	if (row < 2)return (col < 2) ? 1 : 2;
	else {
		return (col < 2) ? 3 : 4;
	}

}

bool validate_SubGrid(int val, int row, int col, vector<vector<bool>> &subGrid) {
	int GridN = getSubGridN(row, col);
	return (subGrid[GridN-1][val-1]) ? false : true;
}

bool validate_row_col(int row, int col, int val, vector<vector<int>> &Grid) {
		for (int k = 0; k < Grid.size(); k++) {
			if (k != col) {
				if (Grid[row][k] == val)  return false; 
			}
			if(k != row)
				if (Grid[k][col] == val)return false;
		}
		
	return true;
}

int is_Fixed_Value(int row, int col, vector<pair<int, int>> &fix){
	
	for (int i = 0; i < fix.size(); i++) {
		if (fix[i].first == row && fix[i].second == col)return true;
	}
	return false;
}

void print_(vector<vector<bool>> &Grid) {
	cout << "printing subGrid" << endl;
	for (int i = 0; i < Grid.size(); i++) {
		for (int k = 0; k < Grid.size(); k++) {
			cout << Grid[i][k] << " ";
		}
		cout << endl;
	}
}

void print(vector<vector<int>> &Grid) {
	for (int i = 0; i < Grid.size(); i++) {
		for (int k = 0; k < Grid.size(); k++) {
			cout << Grid[i][k] << " ";
		}
		cout << endl;
	}
}

bool rough_sol(vector<vector<int>>&Grid, int row,int col, int size, vector<pair<int, int>> &fix,
				vector<vector<bool>>&subGridN) {

	static bool Grid_is_solve = false;
	if (col == Grid.size() && row == Grid.size() - 1) {
		cout << "Grid is solved" << endl;
		Grid_is_solve = true;
		return 0; // return to recursive if
	}

	if (col >= size) { 
		row++;
		col = 0;
	}
	
	if (is_Fixed_Value(row, col, fix)) {
		rough_sol(Grid, row, 1 + col, size, fix, subGridN);
	}
	else {
		int val = Grid[row][col];
		for (int i = 1; i <= 4;i++) {
			val++;
			if (Grid_is_solve)return 0;
			if (val >= 5) {
				Grid[row][col] = 0;
				return true;
			}
			else if (validate_row_col(row, col, val, Grid) && validate_SubGrid(val, row, col, subGridN)) {
				Grid[row][col] = val;
				subGridN[getSubGridN(row, col) - 1][val - 1] = true;
				if (rough_sol(Grid, row, 1 + col, size, fix, subGridN)) {
					int subGV = getSubGridN(row, col);
					subGridN[subGV - 1][val - 1] = false;
				}

			}
		}
	}
}

void main() {
	vector<vector<int>> Grid_0 = { {1,0,0,4},
								   {0,0,0,0},
								   {0,3,2,0},
								   {0,0,0,0} };
								   
	vector<pair<int, int>> FixedPlace = { {0,0},{0,3},{2,1},{2,2} };
	vector<vector<bool>>Grid(4, vector<bool>(4));
	
	intializeer(Grid);
	Grid[0][0] = true;
	Grid[1][3] = true;
	Grid[2][2] = true;
	Grid[3][1] = true;

	rough_sol(Grid_0, 0, 0, Grid.size(), FixedPlace, Grid);
	print(Grid_0);
}