#include <string>
#include <iostream>
#include "Stack.h"
#include <conio.h>
#include <Windows.h>

using namespace std;

struct Node
{
	int val;

	Node* l;
	Node* r;

	Node(int _key=0, Node* _l = NULL, Node* _r = NULL) :
		val(_key), l(_l), r(_r) {}
};

void printLTR(ostream& o, Node* _root)
{
	if (_root == NULL) return;
	printLTR(o, _root->l);
	cout << _root->val << ' ';
	printLTR(o, _root->r);
}

class Text
{
	Node* curr;
	Node* root;
	Stack<Node*> path;

	
public:
	Text() {
		root = NULL;
		Node* l2 = new Node(15);
		Node* l1 = new Node(10);
		root = new Node(12, l1, l2);

		curr = root;
	}

	Node* FindKey(Node* tmp, int key)
	{
		stack_clear();
		if (tmp == NULL)
			throw "Not found";
		if (key == tmp->val)
			return tmp;
		if (key < tmp->val)
		{
			path.push(tmp);
			return FindKey(tmp->l, key);
		}
		else
		{
			path.push(tmp);
			return FindKey(tmp->r, key);
		}
	}

	Node* getroot()
	{
		return root;
	}

	void add(int key)
	{
		Node* res = new Node(key);

		if (root == NULL)
		{
			root = res;
			return;
		}

		Node* x = root;
		Node* y = x;

		while (x != NULL)
		{
			y = x;
			if (key < x->val) 
				x = x->l;
			else
			{
				x = x->r;
			}
		}

		if (key < y->val)
		{
			y->l = new Node(key);
		}
		else
		{
			y->r = new Node(key);
		}
	}


	void down() {
		if (curr == NULL) throw "No elements";
		if (curr->l == NULL) throw "curr->next == NULL";
		path.push(curr);
		curr = curr->l;
	}

	void next() {
		if (curr == NULL) throw "No elements";
		if (curr->r == NULL) throw "curr->next == NULL";
		path.push(curr);
		curr = curr->r;
	}

	void top() {
		if (curr == NULL) throw "No elements";
		if (path.isEmpty()) throw "no way";
		curr = path.pop();
	}
	friend ostream& operator <<(ostream& o, Text& t) {
		printLTR(o, t.root);
		o << endl;
		return o;
	}
	void FreeTree(Node*& root)
	{
		if (root->r)  FreeTree(root->r);
		if (root->l)  FreeTree(root->l);

		delete root;
		root = nullptr;
	}

	void stack_clear()
	{
		path.Empty();
	}

	void Delete(int key)
	{
		Node* n = FindKey(root, key);
		if (n == NULL)
			throw "No found";

		if ((n->l == NULL) && (n->r == NULL))
		{
			if (path.top()->l == n)
			{
				path.top()->l = NULL;
			}
			else
			{
				path.top()->r = NULL;
			}
			delete n;
		}
		else if ((n->l != NULL) && (n->r == NULL))
		{
			if (path.top()->l == n)
			{
				path.top()->l = n->l;
			}
			else
			{
				path.top()->r = n->l;
			}
			delete n;
		}
		else if ((n->l == NULL) && (n->r != NULL))
		{
			if (path.top()->l == n)
			{
				path.top()->l = n->r;
			}
			else
			{
				path.top()->r = n->r;
			}
			delete n;
		}
		else
		{
			Node* t = n->l;
			Node* tm1 = n;
			while (t->r != NULL)
			{
				tm1 = t;
				t = t->r;
			}
			int max = t->val;
			n->val = max;
			tm1->l = t->l;
			t->l = NULL;
			delete t;
		}
	}
};
int main() {
	Text t;
	int res=0;
	int key;
	int op;
	while (true)
	{
		system("cls");
		cout << t;
		if (res!=0)
			cout << res << endl;
		cout << "0. Exit \n";
		cout << "1. Add \n";
		cout << "2. Delete \n";
		cout << "3. Find \n";
		cin >> op;
		try {
			switch (op)
			{
			case 0:
				return 0;
				break;
			case 1:
				cin >> key;
				t.add(key);
				break;
			case 2:
				cin >> key;
				t.Delete(key);
				break;
			case 3:
				cin >> key;
				res=t.FindKey(t.getroot(),key)->val;
				break;
			}
		}
		catch (const char* s)
		{
			cout << s << "\n";
			_getch();
		}
	}
	return 0;
}

