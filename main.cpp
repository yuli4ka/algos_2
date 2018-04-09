#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Red_Black_Tree.h"
using namespace std;

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
        name = "";
        place = "";
        datepoint.dat = "";
    }
};

struct notebook{
    date date;
    vector<event> evets;
    notebook(){
        date.dat = "";
    }
};

bool operator > (notebook a, notebook b){
    if (a.date.dat > b.date.dat)
        return true;
    else
        return false;
}

bool operator < (notebook a, notebook b){
    if (a.date.dat < b.date.dat)
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

bool operator == (notebook a, notebook b){
    if (a.date.dat == b.date.dat)
        return true;
    else
        return false;
}

int main()
{
	spaceRed_Black_Tree::Red_Black_Tree<notebook> tree;
	notebook data1;
	notebook data2;
	notebook data3;
	notebook data4;

	tree.Insert(data1);
	tree.Insert(data2);
	tree.Insert(data3);
	tree.Insert(data4);
	/*tree.Insert(2);
	tree.Insert(3);
	tree.Insert(4);
	tree.Insert(5);
	tree.Insert(6);
	tree.Insert(7);

	tree.Delete(4);

	for (size_t i = 1; i < 8; i++)
	{
		cout << tree.GetRank(i) << endl;
	}
*/
	system("pause");
	return 0;
}
