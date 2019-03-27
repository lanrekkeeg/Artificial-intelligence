/*
sudoku solver using simple forward checking


*/


#include<iostream>
#include<vector>
#include<windows.h>
using namespace std;

using Forward = vector<vector<vector<int>>>;

void intializeer(Forward &square) {
	for (int i = 0; i < 9; i++)
		for (int k = 0; k < 9; k++) {
			for (int j = 0; j < 9; j++) {
				square[i][k][j] = false;

			}
		}
}

int getSubGridN(int row, int col) {
	if (row < 2)return (col < 2) ? 1 : 2;
	else {
		return (col < 2) ? 3 : 4;
	}

}

bool validate_SubGrid(int val, int row, int col, vector<vector<int>> &Grid) {


	int r = (row / 3) * 3;
	int c = (col / 3) * 3;

	int rowend = r + 3;
	int colend = c + 3;

	for (int i = r; i < rowend; i++) {
		for (int k = c; k < colend; k++)
			if (Grid[i][k] == val) {
				return false;
			}
	}

	return true;

}

bool validate_row_col(int row, int col, int val, vector<vector<int>> &Grid) {
	for (int k = 0; k < Grid.size(); k++) {

		if (Grid[row][k] == val)  return false;
		if (Grid[k][col] == val)return false;
	}

	return true;
}

int is_Fixed_Value(int row, int col, vector<pair<int, int>> &fix) {

	for (int i = 0; i < fix.size(); i++) {
		if (fix[i].first == row && fix[i].second == col)return true;
	}
	return false;
}

void print(vector<vector<int>> &Grid) {
	for (int i = 0; i < Grid.size(); i++) {
		for (int k = 0; k < Grid.size(); k++) {
			cout << Grid[i][k] << " ";
		}
		cout << endl;
	}
}

void show(Forward square) {

	for (int i = 0; i < 9; i++) {
		for (int k = 0; k < 9; k++) {
			for (int j = 0; j < 9; j++) {
				cout << square[i][k][j] << " ";

			}
			cout << "   ";
		}
		cout << endl;
	}
}

void reassign(Forward &forGrid, int row, int col, int val) {
	for (int i = col; i < 9; i++) {
		forGrid[row][i][val - 1] = false;

	}
	for (int i = row; i < 9; i++) {
		forGrid[i][col][val - 1] = false;


	}
}

bool simple_check(Forward &forGrid, int row, int col, int val) {

	int count = 0;
	for (int k = col; k < 9; k++) {
		for (int j = 0; j < 9; j++) {
			if (forGrid[row - 1][k][j] == true)count++;

		}
		if (count == 9)return true;
		else count = 0;
	}
	count = 0;
	for (int k = row; k < 9; k++) {
		for (int j = 0; j < 9; j++) {
			if (forGrid[k][col - 1][j] == false)count++;;

		}
		if (count == 9)return true;
		else count = 0;
	}

	return false;
}

void forwardchecking(Forward &forGrid, int row, int col, int val) {

	for (int i = col; i < 9; i++) {
		if (!forGrid[row][i][val - 1]) {
			forGrid[row][i][val - 1] = true;

		}

	}
	for (int i = row + 1; i < 9; i++) {
		if (!forGrid[i][col][val - 1]) {
			forGrid[i][col][val - 1] = true;

		}

	}
}

bool back_tracking(vector<vector<int>>&Grid, int row, int col, int size, vector<pair<int, int>> &fix,
	Forward &Forw) {

	static bool Grid_is_solve = false;
	if (col == Grid.size() && row == Grid.size() - 1) {
		cout << "Grid is solved" << endl;
		Grid_is_solve = true;
		return false;
	}

	if (col >= size) {
		row++;
		col = 0;
	}
	if (is_Fixed_Value(row, col, fix)) {
		back_tracking(Grid, row, 1 + col, size, fix, Forw);
	}
	else {

		int val = Grid[row][col];
		for (int i = 1; i <= 10; i++) {
			val++;
			if (Grid_is_solve)return 0;
			if (val >= 10) {
				Grid[row][col] = 0;
				return true;
			}
			else if (validate_row_col(row, col, val, Grid) && validate_SubGrid(val, row, col, Grid)) {

				forwardchecking(Forw, row, col, val);

				if (simple_check(Forw, row + 1, col + 1, val)) {
					//cout << "save u " << endl;
					reassign(Forw, row, col, val);
					return true;
				}

				Grid[row][col] = val;

				if (back_tracking(Grid, row, 1 + col, size, fix, Forw)) {
					reassign(Forw, row, col, val);
				}

			}
		}
	}
}


void main() {
	Forward squareArray(9, vector<vector<int>>(9, vector<int>(9)));
	vector<vector<int>> Grid = { { 0, 4, 0, 0, 0, 0, 0, 5, 0 },
	{ 0, 0, 9, 0, 8, 2, 0, 4, 0 },
	{ 0, 0, 8, 1, 0, 5, 9, 0, 0 },
	{ 7, 6, 0, 0, 0, 0, 0, 0, 0 },
	{ 8, 0, 5, 0, 2, 0, 4, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 2, 5 },
	{ 0, 0, 0, 3, 0, 1, 2, 0, 0 },
	{ 0, 3, 0, 2, 6, 0, 5, 0, 0 },
	{ 0, 8, 0, 0, 0, 0, 0, 6, 0 } };

	vector<pair<int, int>> FixedPlace;

	intializeer(squareArray);
	for (int i = 0; i < 9; i++)
		for (int k = 0; k < 9; k++) {
			if (Grid[i][k] != 0) {
				FixedPlace.push_back({ i,k });
				//forwardchecking(squareArray, i, k, Grid[i][k]);
			}
		}
	intializeer(squareArray);

	back_tracking(Grid, 0, 0, Grid.size(), FixedPlace, squareArray);
	print(Grid);
}
