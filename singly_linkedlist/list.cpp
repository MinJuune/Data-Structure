#include <iostream>
#include "list.h"

ostream& operator<<(ostream& os, intList& il) {
	Node* ptr = il.first;
	while (ptr != NULL) {
		os << ptr->data << " ";
		ptr = ptr->link;
	}
	os << endl;
	return os;
}

void intList::Push_Back(int e) {
	if (!first) {
		first = last = new Node(e);
	}
	else {
		last->link = new Node(e);
		last = last->link;
	}
}

void intList::Push_Front(int e) {
	if (!first) {
		first = last = new Node(e);
	}
	else {
		Node* newdata = new Node;
		newdata->data = e;
		newdata->link = first;
		first = newdata;
	}
}

void intList::Insert(int e) {
	Node* newdata = new Node;
	Node* temp = new Node;
	temp = first;

	if (!first) {
		newdata->data = e;
		first = newdata;
		last = newdata;
	}
	else if (first->data >= e) {
		newdata->data = e;
		newdata->link = first;
		first = newdata;
	}
	else {
		if (temp != last) {
			if (temp->link->data >= e) {
				newdata->data = e;
				newdata->link = temp->link;
				temp->link = newdata;
			}
			else {
				temp = temp->link;
			}
		}
		if (temp == last) {
			newdata->data = e;
			last->link = newdata;
			last = newdata;
		}
	}
}

void intList::Delete(int e) {
	if (first) {
		Node* temp = new Node;
		temp = first;
		
		if (first->data == e) {
			first = first->link;
			free(temp);
		}
		else {
			while (temp!=last) {
				if (temp->link != last) {
					if (temp->link->data == e) {
						temp->link = temp->link->link;
						break;
					}
					else {
						temp = temp->link;
					}
				}
				else if (temp->link == last) {
					if (temp->link->data == e) {
						temp->link = NULL;
						last = temp;
						break;
					}
					else {
						temp = temp->link;
					}
				}
				else {
					temp = temp->link;
				}
			}
		}
	}
	else {
		cout << "empty list" << endl;
	}
}
