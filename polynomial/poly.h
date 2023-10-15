#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
using namespace std;

class Polynomial;


class Term {
private:
	float coef;
	int exp;

public:
	friend class Polynomial;


	friend istream& operator>>(istream& is, Polynomial& Po);
	friend ostream& operator<<(ostream& os, Polynomial& Po);
};

class Polynomial {
private:
	Term* termArray; // 0이 아닌 항의 배열
	int capacity;    // termArray의 크기
	int terms;       // 0이 아닌 항의 수

public:
	Polynomial() :capacity(1), terms(0) {
		termArray = new Term[capacity];
	}

	void NewTerm(const float theCoeff, const int theExp);

	friend istream& operator>>(istream& is, Polynomial& Po);
	friend ostream& operator<<(ostream& os, Polynomial& Po);

	Polynomial operator+(Polynomial& Po);
	Polynomial operator*(Polynomial& Po);
};


#endif
