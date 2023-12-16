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
	int N;         // 각 테스트케이스 별 레코드의 길이
	int i;         // iterator
	double result_temp;
	double result[4]; // result 배열에 각 알고리즘 별로 실행시간을 저장하게 된다.
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
	


	//여기서부턴 내가 알아서 함
	for (int i = 2; i < T + 2; i++) {
		Sort mysort;

		fstream fin(argv[i]);

		int num_size = 0;    // 파일 첫번째에 있는 이 파일에 들어있는 숫자 갯수

		fin >> num_size;

		int* arr = new int[num_size];
		int* arr_temp_insert = new int[num_size];
		int* arr_temp_quick = new int[num_size];
		int* arr_temp_merge = new int[num_size];
		int* arr_temp_heap = new int[num_size];


		int num_data = 0;
		for (int j = 0; j < num_size; j++) {  
			fin >> num_data;
			arr[j] = num_data;   //입력 데이터 일단 전부 배열에 저장
			arr_temp_insert[j] = num_data;
			arr_temp_quick[j] = num_data;
			arr_temp_merge[j] = num_data;
			arr_temp_heap[j] = num_data;
		}
		fin.close();

		//-----------------------INSERTION--------------------
		
		//측정 시작 위치
		clock_t startTime = clock();
		mysort.InsertionSort(arr_temp_insert, num_size);  // 삽입정렬	
		//측정 종료 위치
		clock_t endTime = clock();

		//측정 시간 계산(ms단위)
		clock_t elapsed = endTime - startTime;

		//Second로 변환
		double timeInSecond = (double)(elapsed / CLOCKS_PER_SEC);

		//result에 저장
		result[0] = timeInSecond;

		//----------------QUICK--------------------
		
		//측정 시작 위치
		startTime = clock();
		//측정 시작 위치
		startTime = clock();
		mysort.QuickSort(arr_temp_quick, 0, num_size - 1);  // 퀵정렬	
		
		//측정 종료 위치
		endTime = clock();

		//측정 시간 계산(ms단위)
		elapsed = endTime - startTime;

		//Second로 변환
		timeInSecond = (double)(elapsed / CLOCKS_PER_SEC);

		//result에 저장
		result[1] = timeInSecond;

		//-----------------MERGE---------------
		
		//측정 시작 위치
		startTime = clock();

		mysort.MergeSort(arr_temp_merge, 0, num_size - 1);  // 합병정렬	
		
		//측정 종료 위치
		endTime = clock();

		//측정 시간 계산(ms단위)
		elapsed = endTime - startTime;

		//Second로 변환
		timeInSecond = (double)(elapsed / CLOCKS_PER_SEC);

		//result에 저장
		result[2] = timeInSecond;

		//-----------------HEAP----------------
		
		//측정 시작 위치
		startTime = clock();

		mysort.HeapSort(arr_temp_heap, num_size);  // 히프정렬	
		
		//측정 종료 위치
		endTime = clock();

		//측정 시간 계산(ms단위)
		elapsed = endTime - startTime;

		//Second로 변환
		timeInSecond = (double)(elapsed / CLOCKS_PER_SEC);

		//result에 저장
		result[3] = timeInSecond;

		cout.precision(5);
		cout << fixed;
		for (int j = 0; j < 4; j++) {
			cout << result[j] << "|";
		}cout << "N=" << num_size << endl;
	}	
}
