#include <iostream>
#include <fstream>
#include "list.h"
using namespace std;

int main(int argc, char* argv[]) {
	intList il;
	int input;

	ifstream is(argv[1]);

	cout << "===============input=========" << endl;

	while (1) {
		is >> input;
		if (input == -1) {
			break;
		}

		il.Insert(input);
		cout << il;
	}

	cout << "=========Delete========" << endl;
	input = 0;
	while (1) {
		is >> input;
		if (input == -1) {
			break;
		}
		il.Delete(input);
		cout << il;
	}
	

	//push_front와 push_back은 2회씩
	cout << "=======Push_Front============" << endl;
	is >> input;
	il.Push_Front(input);
	cout << il;

	is >> input;
	il.Push_Front(input);
	cout << il;

	cout << "==============Push_Back======" << endl;
	is >> input;
	il.Push_Back(input);
	cout << il;

	is >> input;
	il.Push_Back(input);
	cout << il;
}