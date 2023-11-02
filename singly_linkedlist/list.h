using namespace std;

struct Node {
	Node(int d = 0, Node* l = nullptr):data(d),link(l){}
	int data;
	Node* link;
};

struct intList {
	intList() {
		last = first = NULL;
	}

	void Push_Back(int);
	void Push_Front(int);
	void Insert(int);
	void Delete(int);
	Node* first;
	Node* last;
};

ostream& operator<<(ostream&, intList&);
