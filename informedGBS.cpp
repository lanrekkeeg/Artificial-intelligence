#include<iostream>
#include<vector>
#include<fstream>
#include<queue>
#include<functional>
using namespace std;

using Queu = priority_queue < pair<int, pair<int, int>>, vector < pair<int, pair<int, int>>>, greater < pair<int, pair<int, int> > >>;
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

int CalculateHeuristic(int i, int j, int goal[][2]) {
	// calculate Euclidean distance between current cell and the goal
	return sqrt((i - goal[0][0])*(i - goal[0][0]) + (j - goal[0][1])*(j - goal[0][1]));
}

void informedGBS(vector<vector<int>>&Maze, Queu &Q, vector<vector<bool>>&visit,
	int goal[][2], int start[][2], int m, int n) {

	int heu = CalculateHeuristic(start[0][0], start[0][1], goal);
	Q.push({ heu,{ start[0][0], start[0][1] } });

	while (!Q.empty()) {
		pair<int, pair<int, int>> val = Q.top();
		Q.pop();

		int i = 0, j = 0;
		i = val.second.first;
		j = val.second.second;

		visit[i][j] = true;
		cout << "( " << i << "," << j << ")" << " |";
		if (is_Goal(goal, i, j)) {
			cout << "Goal found at " << i << "," << j << endl;
			return;
		}

		if (IsValid_move(Maze, visit, (i - 1), j, m, n)) {
			int heu = CalculateHeuristic((i - 1), j, goal);
			Q.push({ heu,{ (i - 1), j } });
		}

		if (IsValid_move(Maze, visit, (1 + i), j, m, n)) {
			int heu = CalculateHeuristic((1 + i), j, goal);
			Q.push({ heu,{ (1 + i), j } });
		}

		if (IsValid_move(Maze, visit, i, (j - 1), m, n)) {
			int heu = CalculateHeuristic(i, (j - 1), goal);
			Q.push({ heu,{ i, (j - 1) } });

		}

		if (IsValid_move(Maze, visit, i, (1 + j), m, n)) {
			int heu = CalculateHeuristic(i, (1 + j), goal);
			Q.push({ heu,{ i, (1 + j) } });
		}


	}
	cout << "No Goal Found!" << endl;

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
	Queu Priority_fringe;

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			in >> Maze[i][j];
			visit[i][j] = false;
			cout << Maze[i][j] << " ";
		}
		cout << endl;
	}
	informedGBS(Maze, Priority_fringe, visit, goal, start, m, n);
}
