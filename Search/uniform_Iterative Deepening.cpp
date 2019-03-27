/*

Problem# 1,2,3,4,5

*/

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

bool is_visit(vector<vector<bool>> &visit, int i, int j) {
	return visit[i][j];
}

int CalculateHeuristic(int i, int j, int goal[][2]) {
	// calculate Euclidean distance between current cell and the goal 
	return sqrt((i - goal[0][0])*(i - goal[0][0]) + (j - goal[0][1])*(j - goal[0][1]));
}

void print(vector<pair<int, int>> &record) {
	for (auto it = record.begin(); it != record.end(); it++) 
		 cout << "{" << it->first << "," << it->second<< "} |";
		
}

void reset(vector<vector<bool>>& visit, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			visit[i][j] = false;
		}
	}
}

void uninform_iterativeDeepening(vector<vector<int>>&Maze, vector<vector<bool>>& visit, 
								vector<pair<int,int>>&record, bool &flag,int i, int j, 
								int goal[][2], int m, int n, int limit_level, int current_level) {

	visit[i][j] = true;
	record.push_back({ i,j });
	if (is_Goal(goal, i, j)) {
		flag = true;
		return;
	}
	if (current_level > limit_level) {
		return;
	}

	
	if (IsValid_move(Maze, visit, (i - 1), j, m, n) && current_level <= limit_level) {
		current_level++;
		uninform_iterativeDeepening(Maze, visit, record, flag, (i - 1), j, goal, m, n, limit_level, current_level);
		//visit[i - 1][j] = true;
		current_level--;
	}

	
	if (IsValid_move(Maze, visit, (1 + i), j, m, n) && current_level <= limit_level) {
		current_level++;
		uninform_iterativeDeepening(Maze, visit, record, flag, (1 + i), j, goal, m, n, limit_level, current_level);
		//visit[1 + i][j] = true;
		current_level--;
	}
	
	if (IsValid_move(Maze, visit, i, (j - 1), m, n) && current_level <= limit_level) {
		current_level++;
		uninform_iterativeDeepening(Maze, visit, record, flag, i, (j - 1), goal, m, n, limit_level, current_level);
		//visit[i][1 - j] = true;
		current_level--;
	}
	
	if (IsValid_move(Maze, visit, i, (1 + j), m, n) && current_level <= limit_level) {
		current_level++;
		uninform_iterativeDeepening(Maze, visit, record, flag, i, (1 + j), goal, m, n, limit_level, current_level);
		//visit[i][1 + j] = true;
		current_level--;
	}
}

void ID_Util(vector<vector<int>>&Maze, vector<vector<bool>>& visit,
	int start[][2], int goal[][2], int m, int n) {

	int level = 1;
	bool flag = false;
	vector<pair<int, int>> record;
	while (level <= (m * n)) {
		uninform_iterativeDeepening(Maze, visit, record, flag, start[0][0], start[0][1], goal, m, n, level, 1);
		if (flag) {
			print(record);
			return;
		}
		record.clear();
		reset(visit, m, n);
		level++;
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
	Queu Priority_fringe;

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			in >> Maze[i][j];
			visit[i][j] = false;
			cout << Maze[i][j] << " ";
		}
		cout << endl;
	}

	ID_Util(Maze, visit, start, goal, m, n);
}