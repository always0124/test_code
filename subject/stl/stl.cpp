#include <iostream>
#include <atomic>
#include <map>
using namespace std;

class Empty
{
public:
    Empty() {cout << "empty默认构造函数"<<endl;}
    Empty(const Empty&) {cout << "empty默认拷贝构造函数"<<endl;}
    ~ Empty() {cout << "empty默认析构函数"<<endl;}
    atomic_int aint;
};


struct empty{
    atomic_int aint;
    empty() {cout << "empty默认构造函数"<<endl;}
    ~ empty() {cout << "empty默认析构函数"<<endl;}
    empty(const empty&) {cout << "empty默认拷贝构造函数"<<endl;}
};

int main()
{
    empty e;
    map<string, empty> m;
    //m["cui"];
    m.insert(std::make_pair("", e));
    return 0;
}
