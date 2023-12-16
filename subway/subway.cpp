#include <iostream>
#include "subway.h"
#include <stack>
using namespace std;
static int INF = 10000;

Graph::Graph(Node** node_save, Node* nodeIndex, int size, int n_line) :arrSize(size), numLine(n_line) {

	//2���� �迭 ���� �Ҵ�(���� ��ķ� ������ graph)
	weightArr = new double* [arrSize];
	for (int i = 0; i < arrSize; i++) {
		weightArr[i] = new double[arrSize];
	}

	//�ϴ� 2���� �迭 ���� ���Ѵ�� �ʱ�ȭ
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

		if (node_save[i][0].line == node_save[i][1].line) { //ȣ�� ������ 1�� �ɸ�
			weightArr[temp_x][temp_y] = 1;
			weightArr[temp_y][temp_x] = 1;
		}
		else if (node_save[i][0].line != node_save[i][1].line) { //ȣ�� �ٸ��� 30�� �ɸ�
			weightArr[temp_x][temp_y] = 0.5;
			weightArr[temp_y][temp_x] = 0.5;
		}
	}
	//2���� ������ķ� �׷��� ����� ��
}




//�� ��带 �����س��� �迭
void Graph::save_nodeIndex(Node* nodeIndex, int size) {
	newnodeIndex = new Node[size];
	
	for (int i = 0; i < size; i++) {
		newnodeIndex[i] = nodeIndex[i];
	}
}

void Subway::dijkstra(Graph& graph, int s_line, string src, int d_line, string dest,int arrSize) {
	double** weightArr = graph.get_weightArr();          // �� ��带 �����س��� �迭
	Node* nodeIndex = graph.get_new_nodeIndex();         // ����ġ�� ������ �ϰ� ������ķ� ��Ÿ�� �׷���
	int arr_size = arrSize;                              // 2���� �迭�� �� �� ũ��

	int s_temp = 0; // �׷������� ����� �ε��� �ӽ�����
	int d_temp = 0; // �׷������� ������ �ε��� �ӽ�����
	for (int i = 0; i < arrSize; i++) {
		if (nodeIndex[i].line == s_line && nodeIndex[i].sta == src) {
			s_temp = i;
		}
		if (nodeIndex[i].line == d_line && nodeIndex[i].sta == dest) {
			d_temp = i;
		}
	}
	//��������� �˰��� Ǯ�� ���� �迭�� �ʱ�ȭ

	//���⼭���� ���ͽ�Ʈ�� �˰���
	double* dist = new double[arrSize];   // �ִܰŸ� ���
	int* par = new int[arrSize];          // �θ��� ���
	bool* visit = new bool[arrSize];      // �湮�� ��� ���
	saveDP* save = new saveDP[arrSize];   // �� ��庰 �ִܰŸ��� ������� ���

	// �湮��� �ʱ�ȭ
	for (int i = 0; i < arrSize; i++) {
		visit[i] = false;
	}
	//�ִܰŸ� �ʱ�ȭ
	for (int i = 0; i < arrSize; i++) {
		dist[i] = INF;
	}

	//�θ� ��� ��� �ʱ�ȭ
	for (int i = 0; i < arrSize; i++) {
		par[i] = -1;
	}


	int count = 0; //�ݺ����� ù��°�� �ٸ��� �����ϱ� ����
	int visit_count = 0; //visit_end�� true�� ����� ���� ����
	int index = 0;   // �׷������� ����ġ �� ã�� ���� �ε���
	//����� s_temp�̹Ƿ� �� ��带 �������� ����
	while (!visit_end) {
		if (count == 0) {
			dist[s_temp] = 0;      // 1.dist�� ������Ʈ
			par[s_temp] = -1;      // 2.par�� ������Ʈ
			min = dist[s_temp];    // 3.min�� ������Ʈ
			index = s_temp;        // 4.index�� ������Ʈ
			visit[index] = true;   // 5.visit�� ������Ʈ 

			//6.save�� ������Ʈ
			save[index].distance = min;
			save[index].parent = par[index];

			count++;   // �ݺ��� �ι�° ���ʹ� �ٸ��� ����
		}


		else {
			// 1.dist�� 2.par�� ������Ʈ
			for (int i = 0; i < arrSize; i++) {
				if (weightArr[index][i] != INF && !visit[i]) {//�湮�� ���� ���� dist �迭 �ٲٱ�
					//��������� �ִܰŸ����� �� ���� �Ÿ��� ã������ ������Ʈ
					if (min + weightArr[index][i] < dist[i]) {
						dist[i] = min + weightArr[index][i];
						par[i] = index;
					}
				}
			}

			min = INF; // �ּڰ� ������Ʈ ���� �ִ�� ����
			//3.min�� ã��
			for (int i = 0; i < arrSize; i++) {
				if (!visit[i] && dist[i] <= min) {
					min = dist[i];
				}
			}
			
			//4.index�� ã��
			for (int i = 0; i < arrSize; i++) {
				if (dist[i] == min && !visit[i]) {
					index = i;
				}
			}
			
			//5.visit�� ������Ʈ
			visit[index] = true;

			//6.save�� ������Ʈ
			save[index].distance = min;
			save[index].parent = par[index];
		}

		
		//���� ���� �湮������ �ݺ��� ��
		visit_count++;
		if (visit_count == arrSize) {
			visit_end = true;
		}
	}
	// ���ͽ�Ʈ�� �˰��� ǥ �� �������


	// �ִܰŸ��� ���Ե� ��� ������� ����
	int i = d_temp;
	result.push(d_temp);
	second.push(d_temp);      // �ι�° �������� ���� ���� ����

	while (i != -1) {
		i = save[i].parent;
		if (i != -1) {
			result.push(i);
			second.push(i);   // �ι�° �������� ���� ���� ����
		}
	}


	// ȯ�¿����� �ߺ��� �� ������� �ʱ� ���� stack���� �ߺ� ����
	while (!result.empty()) {
		if (temp.empty()) {
			temp.push(result.top());
		}
		else if (nodeIndex[result.top()].sta != nodeIndex[temp.top()].sta) {
			temp.push(result.top());
		}
		result.pop();
	}

	// �ٽ� ��������� ����ϱ� ���� ���� result�� ���� �ű�� 
	while (!temp.empty()) {
		result.push(temp.top());
		temp.pop();
	}

	int i_num = 0;
	int result_num = result.size();
	//�� ���� ���� ������ ����
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
	//������� 1������ ��


	//2�� ���� ����

	second_size = second.size();
	gap_save* result_gap = new gap_save[second_size];

	int j = 0;
	double gap_min; // result_gap �迭���� �ּڰ��� ã�� ����
	while (!second.empty()) {
		//nodeToDest�� �ִܰŸ�-��������� �������� �Ÿ�=���������� �������� �Ÿ� �����
		nodeToDest = dist[d_temp] - save[second.top()].distance;  
		//gap�� ��������� �������� �Ÿ�-���������� �������� �Ÿ�=���� ����
		gap = save[second.top()].distance - nodeToDest;
		
		//resul_gap�� �� ��忡���� �λ���� �ɸ��� �ð� ���̶� �׿� �ش��ϴ� ��� ��ȣ ����
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

	gap_min = INF;   // gap_min �ʱ�ȭ
	// gap_min�� �ð� ���� �ּ�ȭ �Ǵ� �� �ֱ�
	for (int i = 0; i < second_size; i++) {
		if (gap_min > result_gap[i].pos_gap) {
			gap_min = result_gap[i].pos_gap;
		}
	}

	//���� ã���� �ε��� �ʿ��ؼ� result_gap�� index���� temp�� ����
	int temp = 0;
	for (int i = 0; i < second_size; i++) {
		if (result_gap[i].pos_gap == gap_min) {
			temp = result_gap[i].index;
		}
	}

	//����
	middle_name = nodeIndex[temp].sta;
	

	//�ɸ��� �ð�
	double t_min = 0;   // �ɸ��� �ð�(�۰ų� ������)
	double t_max = 0;   // �ɸ��� �ð�(ũ�ų� ������)
	
	//���������� ���������� �ð�
	//���� ���������� �������� �ð����� ���������� �������� �ð��� �� ���
	if (save[temp].distance < (dist[d_temp] - save[temp].distance)) {
		t_min = save[temp].distance;
		t_max = dist[d_temp] - save[temp].distance;
	}
	//���� ���������� �������� �ð����� ���������� �������� �ð��� �� �۰ų� ���ٸ�
	else {
		t_min = dist[d_temp] - save[temp].distance;
		t_max = save[temp].distance;
	}

	// ���2 ���

	//���� ���
	cout << middle_name << endl;

	//�ɸ��ð�(ũ�ų� ���� ��) ���
	int compare_max = static_cast<int>(t_max);
	int compare_max_cout = (t_max - compare_max) * 60;
	if (compare_max_cout == 0) {
		cout << compare_max << ":00" << endl;
	}
	else if (compare_max_cout == 30) {
		cout << compare_max << ":30" << endl;
	}
	
	//�ɸ��� �ð�(�۰ų� ���� ��) ���
	int compare_min = static_cast<int>(t_min);
	int compare_min_cout = (t_min - compare_min) * 60;
	if (compare_min_cout == 0) {
		cout << compare_min << ":00" << endl;
	}
	else if (compare_min_cout == 30) {
		cout << compare_min << ":30" << endl;
	}



	//�޸� ����
	for (int i = 0; i < arrSize; i++) {
		free(weightArr[i]);
	}
	free(weightArr);
	//�޸� ����
	delete[] nodeIndex;
	delete[] dist;
	delete[] par;
	delete[] visit;
	delete[] save;
}