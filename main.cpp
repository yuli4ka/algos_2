#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <random>
#include <iterator> //for vector copying
#include <conio.h>
#include <fstream>
//https://neerc.ifmo.ru/wiki

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
};

long prime_num(long n){
    bool flag = true;
    while(flag){
        long sqrr = sqrt(n);
        for (long i = 2; i <= sqrr; i++)
            if (n % i == 0){
                flag = false;
                break;
            }
        n++;
        flag = !flag;
    }
    return n-1;
}

long prime = 2;

long hash_func(long a, long b, long k, long p, long m){
    return ((a * k + b) % p) % m;
}

/*long key(string data){
        long ans = 0;
        for (long i = 0; i < data.size(); i++)
            ans = (ans*10+long(data[i]-'0')) % 21474836;
        return ans;
    }*/

long key(string data, long a, long b){
        long ans = 0;
        for (long i = 0; i < data.size(); i++)
            ans = (ans*a+long(data[i]+b)) % 21474836;
        return ans;
    }

class secondary_notebook{
    vector<notebook> hashsi;
    long size_mi, a, b;

     void initiating(){
        a = rand() % (prime - 1) +1;
        b = rand() % prime;
    }
public:
    void making_notebook(vector<notebook> data_mi){
        size_mi = data_mi.size();
        if (data_mi.empty())
            return;

        long hashkey, keyy;
        bool flag = true;
        size_mi = size_mi * size_mi;
        hashsi.resize(size_mi);

        while(flag){
            initiating();
            //////
            hashsi.clear();
            hashsi.resize(size_mi);
            //////
            /*cout << data_mi.size() << "size" << endl;
            cout << a << "a" << endl;
            cout << b << "b" << endl;
            cout << size_mi << "size_mi" << endl;*/
            //system("Pause");
            for (long i = 0; i < data_mi.size(); i++){
                            //cout << "here OK" << endl;
                keyy = key(data_mi[i].date.dat,a,b);
                hashkey = hash_func(a,b,keyy,prime,size_mi);
                if (hashsi[hashkey].date.dat != " "){
                    flag = false;
                    break;
                }
                hashsi[hashkey] = data_mi[i];
            }
            flag = !flag;
        }
        //cout << "end of 2nd hash" << endl;
    }

    notebook serching_notebook(string data){
        notebook ans;
        if (size_mi == 0)
            return ans;
        long keyy = key(data,a,b);
        long hash_key = hash_func(a,b,keyy,prime,size_mi);
        if (hashsi[hash_key].date.dat == data)
            return hashsi[hash_key];
        return ans;
    }
};

class secondary_event{
    vector<event> hash_si;
    long size_mi, a, b;

    void initiating(){
        a = rand() % (prime - 1) +1;
        b = rand() % prime;
    }

public:
    secondary_event(){
        size_mi = 0;
        a = 1;
        b = 0;
    }

    void making_event(vector<event> data_mi){
        size_mi = data_mi.size();
        if (data_mi.empty())
            return;

        long hashkey, keyy;
        bool flag = true;
        size_mi = size_mi * size_mi;
        hash_si.resize(size_mi);
        while(flag){
            initiating();

            ////
           hash_si.clear();
           hash_si.resize(size_mi);
            ////



            cout << data_mi.size() << "size" << endl;
            cout << a << "a" << endl;
            cout << b << "b" << endl;
            cout << size_mi << "size_mi" << endl;
            //system("Pause");

            for (long i = 0; i < data_mi.size(); i++){
                keyy = key(data_mi[i].name,a,b);
                hashkey = hash_func(a,b,keyy,prime,size_mi);
                cout << hashkey << "hash_key" << endl;
                cout << keyy << " key " << data_mi[i].name << " name" << endl;
                cout << "here OK" << endl;
                if (hash_si[hashkey].name != " "){  ///////!!!!!
                        cout << "here OKK" << endl;
                    flag = false;
                    break;
                }
                cout << "here not OK" << endl;
                hash_si[hashkey] = data_mi[i];
            }
            system("Pause");
            flag = !flag;
        }
    }

    event searching_event(string data){
        event ans;
        if (hash_si.size() == 0){
            return ans;
        }
        long keyy = key(data,a,b);
        long hash_key = hash_func(a,b,keyy,prime,size_mi);
        if (hash_si[hash_key].name == data)
            return hash_si[hash_key];
        return ans;
    }
};

class first_notebook{
    vector<secondary_notebook> buckets;
    long ha, hb, f_size;
    void initiating(){
        ha = rand() % (prime - 1) +1;
        hb = rand() % prime;
    }

public:
    void making(vector<notebook> data){
        initiating();
        f_size = data.size();
        buckets.resize(f_size);
        vector<vector<notebook>> databuck;
        databuck.resize(f_size);
        long keyy, hash_key;
        for (long i = 0; i < f_size; i++){
            keyy = key(data[i].date.dat,ha,hb);
            hash_key = hash_func(ha,hb,keyy,prime,f_size);
            databuck[hash_key].push_back(data[i]);
        }
        for (long i = 0; i < f_size; i++)
            buckets[i].making_notebook(databuck[i]);
    }

    notebook searching(string name){
        long keyy = key(name,ha,hb);
        //cout << "ups" << endl;
        //cout << keyy << "keyy" << endl;
        //cout << ha << "ha" << endl;
        //cout << hb << "hb" << endl;
        //cout << f_size << "f_size" << endl;
        ///////////
        long hash_key = hash_func(ha,hb,keyy,prime,f_size);
        //cout << "ups" << endl; ///////////
        return buckets[hash_key].serching_notebook(name);
    }
};

class first_event{
    long ha, hb, f_size;
    vector<secondary_event> buckets;
    void initiating(){
        ha = rand() % (prime - 1) +1;
        hb = rand() % prime;
    }

public:
    void making(vector<event> data){
        initiating();
        f_size = data.size();
        buckets.resize(f_size);
        vector<vector<event>> databuck;
        databuck.resize(f_size);
        long keyy, hash_key;
        for (long i = 0; i < f_size; i++){
            keyy = key(data[i].name,ha,hb);
            hash_key = hash_func(ha,hb,keyy,prime,f_size);
            databuck[hash_key].push_back(data[i]);
        }
        for (long i = 0; i < f_size; i++){
            cout << "check one bucket" << endl;
            system("Pause");
            buckets[i].making_event(databuck[i]);
        }
    }

    event searching(string name){
        long keyy = key(name,ha,hb);
        long hash_key = hash_func(ha,hb,keyy,prime,f_size);
        event ans = buckets[hash_key].searching_event(name);
        return ans;
    }
};

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

int menu() {
        char key=0;
        int code;
        do {
                system("cls");
                key=(key+3)%3;
                if (key==0) cout<<"-> Search data."<<endl;
                        else  cout<<"   Search data."<<endl;
                if (key==1) cout<<"-> Search event."<<endl;
                        else  cout<<"   Search event."<<endl;
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

int main(){
    vector<notebook> v_notebook;
    vector<event> v_event;
    reading(v_notebook, v_event);

    prime = prime_num(max(v_notebook.size(), v_event.size()));
    //cout << prime << " prime" << endl;

    first_notebook f_notebook;
    first_event f_event;

            /*notebook note;
            note.date.dat = "12.12.2012";
            //note.evets = "event11";
            event eve;
            eve.datepoint = note.date;
            eve.name = "event11";
            eve.place = "KNU";
            note.evets.push_back(eve);
            v_notebook.push_back(note);
            v_event.push_back(eve);*/

            cout << "KKK" << endl;///////


    //for (int i = 0; i < v_event.size(); i++){
   // cout << v_notebook[i].date.dat << " i date" << endl;
    //cout << v_event[i].name << " i event name" << endl;
    //cout << v_event[i].place << " i event place" << endl;
    //}



    f_notebook.making(v_notebook);

    cout << "PP" << endl; /////////

    f_event.making(v_event);

    cout << "GG" << endl;

    system("Pause");

    /*long n_notebook = v_notebook.size();
    long n_event = v_event.size();*/

    char c=0;
    while (c!=4)
    {
        c=menu();
        system("cls");
        switch (c)
        {
            case 0: {
                string data;
                //cout << prime << "pri" << endl;
                cout << "Give me data like dd.mm.yyyy" << endl;
                cin >> data;
                notebook ans = f_notebook.searching(data);
                if (!ans.evets.size())
                    cout << "There is no event" << endl;
                else{
                    for (long i = 0; i < ans.evets.size(); i++)
                        cout << ans.evets[i].name << " in " << ans.evets[i].place << endl;
                }
                system("pause");
                break;
            }
            case 1: {
                string data;
                cout << "Give me name of event" << endl;
                cin >> data;
                //cout << "????" << data << endl;
                event ans = f_event.searching(data); //////something wrong

                if (ans.name == " ")
                    cout << "There is no event with this name" << endl;
                else{
                    //cout << "?" << endl;
                    cout << ans.datepoint.dat << " in " << ans.place << endl;
                }
                system("pause");
                break;
            }
            case 2: {
                return 0;
            }
            system("cls");
        }

    }
    return 0;
}









/*int main(){


    return 0;
}*/





    /*vector<long> array1;
    array1.resize(4,20);
    copy( array1.begin(),   // итератор начала массива
          array1.end(),     // итератор конца массива
          ostream_iterator<long>(cout," ")   //итератор потока вывода
        );
    cout <<endl;
    array1.resize(6,200);
    copy( array1.begin(),   // итератор начала массива
          array1.end(),     // итератор конца массива
          ostream_iterator<long>(cout," ")   //итератор потока вывода
        );
    cout << endl << "Hello world!" << endl;

    string data = "abcjsbfkjsdbjkbv";
    long ans = 0;
        for (long i = 0; i < data.size(); i++)
            ans += int(data[i]);
    cout << ans << endl;

    vector<event> events(5);
    for (int i = 0; i < events.size(); i++)
        cout << events[i].name << 'e';
    cout << endl;*/
