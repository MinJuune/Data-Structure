#ifndef _SORT_H_
#define _SORT_H_
#include <iostream>
using namespace std;

class Sort {
private:
public:
	void InsertionSort(int* a, const int n);
	int partition(int* a, int low, int high);
	void QuickSort(int* a, int low, int high);
	void maxHeap(int* a, const int root, const int n);
	void HeapSort(int* a, const int n);
	void Merge(int* a, int left, int mid, int right);
	void MergeSort(int* a, int left, int right);
};

void Sort::InsertionSort(int* a, const int n) {
	for (int i = 1; i < n; i++) {
		int temp = a[i];
		int j = i - 1;

		//temp보다 큰 원소는 오른쪽으로 이동
		while (j >= 0 && a[j] > temp) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = temp;
	}
}


int Sort::partition(int* a, int low, int high) {
	int pivot = a[high];
	int i = low - 1;

	for (int j = low; j <= high - 1; j++) {
		if (a[j] < pivot) {
			i++;
			swap(a[i], a[j]);
		}
	}
	swap(a[i + 1], a[high]);
	return i + 1;
}

void Sort::QuickSort(int* a, int low, int high) {
	while (low < high) {
		int pivotIndex = partition(a, low, high);

		if (pivotIndex - low < high - pivotIndex) {
			QuickSort(a, low, pivotIndex - 1);
			low = pivotIndex + 1;
		}
		else {
			QuickSort(a, pivotIndex + 1, high);
			high = pivotIndex - 1;
		}
	}
}


void Sort::maxHeap(int* a, const int root, const int n) {
	int rootNode = root;   //루트 노드
	int leftChild = 2 * root + 1; //왼쪽 자식 노드
	int rightChild = 2 * root + 2; //오른쪽 자식노드

	//왼쪽 자식이 루트보다 크면 root 갱신
	if (leftChild < n && a[leftChild] > a[rootNode]) {
		rootNode = leftChild;
	}

	//오른쪽 자식이 루트보다 크면 root 갱신
	if (rightChild<n && a[rightChild]>a[rootNode]) {
		rootNode = rightChild;
	}

	//rootNode가 루트가 아니라면 교환후 재귀 호출
	if (rootNode != root) {
		swap(a[root], a[rootNode]);
		maxHeap(a, rootNode, n);
	}
}


void Sort::HeapSort(int* a, const int n) {
	//초기 히프 구성
	for (int i = n / 2 - 1; i >= 0; i--) {
		maxHeap(a, i, n);
	}

	//배열을 하나씩 히프에서 추출하여 정렬
	for (int i = n - 1; i > 0; i--) {
		swap(a[0], a[i]);
		maxHeap(a, 0, i);
	}
}


//두개의 정렬된 배열을 합치는 함수
void Sort::Merge(int* a, int left, int mid, int right) {
	int n1 = mid - left + 1; //왼쪽 배열의 크기
	int n2 = right - mid; //오른쪽 배열의 크기

	//임시 배열을 생성하여 데이터 복사
	int* leftArr = new int[n1];
	int* rightArr = new int[n2];

	for (int i = 0; i < n1; i++) {
		leftArr[i] = a[left + i];
	}
	for (int i = 0; i < n2; i++) {
		rightArr[i] = a[mid + 1 + i];
	}

	//두 배열을 합병하여 정렬된 배열 생성
	int i = 0;
	int j = 0;
	int k = left;
	while (i < n1 && j < n2) {
		if (leftArr[i] <= rightArr[j]) {
			a[k] = leftArr[i];
			i++;
		}
		else {
			a[k] = rightArr[j];
			j++;
		}
		k++;
	}

	//남은 원소들 복사
	while (i < n1) {
		a[k] = leftArr[i];
		i++;
		k++;
	}

	while (j < n2) {
		a[k] = rightArr[j];
		j++;
		k++;
	}
}

void Sort::MergeSort(int* a, int left, int right) {
	int mid;
	if (left < right) {
		mid = left + (right - left) / 2;

		//왼쪽과 오른쪽 부분 배열에 대해 재귀적으로 합병 정렬 수행
		MergeSort(a, left, mid);
		MergeSort(a, mid + 1, right);

		//정렬된 두 배열 합병
		Merge(a, left, mid, right);
	}
}



#endif
