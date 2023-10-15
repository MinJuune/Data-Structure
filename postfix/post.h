#ifndef POSTFIX_H
#define POSTFIX_H

#define ID 257
#define NUM 258
#define EQ 259        // equal to
#define NE 260        // not equal to
#define GE 261        // greater than
#define LE 262        // less than
#define AND 263
#define OR 264
#define UMINUS 265    // unary minus
#define MAXLEN 80     // buffer�� �ִ� ũ��

struct Expression {
	Expression(char* s) :str(s), pos(0) {
		for (len = 0; str[len] != '\0'; len++);
	}

	char* str;     // point to char string
	int pos;       // Expression ���� ���� ��ġ�� [0~len-1] ������ ��
	int len;
};

struct Token {
	bool operator==(char);
	bool operator!=(char);

	Token();                       // ���� 0�� NUM ��ū���� �ʱ�ȭ
	Token(char);                   // 1-�� ��ū:type�� �� ��ū ��ü��
	Token(char, char, int);        // 2-�� ��ū�� �� type
	Token(char*, int, int);        // �ǿ����ڿ� ���� �� type
	bool IsOperand();			   // true if the token is ID or NUM

	int type;                      // ascii code for1-char op; predefined for other tokens
	char* str;                     // token value
	int len;                       // length of str
	int ival;                      // used to store an integer for type NUM;init to 0 for ID
};

/*
ostream& operator<<(ostream&, Token t);
Token NextToken(Expression&, bool);
*/

#endif
