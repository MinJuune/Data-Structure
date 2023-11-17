#ifndef _MAXHEAP_H_
#define _MAXHEAP_H_
#include <iostream>
using namespace std;

//아래 3 함수 완성하기
//void ChangeSize1D(int);
//void Push(const T &);
//void Pop();


template <class T>
class Maxheap {
private:
	void ChangeSize1D(int);
	T* heap;
	int heapSize;
	int capacity;
public:
	Maxheap(int _capacity = 10) :heapSize(0) {
		if (_capacity < 1) {
			throw " Must be > 0";
		}
		capacity = _capacity;
		heap = new T[capacity + 1];
	}
	void Push(const T&);
	void Pop();
	bool IsEmpty() {
		return heapSize == 0;
	}
	T Top() {
		return heap[1];
	}
	template <class T2> friend ostream& operator<<(ostream&, Maxheap<T2>&);
};

template <class T>
ostream& operator<<(ostream& os, Maxheap<T>& H) {
	os << "<Heap contents>";
	int i;
	for (i = 1; i <= H.heapSize; i++) {
		os << i << ":" << H.heap[i] << " ";
	}
	os << endl;
	return os;
}


template <class T>
void Maxheap<T>::Push(const T& e) {
	int currentNode = ++this->heapSize;

	while (currentNode != 1 && this->heap[currentNode / 2] < e) {
		this->heap[currentNode] = this->heap[currentNode / 2];
		currentNode /= 2;
	}
	this->heap[currentNode] = e;
}

template <class T>
void Maxheap<T>::Pop() {
	//최대 원소를 삭제한다. 
	if (IsEmpty()) {
		throw "Heap is empty. Cannot delete";
	}
	heap[1].~T(); //최대 원소 삭제
	
	//히프의 마지막 원소 제거
	T lastE = heap[heapSize--];

	int currentNode = 1; //루프
	int child = 2;       // currentNode의 자식
	while (child <= heapSize) {
		//child를 currentNode의 큰자식으로 결정
		if (child < heapSize && heap[child] < heap[child + 1]) {
			child++;
		}

		//currentNode에 lastE를 삽입할수 있는가?
		if (lastE >= heap[child]) {
			break;
		}

		//no
		heap[currentNode] = heap[child];
		currentNode = child;
		child *= 2;
	}
	heap[currentNode]=lastE;
}

template <class T>
void Maxheap<T>::ChangeSize1D(int new_capacity) {
	T* tmp = new T[new_capacity];
	copy(this->heap, this->heap + this->capacity.tmp);
	delete this->heap;
	this->heap = tmp;
}

#endif