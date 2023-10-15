#include <iostream>
#include "polyb.h"
using namespace std;


istream& operator>>(istream& is, Polynomial& Po) {
	int noofterms;
	float coef;
	int exp;

	is >> noofterms;

	for (int i = 0; i < noofterms; i++) {
		is >> coef >> exp;
		Po.NewTerm(coef, exp);
	}

	return is;
}

ostream& operator<<(ostream& os, Polynomial& Po) {
	for (int i = 0; i < Po.capacity - 1; i++) {
		if (i != 0) {
			if (Po.termArray[i].coef > 0) {
				cout << " + ";
			}
			else {
				cout << " ";
			}

		}

		if (Po.termArray[i].exp != 0) {
			if (Po.termArray[i].coef == 1.0) {
				if (Po.termArray[i].exp > 1) {
					os << "x^" << Po.termArray[i].exp;
				}
				else if (Po.termArray[i].exp == 1) {
					os << "x";
				}
			}
			else if (Po.termArray[i].coef == -1.0) {
				if (Po.termArray[i].exp > 1) {
					os << "-x^" << Po.termArray[i].exp;
				}
				else if (Po.termArray[i].exp == 1) {
					os << "-x";
				}

			}


			else {
				if (Po.termArray[i].exp == 1) {
					os << Po.termArray[i].coef << "x";
				}
				else if (Po.termArray[i].exp > 1) {
					os << Po.termArray[i].coef << "x^" << Po.termArray[i].exp;
				}
			}
		}
		else if (Po.termArray[i].exp == 0) {
			cout << Po.termArray[i].coef;
		}



	}
	cout << endl;

	return os;
}

void Polynomial::NewTerm(const float theCoeff, const int theExp) {
	//다항식 뒤에 새로운 항을 추가하는 함수

	if (terms == capacity) {
		capacity = 2 * capacity;
		Term* newTermArray = new Term[capacity];

		copy(termArray, termArray + terms, newTermArray);

		delete[] termArray;
		termArray = newTermArray;
	}

	termArray[terms].coef = theCoeff;
	termArray[terms].exp = theExp;

	terms++;
	capacity++;
}

Polynomial Polynomial::operator+(Polynomial& b) {
	Polynomial c;
	int aPos = 0;
	int bPos = 0;

	while ((aPos < terms) && (bPos < terms)) {
		if (termArray[aPos].exp == b.termArray[bPos].exp) {
			float t = termArray[aPos].coef + b.termArray[bPos].coef;
			c.NewTerm(t, termArray[aPos].exp);
			aPos++;
			bPos++;
		}

		else if (termArray[aPos].exp < b.termArray[bPos].exp) {
			c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++;
		}

		else {
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
	}

	for (; aPos < terms; aPos++) {
		c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	}
	for (; bPos < b.terms; bPos++) {
		c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
	}

	return c;
}

