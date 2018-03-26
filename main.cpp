#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <list>
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
};

struct notebook{
    date date;
    list<event> evets;
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

long prime, numb = 0;

long hash_func(long a, long b, long k, long p, long m){
    return ((a * k + b) % p) % m;
}

class secondary_hash{
    vector<string> hash_si;
    long size_mi, a, b;

public:
    void initiating(){
        a = rand() % (prime - 1) +1;
        b = rand() % prime;
    }
    ///////
    long key(string data){
        long ans = 0;
        for (long i = 0; i < data.size(); i++)
            ans += long(data[i]);
        return ans;
    }

    void making_notebook(vector<string> data_mi){
        size_mi = data_mi.size();
        if (data_mi.empty())
            return;

        long hashkey, keyy;
        bool flag = true;
        size_mi = size_mi * size_mi;
        hash_si.resize(size_mi," ");

        while(flag){
            initiating();
            for (long i = 0; i < data_mi.size(); i++){
                keyy = key(data_mi[i]);
                hashkey = hash_func(a,b,keyy,prime,size_mi);
                if (hash_si[hashkey] != " "){
                    flag = false;
                    break;
                }
                hash_si[hashkey] = data_mi[i];
            }
            flag = !flag;
        }
    }

    ///////
};

int main()
{
    vector<long> array1;
    array1.resize(4,20);
    copy( array1.begin(),   // �������� ������ �������
          array1.end(),     // �������� ����� �������
          ostream_iterator<long>(cout," ")   //�������� ������ ������
        );
    cout <<endl;
    array1.resize(6,200);
    copy( array1.begin(),   // �������� ������ �������
          array1.end(),     // �������� ����� �������
          ostream_iterator<long>(cout," ")   //�������� ������ ������
        );
    cout << endl << "Hello world!" << endl;

    string data = "abcjsbfkjsdbjkbv";
    long ans = 0;
        for (long i = 0; i < data.size(); i++)
            ans += int(data[i]);
    cout << ans << endl;

    return 0;
}
