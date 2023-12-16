#include <iostream>
#include "subway.h"
#include <stack>
using namespace std;
static int INF = 10000;

Graph::Graph(Node** node_save, Node* nodeIndex, int size, int n_line) :arrSize(size), numLine(n_line) {

	//2차원 배열 동적 할당(인접 행렬로 구현한 graph)
	weightArr = new double* [arrSize];
	for (int i = 0; i < arrSize; i++) {
		weightArr[i] = new double[arrSize];
	}

	//일단 2차원 배열 전부 무한대로 초기화
	for (int i = 0; i < arrSize; i++) {
		for (int j = 0; j < arrSize; j++) {
			weightArr[i][j] = INF;
		}
	}

	int temp_x = 0;
	int temp_y = 0;
	for (int i = 0; i < numLine; i++) {
		for (int j = 0; j < arrSize; j++) {
			if (node_save[i][0].line == nodeIndex[j].line && node_save[i][0].sta == nodeIndex[j].sta) {
				temp_x = j;
			}
			if (node_save[i][1].line == nodeIndex[j].line && node_save[i][1].sta == nodeIndex[j].sta) {
				temp_y = j;
			}
		}

		if (node_save[i][0].line == node_save[i][1].line) { //호선 같으면 1분 걸림
			weightArr[temp_x][temp_y] = 1;
			weightArr[temp_y][temp_x] = 1;
		}
		else if (node_save[i][0].line != node_save[i][1].line) { //호선 다르면 30초 걸림
			weightArr[temp_x][temp_y] = 0.5;
			weightArr[temp_y][temp_x] = 0.5;
		}
	}
	//2차원 인접행렬로 그래프 만들기 끝
}




//각 노드를 저장해놓은 배열
void Graph::save_nodeIndex(Node* nodeIndex, int size) {
	newnodeIndex = new Node[size];
	
	for (int i = 0; i < size; i++) {
		newnodeIndex[i] = nodeIndex[i];
	}
}

void Subway::dijkstra(Graph& graph, int s_line, string src, int d_line, string dest,int arrSize) {
	double** weightArr = graph.get_weightArr();          // 각 노드를 저장해놓은 배열
	Node* nodeIndex = graph.get_new_nodeIndex();         // 가중치를 값으로 하고 인접행렬로 나타낸 그래프
	int arr_size = arrSize;                              // 2차원 배열의 각 줄 크기

	int s_temp = 0; // 그래프에서 출발지 인덱스 임시저장
	int d_temp = 0; // 그래프에서 도착지 인덱스 임시저장
	for (int i = 0; i < arrSize; i++) {
		if (nodeIndex[i].line == s_line && nodeIndex[i].sta == src) {
			s_temp = i;
		}
		if (nodeIndex[i].line == d_line && nodeIndex[i].sta == dest) {
			d_temp = i;
		}
	}
	//여기까지는 알고리즘 풀기 위한 배열들 초기화

	//여기서부터 다익스트라 알고리즘
	double* dist = new double[arrSize];   // 최단거리 기록
	int* par = new int[arrSize];          // 부모노드 기록
	bool* visit = new bool[arrSize];      // 방문한 노드 기록
	saveDP* save = new saveDP[arrSize];   // 각 노드별 최단거리랑 이전노드 기록

	// 방문기록 초기화
	for (int i = 0; i < arrSize; i++) {
		visit[i] = false;
	}
	//최단거리 초기화
	for (int i = 0; i < arrSize; i++) {
		dist[i] = INF;
	}

	//부모 노드 기록 초기화
	for (int i = 0; i < arrSize; i++) {
		par[i] = -1;
	}


	int count = 0; //반복문의 첫번째만 다르게 저장하기 위함
	int visit_count = 0; //visit_end값 true로 만들기 위한 변수
	int index = 0;   // 그래프에서 가중치 값 찾기 위한 인덱스
	//출발이 s_temp이므로 이 노드를 기준으로 시작
	while (!visit_end) {
		if (count == 0) {
			dist[s_temp] = 0;      // 1.dist값 업데이트
			par[s_temp] = -1;      // 2.par값 업데이트
			min = dist[s_temp];    // 3.min값 업데이트
			index = s_temp;        // 4.index값 업데이트
			visit[index] = true;   // 5.visit값 업데이트 

			//6.save값 업데이트
			save[index].distance = min;
			save[index].parent = par[index];

			count++;   // 반복분 두번째 부터는 다르게 저장
		}


		else {
			// 1.dist랑 2.par값 업데이트
			for (int i = 0; i < arrSize; i++) {
				if (weightArr[index][i] != INF && !visit[i]) {//방문을 안한 노드면 dist 배열 바꾸기
					//현재까지의 최단거리보다 더 작은 거리를 찾았을때 업데이트
					if (min + weightArr[index][i] < dist[i]) {
						dist[i] = min + weightArr[index][i];
						par[i] = index;
					}
				}
			}

			min = INF; // 최솟값 업데이트 위해 최대로 설정
			//3.min값 찾기
			for (int i = 0; i < arrSize; i++) {
				if (!visit[i] && dist[i] <= min) {
					min = dist[i];
				}
			}
			
			//4.index값 찾기
			for (int i = 0; i < arrSize; i++) {
				if (dist[i] == min && !visit[i]) {
					index = i;
				}
			}
			
			//5.visit값 업데이트
			visit[index] = true;

			//6.save값 업데이트
			save[index].distance = min;
			save[index].parent = par[index];
		}

		
		//만약 전부 방문했으면 반복문 끝
		visit_count++;
		if (visit_count == arrSize) {
			visit_end = true;
		}
	}
	// 다익스트라 알고리즘 표 다 만들었음


	// 최단거리에 포함된 노드 순서대로 저장
	int i = d_temp;
	result.push(d_temp);
	second.push(d_temp);      // 두번째 문제에서 쓰기 위한 스택

	while (i != -1) {
		i = save[i].parent;
		if (i != -1) {
			result.push(i);
			second.push(i);   // 두번째 문제에서 쓰기 위한 스택
		}
	}


	// 환승역같이 중복된 역 출력하지 않기 위해 stack에서 중복 제거
	while (!result.empty()) {
		if (temp.empty()) {
			temp.push(result.top());
		}
		else if (nodeIndex[result.top()].sta != nodeIndex[temp.top()].sta) {
			temp.push(result.top());
		}
		result.pop();
	}

	// 다시 출발지부터 출력하기 위해 스택 result로 값들 옮기기 
	while (!temp.empty()) {
		result.push(temp.top());
		temp.pop();
	}

	int i_num = 0;
	int result_num = result.size();
	//그 사이 전부 지나는 역들
	while (!result.empty()) {
		cout << nodeIndex[result.top()].sta << endl;
		result.pop();
		i_num++;
	}

	int compare = static_cast<int>(dist[d_temp]);
	int compare_cout = (dist[d_temp] - compare) * 60;
	if (compare_cout == 0) {
		cout << compare << ":00" << endl;
	}
	else if (compare_cout == 30) {
		cout << compare << ":30" << endl;
	}
	//여기까지 1번문제 끝


	//2번 문제 시작

	second_size = second.size();
	gap_save* result_gap = new gap_save[second_size];

	int j = 0;
	double gap_min; // result_gap 배열에서 최솟값을 찾아 저장
	while (!second.empty()) {
		//nodeToDest에 최단거리-출발지에서 노드까지의 거리=도착지에서 노드까지의 거리 만들기
		nodeToDest = dist[d_temp] - save[second.top()].distance;  
		//gap에 출발지에서 노드까지의 거리-도착지에서 노드까지의 거리=차이 저장
		gap = save[second.top()].distance - nodeToDest;
		
		//resul_gap에 각 노드에서의 두사람이 걸리는 시간 차이랑 그에 해당하는 노드 번호 저장
		result_gap[j].index = second.top();
		if (gap < 0) {
			result_gap[j].pos_gap = -gap;
		}
		else {
			result_gap[j].pos_gap = gap;
		}

		j++;
		second.pop();
	}

	gap_min = INF;   // gap_min 초기화
	// gap_min에 시각 차이 최소화 되는 값 넣기
	for (int i = 0; i < second_size; i++) {
		if (gap_min > result_gap[i].pos_gap) {
			gap_min = result_gap[i].pos_gap;
		}
	}

	//중점 찾을때 인덱스 필요해서 result_gap의 index값을 temp에 저장
	int temp = 0;
	for (int i = 0; i < second_size; i++) {
		if (result_gap[i].pos_gap == gap_min) {
			temp = result_gap[i].index;
		}
	}

	//중점
	middle_name = nodeIndex[temp].sta;
	

	//걸리는 시간
	double t_min = 0;   // 걸리는 시간(작거나 같은값)
	double t_max = 0;   // 걸리는 시간(크거나 같은값)
	
	//시작점에서 중점까지의 시간
	//만약 시작점에서 노드까지의 시간보다 도착점에서 노드까지의 시간이 더 길면
	if (save[temp].distance < (dist[d_temp] - save[temp].distance)) {
		t_min = save[temp].distance;
		t_max = dist[d_temp] - save[temp].distance;
	}
	//만약 시작점에서 노드까지의 시간보다 도착점에서 노드까지의 시간이 더 작거나 같다면
	else {
		t_min = dist[d_temp] - save[temp].distance;
		t_max = save[temp].distance;
	}

	// 결과2 출력

	//중점 출력
	cout << middle_name << endl;

	//걸린시간(크거나 같은 값) 출력
	int compare_max = static_cast<int>(t_max);
	int compare_max_cout = (t_max - compare_max) * 60;
	if (compare_max_cout == 0) {
		cout << compare_max << ":00" << endl;
	}
	else if (compare_max_cout == 30) {
		cout << compare_max << ":30" << endl;
	}
	
	//걸리는 시간(작거나 같은 값) 출력
	int compare_min = static_cast<int>(t_min);
	int compare_min_cout = (t_min - compare_min) * 60;
	if (compare_min_cout == 0) {
		cout << compare_min << ":00" << endl;
	}
	else if (compare_min_cout == 30) {
		cout << compare_min << ":30" << endl;
	}



	//메모리 해제
	for (int i = 0; i < arrSize; i++) {
		free(weightArr[i]);
	}
	free(weightArr);
	//메모리 해제
	delete[] nodeIndex;
	delete[] dist;
	delete[] par;
	delete[] visit;
	delete[] save;
}