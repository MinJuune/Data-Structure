#ifndef _SUBWAY_H_
#define _SUBWAY_H_
#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct Node {
	int line;
	string sta;
};

struct saveDP {
	double distance;
	int parent;
};

struct gap_save {
	double pos_gap;
	int index;
};

class Graph {
private:
	double** weightArr;
	Node* newnodeIndex;
	int arrSize;
	int numLine;
public:
	//Graph 클래스에 가중치 적혀진 2차원 배열 있다
	Graph(Node** node_save, Node* nodeIndex, int size, int n_line);   
	//지하철 그래프에서 각 노드를 저장해놓은 배열
	void save_nodeIndex(Node* nodeIndex, int size);

	double** get_weightArr() {
		return weightArr;
	}

	Node* get_new_nodeIndex() {
		return newnodeIndex;
	}
};

class Subway {
private:
	stack<int> result;         // 결과 기록
	stack<int> temp;           // 중복 제거 용도
	double min=1000;           // 최단거리 기록
	bool visit_end=false;      // 전부 방문했을때 반복문 끝내기 위한 변수

	stack<int> second;         // 두번째 문제 풀때 필요한 스택(최단거리 노드 들어있음)
	double nodeToDest = 0;     // 두번째 문제 풀때 도착지에서 노드까지 거리 
	double gap = 0;            // 두번째 문제 풀때 각 노드까지 두사람이 걸리는 시간의 차이
	int second_size = 0;       // 두번째 문제 풀때 second스택의 size
	string middle_name;        // 중점 저장
public:
	void dijkstra(Graph& graph, int s_line, string src, int d_line, string dest, int arrSize);
};

#endif
