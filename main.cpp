#include <iostream>
#include <queue>
#include <string>
#include <conio.h>
#include <fstream>
#include <stdlib.h>
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
	void print(Node *, int);
	//void reading();
	Node *root;
	Node *NIL;
	Node *Nod = NIL;
private:


};

void SizeRedBlackTree::insertNode(notebook data){
	Node *curr = root;
	Node *parent = NULL;
	while (curr != NIL){
		curr->size++;
		parent = curr;
		if (data > curr->data)
			curr = curr->right;
		else
			curr = curr->left;
	}
	Node *node = new Node;
	node->data = data;
	node->left = NIL;
	node->right = NIL;
	node->color = RED;
	node->size = 1;
	node->parent = parent;
	if (parent){
		if (data > parent->data)
			parent->right = node;
		else
			parent->left = node;
	}
	else
		root = node;
		insertFixup(node);
}

void SizeRedBlackTree::insertFixup(Node *node){
	while (node != root && node->parent->color == RED){
		if (node->parent == node->parent->parent->left){
			Node *uncle = node->parent->parent->right;
			if (uncle->color == RED){
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else{
				if (node = node->parent->right){
					node = node->parent;
					leftRotate(node);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				rightRotate(node->parent->parent);
			}
		}
		else{
			Node *uncle = node->parent->parent->left;
			if (uncle->color == RED){
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else{
				if (node = node->parent->right){
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

void SizeRedBlackTree::leftRotate(Node *node){
	Node *pilot = node->right;
	node->right = pilot->left;
	if (pilot->left != NIL)
		pilot->left->parent = node;
	pilot->parent = node->parent;
	if (node->parent){
		if (node == node->parent->left)
			node->parent->left = pilot;
		else
			node->parent->right = pilot;
	}
	else
		root = pilot;
	pilot->left = node;
	node->parent = pilot;
	pilot->size = node->size;
	node->size = node->left->size + node->right->size + 1;
}

void SizeRedBlackTree::rightRotate(Node *node){
	Node *pilot = node->left;
	node->left = pilot->right;
	if (pilot->right != NIL)
		pilot->right->parent = node;
	pilot->parent = node->parent;
	if (node->parent){
		if (node == node->parent->right)
			node->parent->right = pilot;
		else
			node->parent->left = pilot;
	}
	else
		root = pilot;
	pilot->right = node;
	node->parent = pilot;
	pilot->size = node->size;
	node->size = node->left->size + node->right->size + 1;
}


void SizeRedBlackTree::deleteTransplant(Node *u, Node *v){
	if (!u->parent)
		root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	u->parent = v->parent;
}

void SizeRedBlackTree::deleteNode(notebook data){
	Node *curr = root;
	Node *parent = NULL;
	while (curr->data != data){
		curr->size--;
		if (data > curr->data)
			curr = curr->right;
		else
			curr = curr->left;
	}
	Node *fix;
	nodeColor color = curr->color;
	if (curr->left == NIL && curr->right == NIL){
		if (curr->parent)
			fix = curr->parent;
		else{
			root = NIL;
			delete curr;
			return;
		}
		if (curr == curr->parent->left)
			curr->parent->left = NIL;
		else
			curr->parent->right = NIL;
	}
	else if (curr->left != NIL && curr->right != NIL){
		Node *toDel = curr->right;
		while (toDel->left != NIL){
			toDel->size--;
			toDel = toDel->left;
		}
		color = toDel->color;
		fix = toDel->right;
		/////
		if (toDel->parent != curr){
			deleteTransplant(toDel, toDel->right);
			toDel->right = curr->right;
			toDel->right->parent = toDel;
		}
		deleteTransplant(curr, toDel);
		toDel->left = curr->left;
		toDel->left->parent = toDel;
		toDel->color = curr->color;
	}
	else if(curr->left == NIL){
		fix = curr->right;
		deleteTransplant(curr, curr->right);
	}
	else{
		fix = curr->left;
		deleteTransplant(curr, curr->left);
	}
	if (color == BLACK)
		deleteFixup(fix);
	delete curr;
}

void SizeRedBlackTree::deleteFixup(Node *node){
	Node *uncle;
	while (node != root && node->color == BLACK){
		if (node = node->parent->left){
			uncle = node->parent->right;
			if (uncle->color == RED){
				uncle->color = BLACK;
				node->parent->color = RED;
				leftRotate(node->parent);
				uncle = node->parent->right;
			}
			if (uncle->left->color == BLACK && uncle->right->color == BLACK){
				uncle->color = RED;
				node = node->parent;
			}
			else if (uncle->right->color == BLACK){
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
		else{
			uncle = node->parent->left;
			if (uncle->color == RED){
				uncle->color = BLACK;
				node->parent->color = RED;
				rightRotate(node->parent);
				uncle = node->parent->left;
			}
			if (uncle->left->color == BLACK && uncle->right->color == BLACK){
				uncle->color = RED;
				node = node->parent;
			}
			else if (uncle->left->color == BLACK){
				uncle->right->color = BLACK;//left?
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
	node->color = BLACK;
}

/*void SizeRedBlackTree::print(Node *curr){
    if (curr == NIL){
        cout << "NIL\t";
        return;
    }
    cout <<curr->data.date.dat << "(";
    if (curr->color == RED)
        cout << "RED,";
    else
        cout << "BLACK,";
    cout << curr->size << ")\t";
    cout << endl;
    print(curr->left);
    print(curr->right);
    ///
}*/

SizeRedBlackTree::Node *SizeRedBlackTree::select(Node *node, int dat){
	int t_size = node->left->size + 1;
	if (node == NIL)
        return NIL;
	if (dat == t_size)
		return node;
	else if (dat < t_size)
		return select(node->left, dat);
	else
		return select(node->right, dat - t_size);
}

/*void SizeRedBlackTree::reading(){ //problems
    ifstream input("database.txt");
    if (!input.is_open()){
        cout << "Oooops. Batabase is clear(cannot find file)" << endl;
        system("Pause");
        return;
    }
    string data = "";
    while ((!input.eof()) && getline(input,data)){
        notebook new_notebook;
        new_notebook.date.dat = data;
        cout << data << endl;
        while ((!input.eof()) && getline(input,data)){
            if (data == "//")
                break;
            event new_event;
            new_event.name = data;
            getline(input,data);
            new_event.place = data;
            new_event.datepoint.dat = new_notebook.date.dat;
            new_notebook.evets.push_back(new_event);
        }
        insertNode(new_notebook);
    }
    input.close();
}*/

void reading(vector<notebook> &v_notebook, vector<event> &v_event){
    ifstream input("database.txt");
    if (!input.is_open()){
        cout << "Oooops. Batabase is clear(cannot find file)" << endl;
        system("Pause");
        return;
    }
    string data = "";
    while ((!input.eof()) && getline(input,data)){
        notebook new_notebook;
        new_notebook.date.dat = data;

        while ((!input.eof()) && getline(input,data)){
            if (data == "//")
                break;
            event new_event;
            new_event.name = data;
            getline(input,data);
            new_event.place = data;
            new_event.datepoint.dat = new_notebook.date.dat;
            new_notebook.evets.push_back(new_event);
            v_event.push_back(new_event);
        }
        v_notebook.push_back(new_notebook);
    }
    input.close();
}

void SizeRedBlackTree::print(Node *p, int level){
    if(p != NULL){
        if (p->right != NULL && p->right != NIL)
            print(p->right, level+1);
        for(int i = 0; i < level; i++) cout<<"\t";
        if (p != NULL && p!= NIL)
            cout<< p->data.date.dat <<endl;
        else
            cout<<"NIL"<<endl;
        if (p->left != NULL && p->left != NIL)
            print(p->left, level+1);
    }
    //if (p == NIL)
      //  cout <<"NIL"<<endl;
}

int menu() {
        char key=0;
        int code;
        do {
                system("cls");
                key=(key+3)%3;
                if (key==0) cout<<"-> Search data."<<endl;
                        else  cout<<"   Search data."<<endl;
                if (key==1) cout<<"-> Print tree."<<endl;
                        else  cout<<"   Print tree."<<endl;
                if (key==2) cout<<"-> Exit."<<endl;
                        else  cout<<"   Exit."<<endl;
                code=_getch();
                if (code==224)
                {
                    code=_getch();
                    if (code==80) key++;
                    if (code==72) key--;
                        }
           }while(code!=13);
        system("cls");
        return key;
}

int main()
{
	SizeRedBlackTree rbt;
	vector<notebook> v_notebook;
    vector<event> v_event;
    reading(v_notebook, v_event);
    for (int i = 0; i < v_notebook.size(); i++){
        cout << v_notebook[i].date.dat << endl;
        rbt.insertNode(v_notebook[i]);
    }
    system("Pause");
    //rbt.reading();
    cout << 'x';
    rbt.print(rbt.root,0);
    cout << 'x';
    char c=0;
    while (c!=4)
    {
        c=menu();
        system("cls");
        switch (c)
        {
            case 0: {
                int data;
                cout << "Give me key" << endl;
                cin >> data;
                rbt.Nod= rbt.select(rbt.root,data);
                if (rbt.Nod == rbt.NIL)
                    cout << "You lose" << endl;
                else{
                cout << rbt.Nod->data.date.dat << endl;
                if (!rbt.Nod->data.evets.size())
                    cout << "There is no event" << endl;
                else{
                    for (long i = 0; i < rbt.Nod->data.evets.size(); i++)
                        cout << rbt.Nod->data.evets[i].name << " in " << rbt.Nod->data.evets[i].place << endl;
                }
                }
                system("pause");
                break;
            }
            case 1: {
                rbt.print(rbt.root,0);
            }
            case 2: {
                return 0;
            }
            system("cls");
        }

    }
	/*notebook note;
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
	rbt.print();*/

	return 0;
}
