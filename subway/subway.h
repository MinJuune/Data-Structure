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
	//Graph Ŭ������ ����ġ ������ 2���� �迭 �ִ�
	Graph(Node** node_save, Node* nodeIndex, int size, int n_line);   
	//����ö �׷������� �� ��带 �����س��� �迭
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
	stack<int> result;         // ��� ���
	stack<int> temp;           // �ߺ� ���� �뵵
	double min=1000;           // �ִܰŸ� ���
	bool visit_end=false;      // ���� �湮������ �ݺ��� ������ ���� ����

	stack<int> second;         // �ι�° ���� Ǯ�� �ʿ��� ����(�ִܰŸ� ��� �������)
	double nodeToDest = 0;     // �ι�° ���� Ǯ�� ���������� ������ �Ÿ� 
	double gap = 0;            // �ι�° ���� Ǯ�� �� ������ �λ���� �ɸ��� �ð��� ����
	int second_size = 0;       // �ι�° ���� Ǯ�� second������ size
	string middle_name;        // ���� ����
public:
	void dijkstra(Graph& graph, int s_line, string src, int d_line, string dest, int arrSize);
};

#endif
