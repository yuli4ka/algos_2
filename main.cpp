#include <iostream>
#include <queue>
#include <string>
using namespace std;

class RedBlackTree
{
public:
	enum nodeColor {RED, BLACK};
	struct Node
	{
		//int data;;
		string data;
		Node *parent;
		Node *right;
		Node *left;
		nodeColor color;
		int size;
	};
	RedBlackTree()
	{
		NIL = new Node;
		NIL->right = NIL;
		NIL->left = NIL;
		NIL->color = BLACK;
		NIL->parent = NULL;
		NIL->size = 0;
		root = NIL;

	}
	void insertNode(string);
	void insertFixup(Node *);
	void deleteNode(string);
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
	RedBlackTree rbt;
	rbt.insertNode("5");
	rbt.insertNode("2");
	rbt.insertNode("3");
	rbt.insertNode("7");
	rbt.insertNode("4");
	rbt.insertNode("9");
	rbt.insertNode("0");
	rbt.insertNode("6");
	rbt.deleteNode("2");
	rbt.print();

	return 0;
}

void RedBlackTree::insertNode(string data)
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

void RedBlackTree::insertFixup(Node * node)
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

void RedBlackTree::leftRotate(Node *node)
{
	Node *rn = node->right;
	node->right = rn->left;

	if (rn->left != NIL)
	{
		rn->left->parent = node;
	}

	rn->parent = node->parent;

	if (node->parent)
	{
		if (node == node->parent->left)
		{
			node->parent->left = rn;
		}
		else
		{
			node->parent->right = rn;
		}
	}
	else
	{
		root = rn;
	}
	rn->left = node;
	node->parent = rn;

	node->size = node->left->size + node->right->size + 1;
	rn->size = rn->left->size + rn->right->size + 1;
}

void RedBlackTree::rightRotate(Node *node)
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


void RedBlackTree::deleteTransplant(Node *u, Node *v)
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

void RedBlackTree::deleteNode(string data)
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

void RedBlackTree::deleteFixup(Node *node)
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

void RedBlackTree::print()
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

		cout << "Data: " << curr->data << ". Color: ";
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

RedBlackTree::Node *RedBlackTree::select(Node *node, int selec)
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
