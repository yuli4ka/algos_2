#include <iostream>
#include <stdlib.h>
#include <vector>
#include <conio.h>
#include <string>
#include <fstream>
#include "binary_tree.h"

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

bool operator >= (notebook a, notebook b){
    if (a.date.dat >= b.date.dat)
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

//
bool operator > (event a, event b){
    if (a.name > b.name)
        return true;
    else
        return false;
}

bool operator >= (event a, event b){
    if (a.name >= b.name)
        return true;
    else
        return false;
}

bool operator < (event a, event b){
    if (a.name < b.name)
        return true;
    else
        return false;
}

bool operator != (event a, event b){
    if (a.name != b.name)
        return true;
    else
        return false;
}

bool operator == (event a, event b){
    if (a.name == b.name)
        return true;
    else
        return false;
}
//

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
    cin.clear();
    getline(is,dt.date.dat);
    string temp;
    cin.clear();
    getline(is,temp);
    while (temp != "//"){
        event new_event;
        new_event.name = temp;
        cin.clear();
        getline(is,temp);
        new_event.place = temp;
        dt.evets.push_back(new_event);
        new_event.datepoint = dt.date;
        cin.clear();
        getline(is,temp);
    }
    return is;
}

istream& operator>>(istream& is, event& dt)
{
    cin.clear();
    getline(is,dt.name);
    cin.clear();
    getline(is,dt.place);
    return is;
}

//
int menu1() {
        char key=0;
        int code;
        do {
                system("cls");
                key=(key+4)%4;
                if (key==0) cout<<"-> Insert date."<<endl;
                        else  cout<<"   Insert date."<<endl;
                if (key==1) cout<<"-> Go."<<endl;
                        else  cout<<"   Go."<<endl;
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

int menu2() {
        char key=0;
        int code;
        do {
                system("cls");
                key=(key+5)%5;
                if (key==0) cout<<"-> Search date."<<endl;
                        else  cout<<"   Search date."<<endl;
                if (key==1) cout<<"-> Search event."<<endl;
                        else  cout<<"   Search event."<<endl;
                if (key==2) cout<<"-> Build date."<<endl;
                        else  cout<<"   Build date."<<endl;
                if (key==3) cout<<"-> Build event."<<endl;
                        else  cout<<"   Build event."<<endl;
                if (key==4) cout<<"-> Exit."<<endl;
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
    /*
    spacebinary_tree::btree<int> n_tree;
    n_tree.insert(2);
    n_tree.insert(4);
    n_tree.insert(1);
    n_tree.insert(10);
    n_tree.insert(15);
    n_tree.insert(25);
    n_tree.make_gv("D:\\GViz\\1.gv");
    */
    spacebinary_tree::btree<notebook> n_tree;
    spacebinary_tree::btree<event> e_tree;
    char c=0;
    while (c!=2)
    {
        c=menu1();
        system("cls");
        switch (c)
        {
            case 0: {
                notebook data;
                cout << "Give me date and events (1st word == event, 2nd word == place of event, '//' == end" << endl;
                cin >> data;
                for (int i = 0; i < data.evets.size(); i++)
                    e_tree.Insert(data.evets[i]);
                n_tree.Insert(data);
                system("pause");
                break;
            }
            case 1: {
                system("Pause");
                break;
            }
            /*case 8: {
                return 0;
            }*/
            system("cls");
        }
    }
    e_tree.print();
    cout << endl << endl << endl;
    n_tree.print();
    system("Pause");
	return 0;
}

