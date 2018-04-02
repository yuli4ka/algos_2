#include <iostream>
#include <queue>
#include <string>
using namespace std;

//hh:mm dd.mm.yyyy
struct date{
    string dat;
    date(){
        dat = " ";
    }
};

struct event{
    string name;
    string place;
    date datepoint;
    event(){
        name = " ";
        place = " ";
        datepoint.dat = " ";
    }
};

struct notebook{
    date date;
    vector<event> evets;
    notebook(){
        date.dat = " ";
    }
public:
    void n_new(string d_new){
        date.dat = d_new;
    }
};

bool operator > (notebook a, notebook b){
    if (a.date.dat > b.date.dat)
        return true;
    else
        return false;
}

bool operator != (notebook a, notebook b){
    if (a.date.dat != b.date.dat)
        return true;
    else
        return false;
}

class SizeRedBlackTree
{
public:
	enum nodeColor {RED, BLACK};
	struct Node
	{
		//int data;;
		notebook data;
		Node *parent;
		Node *right;
		Node *left;
		nodeColor color;
		int size;
	};
	SizeRedBlackTree()
	{
		NIL = new Node;
		NIL->right = NIL;
		NIL->left = NIL;
		NIL->color = BLACK;
		NIL->parent = NULL;
		NIL->size = 0;
		root = NIL;

	}
	void insertNode(notebook);
	void insertFixup(Node *);
	void deleteNode(notebook);
	void deleteTransplant(Node *, Node *);
	void deleteFixup(Node *);
	void leftRotate(Node *);
	void rightRotate(Node *);
	Node *select(Node *, int);
	void print();
private:
	Node *root;
	Node *NIL;
};

int main()
{
	SizeRedBlackTree rbt;
	notebook note;
	note.n_new("5");
	rbt.insertNode(note);
	note.n_new("2");
	rbt.insertNode(note);
	note.n_new("3");
	rbt.insertNode(note);
	note.n_new("7");
	rbt.insertNode(note);
	note.n_new("4");
	rbt.insertNode(note);
	note.n_new("9");
	rbt.insertNode(note);
	note.n_new("0");
	rbt.insertNode(note);
	note.n_new("6");
	rbt.insertNode(note);
	note.n_new("2");
	rbt.deleteNode(note);
	rbt.print();

	return 0;
}

void SizeRedBlackTree::insertNode(notebook data)
{
	Node *curr = root;
	Node *parent = NULL;
	while (curr != NIL)
	{
		curr->size++;
		parent = curr;
		if (data > curr->data)
		{
			curr = curr->right;
		}
		else
		{
			curr = curr->left;
		}
	}

	Node *node = new Node;
	node->data = data;
	node->left = NIL;
	node->right = NIL;
	node->color = RED;
	node->size = 1;
	node->parent = parent;


	if (parent)
	{
		if (data > parent->data)
		{
			parent->right = node;
		}
		else
		{
			parent->left = node;
		}
	}
	else
	{
		root = node;
	}

		insertFixup(node);

}

void SizeRedBlackTree::insertFixup(Node * node)
{
	while (node != root && node->parent->color == RED)
	{
		if (node->parent == node->parent->parent->left)
		{
			Node *uncle = node->parent->parent->right;
			if (uncle->color == RED)
			{
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else
			{
				if (node = node->parent->right)
				{
					node = node->parent;
					leftRotate(node);
				}

				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				rightRotate(node->parent->parent);

			}
		}
		else
		{
			Node *uncle = node->parent->parent->left;
			if (uncle->color == RED)
			{
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else
			{
				if (node = node->parent->right)
				{
					node = node->parent;
					rightRotate(node);
				}

				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				leftRotate(node->parent->parent);

			}
		}
	}
	root->color = BLACK;
}

void SizeRedBlackTree::leftRotate(Node *node)
{
	Node *pilot = node->right;
	node->right = pilot->left;
	if (pilot->left != NIL)
		pilot->left->parent = node;
	pilot->parent = node->parent;
	if (node->parent)
	{
		if (node == node->parent->left)
			node->parent->left = pilot;
		else
			node->parent->right = pilot;
	}
	else
		root = pilot;
	pilot->left = node;
	node->parent = pilot;
	node->size = node->left->size + node->right->size + 1;
	pilot->size = pilot->left->size + pilot->right->size + 1;
}

void SizeRedBlackTree::rightRotate(Node *node)
{
	Node *ln = node->left;

	node->left = ln->right;

	if (ln->right != NIL)
	{
		ln->right->parent = node;
	}

	ln->parent = node->parent;

	if (node->parent)
	{
		if (node == node->parent->right)
		{
			node->parent->right = ln;
		}
		else
		{
			node->parent->left = node;
		}
	}
	else
	{
		root = ln;
	}

	node->right = node;
	node->parent = ln;

	node->size = node->left->size + node->right->size + 1;
	ln->size = ln->left->size + ln->right->size + 1;
}


void SizeRedBlackTree::deleteTransplant(Node *u, Node *v)
{
	if (!u->parent)
	{
		root = v;
	}
	else if (u == u->parent->left)
	{
		u->parent->left = v;
	}
	else
	{
		u->parent->right = v;
	}
	u->parent = v->parent;
}

void SizeRedBlackTree::deleteNode(notebook data)
{
	Node *curr = root;
	Node *parent = NULL;
	while (curr->data != data)
	{
		curr->size--;
		if (data > curr->data)
		{
			curr = curr->right;
		}
		else
		{
			curr = curr->left;
		}
	}
	Node *fix;

	nodeColor color = curr->color;


	if (curr->left == NIL && curr->right == NIL)
	{
		if (curr->parent)
		{
			fix = curr->parent;
		}
		else
		{
			root = NIL;
			delete curr;
			return;
		}

		if (curr == curr->parent->left)
		{
			curr->parent->left = NIL;
		}
		else
		{
			curr->parent->right = NIL;
		}
	}
	else if (curr->left != NIL && curr->right != NIL)
	{
		Node *toDel = curr->right;
		while (toDel->left != NIL)
		{
			toDel->size--;
			toDel = toDel->left;
		}
		color = toDel->color;
		fix = toDel->right;
		/////
		if (toDel->parent != curr)
		{
			deleteTransplant(toDel, toDel->right);
			toDel->right = curr->right;
			toDel->right->parent = toDel;
		}
		deleteTransplant(curr, toDel);
		toDel->left = curr->left;
		toDel->left->parent = toDel;
		toDel->color = curr->color;
	}
	else if(curr->left == NIL)
	{
		fix = curr->right;
		deleteTransplant(curr, curr->right);
	}
	else
	{
		fix = curr->left;
		deleteTransplant(curr, curr->left);
	}
	if (color == BLACK)
	{
		deleteFixup(fix);
	}
	delete curr;
}

void SizeRedBlackTree::deleteFixup(Node *node)
{
	Node *uncle;
	while (node != root && node->color == BLACK)
	{
		if (node = node->parent->left)
		{
			uncle = node->parent->right;
			if (uncle->color == RED)
			{
				uncle->color = BLACK;
				node->parent->color = RED;
				leftRotate(node->parent);
				uncle = node->parent->right;
			}

			if (uncle->left->color == BLACK && uncle->right->color == BLACK)
			{
				uncle->color = RED;
				node = node->parent;
			}
			else if (uncle->right->color == BLACK)
			{
				uncle->left->color = BLACK;
				uncle->color = RED;
				rightRotate(uncle);
				uncle = node->parent->right;
			}

			uncle->color = node->parent->color;
			node->parent->color = BLACK;
			uncle->right->color = BLACK;
			leftRotate(node->parent);
			node = root;
		}
		else
		{
			uncle = node->parent->left;
			if (uncle->color == RED)
			{
				uncle->color = BLACK;
				node->parent->color = RED;
				rightRotate(node->parent);
				uncle = node->parent->left;
			}

			if (uncle->left->color == BLACK && uncle->right->color == BLACK)
			{
				uncle->color = RED;
				node = node->parent;
			}
			else if (uncle->left->color == BLACK)
			{
				uncle->left->color = BLACK;
				uncle->color = RED;
				leftRotate(uncle);
				uncle = node->parent->left;
			}

			uncle->color = node->parent->color;
			node->parent->color = BLACK;
			uncle->left->color = BLACK;
			rightRotate(node->parent);
			node = root;
		}
	}

}

void SizeRedBlackTree::print()
{
	Node *curr;
	queue<Node*> tree;

	tree.push(root);

	Node *split = NULL;
	tree.push(split);

	while (true)
	{
		curr = tree.front();
		tree.pop();

		if (!curr)
		{
			cout << endl;
			if (tree.empty())
			{
				break;
			}
			tree.push(split);
			continue;
		}
		else if (curr == NIL)
		{
			cout << "NIL\t\t";
			continue;
		}

		cout << "Data: " << curr->data.date.dat << ". Color: ";
		if (curr->color == RED)
		{
			cout << "RED.";
		}
		else
		{
			cout << "BLACK.";
		}
		cout << "Size: " << curr->size << ".\t\t";

		tree.push(curr->left);
		tree.push(curr->right);
	}


}

SizeRedBlackTree::Node *SizeRedBlackTree::select(Node *node, int selec)
{
	int rank = node->left->size + 1;
	if (selec == rank)
	{
		return node;
	}
	if (selec < rank)
	{
		select(node->left, selec);
	}
	else
	{
		select(node->right, selec - rank);
	}
}
