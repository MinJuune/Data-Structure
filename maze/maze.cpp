#include <iostream>
#include <stack>
#include <fstream>
using namespace std;

const int MAXSIZE = 100;
bool maze[MAXSIZE + 2][MAXSIZE + 2];
bool mark[MAXSIZE + 1][MAXSIZE + 1] = { 0 };

enum directions { N, NE, E, SE, S, SW, W, NW };   //N=0, NE=1 이렇게 순서가 매겨짐



struct offsets {
	int a, b;
}move_d[8] = { {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1} };

struct Items {
	Items(int xx = 0, int yy = 0, int dd = 0) :x(xx), y(yy), dir(dd) {}
	int x, y, dir;
};

template <typename T>
ostream& operator<<(ostream& os, stack<T>& s) {
	stack<T> temp;

	while (!s.empty()) {
		temp.push(s.top());
		s.pop();
	}

	cout << " ";
	while (!temp.empty()) {
		os <<"-> "<< temp.top() << " ";
		temp.pop();
	}

	return os;
}

ostream& operator<<(ostream& os,const Items& item) {
	//5개의 Items가 출력될때마다 줄바꿈
	static int count = 0;
	os << "(" << item.x << "," << item.y << ")";
	count++;
	if ((count % 5) == 0) {
		cout << endl;
	}
	return os;
}

void getdata(istream& is, int& m, int& p) {
	is >> m >> p;
	for (int i = 0; i < m + 2; i++) {
		maze[i][0] = 1;
		maze[i][p + 1] = 1;
	}
	for (int j = 1; j <= p; j++) {
		maze[0][j] = 1;
		maze[m + 1][j] = 1;
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= p; j++) {
			is >> maze[i][j];
		}
	}
}

void path(const int m, const int p) {
	mark[1][1] = 1;            // visited node
	stack<Items> s;            // stack
	Items temp(1, 1, E);       // 첫번째
	s.push(temp);              // 현재 진행 상황

	while (!s.empty()) {
		temp = s.top();
		s.pop();

		int i = temp.x;
		int j = temp.y;
		int d = temp.dir;

		while (d < 8) {
			int g = i + move_d[d].a;
			int h = j + move_d[d].b;

			if ((g == m) && (h == p)) {
				// 출구 도착
				cout << s;
				cout << "-> (" << i << " " << j << ")" << endl; //마지막 두 위치
				cout << "-> (" << m << " " << p << ")" << endl; //m이랑 p
				return;
			}
			else if ((!maze[g][h]) && (!mark[g][h])) {
				// 갈수 있는 미로고 아직 안갔으면
				mark[g][h] = 1;
				temp.x = i;
				temp.y = j;
				temp.dir = d + 1;
				s.push(temp);

				i = g;
				j = h;
				d = N;  // (g,h)로 이동
			}
			else {
				d++;
			}
		}
		cout << "No path in maze" << endl;
	}
}



int main(int argc, char* argv[]) {
	int m, p; //m by p maze
	if (argc == 1) {
		cerr << "usage: " << argv[0] << "maze_data_file" << endl;
	}
	else {
		ifstream is(argv[1]);
		if (!is) {
			cerr << argv[1] << "does not exist\n";
			exit(1);
		}
		cout << "for maze datafile (" << argv[1] << ")\n";
		getdata(is, m, p);
		is.close();
		path(m, p);
	}
}
