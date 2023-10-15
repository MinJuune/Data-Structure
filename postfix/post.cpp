#include <iostream>
#include <stack>
#include "post.h"
using namespace std;

bool Token::operator==(char b) {
	return len == 1 && str[0] == b;
}

bool Token::operator!=(char b) {
	return len != 1 || str[0] != b;
}

Token::Token() {}

Token::Token(char c) :len(1), type(c) {
	str = new char[1];
	str[0] = c;
} // default type = c itself


Token::Token(char c, char c2, int ty) :len(2), type(ty) {
	str = new char[2];
	str[0] = c;
	str[1] = c2;
}

Token::Token(char* arr, int l, int ty = ID) :len(l), type(ty) {
	str = new char[len + 1];
	for (int i = 0; i < len; i++) {
		str[i] = arr[i];
	}
	str[len] = '\0';

	if (type == NUM) {
		ival = arr[0] - '0';
		for (int i = 1; i < len; i++) {
			ival = ival * 10 + arr[i] - '0';
		}
	}
	else if (type == ID) {
		ival = 0;
	}
	else throw "must be ID or NUM";
}

bool Token::IsOperand() {
	return type == ID || type == NUM;
}

ostream& operator<<(ostream& os, Token t) {
	if (t.type == UMINUS) {
		os << "-u";
	}
	else if (t.type == NUM) {
		os << t.ival;
	}
	else {
		for (int i = 0; i < t.len; i++) {
			os << t.str[i];
		}
	}
	os << " ";
	return os;
}

bool GetID(Expression& e, Token& tok) {
	char arr[MAXLEN];
	int idlen = 0;
	char c = e.str[e.pos];

	if (!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')) {  // c가 문자가 아니면 false 
		return false;
	}

	arr[idlen++] = c;   // c가 문자면 arr에 c저장해 놓고 idlen 하나 더 올리기
	e.pos++;            // 현재위치도 올리기

	while (((c = e.str[e.pos]) >= 'a' && c <= 'z') // c가 영어 문자이거나
		|| (c >= 'A' && c <= 'Z')                  // c가 영어 문자이거나
		|| (c >= '0' && c <= '9')) {                // c가 0에서 9사이의 숫자이면은
		arr[idlen++] = c;                           // arr에 c저장해 놓고 idlen 하나 더 올리기
		e.pos++;                                    // 현재위치도 올리기
	}

	arr[idlen] = '\0';                              // c가 문자나 숫자가 아니라 루프 탈추하면 마지막에 널문자 추가
	tok = Token(arr, idlen, ID);                    // return an ID 
	return true;

}

bool GetInt(Expression& e, Token& tok) {
	char arr[MAXLEN];
	int intlen = 0;
	char c = e.str[e.pos];

	if (!(c >= '0' && c <= '9')) {                   // c가 숫자가 아니면 false 
		return false;
	}

	arr[intlen++] = c;                               // c가 숫자면 arr에 c저장해놓고 intlen 하나 더 올리기
	e.pos++;										 // 현재위치도 올리기

	while ((c = e.str[e.pos]) >= '0' && c <= '9') {      // c가 0에서 9사이의 숫자이면은
		arr[intlen++] = c;                           // arr에 c저장해 놓고 idlen 하나 더 올리기
		e.pos++;                                     // 현재위치도 올리기
	}

	arr[intlen] = '\0';
	tok = Token(arr, intlen, NUM);
	return true;
}

void SkipBlanks(Expression& e) {
	char c;
	while (e.pos < e.len && ((c = e.str[e.pos]) == ' ' || c == '\t')) {
		e.pos++;									// 만약 빈칸이면 현재위치 올리기
	}
}

//*************************
bool TwoCharOp(Expression& e, Token& tok) {
	// 7가지 두 글자 토큰들 <= >= == != && || -u를 처리
	char c = e.str[e.pos];                          // 첫번째로 받은거는 현재위치에 넣기
	char c2 = e.str[e.pos + 1];                     // 두번째로 받은거는 현재위치 다음칸에 넣기
	int op;                                         // op는 왜 만듬

	if (c == '<' && c2 == '=') {                    // LE
		op = LE;
	}
	else if (c == '=' && c2 == '=') {                     // EQ
		op = EQ;
	}
	else if (c == '!' && c2 == '=') {                // NE
		op = NE;
	}
	else if (c == '>' && c2 == '=') {                // GE
		op = GE;
	}
	else if (c == '&' && c2 == '&') {               // AND
		op = AND;
	}
	else if (c == '|' && c2 == '|') {               // OR
		op = OR;
	}
	else if (c == '-' && (c2 >= '0' && c2 <= '9')) {               // UMINUS
		op = UMINUS;
	}
	else {
		return false;   // 맞는 두 글자 토큰이 아니면 false를 return 
	}

	tok = Token(c, c2, op);      // Token에 두개의 문자랑 타입 저장

	e.pos += 2;                  // 문자가 두개니까 현재위치도 두계단 올림
	return true;
}

bool OneCharOp(Expression& e, Token& tok) {  // 1-char 토큰들 처리 ex) + - = 이런 한글자짜리
	char c = e.str[e.pos];
	if (c == '-' || c == '!' || c == '*' || c == '/' || c == '%' || c == '+' || c == '<' ||
		c == '>' || c == '(' || c == ')' || c == '=') {  // 1글짜짜리 토큰이면
		tok = Token(c);                                  // 토큰에 c 넣고
		e.pos++;                                         // 현재위치 올리고
		return true;                                     // true 반환
	}
	return false;
}



Token NextToken(Expression& e, bool INFIX = true) {
	static bool oprrFound = true;   // 종전에 연산자 발견되었다고 가정
	Token tok;
	SkipBlanks(e);    // skip blanks if any

	if (e.pos == e.len) { // No more token left in this expression
		if (INFIX) {
			oprrFound = true;
			return Token('#');
		}
	}

	if (GetID(e, tok) || GetInt(e, tok)) {
		if (INFIX) {
			oprrFound = false;
			return tok;
		}
	}
	if (TwoCharOp(e, tok) || OneCharOp(e, tok)) {
		if (tok.type == '-' && INFIX && oprrFound) {   // operator 후 - 발견
			tok = Token('-', 'u', UMINUS);             // unary minus(-u)로 바꾸시오
		}
		if (INFIX) {
			oprrFound = true;
			return tok;
		}
	}

	throw "illegal Character Found";
}

int icp(Token& t) {   // in-coming priority
	int ty = t.type;

	if (ty == '(') {                                              // ty가 '('면 0
		return 0;
	}
	else if (ty == UMINUS || ty == '!') {                         // UMINUS나 '!'면 1
		return 1;
	}
	else if (ty == '*' || ty == '/' || ty == '%') {               // '*'나 '/'나 '%'면 2
		return 2;
	}
	else if (ty == '+' || ty == '-') {                             // '+'나 '-'면 3
		return 3;
	}
	else if (ty == '<' || ty == '>' || ty == LE || ty == GE) {    // '<'나 '>'나 LE나 GE면 4 
		return 4;
	}
	else if (ty == EQ || ty == NE) {                              // EQ나 NE면 5   
		return 5;
	}
	else if (ty == AND) {                                         // AND면 6
		return 6;
	}
	else if (ty == OR) {                                          // OR이면 7     
		return 7;
	}
	else if (ty == '=') {                                         // '='이면 8
		return 8;
	}
	else if (ty == '#') {                                         // '#'면 10을 return 한다. 
		return 10;
	}
}

int isp(Token& t) {   //in-stack priority
	int ty = t.type;  // stack 에서의 우선순위 결정

	if (ty == '(') {                                              // ty가 '('면 0
		return 9;
	}
	else if (ty == UMINUS || ty == '!') {                         // UMINUS나 '!'면 1
		return 1;
	}
	else if (ty == '*' || ty == '/' || ty == '%') {               // '*'나 '/'나 '%'면 2
		return 2;
	}
	else if (ty == '+' || ty == '-') {                             // '+'나 '-'면 3
		return 3;
	}
	else if (ty == '<' || ty == '>' || ty == LE || ty == GE) {    // '<'나 '>'나 LE나 GE면 4 
		return 4;
	}
	else if (ty == EQ || ty == NE) {                              // EQ나 NE면 5   
		return 5;
	}
	else if (ty == AND) {                                         // AND면 6
		return 6;
	}
	else if (ty == OR) {                                          // OR이면 7     
		return 7;
	}
	else if (ty == '=') {                                         // '='이면 8
		return 8;
	}
	else if (ty == '#') {                                         // '#'면 10을 return 한다. 
		return 10;
	}
}

void Postfix(Expression e) {
	stack<Token> s;
	s.push('#');

	for (Token x = NextToken(e); x != '#'; x = NextToken(e)) {
		if (x.IsOperand()) {   //if (x == NUM || x==ID)이건 왜 틀림?
			cout << x;
		}
		else if (x == ')') {
			//'('까지 스택에서 꺼냄
			for (; s.top() != '('; s.pop()) {
				cout << s.top();
			}
			s.pop(); // '('꺼내기
		}
		else {  //x는 연산자 operator
			for (; isp(s.top()) <= icp(x); s.pop()) {
				if (x == '=' && s.top() == '=') {
					break;
				}
				cout << s.top();
				if (x == '=' && s.top() == '=') {        // 강의록에서 넣으라고 해서 넣음
					break;
				}
			}
			s.push(x);
		}
	}

	//수식의 끝; 공백 스택
	//for (; !s.empty(); cout << s.top(), s.pop());
	//cout << endl;
	//이거를 아래 while문으로 바꾸기
	while (s.top() != '#') {
		cout << s.top();
		s.pop();
	}
	s.pop();
}
