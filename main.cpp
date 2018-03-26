#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <random>
#include <iterator> //for vector copying
//https://neerc.ifmo.ru/wiki

using namespace std;
//hh:mm dd.mm.yyyy
struct date{
    string dat;
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

long prime;

long hash_func(long a, long b, long k, long p, long m){
    return ((a * k + b) % p) % m;
}

long key(string data){
        long ans = 0;
        for (long i = 0; i < data.size(); i++)
            ans += long(data[i]);
        return ans;
    }

class secondary_notebook{
    vector<notebook> hashsi;
    long size_mi, a, b;

public:
    void initiating(){
        a = rand() % (prime - 1) +1;
        b = rand() % prime;
    }

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
            for (long i = 0; i < data_mi.size(); i++){
                keyy = key(data_mi[i].date.dat);
                hashkey = hash_func(a,b,keyy,prime,size_mi);
                if (hashsi[hashkey].date.dat != " "){
                    flag = false;
                    break;
                }
                hashsi[hashkey] = data_mi[i];
            }
            flag = !flag;
        }
    }

    notebook serching_notebook(string data){
        notebook ans;
        if (size_mi == 0)
            return ans;
        long keyy = key(data);
        long hash_key = hash_func(a,b,keyy,prime,size_mi);
        if (hashsi[hash_key].date.dat == data)
            return hashsi[hash_key];
        return ans;
    }
};

class secondary_event{
    vector<event> hash_si;
    long size_mi, a, b;

public:
    void initiating(){
        a = rand() % (prime - 1) +1;
        b = rand() % prime;
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
            for (long i = 0; i < data_mi.size(); i++){
                keyy = key(data_mi[i].name);
                hashkey = hash_func(a,b,keyy,prime,size_mi);
                if (hash_si[hashkey].name != " "){
                    flag = false;
                    break;
                }
                hash_si[hashkey] = data_mi[i];
            }
            flag = !flag;
        }
    }

    event searching_event(string data){
        event ans;
        if (size_mi == 0)
            return ans;
        long keyy = key(data);
        long hash_key = hash_func(a,b,keyy,prime,size_mi);
        if (hash_si[hash_key].name == data)
            return hash_si[hash_key];
        return ans;
    }
};

class first_notebook{
    long ha, hb, f_size;
    vector<secondary_notebook> buckets;

public:
    void initiating(){
        ha = rand() % (prime - 1) +1;
        hb = rand() % prime;
    }

    void making(vector<notebook> data){
        f_size = data.size();
        buckets.resize(f_size);
        vector<vector<notebook>> databuck;
        databuck.resize(f_size);
        long keyy, hash_key;
        for (long i = 0; i < f_size; i++){
            keyy = key(data[i].date.dat);
            hash_key = hash_func(ha,hb,keyy,prime,f_size);
            databuck[hash_key].push_back(data[i]);
        }
        for (long i = 0; i < f_size; i++)
            buckets[i].making_notebook(databuck[i]);
    }

    notebook searching(string name){
        long keyy = key(name);
        long hash_key = hash_func(ha,hb,keyy,prime,f_size);
        return buckets[hash_key].serching_notebook(name);
    }
};

class first_event{
    long ha, hb, f_size;
    vector<secondary_event> buckets;

public:
    void initiating(){
        ha = rand() % (prime - 1) +1;
        hb = rand() % prime;
    }

    void making(vector<event> data){
        f_size = data.size();
        buckets.resize(f_size);
        vector<vector<event>> databuck;
        databuck.resize(f_size);
        long keyy, hash_key;
        for (long i = 0; i < f_size; i++){
            keyy = key(data[i].name);
            hash_key = hash_func(ha,hb,keyy,prime,f_size);
            databuck[hash_key].push_back(data[i]);
        }
        for (long i = 0; i < f_size; i++)
            buckets[i].making_event(databuck[i]);
    }

    event searching(string name){
        long keyy = key(name);
        long hash_key = hash_func(ha,hb,keyy,prime,f_size);
        return buckets[hash_key].searching_event(name);
    }
};

int main()
{
    vector<long> array1;
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
    cout << endl;

    return 0;
}
