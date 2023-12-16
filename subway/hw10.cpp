#include "subway.h"
#include <fstream>
#include <string>


int main(int argc, char* argv[]) {
	int numLine;
	int line1, line2;
	string src, dst;
	int arrSize = 0; //2���� �迭 ũ�� �˱� ����

	if (argc != 3) {
		cerr << "Argument Count is " << argc << endl << "Argument must be  " << argc << endl;
		return 1;
	}

	// �Է¹޾Ƽ� �׷��� �����
	fstream fin(argv[1]);
	if (!fin) {
		cerr << argv[1] << " open failed" << endl;
		return 1;
	}

	//���� ���� �Է� ����
	fin >> numLine;


	//������ ���� ����
	
	//2���� �迭 ���� �Ҵ�(��� ���� ����)
	Node** node_save = new Node* [numLine];
	for (int i = 0; i < numLine; i++) {
		node_save[i] = new Node[2];
	}
	
	//ȯ�¶����� �迭�� ũ�⸦ ���� �ϴ� �ִ� ������
	int numLine2 = 2 * numLine; 
	//1���� �迭 ���� �Ҵ�
	//(node_save�� ������ 2���� ������ 1�������� �ٲٰ� �ߺ��Ǵ� ���� �����Ⱚ ó��)
	Node* nodes = new Node[numLine2];  

	// �����͸� 2���� �迭�� �����ϱ� ���� �ϴ� �� ��� ����
	for (int i = 0; i < numLine; i++) {
		int s_line, d_line;
		double weight;
		string source, dest;
		int s_count = 0; //�迭�� ��� �����Ҷ� �ߺ� ������
		int d_count = 0; //�迭�� ��� �����Ҷ� �ߺ� ������

		//�Է� �ް�
		fin >> s_line >> source >> d_line >> dest;

		//�ϴ� ����
		node_save[i][0].line = s_line;
		node_save[i][0].sta = source;
		node_save[i][1].line = d_line;
		node_save[i][1].sta = dest;

		//ȣ�� �ٸ��� 30��(ȯ��), ȣ�� ������ 1��
		if (s_line != d_line) {
			weight = 0.5;
		}
		else {
			weight = 1;
		}
		
		//�� ��带 �������� �迭�� �߰�
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
	//2���� �迭�� ũ�Ⱑ ������(�ִܰŸ� �˰��� Ǯ�� ���� �׷���)

	int temp = 0;
	//1���� �迭 ���� �Ҵ�
	Node* nodeIndex = new Node[arrSize];
	for (int i = 0; i < numLine2; i++) {
		if (nodes[i].line > 0 && nodes[i].line < 10) { //ȣ���� ������ ���� �ƴ϶��(1~9ȣ�� �̶��)
			nodeIndex[temp].line = nodes[i].line;
			nodeIndex[temp].sta = nodes[i].sta;
			temp++;
		}
	}
	//1���� �迭 nodes���� ������ ���� ���� �־��µ�
	//1���� �迭 nodeIndex�� �ǹ� �ִ� ���� �ű��

	//nodeIndex�� �ǹ� �ִ� ���� �Ű�� nodes�� ���̻� ������ �����Ƿ� �޸� ����
	delete[] nodes;

	//main���� ���� node_save�迭��nodeIndex�迭�� �׷���(2���� �����迭) �����
	Graph myGraph(node_save, nodeIndex, arrSize, numLine);
	//�׷����� �� ��带 �����س��� �迭
	myGraph.save_nodeIndex(nodeIndex, arrSize);

	//weightArr����µ� �ʿ��߰� ������ ������� 2���� �迭 node_save �޸� ����
	for (int i = 0; i < numLine; i++) {
		delete[] node_save[i];
	}
	delete[] node_save;
	//nodeIndex�� Graph Ŭ�������� ���� �ǹǷ� �޸� ����
	delete[] nodeIndex;
	
	//������ ���� ��


	fin.close();

	// ����� ������ �Է� �ޱ�
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
	// 1�� ���� ��� ���
	mySubway.dijkstra(myGraph, line1, src, line2, dst, arrSize);
	
	return 0;	
}