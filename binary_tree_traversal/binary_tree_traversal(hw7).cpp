#include "bt.h"
#include <iostream>
#include <fstream> 
using namespace std;

int main(int argc, char* argv[]) {  
	Tree<double> tree;
	double dval;

	ifstream is(argv[1]);  

	cout << "Enter doubles:\n";

	while (is >> dval) {    
		tree.Insert(dval);
	}
	
	cout << endl;
	cout << "Preorder traversal:";
	tree.Preorder();
	cout << endl << "Inorder traversal:";
	tree.Inorder();
	cout << endl << "Postorder traversal:";
	tree.Postorder();
	cout << endl << "Levelorder traversal:";
	tree.Levelorder();
	cout << endl << "Strack Preorder traversal:";
	tree.StackPreorder();
	cout << endl << "Stack Postorder traversal:";
	tree.StackPostorder();
	cout << endl;
}

