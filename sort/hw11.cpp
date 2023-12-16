#include <iostream>
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include "sort.h"
#include <time.h>
#define CLOCK_PERSEC ((clock_t)1000)
using namespace std;

int main(int argc, char* argv[]) {
	int T = atoi(argv[1]);   // num of test case
	cout << "T=" << T << endl;

	Sort mysort;
	int N;         // �� �׽�Ʈ���̽� �� ���ڵ��� ����
	int i;         // iterator
	double result_temp;
	double result[4]; // result �迭�� �� �˰��� ���� ����ð��� �����ϰ� �ȴ�.
	/*
	result[0]: insertion sort
	result[1]: quick sort
	result[2]: natural merge sort
	result[3]: heap sort
	*/

	typedef double clock_t;

	if (argc < 3) {
		cerr << "wrong argument count" << endl;
		return 1;
	}
	cout << "--INS--|--QUICK--|--NATMH--|--HEAP--|" << endl;
	


	//���⼭���� ���� �˾Ƽ� ��
	for (int i = 2; i < T + 2; i++) {
		Sort mysort;

		fstream fin(argv[i]);

		int num_size = 0;    // ���� ù��°�� �ִ� �� ���Ͽ� ����ִ� ���� ����

		fin >> num_size;

		int* arr = new int[num_size];
		int* arr_temp_insert = new int[num_size];
		int* arr_temp_quick = new int[num_size];
		int* arr_temp_merge = new int[num_size];
		int* arr_temp_heap = new int[num_size];


		int num_data = 0;
		for (int j = 0; j < num_size; j++) {  
			fin >> num_data;
			arr[j] = num_data;   //�Է� ������ �ϴ� ���� �迭�� ����
			arr_temp_insert[j] = num_data;
			arr_temp_quick[j] = num_data;
			arr_temp_merge[j] = num_data;
			arr_temp_heap[j] = num_data;
		}
		fin.close();

		//-----------------------INSERTION--------------------
		
		//���� ���� ��ġ
		clock_t startTime = clock();
		mysort.InsertionSort(arr_temp_insert, num_size);  // ��������	
		//���� ���� ��ġ
		clock_t endTime = clock();

		//���� �ð� ���(ms����)
		clock_t elapsed = endTime - startTime;

		//Second�� ��ȯ
		double timeInSecond = (double)(elapsed / CLOCKS_PER_SEC);

		//result�� ����
		result[0] = timeInSecond;

		//----------------QUICK--------------------
		
		//���� ���� ��ġ
		startTime = clock();
		//���� ���� ��ġ
		startTime = clock();
		mysort.QuickSort(arr_temp_quick, 0, num_size - 1);  // ������	
		
		//���� ���� ��ġ
		endTime = clock();

		//���� �ð� ���(ms����)
		elapsed = endTime - startTime;

		//Second�� ��ȯ
		timeInSecond = (double)(elapsed / CLOCKS_PER_SEC);

		//result�� ����
		result[1] = timeInSecond;

		//-----------------MERGE---------------
		
		//���� ���� ��ġ
		startTime = clock();

		mysort.MergeSort(arr_temp_merge, 0, num_size - 1);  // �պ�����	
		
		//���� ���� ��ġ
		endTime = clock();

		//���� �ð� ���(ms����)
		elapsed = endTime - startTime;

		//Second�� ��ȯ
		timeInSecond = (double)(elapsed / CLOCKS_PER_SEC);

		//result�� ����
		result[2] = timeInSecond;

		//-----------------HEAP----------------
		
		//���� ���� ��ġ
		startTime = clock();

		mysort.HeapSort(arr_temp_heap, num_size);  // ��������	
		
		//���� ���� ��ġ
		endTime = clock();

		//���� �ð� ���(ms����)
		elapsed = endTime - startTime;

		//Second�� ��ȯ
		timeInSecond = (double)(elapsed / CLOCKS_PER_SEC);

		//result�� ����
		result[3] = timeInSecond;

		cout.precision(5);
		cout << fixed;
		for (int j = 0; j < 4; j++) {
			cout << result[j] << "|";
		}cout << "N=" << num_size << endl;
	}	
}
