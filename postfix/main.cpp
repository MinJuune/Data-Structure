#include <iostream>
#include <fstream>
#include "post.h"
using namespace std;

void Postfix(Expression);


bool getdata(istream& is, char a[], int maxlen) {
	if (is.getline(a, maxlen, '\n')) {
		return true;
	}
	else {
		return false;
	}
}


int main(int argc, char* argv[]) {
	char line[MAXLEN];          // 80

	ifstream is(argv[1]);

	cout << "학번 이름 : B911028 김민준" << endl;
	while (getdata(is, line, MAXLEN)) {
		Expression e(line);                 // line 버퍼를 이용하여 Expression을 읽음

		try {
			Postfix(e);
			cout << endl;
		}

		catch (char const* msg) {
			cerr << "Exception:" << msg << endl;
		}
	}
}


