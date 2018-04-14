#include <iostream>
#include <stdlib.h>
#include <vector>
#include <conio.h>
#include "Splay_tree.h"

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

//
bool operator > (event a, event b){
    if (a.name > b.name)
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

istream& operator>>(istream& is, event& dt)
{
    cin.clear();
    getline(is,dt.name);
    getline(is,dt.place);
    return is;
}

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
                if (key==4) cout<<"-> Find date."<<endl;
                        else  cout<<"   Find date."<<endl;
                if (key==5) cout<<"-> Find event."<<endl;
                        else  cout<<"   Find event."<<endl;
                if (key==6) cout<<"-> Find date."<<endl;
                        else  cout<<"   Find date."<<endl;
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

int main()
{
    splay_tree<notebook> n_tree;
    splay_tree<event> e_tree;
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
                n_tree.inserting(n_tree.main_root,data);
                for (int i = 0; i < data.evets.size(); i++)
                    e_tree.inserting(e_tree.main_root,data.evets[i]);
                system("pause");
                break;
            }
            case 1: {
                event data;
                cout << "Give me event and date for this event" << endl;
                //cin >> data;
                cin.clear();
                getline(cin,data.name,'\n');
                getline(cin,data.place,'\n');
                //don`t wanna read name on second time
                notebook note;
                getline(cin, note.date.dat,'\n');
                e_tree.inserting(e_tree.main_root,data);
                //should I print "if-else?"
                if(n_tree.finding(n_tree.main_root,note) == NULL){
                    note.evets.push_back(data);
                    n_tree.inserting(n_tree.main_root,note);
                }
                else{
                    /*n_tree.removing(n_tree.main_root,note);
                    note.evets.push_back(data);
                    n_tree.inserting(n_tree.main_root,note);*/
                    n_tree.main_root->key.evets.push_back(data);
                }
                //
                break;
            }
            case 2: {
                cout << "Give me date for deleting" << endl;
                notebook note;
                cin >> note.date.dat;
                if (n_tree.finding(n_tree.main_root,note) == NULL){
                    cout << "We don't have this date in database";
                    system("pause");
                }
                else{
                    for (int i = 0; i < n_tree.main_root->key.evets.size(); i++)
                        e_tree.removing(e_tree.main_root,note.evets[i]);
                    n_tree.removing(n_tree.main_root,note);
                }
                break;
            }
            case 3: {
                cout << "Give me name of event for deleting" << endl;
                event data;
                cin >> data.name;
                if (e_tree.finding(e_tree.main_root,data) != NULL){
                    notebook note;
                    note.date.dat = data.datepoint.dat;
                    if (n_tree.finding(n_tree.main_root,note) != NULL){
                        /*n_tree.removing(n_tree.main_root,note);
                        for (int i = 0; i < note.evets.size(); i++)
                            if (note.evets[i] == data)
                                note.evets.erase(note.evets.begin()+i);
                        n_tree.Insert(note);*/
                        for (int i = 0; i < n_tree.main_root->key.evets.size(); i++)
                            if (n_tree.main_root->key.evets[i] == data)
                                n_tree.main_root->key.evets.erase(n_tree.main_root->key.evets.begin()+i);
                    }
                    e_tree.removing(e_tree.main_root,data);
                }
                else {
                    cout << "We don't have this event in database";
                    system("pause");
                }
                break;
            }
            case 4: {
                cout << "Give me date for finding" << endl;
                notebook note;
                cin >> note.date.dat;
                if (n_tree.finding(n_tree.main_root,note) == NULL)
                    cout << "We don't have this date in database";
                else{
                    cout << n_tree.main_root->key << endl;
                    for (int i = 0; i < n_tree.main_root->key.evets.size(); i++)
                        cout << n_tree.main_root->key.evets[i] << endl;
                }
                system("Pause");
                break;
            }
            case 5: {
                cout << "Give me name of event for finding" << endl;
                event data;
                cin >> data.name;
                if (e_tree.finding(e_tree.main_root,data) == NULL)
                    cout << "We don't have this event in database";
                else{
                    cout << e_tree.main_root->key << endl;
                    cout << e_tree.main_root->key.datepoint.dat << endl;
                }
                system("Pause");
                break;
            }
            case 6: {
                n_tree.print(n_tree.main_root,0);
                system("Pause");
                break;
            }
            case 7: {
                e_tree.print(e_tree.main_root,0);
                system("Pause");
                break;
            }
            case 8: {
                return 0;
            }
            system("cls");
        }

    }
	system("pause");
	return 0;
}
