#include "subway.h"
#include <fstream>
#include <string>


int main(int argc, char* argv[]) {
	int numLine;
	int line1, line2;
	string src, dst;
	int arrSize = 0; //2차원 배열 크기 알기 위함

	if (argc != 3) {
		cerr << "Argument Count is " << argc << endl << "Argument must be  " << argc << endl;
		return 1;
	}

	// 입력받아서 그래프 만들기
	fstream fin(argv[1]);
	if (!fin) {
		cerr << argv[1] << " open failed" << endl;
		return 1;
	}

	//간선 개수 입력 받음
	fin >> numLine;


	//데이터 저장 시작
	
	//2차원 배열 동적 할당(노드 전부 저장)
	Node** node_save = new Node* [numLine];
	for (int i = 0; i < numLine; i++) {
		node_save[i] = new Node[2];
	}
	
	//환승때문에 배열의 크기를 몰라 일단 최대 값으로
	int numLine2 = 2 * numLine; 
	//1차원 배열 동적 할당
	//(node_save에 저장한 2차원 노드들을 1차원으로 바꾸고 중복되는 값은 쓰레기값 처리)
	Node* nodes = new Node[numLine2];  

	// 데이터를 2차원 배열에 저장하기 위해 일단 각 노드 추출
	for (int i = 0; i < numLine; i++) {
		int s_line, d_line;
		double weight;
		string source, dest;
		int s_count = 0; //배열에 노드 저장할때 중복 방지용
		int d_count = 0; //배열에 노드 저장할때 중복 방지용

		//입력 받고
		fin >> s_line >> source >> d_line >> dest;

		//일단 저장
		node_save[i][0].line = s_line;
		node_save[i][0].sta = source;
		node_save[i][1].line = d_line;
		node_save[i][1].sta = dest;

		//호선 다르면 30초(환승), 호선 같으면 1분
		if (s_line != d_line) {
			weight = 0.5;
		}
		else {
			weight = 1;
		}
		
		//각 노드를 동적으로 배열에 추가
		for (int j = 0; j < numLine2; j++) {
			if (nodes[j].line == s_line && nodes[j].sta == source) {
				s_count++;
			}
			if (nodes[j].line == d_line && nodes[j].sta == dest) {
				d_count++;
			}
		}
		if (s_count == 0) {
			nodes[i].line = s_line;
			nodes[i].sta = source;
			arrSize++;
		}
		if (d_count == 0) {
			nodes[i + numLine].line = d_line;
			nodes[i + numLine].sta = dest;
			arrSize++;
		}
	}
	//2차원 배열의 크기가 정해짐(최단거리 알고리즘 풀기 위한 그래프)

	int temp = 0;
	//1차원 배열 동적 할당
	Node* nodeIndex = new Node[arrSize];
	for (int i = 0; i < numLine2; i++) {
		if (nodes[i].line > 0 && nodes[i].line < 10) { //호선이 쓰레기 값이 아니라면(1~9호선 이라면)
			nodeIndex[temp].line = nodes[i].line;
			nodeIndex[temp].sta = nodes[i].sta;
			temp++;
		}
	}
	//1차원 배열 nodes에는 쓰레기 값도 같이 있었는데
	//1차원 배열 nodeIndex로 의미 있는 값만 옮기기

	//nodeIndex로 의미 있는 값은 옮겼고 nodes는 더이상 쓸일이 없으므로 메모리 해제
	delete[] nodes;

	//main에서 구한 node_save배열과nodeIndex배열로 그래프(2차원 인접배열) 만들기
	Graph myGraph(node_save, nodeIndex, arrSize, numLine);
	//그래프의 각 노드를 저장해놓은 배열
	myGraph.save_nodeIndex(nodeIndex, arrSize);

	//weightArr만드는데 필요했고 이제는 쓸모없는 2차원 배열 node_save 메모리 해제
	for (int i = 0; i < numLine; i++) {
		delete[] node_save[i];
	}
	delete[] node_save;
	//nodeIndex는 Graph 클래스에서 쓰면 되므로 메모리 해제
	delete[] nodeIndex;
	
	//데이터 저장 끝


	fin.close();

	// 출발지 도착지 입력 받기
	fstream fin2(argv[2]);
	if (!fin2) {
		cerr << argv[2] << " open failed" << endl;
		return 1;
	}

	fin2 >> line1 >> src;
	fin2 >> line2 >> dst;

	fin2.close();
	
	double time = 0;
	Subway mySubway;
	// 1번 문제 결과 출력
	mySubway.dijkstra(myGraph, line1, src, line2, dst, arrSize);
	
	return 0;	
}