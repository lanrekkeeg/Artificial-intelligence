/*

Problem# 1,2,3,4,5

*/

#include<iostream>
#include<vector>
#include<fstream>
#include<queue>
using namespace std;

void getFile(ifstream &in, string filename) {

	in.open(filename);
}

bool assert(int i, int j, int m, int n) {
	if (i <=-1 || i >= m || j <= -1 || j >= n) return true;
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

void uninformedBfs(vector<vector<int>>&Maze, vector<vector<bool>>& visit, queue<pair<int,int>>&que,
					int start[][2], int goal[][2], int m, int n) {

	que.push({ start[0][0],start[0][1] });
	while (!que.empty()) {
		pair<int, int> t = que.front();
		que.pop();
		int i = t.first, j = t.second;
		cout << "( " << i << "," << j << ")" << " |";

		if (is_Goal(goal, i, j)) {
			cout << "Goal found at " <<i<<","<<j<< endl;
			return;
		}

		visit[i][j] = true;

		if (is_Goal(goal, (1 - i), j)) {
			cout << "Goal found" << i-1 << "," << j << endl;
			return;
		}
		else if (IsValid_move(Maze, visit, (1 - i), j, m, n)) {
			
			que.push({ (1 - i), j });
			visit[1 - i][j] = true;
		}

		if (is_Goal(goal, (1+i), j)) {
			cout << "Goal found" << i+1 << "," << j << endl;
			return;
		}
		else if (IsValid_move(Maze, visit, (1 + i), j, m, n)) {
			que.push({(1 + i), j});
			
			visit[1 + i][j] = true;
		}
		if (is_Goal(goal, i, (1-j))) {
			cout << "Goal found" << i << "," << 1-j << endl;
			return;
		}
		else if (IsValid_move(Maze, visit, i, (1 - j), m, n)) {
			que.push({ i, (1-j) });
			visit[i][1-j] = true;
		}
		if (is_Goal(goal, i, (1 + j))) {
			cout << "Goal found" << i << "," << 1+j << endl;
			return;
		}
		else if (IsValid_move(Maze, visit, i, (1 + j), m, n)) {
			que.push({ i, (1+j) });
			visit[i][1+j] = true;
		}

	}


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
	queue<pair<int,int>> que;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			in>> Maze[i][j];
			visit[i][j] = false;
			cout<< Maze[i][j]<< " ";
		}
		cout << endl;
	}
	uninformedBfs(Maze, visit, que, start, goal, m, n);
}