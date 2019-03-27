#include<iostream>
#include<vector>
#include<fstream>
#include<queue>
using namespace std;

void getFile(ifstream &in, string filename) {

	in.open(filename);
}

bool assert(int i, int j, int m, int n) {
	if (i <= -1 || i >= m || j <= -1 || j >= n) return true;
	else return false;
}

bool IsValid_move(vector<vector<int>>&Maze, vector<vector<bool>>&visit, int i, int j, int m, int n) {
	if (assert(i, j, m, n)) {
		return false;
	}
	if (Maze[i][j] == 1)return false;
	else if (visit[i][j])return false;
	else return true;

}
bool is_Goal(int goal[][2], int i, int j) {

	return (goal[0][0] == i && goal[0][1] == j) ? true : false;

}

bool is_visit(vector<vector<bool>> &visit, int i, int j) {
	return visit[i][j];
}

void uninformedDfs(vector<vector<int>>&Maze, vector<vector<bool>>& visit,
	int i, int j, int goal[][2], int m, int n) {

	static bool flag = true;
	cout << "( " << i << "," << j << ")" << " |";
	visit[i][j] = true;

	if (is_Goal(goal, i, j)) {
		cout << "Goal found at " << i << "," << j << endl;
		flag = false;
		return;
	}

	if (IsValid_move(Maze, visit, (i-1), j, m, n) && flag) {

		uninformedDfs(Maze, visit, i - 1, j, goal, m, n);
		//visit[1 - i][j] = true;
	}


	if (IsValid_move(Maze, visit, (1 + i), j, m, n) && flag) {

		uninformedDfs(Maze, visit, (1 + i), j, goal, m, n);
		//visit[1 + i][j] = true;
	}
	
	if (IsValid_move(Maze, visit, i, (j - 1), m, n) && flag) {
		uninformedDfs(Maze, visit, i, (j - 1), goal, m, n);
		//visit[i][1 - j] = true;
	}
	
	if (IsValid_move(Maze, visit, i, (1 + j), m, n) && flag) {
		uninformedDfs(Maze, visit, i, 1 + j, goal, m, n);
		//visit[i][1 + j] = true;
	}

}


void DFS_Util(vector<vector<int>>&Maze, vector<vector<bool>>& visit,
	int start[][2], int goal[][2], int m, int n) {

	uninformedDfs(Maze, visit, start[0][0], start[0][1], goal, m, n);
}

int main() {

	int m = 0, n = 0;
	int goal[1][2];
	int start[1][2];
	ifstream in;
	ofstream out;
	getFile(in, "in.txt");
	in >> m >> n;
	in >> start[0][0] >> start[0][1];
	in >> goal[0][0] >> goal[0][1];
	goal[0][0]--, goal[0][1]--;
	vector<vector<int>>Maze(m, vector<int>(n));
	vector<vector<bool>>visit(m, vector<bool>(n));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			in >> Maze[i][j];
			visit[i][j] = false;
			cout << Maze[i][j] << " ";
		}
		cout << endl;
	}
	DFS_Util(Maze, visit, start, goal, m, n);

}