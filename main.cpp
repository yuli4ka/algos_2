#include <iostream>
#include <stdlib.h>
#include <vector>
#include <conio.h>
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

ostream& operator<<(ostream& os, const notebook& dt)
{
    os << dt.date.dat;
    return os;
}

ostream& operator<<(ostream& os, const event& dt)
{
    os << dt.name << " in " << dt.place << ", " << dt.datepoint.dat;
    return os;
}

istream& operator>>(istream& is, notebook& dt)
{
    getline(is,dt.date.dat);
    string temp;
    getline(is,temp);
    while (temp != "//"){
        event new_event;
        new_event.name = temp;
        getline(is,temp);
        new_event.place = temp;
        dt.evets.push_back(new_event);
        new_event.datepoint = dt.date;
        getline(is,temp);
    }
    return is;
}

//
int menu() {
        char key=0;
        int code;
        do {
                system("cls");
                key=(key+9)%9;
                if (key==0) cout<<"-> Insert date."<<endl;
                        else  cout<<"   Insert date."<<endl;
                if (key==1) cout<<"-> Insert event."<<endl;
                        else  cout<<"   Insert event."<<endl;
                if (key==2) cout<<"-> Delete date."<<endl;
                        else  cout<<"   Delete date."<<endl;
                if (key==3) cout<<"-> Delete event."<<endl;
                        else  cout<<"   Delete event."<<endl;
                if (key==4) cout<<"-> Get Rank date."<<endl;
                        else  cout<<"   Get Rank date."<<endl;
                if (key==5) cout<<"-> Get Rank event."<<endl;
                        else  cout<<"   Get Rank event."<<endl;
                if (key==6) cout<<"-> Print tree date."<<endl;
                        else  cout<<"   Print tree date."<<endl;
                if (key==7) cout<<"-> Print tree event."<<endl;
                        else  cout<<"   Print tree event."<<endl;
                if (key==8) cout<<"-> Exit."<<endl;
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
//
int main()
{
    char c=0;
    while (c!=9)
    {
        c=menu();
        system("cls");
        switch (c)
        {
            case 0: {
                notebook data;
                cout << "Give me date and events (1st word == event, 2nd word == place of event, '//' == end" << endl;
                cin >> data;

                cout << data << endl;
                if (data.evets.empty())
                    cout << "There is not event" << endl;
                else
                    cout << data.evets[0] << endl;

                system("pause");
                break;
            }
            case 1: {
                //rbt.print(rbt.root,0);
            }
            case 8: {
                return 0;
            }
            system("cls");
        }

    }
	spaceRed_Black_Tree::Red_Black_Tree<notebook> tree;
	notebook data1;
	data1.date.dat = "sfd";
	cout << data1 << endl;
	notebook data2;
	notebook data3;
	notebook data4;

	event dat1;
	dat1.name = "zz";
	dat1.place = "cc";
	dat1.datepoint = data1.date;
	cout << dat1 << endl;

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
